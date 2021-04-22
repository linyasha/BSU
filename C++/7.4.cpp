#include <iostream>
#include <string>
#include <assert.h>
using std::cout;
using std::cin; 
using std::string; 


struct Node {
   char symbol;
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

LinkedList(const LinkedList& a ) = delete;  

void operator=(const LinkedList& a) = delete;

Node* give_a_head() const {
   return this->head;
}

bool is_empty() {
   return this->head == nullptr;
}

void insert(char b) {
   Node* a = new Node {b};
   if(is_empty()) {
      this->head = a;
      a->next = nullptr;

   }
   else {
      Node* help = this->head;
      for(int i = 1; i < count; i++) {
         help = help->next; 
      }
      help->next = a;
      a->next = nullptr; 
   }
   count++;
}


int size() const {
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

};

LinkedList* func(const LinkedList& l1, LinkedList& l2) {
   LinkedList* new_list = new LinkedList; 
   int size_1 = l1.size();
   int size_2 = l2.size(); 
   Node* help_1 = l1.give_a_head();
   for(int i = 1; i <= size_1; i++) {
      bool help = false; 
      char symbol = help_1->symbol; 
      Node* help_2 = l2.give_a_head();
      for(int j = 1; j <= size_2; j++) {
         if(symbol == help_2->symbol) {
            if(j == 1) l2.remove(nullptr);
            else l2.remove(l2.element(j - 1));
            j--;
            size_2--;
            help = 1;   
         }
         help_2 = help_2->next;
          
      }
      if(help) new_list->insert(symbol); 
      help_1 = help_1->next; 
   }  
   return new_list; 
}

int main() {
   LinkedList l1, l2;
   
   char one[6] = "hell1";
   char two[10] = "1weasdhl1"; 
   for(int i = 0; i < 5; i++) {
      l1.insert(one[i]);  
   }
   for(int i = 0; i < 9; i++) {
      l2.insert(two[i]); 
   }
   LinkedList l_help(l2);
   LinkedList* l = func(l1, l_help); 
   int z = l->size();
   Node* help = l->give_a_head(); 
   for(int i = 1; i <= z; i++ ) {
      cout << help->symbol << ' '; 
      help = help->next;
   }
   delete l;
  
}      


