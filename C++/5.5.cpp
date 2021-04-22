#include <iostream>
#include <iomanip>
#include <cmath>
using std::cout; 
using std::cin; 
using std::setw;
using std::abs;

//typedef double(*help)(double) ; 

double f1(double x, double s = 0) {
    return (x - 1) * (x - 1) - 5;
}


double f2(double x, double s) {
    return x * x - sin(5 * pow(x , s));
}

//функция считает производную 1 и 2 порядка
double derivative(double x, double s, double(*f)(double, double), int p) {
    double h = 0.001; 
    if(p == 1) return (f(x + h, s) - f(x, s)) / h; 
    return (derivative(x + h, s, f2, 1) - derivative(x, s,  f2, 1)) / h;
}

double find_koren(double a, double b, double eps, double(*f)(double, double), double s = 0) {
    double x0 = 0;
    //выбираю начальное приближение 
    if((f(a, s) * derivative(a, s, f, 2)) > 0) x0 = a; 
    else x0 = b;
    //подбираю корень до указанной точности
    while(abs(f(x0, s) / derivative(x0, s,  f, 1)) > eps) {
        x0 = x0 - f(x0, s) / derivative(x0, s, f, 1);
    }
return x0; 
}


int main(){
    double eps = 0.000001;
    double a = -3; 
    double b = 0; 
    double koren_1 = find_koren(a, b, eps, f1);
    cout << "Koren 1 yravnenia = " << koren_1 << '\n'; 
   
    double a_1 = 0.5; 
    double b_1 = 0.8;
    double s = 0.7; 
    while(s <= 1.6) {
      double x0 = find_koren(a_1, b_1, eps, f2, s); 
      cout << s << setw(20) << x0 << setw(30) << "x^2 - sin(5x^s)" << setw(15) << '\n'; 
       s+= 0.3;
      } 

}
