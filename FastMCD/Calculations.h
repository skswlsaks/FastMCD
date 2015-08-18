#ifndef OUTLIERC_CALCULATIONS_H
#define OUTLIERC_CALCULATIONS_H

#include "Eigen/Dense"
#include "Sampling.h"
#include <vector>

using namespace Eigen;

extern MatrixXd data;

struct DistancePair {
    double distance;
    int index;
    bool operator < (const DistancePair& dp) const {
        return distance < dp.distance;
    }
};

class Calculations {

public:
    //MatrixXd sample;
    //Calculations (MatrixXd smp) {sample = smp;};
    Calculations() {};
    MatrixXd ave(MatrixXd sample);
    MatrixXd covarianceMatrix(MatrixXd sample);
    //MatrixXd eigenVector(MatrixXd *value);
    MatrixXd diagonal(MatrixXd b, double qn);
    MatrixXd distance(MatrixXd sample);
    pair<MatrixXd, VectorXi> Cstep(MatrixXd distance, VectorXi indexes);
    vector<DistancePair> Cstep2(vector<DistancePair> dp);
    MatrixXd covariance(MatrixXd s);
    ~Calculations() {};
    
private:


};



#endif //OUTLIERC_CALCULATIONS_H
