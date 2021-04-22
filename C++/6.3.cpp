#include <iostream>
#include <fstream>
#include <string>
#include <ios>

using std::cout; 
using std::cin; 
using std::string; 
using std::ofstream;
using std::ifstream;
using std::ios;
using std::istream;
using std::ostream;

class Students{ 
public:
int cource;
char name[28];
int years;
char fmale;
int ball;
};

Students read(istream& in) {
   Students one;
   in >> one.cource;
   in.ignore(9);
   in.get(one.name, 27); 
   in.ignore(2);
   in >> one.years;
   in.ignore(8);
   in >> one.fmale;
   in.ignore(1);
   in >> one.ball;
   return one; 
}

void write(ostream& out, Students one) {
   out << one.cource << " cource, " << one.name << ", " << one.years << " years, " << one.fmale << ", " << one.ball << '.' << '\n';
}


/*
int main() {
   int cource; 
   Students only_one; 
   cout << "Enter the number of cource whose students you want to determine: " << '\n'; 
   while(true) {
      bool help = false;
      cin >> cource;
      ifstream old_stud("students.txt");
      ofstream new_stud("New_file.txt");
      while(!old_stud.eof()) {
         only_one = read(old_stud); 
         if(only_one.cource == cource) {
            write(new_stud, only_one);
            help = 1;
         }
      }
      if(help) break;
      cout << cource << "st year students are absent. Try defining a different course: " << '\n';
      old_stud.close();
      new_stud.close();
   }
   cout << "The determination was successful =^o^=";
}
*/


int main() {
   Students array[4] { {1,"Pavlov Vladislav Sergeevich", 18, 'M', 6}, {2,"Ovsyank Maxim Alexandrovich", 19, 'M', 5}, 
   {3,"Astasenchko Yanna Sergeevna", 18, 'F', 7}, {4,"Ananyevva Ulyana Maksimovna", 18, 'F', 8}};
   ofstream students("binary.dat", ios::binary); 
   for(int i = 0; i < 4; i++) {
      students.write((char*)& array[i], sizeof(Students) - 1);
   }
   students.close();

   int cource;
   
   cout << "Enter the number of cource whose students you want to determine: " << '\n'; 
   while(true) {
      bool help = false;
      cin >> cource;
      ifstream old_stud("binary.dat", ios::binary);
      ofstream new_stud("new_binary.dat", ios::binary);
      Students only_one;
      while(!old_stud.eof()) {
         old_stud.read((char*)& only_one, sizeof(Students) - 1);
         if (old_stud.fail()) break;
         if(only_one.cource == cource) {
            new_stud.write((char*)& only_one, sizeof(Students) - 1);
            help = 1;
         }
      }
      if(help) break;
      cout << cource << "st year students are absent. Try defining a different course: " << '\n';
      old_stud.close();
      new_stud.close();
   }
   cout << "The determination was successful =^o^=";
}
