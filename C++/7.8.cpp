#include <iostream>
#include <string>
#include <assert.h>
#include <vector>
#include <queue>
using std::cout;
using std::cin; 
using std::string;
using std::vector;  
using std::queue;

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
   public:
      Graph() : quantity(0) {
      }
   bool is_empty() {
      return quantity == 0;
   }

   Vertex* givevertex(int name) {
      if(name > quantity) return nullptr;
      return this->all_vertex[name - 1];
   }

   void vertex_creation(int vertex ) {
      if(is_empty()) {
        Vertex* a = new Vertex; 
        a->name = 1; 
        this->all_vertex.push_back(a); 
        vertex--; 
        quantity++;
      }
      for(int i = 0; i < vertex; i++) {
         Vertex* c = new Vertex;
         c->name = quantity + 1;
         this->all_vertex.push_back(c);
         quantity++; 
      }
   }

   void vertex_editing(int name,  vector<int>& neiborts) {
      if(name > quantity) return; 
      Vertex* main_vertex = this->all_vertex[name - 1]; 
      int size_naighbors = neiborts.size();
      for(int i = 0; i < size_naighbors; i++) {
         Vertex* collateral_vertex = this->all_vertex[neiborts[i] - 1]; 
         bool enter = true; 
         int size_main = main_vertex->neighbors.size();
         for(int i = 0; i < size_main; i++) {
            if(collateral_vertex == main_vertex->neighbors[i]) {
               enter = false; 
               break; 
            }
         }
         if(enter) {
            main_vertex->neighbors.push_back(collateral_vertex); 
            collateral_vertex->neighbors.push_back(main_vertex);
         }

      } 
   }

   int size() {
      return quantity; 
   }


   ~Graph() {
      for(int i = 0; i < quantity; i++) {
         delete this->all_vertex[i]; 
      }
      
   }

};

vector<int> find_way(Graph& first, int begin, int end) {
   vector<int> way; 
   if(begin > first.size() || end > first.size()) return way;
   Vertex* begin_way = first.givevertex(begin); 
   Vertex* end_way = first.givevertex(end);
   queue<Vertex*> a;
   a.push(begin_way); 
   begin_way->label = 0; 
   while(!a.empty() || end_way->label == -1) {
      int k = 1; 
      Vertex* help = a.front(); 
      a.pop(); 
      int size = help->neighbors.size(); 
      for(int i = 0; i < size; i++) {
         Vertex* sosed = help->neighbors[i]; 
         if(sosed->label == -1) {
            a.push(sosed); 
            sosed->label = help->label + 1;
         }
      } 
   }
   vector<int> help {end}; 
   int v = end_way->label; 
   Vertex* last_help = end_way; 
   while(last_help != begin_way) {
      for(int i = 0; ; i++) {
         if(last_help->neighbors[i]->label == v - 1){
            help.push_back(last_help->neighbors[i]->name);
            last_help = last_help->neighbors[i];
            v--;
            break;
         }
      }
   }
   int way_size = help.size();
   for(int i = way_size - 1; i >= 0; i--) {
      way.push_back(help[i]);
      cout << help[i]; 
   }
   return way;
}

int main() {
   Graph first;
   first.vertex_creation(7); 
   
   vector<int> a{4, 7, 2};
   first.vertex_editing(1, a);
   a.clear(); 
   
   a = {1, 5, 3}; 
   first.vertex_editing(2, a); 
   a.clear();

   
   a = {2, 6}; 
   first.vertex_editing(3, a); 
   a.clear();

   
   a = {1, 7}; 
   first.vertex_editing(4, a); 
   a.clear();

   
   a = {2, 7, 6}; 
   first.vertex_editing(5, a); 
   a.clear();

   
   a = {7, 5, 3}; 
   first.vertex_editing(6, a); 
   a.clear();

   
   a = {4, 5, 6, 1}; 
   first.vertex_editing(7, a); 
   a.clear();

   int begin= 1; 
   int end = 6; 
   vector<int> way = find_way(first, begin, end);
}