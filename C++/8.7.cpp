#include <iostream>
#include <string>
#include <assert.h>
#include <queue>
#include <vector>
#include <algorithm>
#include <initializer_list>
using std::cout;
using std::cin; 
using std::reverse; 
using std::string;
using std::vector;  
using std::queue;
using std::initializer_list;
using std::ostream;
using std::istream;

template<typename T>
struct Vertex{
public:
   T name;
   vector<Vertex<T>*> neighbors;
   int label = -1;
};

template<typename T>
class Graph{
   private:
      int quantity;
      vector<Vertex<T>*> all_vertex;
      Vertex<T>* create_vertex(T name) {
         Vertex<T>* a = new Vertex<T>; 
         a->name = name; 
         all_vertex.push_back(a);
         quantity++;
         return a;
      }
   public:
      Graph() : quantity(0) {
      }
   
      Graph(initializer_list<T> other) {
         this->quantity = 0; 
         for(int i = 0; i < other.size(); i++) {
            create_vertex(*(other.begin() + i));
         }
      }

      int size() const{
         return quantity; 
      }

      Vertex<T>* givevertex(T name) {
         Vertex<T>* a = nullptr;
         for(int i = 0; i < quantity; i++){
            if(all_vertex[i]->name == name) {
               a = this->all_vertex[i];
               break;
            }
         }
         return a;
      }

      template<typename R>
      friend ostream& operator<<(ostream& out, Graph<R>& a);

      void vertex_editing(T name,  const vector<T> neiborts) {
         Vertex<T>* main_vertex = givevertex(name);
         if(main_vertex == nullptr) {
            Vertex<T>* a = create_vertex(name); 
            main_vertex = a;   
         }
         for(int i = 0; i < neiborts.size(); i++) {
            Vertex<T>* neibort = givevertex(*(neiborts.begin() + i));
            if(neibort == nullptr) {
               Vertex<T>* a = create_vertex(*(neiborts.begin() + i)); 
               main_vertex->neighbors.push_back(a);
               a->neighbors.push_back(main_vertex); 
               continue;
            }
            bool find = true; 
            for(int j = 0; j < main_vertex->neighbors.size(); j++) {
               if(main_vertex->neighbors[j] == neibort) {
                  find  = false; 
                  break;
               } 
            }
            if(find) {
               main_vertex->neighbors.push_back(neibort);
               neibort->neighbors.push_back(main_vertex); 
            }
         }
         return; 
      }

      void delete_vertex(T name) {
         Vertex<T>* vertex = givevertex(name);
         if(vertex == nullptr) return;
         for(int i = 0; i < vertex->neighbors.size(); i++) {
            Vertex<T>* help_vertex = vertex->neighbors[i];
            int number = 0; 
            for(int j = 0; j < help_vertex->neighbors.size(); j++) {
               if(help_vertex->neighbors[j] == vertex) {
                  number = j; 
                  break;
               }
            }   
            help_vertex->neighbors.erase(help_vertex->neighbors.begin() + number);
         }
         int number = 0;
         for(int i = 0; i < all_vertex.size(); i++) {
            if(all_vertex[i] == vertex) {
               number = i; 
               break;
            }
         }
         all_vertex.erase(all_vertex.begin() + number); 
         quantity--;
         delete vertex;
      }

};

template<typename T>
ostream& operator<<(ostream& out, Graph<T>& a) { 
   if(a.size() == 0) {
      out << "Clear =(" << '\n'; 
      return out;
   }
   for(int i = 0; i < a.size(); i++) {
      Vertex<T>* help = a.all_vertex[i];
      out << help->name << " [";
      for(int j = 0; j < help->neighbors.size(); j++) {
         out << ' ' << help->neighbors[j]->name; 
      } 
      out << " ];" << '\n'; 
   }
   return out;
}

template<typename T>
vector<int> find_way(Graph<T>& first, T begin, T end) {
   vector<int> way; 
   Vertex<T>* begin_way = first.givevertex(begin); 
   Vertex<T>* end_way = first.givevertex(end);
   if(begin_way == nullptr ||  end_way == nullptr) return way;
   queue<Vertex<T>*> a;
   a.push(begin_way); 
   begin_way->label = 0; 
   while(!a.empty() && end_way->label == -1) {
      int k = 1; 
      Vertex<T>* help = a.front(); 
      a.pop(); 
      int size = help->neighbors.size(); 
      for(int i = 0; i < size; i++) {
         Vertex<T>* sosed = help->neighbors[i]; 
         if(sosed->label == -1) {
            a.push(sosed); 
            sosed->label = help->label + 1;
         }
      } 
   }
   way.push_back(end);
   int v = end_way->label; 
   Vertex<T>* last_help = end_way; 
   while(last_help != begin_way) {
      for(int i = 0; ; i++) {
         if(last_help->neighbors[i]->label == v - 1){
            way.push_back(last_help->neighbors[i]->name);
            last_help = last_help->neighbors[i];
            v--;
            break;
         }
      }
   }
   
   return way;
}

int main() {
Graph<int> a;
a.vertex_editing(1, {4, 7, 2}); 
a.vertex_editing(2, {5, 3 ,1});
a.vertex_editing(3, {6, 2});
a.vertex_editing(4, {1, 7});  
a.vertex_editing(5, {6, 7, 2}); 
a.vertex_editing(6, {3, 7, 5}); 
a.vertex_editing(7, {4, 5, 6});
vector<int> way = find_way(a, 1, 6);
for(int i = 0; i < way.size(); i++) {
   cout << way[i] << ' '; 
}
}