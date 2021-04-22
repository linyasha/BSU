#include <iostream>
#include <initializer_list>
#include <cassert>
#include <ctime>

using std::cin; 
using std::cout; 
using std::initializer_list;
using std::istream;
using std::ostream;

const int R = 64;


class R64_UNSINT_10 {
   private:
      int number_of_digits;
      short* main_value;  
   public:

      bool is_empty() const{
         return this->main_value == nullptr;
      }

      int nofd() const {
         return this->number_of_digits;
      }

      R64_UNSINT_10() {
         main_value = nullptr;
         number_of_digits = 0;
         
      }

      R64_UNSINT_10(long long number) {
         assert(number >= 0); 
         this->main_value = new short[R]  { 0 };
         this->number_of_digits = 0;
         if(number == 0) this->number_of_digits++;
         for(int i = R - 1; number != 0; i--){
            main_value[i] = number % 10; 
            number /= 10;
            this->number_of_digits += 1; 
         }
         
      }

      R64_UNSINT_10(const R64_UNSINT_10& other) {
         if(other.is_empty()) {
            this->main_value = nullptr;
            this->number_of_digits = 0;

         }
         else {
            main_value = new short[R]  { 0 };
            number_of_digits = 0;
            for(int i = R - 1; i >= R - other.number_of_digits; i--) {
               main_value[i] = other.main_value[i]; 
               number_of_digits += 1;
            }
         }
      }

      void operator=(const R64_UNSINT_10& other) {
         delete[] this->main_value; 
         if(other.is_empty()) {
            this->main_value = nullptr;
            this->number_of_digits = 0;
            return;

         }
         main_value = new short[R]  { 0 };
         number_of_digits = 0;
         for(int i = R - 1; i >= R - other.number_of_digits; i--) {
            this->main_value[i] = other.main_value[i]; 
            number_of_digits += 1;
         }
      }

      void operator=(long long number){
         assert(number >= 0); 
         delete[] this->main_value; 
         main_value = new short[R]  { 0 };
         this->number_of_digits = 0;
         if(number == 0) this->number_of_digits++;
         for(int i = R - 1; number != 0; i--){
            main_value[i] = number % 10; 
            number /= 10; 
            this->number_of_digits += 1; 
         }
      }

      const short& operator[](int i) const {
         assert(i >= 0 && i < R);
         return this->main_value[i];
      }

   
      short& operator[](int i) {
         assert(i >= 0 && i < R);
         return (this->main_value[i]);
      }

      R64_UNSINT_10 operator+(const R64_UNSINT_10& other) {
         R64_UNSINT_10 new_number = 0;
         new_number.number_of_digits = 0; 
         int size = 0; 
         if(this->number_of_digits >= other.number_of_digits) size = this->number_of_digits;
         else size = other.number_of_digits; 
         for(int i = 1, j = R - 1; i <= size; i++, j--) {
            new_number[j] += this->main_value[j] + other.main_value[j];
            if(new_number[j] >= 10){
               new_number[j - 1] += 1; 
               new_number[j] -= 10;
               new_number.number_of_digits++;
               if(i == size) new_number.number_of_digits++;
               continue;
            }
            new_number.number_of_digits++;
         }
         return new_number; 
      }

      R64_UNSINT_10 operator*(const R64_UNSINT_10& other) {
         R64_UNSINT_10 new_number = 0;
         int help = 0;   
         if(this->number_of_digits >= other.number_of_digits) help = other.number_of_digits;
         else help = this->number_of_digits; 
         for(int i = R - 1; i >= R - this->number_of_digits; i--) {
            for(int j = R - 1, k = i; j >= R - other.number_of_digits; j--, k--) {
               new_number[k] += other[j] * this->main_value[i];
               if((R - k) > help) help = R - k;
               while(new_number[k] >= 10) {
                  new_number[k - 1] += 1; 
                  new_number[k] -= 10; 
                  help = R - k + 1; 
               }
            }
         } 
         new_number.number_of_digits = help; 
         return new_number; 
      }

      ~R64_UNSINT_10() {
         delete[] main_value;
      }

}; 

ostream& operator<<(ostream& out, R64_UNSINT_10& a) { 
   for(int i = R - a.nofd(); i < R; i++) {
      out << a[i];
   }
      return out;
}

istream& operator>>(istream& out, R64_UNSINT_10& a) { 
      long long help; 
      out >> help;
      a = help;
      return out;
}

R64_UNSINT_10 pow(const R64_UNSINT_10& other, int n) {
   R64_UNSINT_10 new_number = other; 
   for(int i = 1; i < n; i++) {
      new_number = new_number * other; 
   }
   return new_number;

}

int main() {
   R64_UNSINT_10 a(8212890625);
   R64_UNSINT_10 b = pow(a, 5);
   cout << b; 
   
}
