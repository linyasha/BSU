#ifndef SNLE
#define SNLE

#include <iostream>
#include <vector>
#include<fstream>
#include <cmath>
#include <exception>

using std::exception;
using std::cout; 
using std::cin; 
using std::vector; 
using std::ifstream;
using std::ofstream;


bool slu_gaus(vector<vector<double>> matrix, vector<double>& x);
void coutMatrix(vector<vector<double>>& matrix);
void permutation_max(vector<vector<double>>& matrix, int j); 
void creat_solution_vector(vector<vector<double>> matrix,vector<double>& x);
double residual(const vector<vector<double>>& matrix, const vector<double>& x);




#endif
