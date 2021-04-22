#include <iostream>
#include <initializer_list>
#include <cassert>
#include <ctime>
#include <cmath>
#include <vector>

const double PI = 4.*atan(1.);
using std::cin; 
using std::cout; 
using std::initializer_list;
using std::istream;
using std::ostream;
using std::vector;

class Complex {
   private:
      double modulee;
      double angle;

   public:
      Complex() {
         this->angle = 0;
         this->modulee = 0;
      }

      Complex(const Complex& other) {
         this->angle = other.angle;
         this->modulee = other.modulee;
      }

      void operator=(const Complex& other) {
         this->angle = other.angle;
         this->modulee = other.modulee;
      } 

      Complex(double module, double angle) {
         assert(angle >= 0 && angle <= 360 && module >= 0);
         this->angle = angle;
         this->modulee = module;
      }

      double get_module() const {
         return this->modulee;
      }
      void set_module(double new_module) {
         assert(new_module >= 0);
         this->modulee = new_module;
      }

      double get_angle() const {
         return this->angle;
      }
      void set_angle(double new_angle) {
         assert(new_angle >= 0 && new_angle <= 360);
         new_angle = new_angle * PI / 180;
         this->angle = new_angle;
      }

      double re() const {
         return this->modulee * cos(this->angle);
      }
      
      double im() const{
         return this->modulee * sin(this->angle);
      }
      Complex operator+(const Complex& other) const {
         Complex  new_coplex;
         //this->help.push_back(new_coplex); 
         double module = (sqrt(pow(this->re() + other.re(), 2) + pow(this->im() + other.im(), 2)));
         double angle = acos((this->re() + other.re()) / module);
         new_coplex.set_module(module); 
         new_coplex.set_angle(angle);
         return new_coplex;
      
      }

      Complex operator-(const Complex& other) const {
         Complex  new_coplex;
         //this->help.push_back(new_coplex); 
         double module = (sqrt(pow(this->re() - other.re(), 2) + pow(this->im() - other.im(), 2)));
         double angle = acos((this->re() - other.re()) / module);
         new_coplex.set_module(module); 
         new_coplex.set_angle(angle);
         return new_coplex;
      
      }

      Complex operator*(const Complex& other) const {
         Complex  new_coplex;
         double angle = this->angle + other.angle; 
         while(angle > 2 * PI) {
            angle -= 2 * PI;
         }
         new_coplex.set_module(this->modulee * other.modulee); 
         new_coplex.set_angle(angle);
         return new_coplex;
      
      }

      Complex operator/(const Complex& other) const {
         Complex  new_coplex;
         double angle = this->angle - other.angle; 
         while(angle < 0) {
            angle += 2 * PI;
         }
         
         new_coplex.set_module(this->modulee / other.modulee); 
         new_coplex.set_angle(angle);
         return new_coplex;
      
      }

      Complex operator^(int n) {
         Complex new_complex;
         double angle = this->angle * n;
         while(angle > 2 * PI) {
            angle -= 2 * PI;
         }
         new_complex.set_module(pow(modulee, n)); 
         new_complex.set_angle(angle);
         return new_complex;
      }

            
      ~Complex() { 
      }

};

ostream& operator<<(ostream& out, Complex& a) { 
      out << "Module: " << a.get_module() << '\n' << "Angle: " << (a.get_angle() * 180 / PI)  << "degrees" << '\n';
      return out;
}

istream& operator>>(istream& out, Complex& a) { 
      double angle, module; 
      // while(true) {
      //    cout << "Enter angle(0 - 360): ";
        out >> angle;
      //    if(angle >= 0 || angle <= 360) break;
      //    cout << "Try again =(" << '\n';   
      // }
      // while(true) {
      //    cout << "Enter module: ";
         out >> module;
      //    if(module > 0) break;
      //    cout << "Try again =(" << '\n';   
      // }
      angle = angle * PI / 180;
      a.set_angle(angle); 
      a.set_module(module); 
      return out;
}
Complex sqrt(const Complex& other) {
         Complex new_complex; 
         double angle = (other.get_angle() + 2 * PI) / 2;
         new_complex.set_module(sqrt(other.get_module())); 
         new_complex.set_angle(angle);
         return new_complex;
         return new_complex;
      }






int main() {
   Complex a(7.5, 9);
   Complex b; 
   cout << a;
   cin >> b; 
   Complex c = a + b;
   Complex d = a - b; 
   Complex f = a / c; 
   Complex g = a * f; 
   Complex h = a^5; 
   Complex k = sqrt(c); 
   cout << k;
}