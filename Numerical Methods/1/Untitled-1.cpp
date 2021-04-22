#include <gaus_method.cpp>

const double EPS = 0.00000001; 

int main() {
      int rangMatrix = 0; 
      vector<vector<double>> matrix; 
      vector<double> x; 
      matrix_readFile(matrix, rangMatrix);
      cout << "Resulting matrix: " << '\n';
      coutMatrix(matrix); 
      if(slu_gaus(matrix, x)) {
            cout << "Answer : "; 
            for(int i = 0; i < x.size(); i++) {
                  cout << "  " << x[i]; 
            }
            cout << '\n' << "Error: " << residual(matrix, x);
            matrix_writeFile(x); 

      }
       
}

void matrix_readFile(vector<vector<double>>& matrix, int& rangMatrix) {
      ifstream matrixFile("Matrix.txt");
      matrixFile >> rangMatrix; 
      matrix = vector<vector<double>>(rangMatrix, vector<double>(rangMatrix + 1, 0));
      for(int i = 0; i < rangMatrix; i++) {
            for(int j = 0; j < rangMatrix + 1; j++) {
                  matrixFile >> matrix[i][j]; 
            }
      }
}

void matrix_writeFile(vector<double>& x) {
      ofstream matrix_file("Solution.txt");
      if(x.size() == 0) {
            matrix_file << "UNDEFINED";
            return; 
      }
      for(int i = 0; i < x.size(); i++) {
            matrix_file << ' ' << x[i]; 
      } 
}

