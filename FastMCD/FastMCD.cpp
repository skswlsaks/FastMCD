#include <iostream>
#include "Scanner.h"
#include "Eigen/Dense"
#include <vector>
using namespace Eigen;

using namespace std;

//typedef Matrix<double, Dynamic, Dynamic, RowMajor> mat;

/*struct veccomp {
	bool operator() (const vec &l, vec &r) {
 return l.;
	}
 };*/


/*bool mySort(pair<double, int> p1, pair<double, int> p2){
    return p1.first < p2.first;
}*/

int main(int argc, char **argv) {
    //cout << "Hello World!" << endl;
    //cout << argv[1] << endl;
    
    /*Scanner* scanner = new Scanner();
     scanner -> file(argc, argv);
     delete scanner;*/
    
    /*mat c(2,1);
    MatrixXd d(3,2);
    d << 7,5,3,6,7,8;
    c << 2,3;
    cout << d*c << endl;
    nth_element(d.data(), d.data()+d.rows()-1, d.data() + d.size());
    nth_element(c.data(), c.data()+c.rows()-1, c.data() + c.size());
    //cout << c << endl;*/
    
    /*MatrixXd d(3,2);
    d << 7,5,3,6,7,8;
    cout << d << endl;
    d.resize(3, 3);
    cout << d << endl;*/
    
    /*pair<double, int> p1(1.23, 9);
    pair<double, int> p2(9.003, 1);
    pair<double, int> p3(4.234, 3);
    
    vector<pair<double, int>> vec;
    vec.push_back(p1);
    vec.push_back(p2);
    vec.push_back(p3);
    
    for(int i = 0; i < vec.size(); i++)
    {
        cout << vec[i].first << "," << vec[i].second << " ";
    }
    cout << "\n" << endl;
    
    sort(vec.begin(), vec.end(), mySort);
    
    for(int i = 0; i < vec.size(); i++)
    {
        cout << vec[i].first << "," << vec[i].second << " ";
    }
    cout << "\n" << endl;
    */
    return 0;
}
