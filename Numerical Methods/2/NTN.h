#ifndef NTN
#define NTN

#include <iostream>
#include<vector>
#include <functional>
#include <cmath>
#include <iomanip>



using std::cout; 
using std::cin; 
using std::vector; 
using std::fabs;
using std::function;


bool solve_snle(const vector<function<double(vector<double>)>>& fu, vector<double> approximation , double eps, vector<double>& result, int& counter);
double derivative(function<double(vector<double>)> f, vector<double> x, int coordinate, double eps);
bool check_free(vector<double> free_odds, double eps);
bool step_check(std::vector<double> x, vector<double> resultX, double eps);

#endif
