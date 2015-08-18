#include <iostream>
#include "Scanner.h"
#include "Eigen/Dense"
#include <vector>
#include "Sampling.h"
#include "Calculations.h"
#include "Execution.h"
using namespace Eigen;
using namespace std;

extern MatrixXd data;

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

	Scanner* scanner = new Scanner();
	scanner->file(argc, argv);

	delete scanner;


	Sampling s;
	MatrixXd ttt = s.randomSample((int) data.cols());
	//cout << ttt << endl;
	//cout << s.addSample(ttt) << endl;
    
    Execution e;
    e.step42();
    
//
//    vector<double> vec;
//    vec.push_back(2.3);
//    vec.push_back(5.3);
//    vec.push_back(3.5);
//    cout << vec[2] << endl;
//    
//    vec.resize(2);
//    cout << vec.size() << endl;
//    vec.push_back(9);
//    cout << vec.size() << endl;
//
    
    
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

	/*
	 int t[5];
	 for (int i = 0; i < 5; ++i) {
	 t[i] = i;
	 }

	 random_shuffle(t, t+5);
	 for (int i = 0; i < 5; ++i) {
	 cout << t[i];
	 }
	 */

	return 0;
}
