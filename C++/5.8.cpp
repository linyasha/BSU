
#include <iostream>
#include <iomanip>
using std::cin; 
using std::cout; 
using std::setw;


void beautiful() {
	cout << '\n' << "_________________________________________________" << '\n';
}

void random_array(int* array, int n) {
	
	for (int i = 0; i < n; i++) {
		array[i] = rand() % 50 + 1;
		
	}
}

void print_array(int* p, int n) {
	for (int i = 0; i < n; i++) {
		cout << p[i] << setw(5);
	}
	cout << '\n';
}

template<typename T>
void swap_elements(T* a, T*  b) {
	T help = *a; 
	*a = *b; 
	*b = help;
}

template<typename T>
void zapolnenie_massiva(T* array_1, T* first, T* second, int n) {
	for(int i = 0, j = 0; i < n; i++ ) {
		if(i < n / 2) {
			first[i] = array_1[i];
			continue;
			}
		second[j] = array_1[i];
		j++;
	}
}

template<typename T>
void sliyanie_massiva(T* array_1, T* first, T* second, int n) {
	for(int i = 0, j = 0, k = 0; k < n; k++) {
			if(i >= n / 2) {
				array_1[k] = second[j]; 
				j++;
				continue;
			}
			if(j >= n / 2 + 1) {
				array_1[k] =first[i]; 
				i++;
				continue;
			}
			if((first[i] < second[j] && i < n / 2)) {
				array_1[k] = first[i];
				i++;
				continue;
			}
			array_1[k] = second[j];
			j++;
	}

}


template<typename T>
void merge_sort(T* array_1, T* array_2) {
	int n = array_2 - array_1;
	if(n == 1) return;
	if(n == 2) {
		if(array_1[0] > array_1[1]) swap_elements (&array_1[0], &array_1[1]);
		return;
	}
	merge_sort<T>(&array_1[0], &array_1[n / 2]);
	merge_sort<T>(&array_1[n / 2], &array_1[n]);
	 
	T* first = new T[n / 2];
	T* second = new T[(n + 1) / 2]; 
	zapolnenie_massiva<T>(array_1, first, second, n);
	sliyanie_massiva<T>(array_1, first, second, n);
	delete[] first;
	delete[] second;

}

int main() {
	const int k = 14;

	int array_1[k];
	srand(time(0));
   random_array(array_1, k);

	cout << "Array of random numbers: " << '\n';
	print_array(array_1, k);
	beautiful();

   merge_sort<int>(&array_1[0], &array_1[k]);
   merge_sort<int>(array_1, array_1 + k);
   
	cout << "Array sort by merge sort: " << '\n';
	print_array(array_1, k);
	beautiful();
	
}
