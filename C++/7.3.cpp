#include <iostream>
#include <string>
#include <assert.h>
using std::cout;
using std::cin; 
using std::string; 


struct Node {
   char name[28];
   int cource;
   double ball;
   string date;
   Node* next;
};


class LinkedList {
private:
Node* head;
int count = 0; 
public:
LinkedList() {
    this->head = nullptr; 
}


bool is_empty() {
   return this->head == nullptr;
}

void insert(Node* b) {
   Node* a = new Node {*b}; 
   a->next = nullptr; 
  if(is_empty()) {
      this->head = a; 
      a->next = nullptr;
      count++;
   }
   else {
      Node* help = this->head;
      Node* help_before = nullptr;
      int k = 0;
      for(; k < count; k++) {
         if(a->name[0] >= help->name[0]) {
            help_before = help;
            help = help->next;

         }
         else break;
      }
      if(k == 0) {
         a->next = this->head;
         this->head = a;
         count++;
      }
      else{
         help_before->next = a;
         a->next = help;
         count++;
      }

   }
}
int size() {
   return count; 
}

Node* element(int n) {
   assert(!(count == 0 || n > count));
   Node* a = this->head;
   for(int i = 1; i < n; i++) {
      a = a->next;
   }
   return a; 
}


void remove(Node* a) {
   if(a != nullptr) assert(!(is_empty() || a->next == nullptr));
   if(a == nullptr){
      Node* help = this->head->next;
      delete this->head;
      this->head = help;
   } 
   else {
      Node* help = a->next->next;
      delete a->next;
      a->next = help;
      
   }
   count--;
}

~LinkedList() {
  while(!(is_empty())) {
     if(count == 1) remove(nullptr);
     else remove(this->head); 
  }
}

LinkedList(const LinkedList&) = delete;
void operator=(const LinkedList&) = delete;
};


int main() {
   LinkedList student;
   Node a = {"Pavlov Vladislav Sergeevich", 1, 7, "11.06.2000"};
   student.insert(&a); 
   Node b = {"Ovsyank Maxim Alexandrovich", 2, 4.6, "15.01.1999"};
   student.insert(&b);
   Node c = {"Ananyevva Ulyana Maksimovna", 2, 6, "02.01.1999"};
   student.insert(&c);
   Node d = {"Lynko Artur Vyacheslavivich", 4, 8, "30.11.1997"};
   student.insert(&d);
   Node e = {"Astasenchko Yanna Sergeevna", 3, 6.8, "16.02.1998"};
   student.insert(&e);
   int size = student.size(); 
   for(int i = 1; i <= size; i++) {
      cout << student.element(i)->cource << '\n'; 
   }
   int cource;
   LinkedList new_cource; 
   cout << "Enter the number of cource whose students you want to determine: " << '\n'; 
   while(true) {
      bool help_1 = false;
      cin >> cource;
      for(int i = 1; i <= size; i++) {
         Node* help = student.element(i);
         if(cource == help->cource) {
            new_cource.insert(help); 
            if(i == 1) student.remove(nullptr);
            else student.remove(student.element(i - 1));
            i--;
            size--;
            help_1 = 1; 
         }
      }
      if(help_1) break;
      cout << cource << "st year students are absent. Try defining a different course: " << '\n';
   }
   cout << "The determination was successful =^o^=" << '\n';
}      


