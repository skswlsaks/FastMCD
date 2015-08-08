#include "Execution.h"
#include "Sampling.h"
#include "Calculations.h"
#include <vector>

struct DetAndData {
    // determinant of each sample
    double det;
    // corresponding data;
    MatrixXd mat;
    // index of data
    VectorXi index;
    bool operator < (const DetAndData& dd) const {
        return det < dd.det;
    }
};

void Execution::step4() {
    Sampling s;
    Calculations cal;
    VectorXd indexes;
    vector<DetAndData> vec;
    DetAndData dad;
    for (int i = 0; i < data.rows(); ++i) {
        indexes(i) = i;
    }
    for (int i = 0; i < 500; ++i) {
        MatrixXd sample = s.randomSample();
        VectorXd distance = cal.distance(sample);
        // pair of sample and indexes(in data) of sample
        pair<MatrixXd, VectorXi> pair;
        pair = cal.Cstep(distance, indexes);
        pair = cal.Cstep(pair.first, pair.second);
        dad.det = cal.covariance(pair.first).determinant();
        dad.mat = pair.first;
        vec.push_back(dad);
    }
    
    sort(vec.begin(), vec.end());
    vector<DetAndData> resultVector;
    for (int i = 0; i < 10; ++i) {
        DetAndData d = vec[i];
        pair<MatrixXd, VectorXi> p;
        double det = 0;
        double prev = 0;
        do {
            prev = det;
            p = cal.Cstep(cal.distance(d.mat), d.index);
            det = cal.covariance(p.first).determinant();
            dad.det = det;
            dad.mat = p.first;
            resultVector.push_back(dad);
        } while (det == 0 || prev == det);
    }
    
    sort(resultVector.begin(), resultVector.end());
    
    //Result
    MatrixXd ave = cal.Ave(resultVector[0].mat);
    double resultDet = resultVector[0].det;
}

