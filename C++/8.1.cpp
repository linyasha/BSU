#include <iostream>
#include <initializer_list>
#include <cassert>
#include <ctime>
#include <fstream>


const unsigned int size = 1000000;

using std::cin; 
using std::cout; 
using std::initializer_list;
using std::istream;
using std::ostream;
using std::ofstream;
using std::ifstream;

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
      assert(!(quauntity < 0));
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
      assert(!(quauntity < 0));
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
            not_initialized = 1;|
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
            not_initialized = 1;|
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
      assert(!(i >= this->quauntity) && !(i < 0));
      return this->begin_array[i];
   }

   T& operator[](int i) {
      assert(!(i >= this->quauntity) && !(i < 0));
      not_initialized = 0; 
      return (this->begin_array[i]);
   }
   
   template<typename D>
   friend istream& operator>>(istream& out, vector<D>& a);

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
      this->begin_array[this->quauntity] = value; 
      
   }
  
   ~vector() {
      delete[] this->begin_array;
   }

};

void random_value(vector<int>& other) {
      for(int i = 0; i < other.size(); i++) {
         other.gbegin()[i] = rand() % 1001;
      }
}

template<typename T>
ostream& operator<<(ostream& out, vector<T>& a) { 
      for(int i = 0; i < a.size(); i++) {
         out << a[i] << ' ';
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


int main() {
   srand(time(0));
   //заполняю файл числами
   ofstream number("File.txt"); 
   for(int i = 0; i < size; i++) {
      number << ' ' << rand() % 10001;
   }
   number.close();
   
   ifstream fout("File.txt"); 
   vector<int> a (10001, 0); 
   while(!fout.eof()) {
      int help; 
      fout >> help; 
      if(help >= 10001 || fout.fail()) break; 
      a[help] += 1; 
   }
   vector<int> last; 
   for(int j = 1; j < 10001; j++) {
      if(a[j] > 1) last.push_back(j); 
   }
   cout << " =^o^= ";
}