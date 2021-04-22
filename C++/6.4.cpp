#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>


using std::cout;
using std::cin; 
using std::setw;
using std::sort; 
using std::string;

class IPV_4 {
private:
uint32_t one: 8; 
uint32_t two: 8; 
uint32_t three: 8; 
uint32_t four: 8; 
public:
void print() {
   cout << this->one << '.' << this->two << '.' << this->three << '.' << this->four << '\n';  
}

void random() {
   this->one = rand() % 255 + 1;
   this->two = rand() % 255 + 1;
   this->three = rand() % 255 + 1; 
   this->four = rand() % 255 + 1;
}

int get(int k = 1) const {
   if(k == 1) return this->one;
   if(k == 2) return this->two;
   if(k == 3) return this->three;
   if(k == 4) return this->four;
   return 0;
}

};

bool sravnenie(const IPV_4& a, const IPV_4& b) {
   if(a.get() == b.get()){
      if(a.get(2) == b.get(2)){
         if(a.get(3) == b.get(3)) return a.get(4) < b.get(4);
         return a.get(3) < b.get(3);
      }
      return a.get(2) < b.get(2);
   }
   return a.get() < b.get(); 
} 

int main() {
   srand(time(0));
   int size; 
   cout << "Enter number of IP, which was genarating: "; 
   cin >> size;
   IPV_4* array_ip = new IPV_4[size];
   for(int i = 0; i < size ;i++) {
      array_ip[i].random(); 
      array_ip[i].print();
   }
   cout << "\nBy class:\n";
   sort(array_ip, array_ip + size, sravnenie);
   int i = 0;
   while(true) {
      cout << "Class A: " << '\n'; 
      while(i < size && array_ip[i].get() <= 127) {
         array_ip[i].print(); 
         i++;
      }
      cout << "Class B: " << '\n';
      while(i < size && array_ip[i].get() >= 128 && array_ip[i].get() <= 191){
        array_ip[i].print(); 
        i++; 
      } 
      cout << "Class C:  " << '\n';
      while(i < size && array_ip[i].get() >= 192 && array_ip[i].get() <= 223){
         array_ip[i].print();
         i++;
      }
      cout << "Class D:  " << '\n';
      while(i < size && array_ip[i].get() >= 224 && array_ip[i].get() <= 239) {
         array_ip[i].print();
         i++;
      }
      cout << "Class E:  " << '\n';
      while(i < size && array_ip[i].get() >= 240 && array_ip[i].get() <= 247) {
         array_ip[i].print();
         i++;
      }
      break;  
   }

   delete[] array_ip; 
}