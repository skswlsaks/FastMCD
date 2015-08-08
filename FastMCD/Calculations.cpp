#include "Eigen/Dense"
#include "Calculations.h"
#include <utility>
#include <vector>

using namespace std;
using namespace Eigen;

struct DistancePair {
    double distance;
    int index;
    bool operator < (const DistancePair& dp) const {
        return distance < dp.distance;
    }
};

VectorXd Calculations::Ave(MatrixXd sample) {
    int row = (int) sample.rows();
    int col = (int) sample.cols();
    double sum = 0;
    VectorXd res(col);
    for (int i = 0; i < col; ++i) {
        for (int j = 0; j < row; ++j) {
            sum += sample(j, i);
        }
        res(col) = sum/row;
    }
    return res;
}

MatrixXd Calculations::covariance(MatrixXd sample) {
    MatrixXd cov;
    double det;
    do {
        MatrixXd centered = sample.rowwise() - sample.colwise().mean();
        cov = (centered.adjoint() * centered) / double(sample.rows() - 1);
        det = cov.determinant();
        if (det == 0) {
            Sampling s;
            sample = s.addSample(sample);
        }
    } while (cov.determinant() == 0);
    return cov;
}

VectorXd Calculations::distance(MatrixXd sample) {
    MatrixXd sub = data - sample;
    MatrixXd cov = covariance(sample);
    cov = cov.inverse();
    MatrixXd subT = sub.transpose();
    VectorXd distance = subT * cov * sub;
    return distance;
}

pair<MatrixXd, VectorXi> Calculations::Cstep(VectorXd d, VectorXi indexes) {
    int h = (int) (0.75 * d.size());
    //int k = (int) (d.rows() - 1);
    //nth_element(d.data(), d.data()+k, d.data()+d.size());
    
    // Construct a pair with distance and coresponding indexes
    DistancePair indexPair;
    // Store all the pair in vector to sort;
    vector<DistancePair> vec;
    for (int i = 0; i < d.rows(); ++i) {
        indexPair.distance = d(i);
        indexPair.index = indexes(i);
        vec.push_back(indexPair);
    }
    sort(vec.begin(), vec.end());
    
    // Construct result matrix (index convert to real data)
    MatrixXd res(h, data.cols());
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < data.cols(); ++j){
            res(i,j) = data(vec[i].index, j);
        }
    }
    
    // Construct result index vector;
    for (int i = 0; i < h; ++i) {
        indexes(i) = vec[i].index;
    }
    
    pair<MatrixXd, VectorXi> resultPair(res, indexes);
    // return matrix of (pi(1), pi(2), pi(3)....pi(h))
    return resultPair;
}


/*MatrixXd Calculations::eigenVector(MatrixXd *value) {
    EigenSolver<MatrixXd> es(*value);
    return es.eigenvectors();
}*/

MatrixXd Calculations::diagonal(MatrixXd b, double qn) {
    b = b*(pow(qn, 2));
    b = b.diagonal();
    return b;
}



