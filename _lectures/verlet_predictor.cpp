```cpp
verlet_step1(Atoms &amp;atoms, double timestep, double mass) {
    atoms.velocities += 0.5 * atoms.forces * timestep / mass;
    atoms.positions += atoms.velocities * timestep;
}
```
