   #include <iostream>
   #include <fstream>
   #include <string>
   #include <ctime>

   const unsigned int size = 1000000;

   using std::cout; 
   using std::cin;  
   using std::ofstream;
   using std::ifstream;
   using std::istream;
   using std::ostream;

int main() {
   srand(time(0));
   //заполняю файл числами
   ofstream number("File.txt"); 
   for(int i = 0; i < size; i++) {
      number << ' ' << (rand() % 10000) + 1;
   }
   number.close(); 
   //прохожу по файлу и считаю повторения каждого числа
   ifstream fout("File.txt"); 
   int array[10001]{0}; 
   while(!fout.eof()) {
      int help; 
      fout >> help; 
      if(help >= 10001 || fout.fail()) break; 
      array[help] += 1; 
   }
   //считаю сколько чисел встретилось больше 1 раза
   int size_new_array;
   for(int i = 0; i < 10001; i++) {
      if(array[i] > 1) size_new_array++;
   }
   int* new_array = new int[size_new_array];
   //получаю окончательный массив с нужными числами
   ofstream name("New_file.txt"); 
   for(int i, j = 0; i < size_new_array; j++) {
      if(array[j] > 1) {
         new_array[i++] = j;
      }
   }
   cout << "New_array creating =^-^="; 
   delete[] new_array;

}

