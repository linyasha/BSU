#include <iostream>
#include <string>
#include <assert.h>

using std::cout;
using std::cin; 
using std::string; 


char* func(const char* l1, const char* l2) {
   int size = 0; 
   while(l1[size] != '\0') {
      size++;
   }
   char* l = new char[size + 1]{'\0'}; 
   for(int i = 0, o = 0; i < size; i++) {
      char help = l1[i]; 
      for(int j = 0; l2[j] != '\0'; j++) {
         if(help == l2[j]) {
            bool repeat = 1;
            for(int z = 0; z < o; z++) {
               if(help == l[z]) {
                  repeat = 0;
                  break;
               }
            }
            if(repeat){
               l[o] = help;  
               o++;
            }
            break;
         }
      }
   }
   return l;
   
}

int main() {
   int n = 10; 
   char* l1 = new char[n] {"aglgyvnsg"}; 
   char* l2 = new char[n] {"vnbhdfafi"}; 
   char* l = func(l1, l2);
   for(int i = 0; l[i] != '\0'; i++) {
      cout << l[i] << ' '; 
   }
   delete[] l1;
   delete[] l2;
   delete[] l;
}