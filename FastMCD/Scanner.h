#ifndef SCANNER_H_
#define SCANNER_H_

#include<fstream>
#include<string>
#include "Eigen/Dense"
#include "Sampling.h"
using namespace std;
using namespace Eigen;

extern MatrixXd data;

class Scanner {
public:
	Scanner() {};
	~Scanner() {};
	int file(int argc, char **argv);
	void loadfile(char **argv);
	void split(const string& s, int rowNum);
	char deliminator = ',';
	int colNum = 1;

};


#endif /* SCANNER_H_ */
