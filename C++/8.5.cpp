#include <iostream>
#include <initializer_list>
#include <assert.h>

using std::istream;
using std::ostream;
using std::cout;
using std::cin; 
using std::initializer_list; 


template <typename T>
struct Node {
   public:
      T symbol;
      Node<T>* next;
      Node<T>* early; 

};

template<typename T>
class LinkedList {
   private:
      Node<T>* head;
      Node<T>* tail; 
      int count = 0; 
   public:
      LinkedList() {
         this->head = nullptr;
         this->tail = nullptr; 
      }

      int size() const {
         return count; 
      }

      Node<T>* ghead() {
         return this->head;
      }

      Node<T>* gtail() {
         return this->tail;
      }

      bool is_empty() {
         return this->head == nullptr;
      }

      void insert(T b) {
         Node<T>* a = new Node<T> {b};
         a->next = nullptr;
         if(is_empty()) {
            this->head = a;
            this->tail = a;
            a->early = nullptr;
         }
         else {
            a->early = this->tail;
            this->tail->next = a; 
            this->tail = a;            
         }
         count++;
      }


      Node<T>* element(int n) {
         assert(!(count == 0 || n > count));
         Node<T>* a = this->head;
         for(int i = 1; i < n; i++) {
            a = a->next;
         }
         return a; 
      }

      void new_head(T value) {
         if(is_empty()) insert(value); 
         else this->head->symbol = value;
      }

      const Node<T>* element(int n) const {
         assert(!(count == 0 || n > count));
         Node<T>* a = this->head;
         for(int i = 1; i < n; i++) {
            a = a->next;
         }
         return a; 
      }

      LinkedList(initializer_list<T> other) {
         this->head = nullptr;
         this->tail = nullptr;

         for(int i = 0; i < other.size(); i++) {
            insert(*(other.begin() + i));
         }
      } 

      LinkedList(const LinkedList<T>& a ) {
         this->head = nullptr; 
         this->tail = nullptr;
         Node<T>* help = a->head;
         for(int i = 1; i <= a.size(); i++) {
            insert(help->symbol);
            help = help->next;
         }
      }

      void operator=(const LinkedList<T>& a) {
         while(!(is_empty())) {
            if(count == 1) remove(nullptr);
            else remove(this->head); 
         }  
         Node<T>* help = a.ghead();
         for(int i = 1; i <= a.size(); i++) {
            insert(help->symbol);
            help = help->next;
         }
      }

      void remove(Node<T>* a) {
         if(a != nullptr) assert(!(is_empty() || a->next == nullptr));
         if(a == nullptr){
            Node<T>* help = this->head->next;
            delete this->head;
            this->head = help;
            if(count == 1) this->tail = nullptr;
            else this->head->early = nullptr;
         } 
         else {
            if(a->next == this->tail) {
               delete this->tail;
               a->next = nullptr;
               this->tail = a; 
            }
            else {
               Node<T>* help = a->next->next;
               delete a->next;
               help->early = a; 
               a->next = help;
            }
         }
         count--;
      }

      void delete_list() {
         while(!(is_empty())) {
            if(count == 1) remove(nullptr);
            else remove(this->head); 
         }   
      }

      ~LinkedList() {
         while(!(is_empty())) {
            if(count == 1) remove(nullptr);
            else remove(this->head);
         }
      }

};

template<typename T>
ostream& operator<<(ostream& out, LinkedList<T>& a) { 
      if(a.ghead() == nullptr) {
         out << "Clear =(" << '\n'; 
         return out;
      }
      Node<T>* help = a.ghead(); 
      for(int i = 0; i < a.size(); i++) {
         out << help->symbol << ' ';
         help = help->next;
      }
      out << '\n'; 
      return out;
}

int main() {
   int n = 5;  
   LinkedList<int> a {1, 3, 5, 7, 9, 11, 13, 15, 17, 19}; //2n
   cout << a << '\n'; 
   double result = 1; 
   Node<int>* one = a.ghead(); 
   Node<int>* second = a.gtail(); 
   for(int i = 0; i < n; i++) {
      result *= one->symbol - second->symbol; 
      one = one->next->next;
      second = second->early->early;

   }
   cout << result; 
}
