#include <iostream>
#include <iomanip>
#include <cmath>
using std::cout; 
using std::cin; 
using std::setw;
using std::abs;

double f1(double x, double s, double t) {
   return s * ((x * x)/(log(pow(x,t)) + cos(pow(x, 1/3.0 )) * cos(pow(x, 1/3.0))));
}

double integral(double(*f)(double, double, double), double a, double b,double s, double t, double eps) {
int n = 10;
double x0 = 0;
double x1 = 0;
double shag = 0; 
while(true) {
      double shag = (b - a) / (n / 2);
      double sum = 0; 
         for(double klon = shag; klon <= b; klon+= shag) {
            sum += f(a + klon, s, t);  
         }
      double x0 = shag * sum; 

   shag = (b - a) / n;
      sum = 0; 
      for(double klon = shag; klon <= b; klon+= shag) {
         sum += f(a + klon, s, t);  
      }
   double x1 = shag * sum; 

   if(abs(x1 - x0) < eps){
      return x1;
   }
   n*= 2;
}
}

int main() {
double a = 2.63;
double b = 3.10;
double eps = 0.000001;
   for(double s = 1, t = 1; t <= 3; t+= 1) {
      double x0 = 0;
      x0 = integral(f1, a, b, s, t, eps); 
      cout << s << setw(10) << t << setw(10) << x0 << '\n';
      
   }
      

}


