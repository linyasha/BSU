#include <iostream>
#include <string>
#include <initializer_list>
#include <cassert>
#include <iomanip>
#include <ctime>
using std::cout;
using std::cin; 
using std::initializer_list;
using std::ostream;
using std::istream;
using std::string;
using std::setw;

char* number_to_string(int n) {
   int size = 0;
   int n_coppy = n;
   while(n_coppy != 0) {
      n_coppy /= 10; 
      size++;
   }
   char* help = new char[size + 1] {'\0'}; 
   size--;
   while(n != 0) {
      int k = n % 10; 
      n /= 10; 
      help[size] = k + 48; 
      size--;
   }
   return help;
}


template<typename T>
class vector {
private:
   T* begin_array; 
   int quauntity; 
   bool not_initialized;
public:

   int size() const {
      return this->quauntity;
   }

   T* gbegin() {
      return this->begin_array; 
   }

   vector() {
      this->begin_array = nullptr; 
      this->quauntity = 0; 
      not_initialized = 1;
   }

   vector (const vector& other) {
      if(other.quauntity == 0) {
         this->begin_array = nullptr;
      }
      else this->begin_array = new T[other.quauntity];
      this->quauntity = other.quauntity;
      if(other.not_initialized) {
         this->not_initialized = 1;
         return;
      }
      for(int i = 0; i < other.quauntity; i++) {
         begin_array[i] = other.begin_array[i];
      }
      this->not_initialized = 0;
   }

   vector(int quauntity) {
      assert(quauntity >= 0);
      if(quauntity == 0) {
         this->begin_array = nullptr;
         this->quauntity = 0; 
      } 
      else{
         this->quauntity = quauntity; 
         this->begin_array = new T[quauntity]; 
      }
      not_initialized = 1;
   }

   vector(int quauntity, T value) {
      assert(quauntity >= 0);
      this->quauntity = quauntity; 
      if(quauntity == 0) {
         this->begin_array = nullptr; 
         not_initialized = 1;
      }
      else { 
         this->begin_array = new T[this->quauntity];
         this->not_initialized = 0;
         for(int i = 0; i < this->quauntity; i++) {
            begin_array[i] = value;
         } 
      }
   }

   vector(initializer_list<T> other) {
      this->quauntity = other.size();
      if(this->quauntity == 0) {
         this->begin_array = nullptr;
         not_initialized = 1;
      } 
      else {
         this->begin_array = new T[this->quauntity];
         this->not_initialized = 0;
         for(int i = 0; i < this->quauntity; i++) {
            begin_array[i] = *(other.begin() + i);
         } 
      }
   }

   void operator=(initializer_list<T> other) {
      if(other.size() != this->quauntity) {
         delete[] this->begin_array;
         this->quauntity = other.size();
         if(this->quauntity == 0) {
            this->begin_array = nullptr; 
            not_initialized = 1;
            return;   
         }
         this->begin_array = new T[this->quauntity];
      }
      if(this->quauntity != 0) not_initialized = 0;
      else not_initialized = 1;
      for(int i = 0; i < this->quauntity; i++) {
         begin_array[i] = *(other.begin() + i);
      }
   }

   void operator=(const vector& other) {
      if(other.size() != this->quauntity) {
         delete[] this->begin_array;
         this->quauntity = other.size();
         if(this->quauntity == 0) {
            this->begin_array = nullptr; 
            not_initialized = 1;
            return;   
         }
         this->begin_array = new T[this->quauntity];
      }
      if(this->quauntity != 0) not_initialized = 0;
      else not_initialized = 1;
      for(int i = 0; i < this->quauntity; i++) {
         begin_array[i] = other.begin_array[i];
      }
   }

   const T& operator[](int i) const {
      try{
         if(i >= this->quauntity || i < 0) throw -1; 
      }
      catch(int a) {
         
         cout << "Invalid number of coloumns" << '\n'; 
         throw; 
      }
      return this->begin_array[i];
   }

   T& operator[](int i) {
      try{
         if(i >= this->quauntity || i < 0) throw -1; 
      }
      catch(int a) {
         cout << "Invalid number of coloumns" << '\n';
         throw; 
      }
      not_initialized = 0; 
      return this->begin_array[i];
   }

   void resize(int other_size) {
      assert(!(other_size < 0));
      if(other_size == this->quauntity) return;
      if(other_size == 0) {
         delete[] this->begin_array;
         this->quauntity = 0;
         this->begin_array = nullptr;
         not_initialized = 1; 
      }
      else{   
         T* new_array = new T[other_size];
         if(!(this->not_initialized)) {
            int k = 0;
            if(other_size < this->quauntity) k = other_size;
            else k = this->quauntity;
            for(int i = 0; i < k; i++) {
               new_array[i] = this->begin_array[i];
            }
         }
         this->quauntity = other_size;
         delete[] this->begin_array;
         this->begin_array = new_array;
      }
   }

