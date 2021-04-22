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

//!!!!!!!!!!!!!!!!!!!!!!!
double derivative(function<double(double)> func, vector<double> x) {
    double h = 0.001; 
    return (func(x + h) - func(x)) / h;
}
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


// void show_array_rand(double **a, int *IOR, int n)
// {
//    for (int i = 0; i < n; i++)
//    {
//       for (int j = 0; j < n; j++)
//       {
//          cout << setw(10) << a[IOR[i] - 1][j];
//       }
//       cout << "  |" << setw(8) << a[IOR[i] - 1][n];
//       cout << "\n";
//    }
// }






bool method_Newton(   , double k1, double k2, int k, double&  ) {

}

int main()
{
   system("chcp 65001");
   int r;
   double k1, k2, k;
   double delta1, delta2;
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
   cout << "Установите ограничение на число итераций : ";
   cin >> k;

   cout << "k1 = " << k1 << " k2 = " << k2 << "\n";
   cout << f1(k1, k2);
   cout << "\n";
   cout << f2(k1, k2);
   cout << "\n";
   method_Newton();
   
   delta1 = 0;
   delta2 = 0;
   double old_k1, old_k2;

   for (k = 0; k < 1000; k++)
   {
      old_k1 = k1;
      old_k2 = k2;

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
   cout << "\n" << "k1 = " << k1 << " k2 = " << k2 << "\n";
   
}
