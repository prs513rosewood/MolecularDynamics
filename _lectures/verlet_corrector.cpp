```cpp
void verlet_step2(Atoms &amp;atoms, double timestep, double mass) {
    atoms.velocities += 0.5 * atoms.forces * timestep / mass; 
}
```
