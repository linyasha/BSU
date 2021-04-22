#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>

using std::vector; 
using std::unordered_map;
using std::pair;
using std::set;
using std::cout; 
using std::cin; 
using std::string; 
using std::ofstream;
using std::ifstream;
using std::istream;
using std::ostream;
using std::getline;

bool need_char(char a) {
   if((a >= 'a' && a <= 'z') || a == 95) return 1;
   return 0; 
}

int main() {

   ifstream old_stud("traning.cpp");

   set<string> all_keywords = {"alignas","alignof ","and","and_eq","asm","atomic_cancel","atomic_commit","atomic_noexcept","auto",
   "bitand","bitor","bool","break","case","catch","char","char8_t" ,"char16_t" ,"char32_t" ,"class","compl","concept","const",
   "consteval" ,"constexpr","constinit" ,"const_cast","continue","co_await","co_return","co_yield","decltype","default","delete",
   "do","double","dynamic_cast","else","enum","explicit","expor","extern","false","float","for","friend","goto","if","inline","int",
   "long","mutable" ,"namespace","new","noexcept","not","not_eq","nullptr" ,"operator","or","or_eq","private","protected","public",
   "reflexpr" ,"register" ,"reinterpret_cast","requires","return","short","signed","sizeof","static","static_assert","static_cast",
   "struct","switch","synchronized","template","this","thread_local","throw","true","try","typedef","typeid","typename","union",
   "unsigned","using","virtual","void","volatile","wchar_t","while","xor","xor_eq"};
 
   vector<vector<string>> keywords; 
   while(!old_stud.eof()) {
      vector<string> need; 
      string all_line; 
      getline(old_stud, all_line);
      string help; 
      for(int j = 0; j < all_line.size(); j++) {
         if(need_char(all_line[j])) help.push_back(all_line[j]);
         else {
            if(!help.empty()) {
               need.push_back(help);
               help.clear();
            }
            while(j + 1 < all_line.size() && !need_char(all_line[j + 1])) {
               j++;
            }
         }
      }
      keywords.push_back(need); 
   }
   
   unordered_map<string, vector<int>> result; 
   for(int line = 0; line < keywords.size(); line++) {
      for(int k = 0; k < keywords[line].size(); k++) {
         string test_word = keywords[line][k];
         auto it = all_keywords.find(test_word);
         if(it != all_keywords.end()) {
            result[test_word].push_back(line + 1);  
         }
      }
   }
   
   for(auto &iten : result) {
      cout << iten.first << ", " << iten.second.size() << " repeats, " << "{ "; 
      for(int i = 0; i < iten.second.size(); i++) {
         cout << iten.second[i] << ' '; 
      }
      cout << "} lines" << '\n';
   }

}