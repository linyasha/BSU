#include "SLE.h"


bool slu_gaus(vector<vector<double>> matrix, vector<double>& x) {
      for(int i = 0; i < matrix.size(); i++) {
            
            try {
                  permutation_max(matrix, i);
            }
            catch(std::domain_error& e) {
                  cout << e.what();  
                  return 0;
            }
            double milty = 1 / matrix[i][i];
            for(int g = i; g < matrix[0].size(); g++) {
                  matrix[i][g] *= milty; 
            } 
            vector<double> help_line = matrix[i];  
            for(int k = i + 1; k < matrix.size(); k++) {
                  milty = (-matrix[k][i]); 
                  for(int e = 0; e < matrix[0].size(); e++) {
                      matrix[k][e] += help_line[e] * milty; 
                  }

            }
      } 
      creat_solution_vector(matrix, x);
      return 1; 
}

double residual(const vector<vector<double>>& matrix, const vector<double>& x) {
      double max = 0; 
      for(int i = 0; i < matrix.size(); i++) {
            double help = 0; 
            for(int j = 0; j < x.size(); j++) {
                  help += matrix[i][j] * x[j];
            }
            if(fabs(help - matrix[i][matrix[0].size() - 1]) > max) max = fabs(help - matrix[i][matrix[0].size() - 1]);
      }
      return max; 

}

void coutMatrix(vector<vector<double>>& matrix) {
      for(int i = 0; i < matrix.size(); i++) {
            for(int j = 0; j < matrix[0].size(); j++) {
                  cout << "   " << matrix[i][j]; 
            }
            cout << '\n'; 
      }
}

void permutation_max(vector<vector<double>>& matrix, int j) {
      double max = fabs(matrix[j][j]); 
      int coord_max = j; 
      for(int i = j + 1; i < matrix.size(); i++) {
            if(fabs(matrix[i][j]) > max) {
                  max = fabs(matrix[i][j]);
                  coord_max = i; 
            }
      }
      if (max <= eps) {
            throw std::domain_error("Solution not found"); 
      }
      else {
            if(coord_max != j) matrix[coord_max].swap(matrix[j]);
      }

}

void creat_solution_vector(vector<vector<double>> matrix,vector<double>& x) {
      vector<double> help_vector (matrix.size(), 0); 
      for(int i = matrix.size() - 1; i >= 0; i--) { 
            help_vector[i] = matrix[i][matrix[0].size() - 1] / matrix[i][i]; 
            for(int j = i - 1; j >= 0; j--) {
                  matrix[j][matrix[0].size() - 1] -= matrix[j][i] * help_vector[i];
            }
      }
      x = help_vector;        
}
