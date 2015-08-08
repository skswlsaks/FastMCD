#ifndef SAMPLING_H_
#define SAMPLING_H_

#include "Eigen/Dense"

using namespace Eigen;
using namespace std;



class Sampling {
public:

	Sampling (){};
	Sampling(MatrixXd m);

	MatrixXd addSample(MatrixXd sample);
    MatrixXd randomSample();
	//double Qn(VectorXd& y);
	//VectorXd calculateQn();
	~Sampling (){};
private:



};



#endif /* SAMPLING_H_ */
