//
// Created by pastewka on 17.04.21.
//

#ifndef FPS_XYZ_H
#define FPS_XYZ_H

#include "atoms.h"

/*
 * Read positions from an XYZ file. XYZ files are structured a follows:
 *     line 1: Number of atoms
 *     line 2: Comment line (is ignored)
 *     following lines: Name X Y Z
 *         where Name is some name for the atom and X Y Z the position
 */
std::tuple<Names_t, Positions_t> read_xyz(std::string filename);

/*
 * Read positions and velocities from an XYZ file.
 * The XYZ file is structured a follows:
 *     line 1: Number of atoms
 *     line 2: Comment line (is ignored)
 *     following lines: Name X Y Z VX VY VZ
 *         where Name is some name for the atom, X Y Z the position
 *         and VX, VY, VZ the velocity of the atom
 */
std::tuple<Names_t, Positions_t, Velocities_t> read_xyz_with_velocities(std::string filename);

/*
 * Write positions and velocities to an XYZ file.
 * The XYZ file is structured a follows:
 *     line 1: Number of atoms
 *     line 2: Comment line (is ignored)
 *     following lines: Name X Y Z VX VY VZ
 *         where Name is some name for the atom, X Y Z the position
 *         and VX, VY, VZ the velocity of the atom
 */
void write_xyz(std::string filename, Atoms& atoms);

#endif //FPS_XYZ_H
