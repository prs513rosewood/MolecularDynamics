/*
* Copyright 2021 Lars Pastewka
*           2021 wolfram.noehring@imtek.uni-freiburg.de
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

#include <iomanip>
#include <iostream>
#include <fstream>

#include "xyz.h"

std::tuple<Names_t, Positions_t> read_xyz(std::string filename) {
    std::ifstream file(filename);

    if (file.is_open()) {
        // First line contains number of atoms
        int nb_atoms;
        file >> nb_atoms;
        // Skip rest of line
        std::string auxinfo;
        std::getline(file, auxinfo);

        // Second line contains a comment - in extended XYZ this line contains
        // auxiliary information
        std::getline(file, auxinfo);

        // Data structures for names and positions
        Names_t names(nb_atoms);
        Eigen::Array3Xd positions(3, nb_atoms);

        // Now follows a line for each atom
        for (int i = 0; i < nb_atoms; ++i) {
            std::string tmp;
            file >> names[i] >> positions(0, i) >> positions(1, i) >> positions(2, i);
            std::getline(file, tmp);
        }

        // Close file, we're done
        file.close();

        return {names, positions};
    } else {
        throw std::runtime_error("Could not open file");
    }
}

std::tuple<Names_t, Positions_t, Velocities_t> read_xyz_with_velocities(std::string filename) {
    std::ifstream file(filename);

    if (file.is_open()) {
        // First line contains number of atoms
        int nb_atoms;
        file >> nb_atoms;
        // Skip rest of line
        std::string auxinfo;
        std::getline(file, auxinfo);

        // Second line contains a comment - in extended XYZ this line contains
        // auxiliary information
        std::getline(file, auxinfo);

        // Data structures for names and positions
        Names_t names(nb_atoms);
        Eigen::Array3Xd positions(3, nb_atoms);
        Eigen::Array3Xd velocities(3, nb_atoms);

        // Now follows a line for each atom
        for (int i = 0; i < nb_atoms; ++i) {
            std::string tmp;
            file >> names[i] >> positions(0, i) >> positions(1, i) >> positions(2, i)
                 >> velocities(0, i) >> velocities(1, i) >> velocities(2, i);
            std::getline(file, tmp);
        }

        // Close file, we're done
        file.close();

        return {names, positions, velocities};
    } else {
        throw std::runtime_error("Could not open file");
    }
}

void write_xyz(std::string filename, Atoms &atoms) {
    std::ofstream file(filename);

    // Number of atoms
    file << atoms.nb_atoms() << std::endl;

    // Comment line
    file << std::endl;

    // Element name, position
    for (int i = 0; i < atoms.nb_atoms(); ++i) {
        file << std::setw(2) << atoms.names[i] << " "
             << std::setw(10) << atoms.positions.col(i).transpose()
             << std::setw(10) << atoms.velocities.col(i).transpose()
             << std::endl;
    }

    // Close file, we're done
    file.close();
}
