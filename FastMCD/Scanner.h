#ifndef SCANNER_H_
#define SCANNER_H_

#include<fstream>
#include<string>
#include "Eigen/Dense"
using namespace std;
using namespace Eigen;

class Scanner {
public:
	Scanner() {};
	~Scanner() {};
	int file(int argc, char **argv);
	void loadfile(istream& in, MatrixXd *data);
	void split(const string& s, MatrixXd *data, int rowNum);
	char deliminator = ';';
	int colNum = 7;

};


#endif /* SCANNER_H_ */
