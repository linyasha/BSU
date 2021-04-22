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
};

template <typename T>
class LinkedList {
   private:
      Node<T>* head;
      int count = 0; 
   public:

      LinkedList() {
         this->head = nullptr; 
      }

      Node<T>* ghead() const {
         return this->head;
      }

      bool is_empty() {
         return this->head == nullptr;
      }

      int size() const {
         return count; 
      }

      void insert(T b) {
         Node<T>* a = new Node<T> {b};
         if(is_empty()) {
            this->head = a;
            a->next = nullptr;
         }
         else {
            Node<T>* help = this->head;
            for(int i = 1; i < count; i++) {
               help = help->next; 
            }
            help->next = a;
            a->next = nullptr; 
         }
         count++;
      }

      void new_head(T value) {
         if(is_empty()) insert(value); 
         else this->head->symbol = value;
      } 

      Node<T>* element(int n) {
         assert(!(count == 0 || n > count));
         Node<T>* a = this->head;
         for(int i = 1; i < n; i++) {
            a = a->next;
         }
         return a; 
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
         for(int i = 0; i < other.size(); i++) {
            insert(*(other.begin() + i));
         }
         cout << '\n';
      } 

      LinkedList(const LinkedList<T>& a ) {
         this->head = nullptr; 
         Node<T>* help = a.ghead();
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
         if(a != nullptr) assert(!is_empty() && a->next != nullptr);
         if(a == nullptr){
            Node<T>* help = this->head->next;
            delete this->head;
            this->head = help;
         } 
         else {
            Node<T>* help = a->next->next;
            delete a->next;
            a->next = help;
            
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
         delete_list();
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

template<typename T>
LinkedList<T> func(const LinkedList<T>& l1, LinkedList<T>& l2) {
   LinkedList<T> new_list; 
   int size_1 = l1.size();
   int size_2 = l2.size(); 
   Node<T>* help_1 = l1.ghead();
   for(int i = 1; i <= size_1; i++) {
      bool help = false; 
      T symbol = help_1->symbol; 
      Node<T>* help_2 = l2.ghead();
      Node<T>* help_2_before = nullptr;
      
      for(int j = 1; j <= size_2; j++) {
         if(symbol == help_2->symbol) {
            if(j == 1) l2.remove(nullptr);
            else l2.remove(help_2_before);
            j--;
            size_2--;
            help = 1;   
         }
         help_2_before = help_2;
         help_2 = help_2->next;
          
      }
      if(help) new_list.insert(symbol); 
      help_1 = help_1->next; 
   }  
   return new_list; 
}


int main() {
   LinkedList<char> a {'h', 'e', 'l', 'l', '2'};
   LinkedList<char> b {'l','w','e','a','s','d','h','l','1'};
   LinkedList<char> help(b);
   LinkedList<char> c = func<char>(a, help);
   cout << c; 



}

