#include <iostream>
#include <string>
#include <assert.h>
#include <ctime>
using std::cout;
using std::cin; 
using std::string; 



struct Node {
   int symbol;
   Node* next;
};

class Ochered {
private:
   Node* head;
   Node* tail; 
   int count = 0; 
public:
   Ochered() {
      this->head = nullptr;
      this->tail = nullptr; 
   }

   Ochered(const Ochered& a ) = delete; 
   void operator=(const Ochered& a) = delete;

   Node* ghead() {
      return this->head;
   }

   bool is_empty() {
      return this->root == nullptr;
   }

void insert(int b) {
   Node* a = new Node {b, nullptr, nullptr};
   if(is_empty()) {
      this->root = a;
   }
   else {
      Node* help = this->root; 
      while(true) {
         if(a->symbol < help->symbol) {
            if(help->left == nullptr) {
               help->left = a; 
               break;
            }
            else help = help->left; 
         }
         else {
            if(help->rigth == nullptr) {
               help->rigth = a; 
               break;
            }
            else help = help->rigth; 
         }
      } 
   }
   count++;
}


int size() const {
   return count; 
}

Node* element(int n) {
   assert(!(count == 0));
   Node* help = this->root;
   while(true) {
      if(n == help->symbol) return help;
      else {
         if (n < help->symbol) {
            if(help->left != nullptr) help = help->left;
            else return nullptr;
         }
         else {
            if(help->rigth != nullptr) help = help->rigth;
            else return nullptr;
         }
      }
   }
   return help; 
}

void cut_a_tree(Node* root) {
   if(root != nullptr) {
      if(root->left != nullptr) cut_a_tree(root->left);
      if(root->rigth != nullptr) cut_a_tree(root->rigth);
      delete root;
   }
   else return;
}

int k_elemets(Node* root, int need, int level = 1) {
   int result = 0;
   if(level == need) {
      result++;
      return result;
   }    
   if(root != nullptr) {
      if(root->left != nullptr) result += k_elemets(root->left, need, level + 1);
      if(root->rigth != nullptr) result += k_elemets(root->rigth, need, level + 1);
   }
   return result;
}


~Ochered() {
  cut_a_tree(this->root);
}

};


int main() {
   srand(time(0));
   int n = 5; 
   Ochered wood;
   for(int i = 0; i < n; i++) {
      int k = rand() % 21;
      cout << k << ' ';
      wood.insert(k);
   }
   int need = 3; //требуемый уровень, количество листьев на котором нужно узнать
   int result = wood.k_elemets(wood.groot(), need); 
   cout << '\n' << result << '\n'; 
}
