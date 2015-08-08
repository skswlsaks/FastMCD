#ifndef __FastMCD__Execution__
#define __FastMCD__Execution__

#include <stdio.h>
#include "Eigen/Dense"

using namespace Eigen;

extern MatrixXd data;

class Execution {
public:
    Execution () {};
    
    void step4();
    
    
    ~Execution () {};
};


#endif /* defined(__FastMCD__Execution__) */
