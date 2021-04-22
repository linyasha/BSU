#include <iostream>
#include <string>
#include <assert.h>
#include <forward_list>
#include <algorithm>
using std::find;
using std::cout;
using std::cin; 
using std::string; 
using std::forward_list;



template<typename T>
forward_list<T> repeat(const forward_list<T>& list_1, const forward_list<T>& list_2) {
   forward_list<T> new_list; 
   for(T symbol_of_list1 : list_1) { 
      auto help = find(list_2.begin(), list_2.end(), symbol_of_list1); 
      if(help != list_2.end()) {
         help = find(new_list.begin(), new_list.end(), symbol_of_list1); 
         if(help == new_list.end()) new_list.push_front(symbol_of_list1);
      }   
   }  
   return new_list; 
}

int main() {
   forward_list<char> list_1 = {'h', 'e', 'l', 'l', '2'};
   forward_list<char> list_2 = {'l', 'w', 'e', 'a', 's', 'd', 'h', 'l', '1'};
   forward_list<char> result_list = repeat<char>(list_1, list_2);
   
   for(char x : result_list) {
      cout << ' ' <<  x; 
   }
}


