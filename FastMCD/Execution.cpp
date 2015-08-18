#include "Execution.h"
#include "Sampling.h"
#include "Calculations.h"
#include <array>
#include <vector>

#include <iostream>

using namespace std;

struct DetAndData {
	// determinant of each sample
	double det;
	// corresponding data;
	MatrixXd mat;
	// index of data
	VectorXi index;
	bool operator <(const DetAndData& dd) const {
		return det < dd.det;
	}
};

struct DetAndDP {
    // determinant of each sample
    double det;
    // corresponding data;
    vector<DistancePair> dp;
    bool operator <(const DetAndDP& dd) const {
        return det < dd.det;
    }
};

void Execution::step4() {
	Sampling s;
	Calculations cal;
	VectorXi indexes(data.rows());
	vector<DetAndData> vec;
	DetAndData dad;
	for (int i = 0; i < data.rows(); ++i) {
		indexes(i) = i;
	}
	for (int i = 0; i < 500; ++i) {
        if (i == 100) {
            cout << "HEre" << endl;
        }
		MatrixXd sample = s.randomSample((int) data.cols());
		MatrixXd distance = cal.distance(sample);
		// pair of sample and indexes(in data) of sample
		pair<MatrixXd, VectorXi> pairs;
		pairs = cal.Cstep(distance, indexes);
		pairs = cal.Cstep(pairs.first, pairs.second);
		dad.det = cal.covarianceMatrix(pairs.first).determinant();
		dad.mat = pairs.first;
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
			det = cal.covarianceMatrix(p.first).determinant();
			dad.det = det;
			dad.mat = p.first;
			resultVector.push_back(dad);
		} while (det == 0 || prev == det);
	}

	sort(resultVector.begin(), resultVector.end());

	//Result
	MatrixXd ave = cal.ave(resultVector[0].mat);
	//double resultDet = resultVector[0].det;
}


void Execution::step42() {
    Sampling s;
    Calculations cal;
    VectorXi indexes(data.rows());
    vector<DetAndDP> vec;

    for (int i = 0; i < data.rows(); ++i) {
        indexes(i) = i;
    }
    for (int i = 0; i < 500; ++i) {
        if (i == 500) {
            cout << "HEre" << endl;
        }
        MatrixXd sample = s.randomSample((int) data.cols());
        MatrixXd distance = cal.distance(sample);
        vector<DistancePair> dp;
        for (int j = 0; j < distance.rows(); ++j) {
            DistancePair tmp;
            tmp.distance = distance(i,0);
            tmp.index = indexes(i);
            dp.push_back(tmp);
        }
        
        dp = cal.Cstep2(dp);
        dp = cal.Cstep2(dp);
        MatrixXd H(dp.size(), data.cols());
        H = constructMatrixWithIndex(dp);
        DetAndDP dad;
        dad.det = cal.covarianceMatrix(H).determinant();
        dad.dp = dp;
        vec.push_back(dad);
    }
    
    sort(vec.begin(), vec.end());
    
    vector<DetAndDP> resultVector;
    for (int i = 0; i < 10; ++i) {
        DetAndDP d = vec[i];
        double det = 0;
        double prev = 0;
        vector<DistancePair> dp;
        do {
            prev = det;
            dp = cal.Cstep2(d.dp);
            MatrixXd H(d.dp.size(), data.cols());
            H = constructMatrixWithIndex(dp);
            det = cal.covarianceMatrix(H).determinant();
            DetAndDP dad;
            dad.det = det;
            dad.dp = dp;
            resultVector.push_back(dad);
        } while (det == 0 || prev == det);
    }
    
    sort(resultVector.begin(), resultVector.end());
    
    //resultVector[0];
    
}

MatrixXd Execution::constructMatrixWithIndex(vector<DistancePair> dp) {
    MatrixXd H(dp.size(), data.cols());
    for (int j = 0; j < dp.size(); ++j) {
        H.row(j) = data.row(dp[j].index);
    }
    return H;
}


void Execution::step5() {
	int n = (int) data.rows();
	Sampling s;
	Calculations cal;
	int indexes[n];
	for (int i = 0; i < data.rows(); ++i) {
		indexes[i] = i;
	}
	random_shuffle(indexes, indexes + n);

	int nsub = n / 5;
	int h = (int) data.cols();
	int hsub = nsub * (h / n);

	// Construct disjoint random subsets
	MatrixXd subsets[5];
	VectorXi subsetIndex[5];
	for (int i = 0; i < 5; ++i) {
		for (int j = i * nsub; j < i * nsub; ++j) {
			subsetIndex[i] (j % nsub) = indexes[j];
			for (int k = 0; k < data.cols(); ++k) {
				subsets[i](j % nsub, k) = data(indexes[j], k);
			}
		}
	}

	MatrixXd samples[5];
	DetAndData dad;
	vector<DetAndData> vec;
	for (unsigned int i = 0; i < sizeof(subsets) / sizeof(subsets[0]); ++i) {
		for (int j = 0; j < 100; ++j) {
			samples[j] = s.randomSample(hsub);
			VectorXd distance = cal.distance(samples[j]);
			pair<MatrixXd, VectorXi> pairs;
			pairs = cal.Cstep(distance, subsetIndex[i]);
			pairs = cal.Cstep(pairs.first, pairs.second);
			dad.det = cal.covarianceMatrix(pairs.first).determinant();
			dad.mat = pairs.first;
			dad.index = pairs.second;
			vec.push_back(dad);
		}
	}
	sort(vec.begin(), vec.end());

	MatrixXd sample;
	vector<DetAndData> vecMerged;
	for (int i = 0; i < 50; ++i) {
		sample = s.randomSample(h);
		VectorXd distance = cal.distance(sample);
		pair<MatrixXd, VectorXi> pairs;
		pairs = cal.Cstep(distance, vec[i].index);
		pairs = cal.Cstep(pairs.first, pairs.second);
		dad.det = cal.covarianceMatrix(pairs.first).determinant();
		dad.mat = pairs.first;
		dad.index = pairs.second;
		vecMerged.push_back(dad);
	}
	sort(vecMerged.begin(), vecMerged.end());

	//return
	/*MatrixXd ave = cal.Ave(vecMerged[0].mat);
	double resDet = vecMerged[0].det;*/
}
