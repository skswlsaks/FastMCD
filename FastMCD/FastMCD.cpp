#include <iostream>
#include "Scanner.h"
#include "Eigen/Dense"
using namespace Eigen;

using namespace std;

typedef Matrix<double, Dynamic, Dynamic, RowMajor> mat;

/*struct veccomp {
	bool operator() (const vec &l, vec &r) {
 return l.;
	}
 };*/

int main(int argc, char **argv) {
    //cout << "Hello World!" << endl;
    //cout << argv[1] << endl;
    
    /*Scanner* scanner = new Scanner();
     scanner -> file(argc, argv);
     delete scanner;*/
    
    mat c(2,1);
    MatrixXd d(3,2);
    d << 7,5,3,6,7,8;
    c << 2,3;
    cout << d*c << endl;
    nth_element(d.data(), d.data()+d.rows()-1, d.data() + d.size());
    nth_element(c.data(), c.data()+c.rows()-1, c.data() + c.size());
    //cout << c << endl;
    return 0;
}