   void push_back(T value) {
      resize(this->quauntity + 1); 
      this->begin_array[this->quauntity - 1] = value;
      this->not_initialized = false;

      
   }
  
   ~vector() {
      delete[] this->begin_array;
   }

};

template<typename T>
ostream& operator<<(ostream& out, vector<T>& a) { 
      for(int i = 0; i < a.size(); i++) {
         out << setw(8) << a[i];
      }
      out << '\n'; 
      return out;
}

template<typename T>
istream& operator>>(istream& out, vector<T>& a) { 
      for(int i = 0; i < a.size(); i++) {
         out >> a[i];
      }
      return out;
}


template<typename T>
class Matrix {
   private: 
      static int number; 
      string name = "Matrix "; 
      int number_i = 0;
      int number_j = 0; 
      vector<vector<T>> strings;
   public:
      Matrix() {
         number_j = 0;
         number_i = 0; 
         number += 1;
         name += number_to_string(number); 
      }
      
   private:
      void add_string(int number) {
         for(int i = 0; i < number; i++) {
            vector<T> a(number_j, 0);  
            strings.push_back(a); 
            number_i++; 
         }
      }

   public:
      Matrix(int i, int j) {
         number_j = j;
         number += 1;
         name += number_to_string(number); 
         add_string(i); 
      }

      vector<T>& operator[](int i) {
         try{
            if(i >= number_i || i < 0) throw -1; 
         }
         catch(int a) {
            cout << "Invalid number of lines " << '\n';
            throw; 
         } 
         return strings[i]; 
      }

      const vector<T>& operator[](int i) const {
         try{
            if(i >= number_i || i < 0) throw -1; 
         }
         catch(int a) {
            cout << "Invalid number of lines " << '\n';
            throw; 
         } 
         return strings[i]; 
      }

      void resize_lines(int i) {
         assert(i >= 0); 
         if(i == number_i) return;
         if(i == 0) delete_matrix(); 
         if(i > number_i) add_string(i - number_i); 
         else {
            strings.resize(i); 
            this->number_i = i;
         }
      }

      void resize_coloumns(int j) {
         assert(j >= 0); 
         if(j == number_j) return;
         if(j == 0) delete_matrix(); 
         for(int i = 0; i < number_i; i++) {
            this->strings[i].resize(j);
         }
      }
      
      template<typename D>
      friend ostream& operator<<(ostream& out, Matrix<D>& a);
 
      template<typename Z>
      friend void random_value(Matrix<Z>& a);
      
      template<typename K>
      friend vector<K> min_vector(const Matrix<K>& p);

      void delete_matrix() {  
         this->strings.resize(0); 
         this->number_i = 0; 
         this->number_j = 0; 
      }
}; 

template<typename T>
ostream& operator<<(ostream& out, Matrix<T>& a) { 
   out << '\n' << a.name << '\n';
   for(int i = 0; i < a.number_i; i++) {
      out << a[i];
   }
   out << '\n'; 
   return out;
}

template<typename T>
void random_value(Matrix<T>& a) {
   for(int i = 0; i < a.number_i; i++) {
      for(int j = 0; j < a.number_j; j++) {
         double sum = rand() % 101;
         a[i][j] = rand() % 101 + ((rand() % 100) / 10.);
      }
   }

}

template<typename T>
vector<T> min_vector(const Matrix<T>& p) {
   int size = p.number_i; 
   vector<T> min_vector(2*size - 1); 
   for(int j = 0, k = 0, i = 0; k < 2*size - 1; k++) {
      if(j < size) {
         int min = p[i][j]; 
         for(int j_coppy = j, i_coppy = i; j_coppy >= 0; j_coppy--, i_coppy++) {
            if(p[i_coppy][j_coppy] < min) min = p[i_coppy][j_coppy];
         }
         min_vector[k] = min;
         j++;
      }
      else {
         i+= 1;
         int min = p[i][j - 1]; 
         for(int j_coppy = j - 1, i_coppy = i; i_coppy < size; j_coppy--, i_coppy++) {
            if(p[i_coppy][j_coppy] < min) min = p[i_coppy][j_coppy];
         }
         min_vector[k] = min;
      }
   }

   return min_vector; 
}

template<typename T>
int Matrix<T>::number = 0;


int main() {
srand(time(0));

Matrix<int> a(5, 5);
random_value<int>(a); 
cout << a; 
vector<int> end = min_vector<int>(a); 
cout << end;



}