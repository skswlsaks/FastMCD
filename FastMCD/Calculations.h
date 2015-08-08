#ifndef OUTLIERC_CALCULATIONS_H
#define OUTLIERC_CALCULATIONS_H

#include "Eigen/Dense"
#include "Sampling.h"

using namespace Eigen;

extern MatrixXd data;

class Calculations {

public:
    //MatrixXd sample;
    //Calculations (MatrixXd smp) {sample = smp;};
    Calculations() {};
    VectorXd Ave(MatrixXd sample);
    MatrixXd covariance(MatrixXd sample);
    //MatrixXd eigenVector(MatrixXd *value);
    MatrixXd diagonal(MatrixXd b, double qn);
    MatrixXd distance(MatrixXd sample);
    void Cstep(MatrixXd distance);
    ~Calculations();
};



#endif //OUTLIERC_CALCULATIONS_H