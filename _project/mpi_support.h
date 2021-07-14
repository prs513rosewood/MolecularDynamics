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

#ifndef YAMD_MPI_SUPPORT_H
#define YAMD_MPI_SUPPORT_H

#include <mpi.h>

#include <Eigen/Dense>

/*
 * Wrap integer value to interval [0..range-1]. This is the modulo operation.
 */
template<typename T>
inline T wrap_to_interval(T value, T range) {
    while (value < 0) value += range;
    while (value > range - 1) value -= range;
    return value;
}

/*
 * Wrap integer value to a distance on the interval [0..range-1].
 */
template<typename T>
inline T wrap_to_distance(T value, T range) {
    T v{value + range / 2};
    return wrap_to_interval(v, range) - range / 2;
}

namespace MPI {

/*
 * The following function convert C++ data types to MPI type identifiers at
 * compile time. Example: MPI_Datatype t_int{mpi_type<int>()};
 */

    template<typename T, typename T2 = T>
    inline decltype(auto) mpi_type() {
        static_assert(std::is_same<T, T2>::value,
                      "T2 is a SFINAE parameter, do not touch");
        static_assert(std::is_same<T, T2>::value and not std::is_same<T, T2>::value,
                      "The type you're trying to map has not been declared.");
        return MPI_LONG;
    }

    template<>
    inline decltype(auto) mpi_type<char>() {
        return MPI_CHAR;
    }

    template<>
    inline decltype(auto) mpi_type<short>() {
        return MPI_SHORT;
    }

    template<>
    inline decltype(auto) mpi_type<int>() {
        return MPI_INT;
    }

    template<>
    inline decltype(auto) mpi_type<long>() {
        return MPI_LONG;
    }

    template<>
    inline decltype(auto) mpi_type<long long>() {
        return MPI_LONG_LONG_INT;
    }

    template<>
    inline decltype(auto) mpi_type<unsigned char>() {
        return MPI_UNSIGNED_CHAR;
    }

    template<>
    inline decltype(auto) mpi_type<unsigned short>() {
        return MPI_UNSIGNED_SHORT;
    }

    template<>
    inline decltype(auto) mpi_type<unsigned int>() {
        return MPI_UNSIGNED;
    }

    template<>
    inline decltype(auto) mpi_type<unsigned long>() {
        return MPI_UNSIGNED_LONG;
    }

    template<>
    inline decltype(auto) mpi_type<float>() {
        return MPI_FLOAT;
    }

    template<>
    inline decltype(auto) mpi_type<double>() {
        return MPI_DOUBLE;
    }

    /*
     * Call MPI_Sendrecv with correct data types.
     */
    template<typename T>
    T sendrecv(T &sendval, int dest, int source, MPI_Comm comm) {
        T recvval{};
        MPI_Sendrecv(&sendval, 1, mpi_type<T>(), dest, 0,
                     &recvval, 1, mpi_type<T>(), source, 0,
                     comm, nullptr);
        return recvval;
    }

    /*
     * Call MPI_Allreduce with correct data types.
    */
    template<typename T>
    T allreduce(T sendval, MPI_Op op, MPI_Comm comm) {
        T recvval{};
        MPI_Allreduce(&sendval, &recvval, 1, mpi_type<T>(), op, comm);
        return recvval;
    }

    namespace Eigen {

        template<int i, typename B, typename T>
        void pack_buffer_entry(B buffer, T arg) {
            static_assert(B::RowsAtCompileTime == i + 1, "Your buffer has the wrong number of rows");
            buffer(i) = arg;
        }

        template<int i, typename B, typename T, typename ... Ts>
        void pack_buffer_entry(B buffer, T arg, Ts... args) {
            buffer(i) = arg;
            pack_buffer_entry<i + 1>(buffer, args...);
        }

        template<typename B, typename ... Ts>
        void pack_buffer_entry(B buffer, Ts... args) {
            pack_buffer_entry<0>(buffer, args...);
        }

        template<int i, typename B, typename T>
        void unpack_buffer_entry(B &buffer, T &arg) {
            static_assert(B::RowsAtCompileTime == i + 1, "Your buffer has the wrong number of rows");
            arg = buffer(i);
        }

        template<int i, typename B, typename T, typename ... Ts>
        void unpack_buffer_entry(B &buffer, T &arg, Ts &... args) {
            arg = buffer(i);
            unpack_buffer_entry<i + 1>(buffer, args...);
        }

        template<typename B, typename ... Ts>
        void unpack_buffer_entry(B &buffer, Ts &... args) {
            unpack_buffer_entry<0>(buffer, args...);
        }

        template<typename B, typename M, typename... Ts>
        void pack_buffer(B &buffer, M mask, const Ts &...args) {
            assert(buffer.cols() == mask.count());
            ::Eigen::Index buffer_index{0};
            for (std::size_t i{0}; i < mask.size(); ++i) {
                if (mask[i]) {
                    pack_buffer_entry(buffer.col(buffer_index), args(i)...);
                    buffer_index++;
                }
            }
            assert(buffer_index == mask.count());
        }

        template<typename B, typename... Ts>
        void unpack_buffer(B &buffer, ::Eigen::Index offset, const Ts &...args) {
            ::Eigen::Index buffer_index{0};
            for (auto &&buffer_entry: buffer.colwise()) {
                unpack_buffer_entry(buffer_entry, const_cast<Ts &>(args)(offset + buffer_index)...);
                buffer_index++;
            }
        }

        /*
         * Call MPI_Sendrecv for data stored in Eigen arrays; deduce data types
         * and size automatically.
         */
        template<typename SendType, typename RecvType>
        void sendrecv(const SendType &sendarr, int dest, const RecvType &recvarr, int source, MPI_Comm &comm) {
            // Some trickery: recvbuf for MPI_Sendrecv cannot be NULL, we hence use a dummy buffer when no data is received.
            typename RecvType::Scalar dummy_recv_buffer[0];
            typename RecvType::Scalar *recv_buffer{const_cast<RecvType &>(recvarr).derived().data()};
            if (!recv_buffer) recv_buffer = dummy_recv_buffer;

            MPI_Sendrecv(const_cast<SendType &>(sendarr).derived().data(), sendarr.size(),
                         mpi_type<typename SendType::Scalar>(), dest, 0,
                         recv_buffer, recvarr.size(),
                         mpi_type<typename RecvType::Scalar>(), source, 0,
                         comm, nullptr);
        }

        /*
         * Call MPI_Allgather with correct data types.
         */
        template<typename T, typename RecvType>
        void allgather(T &sendval, RecvType &recvbuf, MPI_Comm &comm) {
            MPI_Allgather(&sendval, 1, mpi_type<T>(), recvbuf.data(), 1, mpi_type<typename RecvType::Scalar>(), comm);
        }

    }
}

#endif //YAMD_MPI_SUPPORT_H
