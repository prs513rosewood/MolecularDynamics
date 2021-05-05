//
// Created by pastewka on 17.04.21.
//

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
                 >> velocities(0, i) >> velocities(1, i) >> velocities(3, i);
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
