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

#ifndef FPS_NEIGHBORS_H
#define FPS_NEIGHBORS_H

#include "atoms.h"

class NeighborList {
public:
    NeighborList(double interaction_range);

    const std::tuple<const Eigen::ArrayXi &, const Eigen::ArrayXi &> update(const Atoms &atoms);

    const std::tuple<const Eigen::ArrayXi &, const Eigen::ArrayXi &> neighbors() const {
        if (seed_.size() > 0) {
            return {seed_, neighbors_};
        } else {
            throw std::runtime_error("Neighbor list not yet computed. Use `update` to compute it.");
        }
    }

    class iterator : public std::iterator<
            std::input_iterator_tag,
            std::tuple<int, int>,    // value_type
            std::tuple<int, int>,    // difference_type
            std::tuple<int, int> *,  // pointer
            std::tuple<int, int>> {  // reference
    public:
        explicit iterator(const Eigen::ArrayXi &seed, const Eigen::ArrayXi &neighbors, int i, int n)
                : seed_{seed}, neighbors_{neighbors}, i_{i}, n_{n} {}

        iterator &operator++() {
            n_++;
            if (n_ == seed_(i_ + 1)) {
                i_++;
            }
            return *this;
        }

        bool operator==(iterator other) const { return n_ == other.n_; }

        bool operator!=(iterator other) const { return n_ != other.n_; }

        reference operator*() const { return {i_, neighbors_(n_)}; }

    protected:
        const Eigen::ArrayXi &seed_;
        const Eigen::ArrayXi &neighbors_;
        int i_, n_;
    };

    iterator begin() const {
        if (seed_.size() > 0) {
            return iterator(seed_, neighbors_, 0, seed_(0));
        } else {
            throw std::runtime_error("Neighbor list not yet computed. Use `update` to compute it.");
        }
    }

    iterator end() const {
        if (seed_.size() > 0) {
            return iterator(seed_, neighbors_, seed_.size() - 2, seed_(seed_.size() - 1));
        } else {
            throw std::runtime_error("Neighbor list not yet computed. Use `update` to compute it.");
        }
    }

protected:
    template<typename T>
    static decltype(auto) coordinate_to_index(const T &x, const T &y, const T &z, const Eigen::Array3i &nb_grid_pts) {
        return x + nb_grid_pts(0) * (y + nb_grid_pts(1) * z);
    }

    int coordinate_to_index(const Eigen::Array3i &c, const Eigen::Array3i &nb_grid_pts) {
        return coordinate_to_index(c(0), c(1), c(2), nb_grid_pts);
    }

    double interaction_range_;

    Eigen::ArrayXi seed_;
    Eigen::ArrayXi neighbors_;
};

#endif //FPS_NEIGHBORS_H
