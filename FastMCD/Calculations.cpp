#include "Eigen/Dense"
#include "Calculations.h"

using namespace Eigen;

//typedef MatrixXd<double, Dynamic, Dynamic, RowMajor> Mat;


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

MatrixXd Calculations::distance(MatrixXd sample) {
    MatrixXd sub = data - sample;
    MatrixXd cov = covariance(sample);
    cov = cov.inverse();
    MatrixXd subT = sub.transpose();
    MatrixXd distance = subT * cov * sub;
    return distance;
}

void Calculations::Cstep(MatrixXd d) {
    int h = (int) 0.75 * d.rows();
    int k = (int) d.rows() - 1;
    nth_element(d.data(), d.data()+k, d.data()+d.size());



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



