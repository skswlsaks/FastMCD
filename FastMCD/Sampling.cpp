#include "Sampling.h"

using namespace Eigen;
using namespace std;

MatrixXd data;
int *indexOfData;

Sampling::Sampling (MatrixXd m) {
    data = m;
    indexOfData = new int[data.cols()+1];
}

MatrixXd Sampling::randomSample() {
	int p = (int) data.cols();
    int count = 0;
    do {
        int tmp = rand() % (data.rows());
        if (find(indexOfData, indexOfData+p+1, tmp)
            != indexOfData+p+1) {
            indexOfData[count] = tmp;
            ++count;
        }
    } while (count != p+1);

    MatrixXd sample(p+1, p);
    for (int i = 0; i < p+1; ++i) {
        for (int j = 0; j < p; ++j) {
            sample(i, j) = data(indexOfData[i], j);
        }
    }

    return sample;
}

MatrixXd Sampling::addSample(MatrixXd sample) {
    // expand array by copying memory
    int sizeArray = (sizeof(indexOfData)/sizeof(*indexOfData)) + 1;
    int *tmp = new int[sizeArray];
    copy(indexOfData, indexOfData+sizeArray, tmp);
    delete [] indexOfData;
    indexOfData = tmp;
    
    bool cond = true;
    int randNum;
    do {
        randNum = rand() % (data.rows());
        if (find(indexOfData, indexOfData+sizeArray, randNum) != indexOfData+sizeArray) {
            *(indexOfData + sizeArray - 1) = 0;
            cond = false;
        }
    } while (cond);
    int row = (int) sample.rows();
    int col = (int) sample.cols();
    sample.resize(row+1, col);
    for (int i = 0; i < col; ++i){
        sample(row, i) = data(randNum, i);
    }
    return sample;
}


/*double Sampling::Qn(VectorXd& y) {
    // Copy from r c++ package;
    return 0;
}*/


/*VectorXd Sampling::calculateQn() {
    VectorXd qn(data.cols());
    VectorXd y(data.rows());
    for (int j = 0; j < data.cols(); ++j) {
        for (int i = 0; i < data.rows(); ++i) {
            y(i) = data(i,j);
        }
        qn(j) = Qn(y);
    }
    return qn;
}*/

