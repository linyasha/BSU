#include <iostream>
#include <string>
#include <assert.h>
#include <ctime>
#include <initializer_list>

using std::cout;
using std::cin; 
using std::string; 
using std::initializer_list; 
using std::istream;
using std::ostream;


template<typename T>
struct Node {
   T symbol;
   Node<T>* left;
   Node<T>* right;
};


template<typename T>
class Wood {
   private:
      Node<T>* root; 
      void insert_koppy(const Node<T>* one) {
         insert(one->symbol);
         if(one->right != nullptr) insert_koppy(one->right); 
         if(one->left != nullptr) insert_koppy(one->left); 
      }
   public:
      Wood() {
         this->root = nullptr;
      }

      Node<T>* groot() {
         return this->root;
      }

      void new_root(T value) {
         if(is_empty()) insert(value);
         else this->root->symbol = value;
      }

      bool is_empty() const{
         return this->root == nullptr;
      }

      void insert(T b) {
         Node<T>* a = new Node<T> {b, nullptr, nullptr};
         if(is_empty()) {
            this->root = a;
         }
         else {
            Node<T>* help = this->root; 
            while(true) {
               if(a->symbol < help->symbol) {
                  if(help->left == nullptr) {
                     help->left = a; 
                     break;
                  }
                  else help = help->left; 
               }
               else {
                  if(help->right == nullptr) {
                     help->right = a; 
                     break;
                  }
                  else help = help->right; 
               }
            } 
         }
      }

      Node<T>* element(T n) {
         if(is_empty()) return nullptr;
         Node<T>* help = this->root;
         while(true) {
            if(n == help->symbol) return help;
            else {
               if (n < help->symbol) {
                  if(help->left != nullptr) help = help->left;
                  else return nullptr;
               }
               else {
                  if(help->right != nullptr) help = help->right;
                  else return nullptr;
               }
            }
         }
         return help; 
      }

      Wood<T>(initializer_list<T> other) {
         this->root = nullptr;;
         for(int i = 0; i < other.size(); i++) {
            insert(*(other.begin() + i));
         }
      }
      
      Wood<T>(const Wood<T>& a ) {
         this->root = nullptr;
         if(a.is_empty()) return;
         insert_koppy(a.root); 
      } 

      void operator=(const Wood<T>& a) {
         cut_a_tree(this->root); 
         if(a.is_empty()) return;
         insert_koppy(a.root); 
      }

      void cut_a_tree(Node<T>* root) {
         if(root != nullptr) {
            if(root->left != nullptr) cut_a_tree(root->left);
            if(root->right != nullptr) cut_a_tree(root->right);
            delete this->root;
            this->root = nullptr;
         }
         elreturn;
      }

      void delete_list(T value) {
         Node<T>* help = element(value); 
         if(help == nullptr) return;
         if(help->left == nullptr && help->right == nullptr) delete help; 
      }

      int k_elemets(Node<T>* root, int need) {
         int result = 0;
         if(1 == need) {
            result++;
            return result;
         }    
         if(root != nullptr) {
            if(root->left != nullptr) result += k_elemets(root->left, need - 1);
            if(root->right != nullptr) result += k_elemets(root->right, need - 1);
         }
         return result;
      }

      ~Wood() {
         cut_a_tree(this->root);
      }

};

template<typename T>
ostream& eazy_cout(ostream& out, Node<T>* help) {
   out << help->symbol << ' '; 
   if(help->right != nullptr) eazy_cout(out, help->right); 
   if(help->left != nullptr) eazy_cout(out, help->left);
   return out;
}

template<typename T>
ostream& operator<<(ostream& out, Wood<T>& a) { 
   out << "[ ";
   if(!(a.is_empty())) eazy_cout(out, a.groot());
   out << " ]";
   return out; 
}

int main() {
   Wood<int> a {1, 5, 6, 4, 2, 3}; 
   cout << a; 
   cout << a.k_elemets(b.groot(), 1);



}