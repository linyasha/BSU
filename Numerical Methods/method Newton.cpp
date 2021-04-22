#include <iostream>
#include <functional>
#include <vector>
#include <cmath>
#include <exception>
#include <iomanip>

using std::exception;
using std::cout; 
using std::cin; 
using std::setw;
using std::vector; 
using std::fabs;
using std::function;


const double eps = 0.00000000001;
const int iter = 100;

//!!!!!!!!!!!!!!!!!!!!!!!
// double derivative(function<double(double)> func, vector<double> x) {
//     double h = 0.001; 
//     return (func(x + h) - func(x)) / h;
// }
//!!!!!!!!!!!!!!!!!!!!!!!!!!!

double f1(double x1, double x2)
{
   return (pow(x1, 2) * pow(x2, 2) - 3 * pow(x1, 2) - 6 * pow(x2, 3) + 8);
}

double f2(double x1, double x2)
{
   return (pow(x1, 4) - 9 * x2 + 2);
}

void show_matrix(vector<vector<double>> a)
{
   for (int i = 0; i < a.size() ; i++)
   {
      for (int j = 0; j < a[0].size() ; j++)
      {
         cout << setw(10) << a[i][j];
      }
      cout << "\n";
   }
}



bool method_Newton(const vector<function<double(double,double)>>& f, vector<double> approximation , vector<double>& result, int& counter) {
      
   vector<double> delta;
   vector<double> old_approximation(approximation.size(), 0);   
   for (; counter < iter; counter++) {
         for(int i = 0; i < approximation.size(); i++) {
            old_approximation[i] = approximation[i]; 
         }
         vector<vector<double>> array (f.size(), vector<double>(approximation.size(), 0)); 

         //заполняю матрицу якоби\\

         cout << "Матрица Якоби:\n";
         show_matrix(array);
         cout << "\n";
         double *x = methodGauss (array, n);

         cout << "deltaX:\n";
         cout << x[0] << " " << x[1] << "\n";

         k1 += x[0];
         k2 += x[1];
         cout << "k1 = " << k1 << " k2 = " << k2 << "\n";


         if (fabs(f1(old_k1, old_k2)) >= fabs(f2(old_k1, old_k2))) delta1 = fabs(f1(old_k1, old_k2));
         else delta1 = fabs(f2(old_k1, old_k2));


         if (fabs(k1) >= 1)
         {
            if (fabs((k1 - old_k1) / k1) >= fabs((k2 - old_k2) / k2)) delta2 = fabs((k1 - old_k1) / k1);
            else delta2 = fabs((k2 - old_k2) / k2);
         }
         if (fabs(k1) < 1)
         {
            if (fabs(k1 - old_k1) >= fabs(k2 - old_k2)) delta2 = fabs(k1 - old_k1);
            else delta2 = fabs(k2 - old_k2);
         }
         cout << "delta1 = " << delta1 << " delta2 = " << delta2 << "\n";
         
         if ((fabs(delta1) <= eps) && (fabs(delta2) <= eps)) break;
         cout << "---------------------------------------------\n";
      }
}


// }

int main()
{
   system("chcp 65001");
   int r;
   double k1, k2; 
   int counter = 0; 
   cout << "Какое начальное приближение взять 1:(-1.5; 1.5) 2:(-1; 1): ";
   cin >> r;
   switch (r)
   {
      case 1:
         k1 = -1.5;
         k2 = 1.5;
      break;
      case 2:
         k1 = -1;
         k2 = 1;
      break;
   }

   vector<function<double(double,double)>> func {f1, f2}; 
   vector<double> approximation {k1, k2}; 
   vector<double> result(approximation.size(), 0); 
   method_Newton(func, approximation, result, counter);

}