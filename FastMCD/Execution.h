#ifndef __FastMCD__Execution__
#define __FastMCD__Execution__

#include <stdio.h>
#include "Eigen/Dense"
#include <vector>
#include "Calculations.h"

using namespace Eigen;

extern MatrixXd data;

class Execution {
public:
    Execution () {};
    
    void step4();
    void step42();
    void step5();
    
    MatrixXd constructMatrixWithIndex(vector<DistancePair> dp);
    
    ~Execution () {};
};


#endif /* defined(__FastMCD__Execution__) */
