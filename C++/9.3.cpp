#include <iostream>
#include <string>
#include <stack>

using std::cin; 
using std::cout; 
using std::string; 
using std::stack;

string algebtaic_to_polska(const string& expression) {
   string output_array;
   stack<char> sings;
   bool help_minus = false; 
   for(int i = 0; i < expression.size(); i++) {
      char symbol = expression[i];
      if(symbol == ' ') continue;  
      if(symbol >= '0' && symbol <= '9') {
         output_array += symbol; 
         if((i + 1) == expression.size() || expression[i + 1] < '0' || expression[i + 1] > '9') output_array += '.';  
      }
      else {
         char help; 
         switch(symbol) {
            case '-': 
               if(expression[i + 1] == '(') {
                  help_minus = true; 
                  break;  
               } 
               if(i == 0 || expression[i - 1] == '(') {
                  while(expression[i + 1] >= '0' && expression[i + 1] <= '9') {
                     output_array += expression[i + 1]; 
                     i++;
                  }
                  output_array += '@'; // унарный минус - собака =)
                  break;
               }
               if(!sings.empty()){
                  help = sings.top(); 
                  if(help == '*' || help == '/' || help == '%' || help == '+') {
                     sings.pop(); 
                     output_array += help;
                  }
               }
               sings.push(symbol); 
            break;
            case '(' :
               sings.push(symbol);
            break;
            case ')' :
               help = sings.top(); 
               while(help != '(') {
                  output_array += help; 
                  sings.pop(); 
                  help = sings.top();
               }
               sings.pop(); 
               if(help_minus) {
                  output_array += '@'; 
                  help_minus = false;
               }
            break;
            case '+' :
               if(!sings.empty()){
                  help = sings.top(); 
                  if(help == '*' || help == '/' || help == '%' || help == '-') {
                     sings.pop(); 
                     output_array += help;
                  }
               }
               sings.push(symbol);
            break;
            case '*' :
               if(!sings.empty()){
                  help = sings.top(); 
                  if(help == '/' || help == '%') {
                     sings.pop(); 
                     output_array += help;
                  }
               }
               sings.push(symbol);
            break;
            case '/': 
               if(!sings.empty()){
                  help = sings.top(); 
                  if(help == '*' || help == '%') {
                     sings.pop(); 
                     output_array += help;
                  }
               }
               sings.push(symbol);
            break;
            case '%': 
               if(!sings.empty()){
                  help = sings.top(); 
                  if(help == '/' || help == '*') {
                     sings.pop(); 
                     output_array += help;
                  }
               }
               sings.push(symbol);
            break;
         }
      }
   }
   while(!sings.empty()) {
      char help = sings.top(); 
      output_array+= help;
      sings.pop(); 
   }
   return output_array; 
}

double result_by_polska(const string& expression) {
   double result = 0; 
   string polska = algebtaic_to_polska(expression);
   
   stack<double> calculation; 
   for(int i = 0; i < polska.size(); i++){
      char symbol = polska[i]; 
      if(symbol >= '0' && symbol <= '9') {
         string help_number; 
         int result = 0; 
         while(polska[i] != '.') {
            help_number += polska[i];
            i++; 
         }
         int size = 1;
         int size_string = help_number.size();
         for(int i = 1; i < size_string; i++) {
            size *= 10; 
         }
         for(int i = 0; i < size_string; i++) {
            result += (help_number[i] - 48) * size; 
            size /= 10; 
         }
         calculation.push(result); 
      }
      
      else{
         if(symbol == '@') {
            int number = calculation.top();
            calculation.pop(); 
            calculation.push(0 - number); 
            continue;
         }
         int b = calculation.top(); 
         calculation.pop();
         int a = calculation.top(); 
         calculation.pop(); 
         switch (symbol) {
            case '+':
               calculation.push(a + b);
            break;
            case '-':
               calculation.push(a - b);
            break;
            case '*':
               calculation.push(a * b);
            break;
            case '/':
               calculation.push(a / b);
            break;
            case '%':
               calculation.push(a % b);
            break;
         }
      }
   }
   result = calculation.top();
   return result; 
}


int main() {
   string algebraic_expression {"(6 + 9 - 5) / (8 + 1 * 2) + 7 % 7"};
   //string algebraic_expression {"(15 * 3 + 4)"};
   double result =  result_by_polska(algebraic_expression);
   cout << algebraic_expression << " = " << result; 

}