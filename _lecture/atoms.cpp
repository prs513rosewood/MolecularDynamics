```cpp

using Velocities_t = Eigen::Array3Xd;
using Forces_t = Eigen::Array3Xd; 

class Atoms { 
public: 
    Positions_t positions; 
    Velocities_t velocities; 
    Forces_t forces; 
   Atoms(Positions_t &amp;p) :
           positions{p}, velocities{3, p.cols()}, forces{3, p.cols()} {
       velocities.setZero();
       forces.setZero();
   }
   size_t nb_atoms() {
       return positions.cols();
   }
};
```
