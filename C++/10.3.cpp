#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <algorithm>
#include <initializer_list>

using std::initializer_list; 
using std::cout; 
using std::cin; 
using std::string; 
using std::ofstream; 
using std::ifstream; 
using std::istream;
using std::ostream;
using std::ios; 


enum ClassID{
WINDOW,
GRAFIC_ELEMENT,
ELLIPSE 
};

template<typename T>
class vector {
private:
   T* begin_array; 
   int quauntity; 
   bool not_initialized;
public:

   int size() const {
      return this->quauntity;
   }

   T* gbegin() {
      return this->begin_array; 
   }

   vector() {
      this->begin_array = nullptr; 
      this->quauntity = 0; 
      not_initialized = 1;
   }

   vector (const vector& other) {
      if(other.quauntity == 0) {
         this->begin_array = nullptr;
      }
      else this->begin_array = new T[other.quauntity];
      this->quauntity = other.quauntity;
      if(other.not_initialized) {
         this->not_initialized = 1;
         return;
      }
      for(int i = 0; i < other.quauntity; i++) {
         begin_array[i] = other.begin_array[i];
      }
      this->not_initialized = 0;
   }

   vector(int quauntity) {
      assert(quauntity >= 0);
      if(quauntity == 0) {
         this->begin_array = nullptr;
         this->quauntity = 0; 
      } 
      else{
         this->quauntity = quauntity; 
         this->begin_array = new T[quauntity]; 
      }
      not_initialized = 1;
   }

   vector(int quauntity, T value) {
      assert(quauntity >= 0);
      this->quauntity = quauntity; 
      if(quauntity == 0) {
         this->begin_array = nullptr; 
         not_initialized = 1;
      }
      else { 
         this->begin_array = new T[this->quauntity];
         this->not_initialized = 0;
         for(int i = 0; i < this->quauntity; i++) {
            begin_array[i] = value;
         } 
      }
   }

   vector(initializer_list<T> other) {
      this->quauntity = other.size();
      if(this->quauntity == 0) {
         this->begin_array = nullptr;
         not_initialized = 1;
      } 
      else {
         this->begin_array = new T[this->quauntity];
         this->not_initialized = 0;
         for(int i = 0; i < this->quauntity; i++) {
            begin_array[i] = *(other.begin() + i);
         } 
      }
   }

   void operator=(initializer_list<T> other) {
      if(other.size() != this->quauntity) {
         delete[] this->begin_array;
         this->quauntity = other.size();
         if(this->quauntity == 0) {
            this->begin_array = nullptr; 
            not_initialized = 1;
            return;   
         }
         this->begin_array = new T[this->quauntity];
      }
      if(this->quauntity != 0) not_initialized = 0;
      else not_initialized = 1;
      for(int i = 0; i < this->quauntity; i++) {
         begin_array[i] = *(other.begin() + i);
      }
   }

   void operator=(const vector& other) {
      if(other.size() != this->quauntity) {
         delete[] this->begin_array;
         this->quauntity = other.size();
         if(this->quauntity == 0) {
            this->begin_array = nullptr; 
            not_initialized = 1;
            return;   
         }
         this->begin_array = new T[this->quauntity];
      }
      if(this->quauntity != 0) not_initialized = 0;
      else not_initialized = 1;
      for(int i = 0; i < this->quauntity; i++) {
         begin_array[i] = other.begin_array[i];
      }
   }

   const T& operator[](int i) const {
      try{
         if(i >= this->quauntity || i < 0) throw -1; 
      }
      catch(int a) {
         
         cout << "Invalid number of coloumns" << '\n'; 
         throw; 
      }
      return this->begin_array[i];
   }

   T& operator[](int i) {
      try{
         if(i >= this->quauntity || i < 0) throw -1; 
      }
      catch(int a) {
         cout << "Invalid number of coloumns" << '\n';
         throw; 
      }
      not_initialized = 0; 
      return this->begin_array[i];
   }

   void resize(int other_size) {
      assert(!(other_size < 0));
      if(other_size == this->quauntity) return;
      if(other_size == 0) {
         delete[] this->begin_array;
         this->quauntity = 0;
         this->begin_array = nullptr;
         not_initialized = 1; 
      }
      else{   
         T* new_array = new T[other_size];
         if(!(this->not_initialized)) {
            int k = 0;
            if(other_size < this->quauntity) k = other_size;
            else k = this->quauntity;
            for(int i = 0; i < k; i++) {
               new_array[i] = this->begin_array[i];
            }
         }
         this->quauntity = other_size;
         delete[] this->begin_array;
         this->begin_array = new_array;
      }
   }

   void push_back(T value) {
      resize(this->quauntity + 1); 
      this->begin_array[this->quauntity - 1] = value;
      this->not_initialized = false;

      
   }
  
   ~vector() {
      
      delete[] this->begin_array;
   }

};


