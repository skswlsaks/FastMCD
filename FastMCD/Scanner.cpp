#include "Scanner.h"
#include <iostream>
#include "Eigen/Dense"
#include <cstring>

using namespace std;
using namespace Eigen;


void Scanner::split(const string& s, MatrixXd *data, int rowNum) {

	int count = 0;
	int i = 0;
	int j = (int) s.find(deliminator);

	while(j >= 0) {

		string tmp= s.substr(i, j-i);
		(*data)(rowNum-1, count) = atof(tmp.c_str());
		cout << (*data)(rowNum-1, count) << endl;
		i = ++j;
		j = (int) s.find(deliminator, j);

		++count;

//		if (j < 0) {
//			double ss = atof(s.substr(i, j-i).c_str());
//			(*data)(rowNum-1, count) = ss;
//		}

	}
}

void Scanner::loadfile(istream& in, MatrixXd *data) {
	string tmp;

	int rowNum = 1;
	while (!in.eof()) {

		getline(in, tmp, '\n');

		split (tmp, data, rowNum);

		tmp.clear();
		++rowNum;
		if (!in.eof()) {
			(*data).resize(rowNum, colNum);
		}


	}
}


int Scanner::file(int argc, char **argv) {

	if (argc < 2)
			return -1;

	ifstream in (argv[1]);

	if (!in)
		return -1;

//	string tmp;
//	char *tok;
//	int count = 0;
//	getline(in, tmp, '\n');
//	tok = strtok(*tmp.c_str(), deliminator);
//	while (tok != NULL) {
//		tok = strtok(NULL, ';');
//		++count;
//	}

	MatrixXd *data = new MatrixXd;
	(*data).resize(1, colNum);

	loadfile(in, data);

		// Do Something;

//	for (vector<double*>::iterator p = data.begin();
//		 p != data.end(); p++) {
//		delete[] *p;
//	}
	delete data;

	return 0;
}
