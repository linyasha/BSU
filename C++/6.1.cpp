#include <iostream>
#include <iomanip>
#include <string>
using std::cin; 
using std::cout; 
using std::string; 
using std::setw; 

/*   
int main() { 
   string text = "Heello, boys. Today i go hoome, becouse Corooona Virus here."; 
   cout << text << '\n'; 
   string new_string; 
   for(int i = 0; i < text.size(); i++) {   // вопрос: пытался вынести цикл в функицю но возникли проблемы с 'char literal = text[i]'. к слову,
                                             //  в main все работает. Почему ? 
      int repeat = 0; 
      char literal = text[i]; 
      for(int j = 0; j < text.size(); j++) {
         if(text[j] == literal) repeat++;
      }
     if(repeat != 2) new_string += literal; 
     else new_string += ' ';
      
   }
   text = new_string;
   cout << text << '\n'; 
   
}
   
*/

/*
int main() {
   string number_16 = "F.FC8D3AE685D"; //15.98653
   //string number_16 = "0.A";
   cout << number_16 << '\n'; 
   bool minus = 0;
   double number_10 = 0; 
   double exps = 0.0625;
   for(int i = 0; number_16[i] != '.' && i < number_16.size(); i++) {
      if(number_16[i] == '-') {
         minus = 1;
         continue;
      }
		exps *= 16; 
   }
   
	for (int i = 0; i < number_16.size(); i++) {
		if (number_16[i] == '-' || number_16[i] == '.') {
			continue; 
		}
		double help = 0; 
		if (number_16[i] <= 'F' && number_16[i] >= 'A') help = (number_16[i] - 'A') + 10; 
		else help = number_16[i] - '0'; 
		number_10 += help * exps;
		exps /= 16;
	}

   if(minus) number_10 = 0 - number_10;  
   cout << number_10 << '\n';  
}

*/

// bool glasnaya(char a) {
// 	if (a == 'A' || a == 'E' || a == 'I' || a == 'O' || a == 'U' || a == 'Y' || a == 'a' 
//    || a == 'e' || a == 'i' || a == 'o' || a == 'u' || a == 'y') return 1;
// 	return 0; 
// }

// bool razdelitel(char a) {
// 	if (a == ' ' || a == '.' || a == ',' || a == ':' || a == ';' || a == '!' || a == '?' || a == '"' || a == '(' || a == ')') return 1; 
// 	return 0;
// }

// int max_glasnih(const string& stroch) {
// int max = 0;
// for (int i = 0, glasnie = 0; i < stroch.size(); i++) {		
//       if (glasnaya(stroch[i])) {
// 			glasnie++;
// 			continue;
// 		}
// 		if (razdelitel(stroch[i])) { 
// 			if (max < glasnie) {
// 				max = glasnie; 
// 			}
// 			glasnie = 0;
// 		}
// }
// return max;
// }


// int main() {
//    string stroch = "Hello, my names Goolea. I would like chokotate. Oooh: \" Please, go home\".";
//    string new_string; 
//    cout << stroch << '\n'; 
//    string& k = stroch; 
//    int glasnie = max_glasnih(k);  // максимальное число гласных 
   
// 	for (int i = 0, glasnih_slovo = 0, schetchik_bukv = 0; i < stroch.size(); i++) {   // цикл проверяет, соответствует ли количество гласных в слове максимальному значению, 
			
// 		if (schetchik_bukv == 0 && razdelitel(stroch[i])) continue;
// 		else schetchik_bukv++;
// 		if (glasnaya(stroch[i])) {  // считаю гласные
// 			glasnih_slovo++;
// 			continue;
// 		}
// 		if (razdelitel(stroch[i])) {
// 			if (glasnie == glasnih_slovo) {   // записываю слово  
// 				for(int j = i - schetchik_bukv; j < i; j++) {
// 					new_string += stroch[j];
// 				}
// 				new_string+= ',';
// 			}
// 			glasnih_slovo = 0; 
// 			schetchik_bukv = 0; 
			
// 		}


//    }
// 	cout << new_string << '\n'; 
// }


const int size = 56; 

/*
int main() {
   int z = 1;
   char student_1[size] = " cource, Pavlov Vladislav Sergeevich, 18 years, male, 6";
   char student_2[size] = " cource, Ovsyank Maxim Alexandrovich, 19 years, male, 5";
   char student_3[size] = " cource, Ovsyannik Evgeny Sergeevich, 18 years, male, 4";
   char student_4[size] = " cource, Anavich Ulyana Maksimovna, 18 years, female, 8";
   ofstream students("binary.dat", ios::binary);
   students.write((char*)& z, sizeof(int));
   students.write((char*)& student_1, size - 1);
   z = 2;
   students.write((char*)& z, sizeof(int));
   students.write((char*)& student_2, size - 1);
   z = 3;
   students.write((char*)& z, sizeof(int));
   students.write((char*)& student_3, size - 1);
   z = 4;
   students.write((char*)& z, sizeof(int));
   students.write((char*)& student_4, size - 1);
   students.close();

   int cource;
   cout << "Enter the number of cource whose students you want to determine: " << '\n'; 
   while(true) {
      int help_cource; 
      char help_string[size];
      bool help = false;
      cin >> cource;
      ifstream old_stud("binary.dat", ios::binary);
      ofstream new_stud("new_binary.dat", ios::binary);
      while(!old_stud.eof()) {
         old_stud.read((char*)& help_cource, sizeof(int));
         //old_stud.ignore(1);
         if(help_cource == cource) {
            old_stud.read((char*)& help_string, size - 1);
            new_stud.write((char*)& help_cource, sizeof(int));
            new_stud.write((char*)& help_string, size - 1);
            help = 1;
         }
         else old_stud.ignore(size - 1);
      }
      if(help) break;
      cout << cource << "st year students are absent. Try defining a different course: " << '\n';
      old_stud.close();
      new_stud.close();
   }
   cout << "The determination was successful =^o^=";
}

*/


