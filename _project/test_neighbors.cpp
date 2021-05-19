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

#include "atoms.h"
#include "neighbors.h"

#include <gtest/gtest.h>

TEST(NeighborsTest, Test1) {
    Names_t names{{"H", "H", "H", "H"}};
    Positions_t positions(3, 4);
    positions << 0,  1,  0,  0,
                 0,  0,  1, -1,
                 0,  0,  0,  0;

    Atoms atoms(names, positions);
    NeighborList neighbor_list(1.5);
    auto &[seed, neighbors]{neighbor_list.update(atoms)};

    EXPECT_TRUE((neighbors(Eigen::seq(seed(0), seed(1)-1)) == Eigen::Array3i{3, 1, 2}).all());
    EXPECT_TRUE((neighbors(Eigen::seq(seed(1), seed(2)-1)) == Eigen::Array3i{3, 0, 2}).all());
    EXPECT_TRUE((neighbors(Eigen::seq(seed(2), seed(3)-1)) == Eigen::Array2i{0, 1}).all());
    EXPECT_TRUE((neighbors(Eigen::seq(seed(3), seed(4)-1)) == Eigen::Array2i{0, 1}).all());
}
