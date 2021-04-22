#include <iostream>
#include <iomanip>
using std::cin; 
using std::cout; 
using std::setw;


   const int size = 5; 

void print_array(int* p, int n) {
	for (int i = 0; i < n; i++) {
		cout << setw(5) << p[i];
	}
	cout << '\n'; 
}
void print_array(int (*board)[size]) {
	for (int i = 0; i < size; i++) {
		print_array(board[i], size); 
	}
}
void enter_coordinates(int* x, int * y) {
   int x_coppy, y_coppy;
   cout << "Enter the coordinates of the horse :" << '\n';
   while(true) {
      cout << "x = ";
      cin >> x_coppy;
      cout << "y = "; 
      cin >> y_coppy; 
      if((x_coppy > 8 || x_coppy < 1) || (y_coppy > 8 || y_coppy < 1)) {
         cout << "Invalid cordinates. Try again =( " << '\n';
         continue;
      }
      *x = x_coppy;
      *y = y_coppy;
      return;
   }
}
bool horse_riding(int x, int y, int (*board)[size], int possition) {
   
   board[y][x] = possition;
   
   if(possition == size * size) return true;
   
   //проверяю возможность хода и был ли конь уже на этой клетке ранее
   if(x + 1 < size && y + 2 < size && board[y + 2][x + 1] == 0) {
      if (horse_riding(x + 1, y + 2, board, possition + 1)) return true;
   }
   if(x - 1 >= 0 && y + 2 < size && board[y + 2][x - 1] == 0) {
       if (horse_riding(x - 1, y + 2 , board, possition + 1)) return true;
   }
   if(x + 2 < size && y - 1 >= 0 && board[y - 1][x + 2] == 0) {
      if(horse_riding(x + 2, y - 1, board, possition + 1)) return true;
   }
   if(x + 2 < size && y + 1 < size && board[y + 1][x + 2] == 0) {
      if(horse_riding(x + 2, y + 1, board, possition + 1)) return true;
   }
   if(x - 2 >= 0 && y + 1 < size && board[y + 1][x - 2] == 0) {
      if(horse_riding(x - 2, y + 1, board, possition + 1)) return true;
   }
   if(x - 2 >= 0 && y - 1 >= 0 && board[y - 1][x - 2] == 0) {
      if(horse_riding(x - 2, y - 1, board, possition + 1)) return true;  
   }
   if(x - 1 >= 0 && y - 2 >= 0 && board[y - 2][x - 1] == 0) {
      if(horse_riding(x - 1, y - 2, board, possition + 1)) return true;
   }
   if(x + 1 < size && y - 2 >= 0 && board[y - 2][x + 1] == 0) {
     if(horse_riding(x + 1, y - 2, board, possition + 1)) return true;
   }
   
   board[y][x] = 0;
   return false;
   
}


int main() {

   int board[size][size]{0}; 

   int x, y;

   enter_coordinates(&x, &y); 

   bool existence = horse_riding(x--, y--, board, 1);
   if(existence) print_array(board);
   else cout << "There is no bypass from this position =(" << '\n';
}