#include "Eigen/Dense"
#include "Calculations.h"
#include <utility>
#include <vector>

#include <iostream>

using namespace std;
using namespace Eigen;



MatrixXd Calculations::ave(MatrixXd sample) {
    return sample.colwise().mean();
}

MatrixXd Calculations::covarianceMatrix(MatrixXd sample) {
    MatrixXd cov;
    double det;
    do {
        cov = covariance(sample);
        det = cov.determinant();
        if (det == 0) {
            Sampling s;
            sample = s.addSample(sample);
        }
    } while (cov.determinant() == 0);
    return cov;
}

MatrixXd Calculations::distance(MatrixXd sample) {
    MatrixXd sub = data.rowwise() - sample.colwise().mean();
    MatrixXd cov = covarianceMatrix(sample);
    cov = cov.inverse();
    MatrixXd distance(sub.rows(), 1);
    for (int i = 0; i < sub.rows(); ++i) {
        MatrixXd tmp = sub.row(i);
        distance.row(i) = tmp * cov * tmp.transpose();
    }
    return distance;
}

pair<MatrixXd, VectorXi> Calculations::Cstep(MatrixXd d, VectorXi indexes) {
    int h = (int) (0.75 * d.rows());
    
    // Construct a pair with distance and coresponding indexes

    // Store all the pair in vector to sort;
    vector<DistancePair> vec;
    for (int i = 0; i < d.rows(); ++i) {
        DistancePair indexPair;
        indexPair.distance = d(i,0);
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

vector<DistancePair> Calculations::Cstep2(vector<DistancePair> dp) {
    int h = (int) (0.75 * dp.size());
    sort(dp.begin(), dp.end());
    dp.resize(h);
    return dp;
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

MatrixXd Calculations::covariance(MatrixXd s) {
    MatrixXd centered = s.rowwise() - s.colwise().mean();
    MatrixXd sum(s.cols(), s.cols());
	for (int i = 0; i < s.rows(); ++i) {
		MatrixXd tmp = centered.row(i);
		sum += tmp.transpose() * tmp;
	}
	return sum/ double(s.rows()-1);
}