class Grafic_Interface_element {
   protected: 
      string name;
      int x_coordinates; 
      int y_coordinates; 
      int occupied_width; 
      int occupied_height; 
      bool visible;
   public:

      Grafic_Interface_element() : x_coordinates(5), y_coordinates(5), occupied_height(2), occupied_width(2), visible(0), name("Unnamed") {

      }

      void change_visibility(bool other) {
         this->visible = other; 
      }

      void resize_element(int new_width, int new_height = 0) {
         assert(new_width >= 0 && new_height >= 0); 
         this->occupied_width = new_width; 
         this->occupied_height = new_height; 
      }
      virtual ClassID getclassID() {
         return GRAFIC_ELEMENT; 
      }
      
      friend void selializeGrElement(const Grafic_Interface_element* object);
      friend void serialize(Grafic_Interface_element* element);
      virtual void info() {
         cout << "Name: " << name << '\n';
         cout << "Coordinates: " << x_coordinates << 'x' << y_coordinates << ";" << '\n'; 
         cout << "Height:  " << occupied_height << ", " << "Windht :" << occupied_width << ';' << '\n';   
         cout << "Visible: " ; 
         if(this->visible) cout << "on" << ';' << '\n'; 
         else cout << "off" << ';' << '\n'; 
      }

      void change_position(int dx, int dy) {
         this->x_coordinates += dx; 
         this->y_coordinates += dy; 
      }

      void change_name(string new_name) {
         this->name = new_name;
      }
      Grafic_Interface_element(const Grafic_Interface_element& other) = delete; 
      void operator=(const Grafic_Interface_element& other) = delete; 

      Grafic_Interface_element(string name, int x_coord = 5, int y_coord = 5, int height = 2, int width = 2) {
         assert(y_coord >= 0 && x_coord >= 0);
         resize_element(width, height); 
         this->x_coordinates = x_coord; 
         this->y_coordinates = y_coord; 
         this->name = name;
         if(height == 0 || width == 0) {
            this->visible = 0; 
            return; 
         }
         this->visible = 1; 
      }

      virtual ~Grafic_Interface_element() 
      {}
}; 


class Window : public Grafic_Interface_element { 
   protected: 
      vector<Grafic_Interface_element*> elements_window; 

   public:
      Window() : Grafic_Interface_element("Unnamed", 100, 100, 20, 20)
      {}

      Window(string name, int x_coord = 100 , int y_coord = 100 , int height = 20, int width = 20) 
      : Grafic_Interface_element(name, x_coord, y_coord, height, width) 
      {}

      void info() override {
         Grafic_Interface_element::info(); 
         cout << "Snap elements to window : "; 
         for(int i = 0; i < elements_window.size(); i++) {
            Grafic_Interface_element* help = elements_window[i]; 
            help->info(); 
         }
      }
      
      ClassID getclassID() override {
         return WINDOW; 
      }
      void snap_to_window(Grafic_Interface_element* element) {
         this->elements_window.push_back(element); 
      }
      friend void selializeWindow(const Window* object);
      ~Window() {
         for(int i = 0; i < elements_window.size(); i++) {
            delete elements_window[i]; 
         }
         elements_window.resize(0);
      }
}; 


class Ellipse : public Window {
   protected: 
      string FillColour; 
      string BorderColour;
   public: 
   Ellipse() : Window("Cut_Ellipse"), FillColour("Black"), BorderColour("White") 
   {}

   Ellipse(string FillColour, string BorderColour, int x_coord = 0, int y_coord = 0, int height = 0, int width = 0)
    : Window("Cut_Ellipse", x_coord, y_coord, height, width), FillColour(FillColour), BorderColour(BorderColour) 
   {}
   friend void selializeEllipse(const Ellipse* object);
  
   ClassID getclassID() override {
         return ELLIPSE; 
      }

   void change_fillcolour(string new_colour) {
      this->FillColour = new_colour; 
   }

   
   void info() override {
      Window::info(); 
      cout << "FillColour: " << FillColour; 
      cout << "BorderColour: " << BorderColour; 
   }

   void change_bordercolour(string new_colour) {
      this->BorderColour = new_colour; 
   }
}; 

void selializeWindow(const Window* object) {
   ifstream fin("file.txt", ios::app); 

   fin.close();
}


void selializeEllipse(const Ellipse* object) {
   ifstream fin("file.txt", ios::app); 

   fin.close();
}

void selializeGrElement(const Grafic_Interface_element* object) {
   ifstream fin("file.txt", ios::app); 

   fin.close();
}

void serialize(Grafic_Interface_element* element) { 
ifstream fin("file.txt", ios::app); 
if(element->getclassID() == WINDOW) {
   fin >> "WINDOW";
   Window* w = dynamic_cast<Window*>(element); 
   selializeWindow(w); 
}
else {
   if(element->getclassID() == ELLIPSE) {
      Ellipse* w = dynamic_cast<Ellipse*>(element);
      selializeEllipse(w);  
   }
   else selializeGrElement(element);
}

void deserialize

}

int main() {


}