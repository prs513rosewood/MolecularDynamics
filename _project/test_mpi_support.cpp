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

#include <gtest/gtest.h>

#include "mpi_support.h"

TEST(MPISupport, MPIType) {
    EXPECT_EQ(MPI::mpi_type<char>(), MPI_CHAR);
    EXPECT_EQ(MPI::mpi_type<short>(), MPI_SHORT);
    EXPECT_EQ(MPI::mpi_type<int>(), MPI_INT);
    EXPECT_EQ(MPI::mpi_type<long>(), MPI_LONG);
    EXPECT_EQ(MPI::mpi_type<long long>(), MPI_LONG_LONG_INT);
    EXPECT_EQ(MPI::mpi_type<unsigned char>(), MPI_UNSIGNED_CHAR);
    EXPECT_EQ(MPI::mpi_type<unsigned short>(), MPI_UNSIGNED_SHORT);
    EXPECT_EQ(MPI::mpi_type<unsigned int>(), MPI_UNSIGNED);
    EXPECT_EQ(MPI::mpi_type<unsigned long>(), MPI_UNSIGNED_LONG);
    EXPECT_EQ(MPI::mpi_type<float>(), MPI_FLOAT);
    EXPECT_EQ(MPI::mpi_type<double>(), MPI_DOUBLE);
}

TEST(MPISupport, Wrap) {
    EXPECT_EQ(wrap_to_interval(0, 7), 0);
    EXPECT_EQ(wrap_to_interval(1, 7), 1);
    EXPECT_EQ(wrap_to_interval(-1, 7), 6);

    EXPECT_EQ(wrap_to_distance(0, 7), 0);
    EXPECT_EQ(wrap_to_distance(1, 7), 1);
    EXPECT_EQ(wrap_to_distance(-1, 7), -1);
    EXPECT_EQ(wrap_to_distance(3, 7), 3);
    EXPECT_EQ(wrap_to_distance(-3, 7), -3);
    EXPECT_EQ(wrap_to_distance(4, 7), -3);
    EXPECT_EQ(wrap_to_distance(-4, 7), 3);
}