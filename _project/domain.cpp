/*
* Copyright 2021 Lars Pastewka
*
* ### MIT license
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#include <sstream>

#include "domain.h"
#include "mpi_support.h"


Domain::Domain(const MPI_Comm &comm, const Eigen::Array3d &domain_length,
               const Eigen::Array3i &decomposition, const Eigen::Array3i &periodicity)
        : domain_length_{domain_length}, decomposition_{decomposition}, periodicity_{periodicity}, nb_local_{0},
          is_enabled_{false}, offset_left_{Eigen::Matrix3d::Zero()}, offset_right_{Eigen::Matrix3d::Zero()} {
    MPI_Comm_size(comm, &size_);
    if (decomposition_.prod() != size_) {
        std::stringstream s;
        s << "Domain decomposition into " << decomposition_ << " domains is not possible with an MPI communicator with "
          << size_ << " processes.";
        throw std::runtime_error(s.str());
    }
    MPI_Cart_create(comm, 3, decomposition_.data(), periodicity_.data(), 1, &comm_);
    MPI_Comm_rank(comm_, &rank_);
    MPI_Cart_coords(comm_, rank_, 3, coordinate_.data());
    for (int dim{0}; dim < 3; ++dim) {
        MPI_Cart_shift(comm_, dim, 1, &left_(dim), &right_(dim));
    }

    _update_offsets();

    std::cout << "Rank " << rank_ << " has coordinate " << coordinate_.transpose() << "." << std::endl;
}


Domain::~Domain() {

}


void Domain::_update_offsets() {
    // Determine offsets for periodic boundary conditions.
    offset_left_ = (coordinate_ == 0).select(domain_length_, Eigen::Array3d::Zero())
            .matrix().asDiagonal();
    offset_right_ = (coordinate_ == decomposition_ - 1).select(-domain_length_, Eigen::Array3d::Zero())
            .matrix().asDiagonal();
}


void Domain::enable(Atoms &atoms) {
    // This only works if decomposition is disabled.
    assert_disabled();

    // Make a copy of the full atoms object.
    Atoms global_atoms{atoms};

    int local_index = 0;  // index for atom on local process
    for (int global_index = 0; global_index < global_atoms.nb_atoms(); global_index++) {
        if ((get_coordinate(global_atoms.positions.col(global_index)) == coordinate_).all()) {
            // This atom resides in the local domain. We need to add it to the domain-local atoms array.
            atoms.masses(local_index) = global_atoms.masses(global_index);
            atoms.positions.col(local_index) = global_atoms.positions.col(global_index);
            atoms.velocities.col(local_index) = global_atoms.velocities.col(global_index);
            atoms.forces.col(local_index) = global_atoms.forces.col(global_index);

            // Increase the index for local atoms.
            local_index++;
        }
    }

    // Resize atoms object to fit all process-local atoms.
    atoms.resize(local_index);
    nb_local_ = atoms.nb_atoms();

    is_enabled_ = true;
}


void Domain::disable(Atoms &atoms) {
    // This method only works if decomposition is enabled.
    assert_enabled();

    // Make a copy of the full atoms object.
    Atoms local_atoms{atoms};

    // We first need to figure how many atoms there are in total.
    Eigen::ArrayXi recvcount(size_);
    MPI::Eigen::allgather(nb_local_, recvcount, comm_);

    Eigen::Index nb_global_atoms{recvcount.sum()};

    // Resize atoms object to fit all (global) atoms.
    atoms.resize(nb_global_atoms);

    // Compute where in the global array we need to place the results.
    Eigen::ArrayXi displ(size_);
    displ(0) = 0;
    for (int i = 0; i < size_ - 1; i++) displ(i + 1) = displ(i) + recvcount(i);

    // Gather masses, positions, velocities and forces into their respective arrays.
    MPI_Allgatherv(local_atoms.masses.data(), nb_local_, MPI_DOUBLE, atoms.masses.data(), recvcount.data(),
                   displ.data(), MPI_DOUBLE, comm_);
    recvcount *= 3;
    displ *= 3;
    MPI_Allgatherv(local_atoms.positions.data(), 3 * nb_local_, MPI_DOUBLE, atoms.positions.data(), recvcount.data(),
                   displ.data(), MPI_DOUBLE, comm_);
    MPI_Allgatherv(local_atoms.velocities.data(), 3 * nb_local_, MPI_DOUBLE, atoms.velocities.data(), recvcount.data(),
                   displ.data(), MPI_DOUBLE, comm_);
    MPI_Allgatherv(local_atoms.forces.data(), 3 * nb_local_, MPI_DOUBLE, atoms.forces.data(), recvcount.data(),
                   displ.data(), MPI_DOUBLE, comm_);

    is_enabled_ = false;
}


Eigen::Index Domain::_exchange_atoms(Atoms &atoms, int dim) {
    // We first need to inform our neighbor how many atoms we are going to send.
    Eigen::Index nb_send_left{0}, nb_send_right{0};
    for (Eigen::Index i{0}; i < nb_local_; ++i) {
        auto domain_coordinate{get_coordinate(atoms.positions.col(i))};
        if (domain_coordinate(dim) < coordinate_(dim)) {
            nb_send_left++;
        } else if (domain_coordinate(dim) > coordinate_(dim)) {
            nb_send_right++;
        }
    }

    // Communicate number of atoms to neighbors.
    auto nb_recv_right{MPI::sendrecv(nb_send_left, left_(dim), right_(dim), comm_)};
    auto nb_recv_left{MPI::sendrecv(nb_send_right, right_(dim), left_(dim), comm_)};

    // Pack send buffers (for mass, positions and velocities; we don't send forces since they are valid for individual
    // time steps only).
    Eigen::Array<double, 7, Eigen::Dynamic> send_left(7, nb_send_left), send_right(7, nb_send_right);
    Eigen::Index ileft{0}, iright{0};
    for (Eigen::Index i{0}; i < nb_local_;) {
        auto domain_coordinate{get_coordinate(atoms.positions.col(i))};
        if (domain_coordinate(dim) < coordinate_(dim)) {
            // Pack masses, positions and velocities into send buffer.
            MPI::Eigen::pack_buffer_entry(
                    send_left.col(ileft),
                    atoms.masses(i),
                    atoms.positions(0, i) + offset_left_(0, dim),
                    atoms.positions(1, i) + offset_left_(1, dim),
                    atoms.positions(2, i) + offset_left_(2, dim),
                    atoms.velocities(0, i),
                    atoms.velocities(1, i),
                    atoms.velocities(2, i));
            ileft++;

            // Since this atom will leave the domain, we need to remove it. We simply move the last atom in place.
            if (i < nb_local_) {
                nb_local_--;
                atoms.masses(i) = atoms.masses(nb_local_);
                atoms.positions.col(i) = atoms.positions.col(nb_local_);
                atoms.velocities.col(i) = atoms.velocities.col(nb_local_);
            }
        } else if (domain_coordinate(dim) > coordinate_(dim)) {
            // Pack masses, positions and velocities into send buffer.
            MPI::Eigen::pack_buffer_entry(
                    send_right.col(iright),
                    atoms.masses(i),
                    atoms.positions(0, i) + offset_right_(0, dim),
                    atoms.positions(1, i) + offset_right_(1, dim),
                    atoms.positions(2, i) + offset_right_(2, dim),
                    atoms.velocities(0, i),
                    atoms.velocities(1, i),
                    atoms.velocities(2, i));
            iright++;

            // Since this atom will leave the domain, we need to remove it. We simply move the last atom in place.
            if (i < nb_local_) {
                nb_local_--;
                atoms.masses(i) = atoms.masses(nb_local_);
                atoms.positions.col(i) = atoms.positions.col(nb_local_);
                atoms.velocities.col(i) = atoms.velocities.col(nb_local_);
            }
        } else {
            i++;
        }
    }

    assert(ileft == nb_send_left);
    assert(iright == nb_send_right);

    // Communicate buffers.
    Eigen::Array<double, 7, Eigen::Dynamic> recv_left(7, nb_recv_left), recv_right(7, nb_recv_right);
    MPI::Eigen::sendrecv(send_left, left_(dim), recv_right, right_(dim), comm_);
    MPI::Eigen::sendrecv(send_right, right_(dim), recv_left, left_(dim), comm_);

    // Resize atoms array. This will discard all ghost atoms.
    atoms.resize(nb_local_ + nb_recv_left + nb_recv_right);

    // Unpack buffers.
    MPI::Eigen::unpack_buffer(recv_left, nb_local_,
                              atoms.masses,
                              atoms.positions.row(0), atoms.positions.row(1), atoms.positions.row(2),
                              atoms.velocities.row(0), atoms.velocities.row(1), atoms.velocities.row(2));
    MPI::Eigen::unpack_buffer(recv_right, nb_local_ + nb_recv_left,
                              atoms.masses,
                              atoms.positions.row(0), atoms.positions.row(1), atoms.positions.row(2),
                              atoms.velocities.row(0), atoms.velocities.row(1), atoms.velocities.row(2));

    // Update number of process-local atoms.
    assert(nb_local_ + recv_left.cols() + recv_right.cols() == atoms.nb_atoms());
    nb_local_ = atoms.nb_atoms();

    return nb_send_left + nb_send_right;
}


void Domain::exchange_atoms(Atoms &atoms) {
    // This method only works if decomposition is enabled.
    assert_enabled();

    // Loop as long as there is something left to be send. Multiple iterations
    // happen if atoms are farther than one subdomain away from where they
    // should be. (This should only happen under exceptional circumstances.)
    Eigen::Index nb_send_global{1};
    while (nb_send_global > 0) {
        // Loop over all Cartesian dimensions
        Eigen::Index nb_send_local{0};
        for (int dim{0}; dim < 3; ++dim) {
            nb_send_local += _exchange_atoms(atoms, dim);
        }

        // Determine how much data was send in this iteration.
        nb_send_global = MPI::allreduce(nb_send_local, MPI_SUM, comm_);
    }
}


std::tuple<Eigen::Index, Eigen::Index>
Domain::_update_ghosts(Atoms &atoms, double border_width, int dim,
                       Eigen::Index left_start, Eigen::Index left_len,
                       Eigen::Index right_start, Eigen::Index right_len) {
    // Boundaries of the Cartesian domain.
    double left_domain_boundary{coordinate_(dim) * domain_length_(dim) / decomposition_(dim)};
    double right_domain_boundary{(coordinate_(dim) + 1) * domain_length_(dim) / decomposition_(dim)};

    // We only consider the positions that were just received. Note that left positions are those that need to
    // send to the left (but that were received from the right). Right positions are those that need to be send
    // to the right (and were received from the left).
    auto &&left_positions{atoms.positions(Eigen::all, Eigen::seqN(left_start, left_len))};
    auto &&right_positions{atoms.positions(Eigen::all, Eigen::seqN(right_start, right_len))};

    // Determine atoms that need to be send to the left and the right.
    auto left_mask{left_positions.row(dim) < left_domain_boundary + border_width};
    auto right_mask{right_positions.row(dim) > right_domain_boundary - border_width};

    // Communicate number of ghost particles that will be transferred to neighbors.
    auto nb_send_left{left_mask.count()}, nb_send_right{right_mask.count()};
    auto nb_recv_right{MPI::sendrecv(nb_send_left, left_(dim), right_(dim), comm_)};
    auto nb_recv_left{MPI::sendrecv(nb_send_right, right_(dim), left_(dim), comm_)};

    // Pack send buffers. We only need positions.
    Eigen::Array3Xd send_left(3, nb_send_left), send_right(3, nb_send_right);
    MPI::Eigen::pack_buffer(send_left, left_mask,
                            left_positions.row(0) + offset_left_(0, dim),
                            left_positions.row(1) + offset_left_(1, dim),
                            left_positions.row(2) + offset_left_(2, dim));
    MPI::Eigen::pack_buffer(send_right, right_mask,
                            right_positions.row(0) + offset_right_(0, dim),
                            right_positions.row(1) + offset_right_(1, dim),
                            right_positions.row(2) + offset_right_(2, dim));

    // Send and receive buffers.
    Eigen::Array3Xd recv_right(3, nb_recv_right), recv_left(3, nb_recv_left);
    MPI::Eigen::sendrecv(send_left, left_(dim), recv_right, right_(dim), comm_);
    MPI::Eigen::sendrecv(send_right, right_(dim), recv_left, left_(dim), comm_);

    // Resize Atoms object to store additional ghost atoms. Note that this invalidates left_mask and right_mask
    // and we cannot use this after this step.
    auto nb_last{atoms.nb_atoms()};
    atoms.resize(nb_last + nb_recv_left + nb_recv_right);

    // Unpack receive buffers.
    MPI::Eigen::unpack_buffer(recv_left, nb_last,
                              atoms.positions.row(0), atoms.positions.row(1), atoms.positions.row(2));
    MPI::Eigen::unpack_buffer(recv_right, nb_last + nb_recv_left,
                              atoms.positions.row(0), atoms.positions.row(1), atoms.positions.row(2));

    return {nb_recv_left, nb_recv_right};
}


void Domain::update_ghosts(Atoms &atoms, double border_width) {
    // This method only works if decomposition is enabled.
    assert_enabled();

    // Remove all ghosts.
    atoms.resize(nb_local_);

    // Loop over all Cartesian dimensions
    for (int dim{0}; dim < 3; ++dim) {
        // In the first iteration below, we consider all atoms for sending into the neighboring ghost buffers. For
        // the first Cartesian dimension, those are only the process-local atoms. For the y- and z-direction, those
        // include the ghost atoms received before in the other directions.
        Eigen::Index left_start{0}, left_len{atoms.nb_atoms()}, right_start{0}, right_len{atoms.nb_atoms()};

        // Loop as long as there is something left to be send/received. Multiple iterations happen if a subdomain is
        // smaller than the border width.
        Eigen::Index nb_recv_global{1};
        while (nb_recv_global > 0) {
            // Store number of atoms before receiving new ghosts.
            auto nb_atoms_before_recv{atoms.nb_atoms()};

            // Send/receive ghost atoms.
            auto[nb_recv_left, nb_recv_right]{
                _update_ghosts(atoms, border_width, dim, left_start, left_len, right_start, right_len)};

            // In the next iterations, we only consider ghosts that were just received. We only consider sending those
            // ghost received from the left to the right.
            right_start = nb_atoms_before_recv;
            right_len = nb_recv_left;

            // We only consider sending those ghost received from the right to the left.
            left_start = nb_atoms_before_recv + nb_recv_left;
            left_len = nb_recv_right;

            // Determine how much data was received in this iteration.
            nb_recv_global = MPI::allreduce(nb_recv_left + nb_recv_right, MPI_SUM, comm_);
        }
    }
}


void Domain::scale(Atoms &atoms, Eigen::Array3d domain_length) {
    Eigen::Array3d scale_factor{domain_length / domain_length_};

    // Invalidate ghosts.
    atoms.resize(nb_local_);

    // Rescale atomic positions.
    for (auto &&position: atoms.positions.colwise()) {
        position *= scale_factor;
    }

    // Update domain length.
    domain_length_ = domain_length;
    _update_offsets();
}
