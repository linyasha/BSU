#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>


using std::cout; 
using std::cin;  
using std::setw; 

const int size = 5; 

int* random_array(int n) {
	int* p = new int[n]; 
	 
	for (int i = 0; i < n; i++) {
		p[i] = rand() % 100 + 1;	
	}
	return p; 
}

int** random_array(int n, int k) {
	int** p = new int* [n];
	for (int i = 0; i < n; i++) {
		p[i] = random_array(k);
	}
	return p; 
}

void print_array(int* p, int n) {
	for (int i = 0; i < n; i++) {
		cout << setw(5) << p[i];
	}
	cout << '\n'; 
}

void print_array(int** p, int a, int b) {
	for (int i = 0; i < a; i++) {
		print_array(p[i], b); 
	}
}

int* vector(int** p) {
   int* vector = new int[2*size - 1]; 
   for(int j = 0, k = 0, i = 0; k < 2*size - 1; k++) {
      if(j < size) {
         int min = p[i][j]; 
         for(int j_coppy = j, i_coppy = i; j_coppy >= 0; j_coppy--, i_coppy++) {
            if(p[i_coppy][j_coppy] < min) min = p[i_coppy][j_coppy];
         }
         vector[k] = min;
         j++;
      }
      else {
         i+= 1;
         int min = p[i][j - 1]; 
         for(int j_coppy = j - 1, i_coppy = i; i_coppy < size; j_coppy--, i_coppy++) {
            if(p[i_coppy][j_coppy] < min) min = p[i_coppy][j_coppy];
         }
         vector[k] = min;
      }
   }

   return vector; 
}

int* vector(int* p) {
   int* vector = new int[2*size - 1]; 
   for(int j = 0, i = 1, k = 0; k < 2*size - 1; k++) {
      if(j < size) {
         int min = p[j]; 
         for(int j_coppy = j + (size - 1), i = 0; i < j; j_coppy += (size - 1), i++) {
            if(p[j_coppy] < min) min = p[j_coppy];
         }
         vector[k] = min;
         j++;
      }
      else {
         int z = (j - 1) + size * i;
         int min = p[z]; 
         for(int j_coppy = z + (size - 1), l = 0; l < (j - 1) - i; j_coppy += (size - 1), l++) {
            if(p[j_coppy] < min) min = p[j_coppy];
         }
         vector[k] = min;
         i++;
      }
   }

   return vector;   


}
/*
int main() {
   srand(time(0));
   int** matrix_4 = random_array(size, size);
   print_array(matrix_4, size, size); 
   int* array = vector(matrix_4); 
   cout << "Vector(min.ements): " << '\n';
   print_array(array, 2*size - 1);
   
}
*/

int main() {
   srand(time(0));
   int* matrix_4 = random_array(size * size);
   for(int i = 0; i < size * size; i+= size) {
      print_array(matrix_4 + i, size); 
   }
   int* array = vector(matrix_4); 
   cout << "Vector(min.ements): " << '\n';
   print_array(array, 2*size - 1);


}