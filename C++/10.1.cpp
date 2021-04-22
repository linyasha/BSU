#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>
#include <initializer_list>


using std::initializer_list; 
using std::vector; 
using std::cout; 
using std::cin; 
using std::string; 
using std::istream;
using std::ostream;


//     схема наследования
//                                        Графический элемент интерфейса 
//                                          \\       \\      \\       \\     \\
//                                        Кнопка    Окно     Ярлык    Значек
//                                                    \\
//                                                    
//
//


template <typename T>
struct Node {
   public:
      T object;
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
         Node<T>* a = new Node<T>;
         a->object = b;
         if(is_empty()) {
            this->head = a;
            a->next = nullptr;
         }
         else {
            a->next = this->head; 
            this->head = a; 
         }
         count++;
      }

      Node<T>* before_element_find(T element) {
         if(count == 1) return nullptr; 
         Node<T>* help = this->head; 
         for(int i = 1; i < this->count; i++) {
            if(help->next->object == element) return help; 
            help = help->next;
         }
         return nullptr;
      }

      T operator[](int n) {
         assert(count != 0 || n < count);
         Node<T>* a = this->head;
         for(int i = 1; i < n; i++) {
            a = a->next;
         }
         return a->object; 
      }

      const T operator[](int n) const {
         assert(count != 0 || n < count);
         Node<T>* a = this->head;
         for(int i = 1; i < n; i++) {
            a = a->next;
         }
         return a->object; 
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
         if(a != nullptr) assert(!is_empty() && a->next != nullptr);;
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
      LinkedList<Grafic_Interface_element*> elements_window; 

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

      void untie_element(Grafic_Interface_element* element) {
         elements_window.remove(elements_window.before_element_find(element)); 
      }

      void snap_to_window(Grafic_Interface_element* element) {
         this->elements_window.insert(element); 
      }

      ~Window() {
         for(int i = 0; i < elements_window.size(); i++) {
            delete elements_window[i]; 
         }
         elements_window.delete_list(); 
      }
}; 

class Folder : Window {
   protected: 
      vector<Grafic_Interface_element*> content; 
   public: 
      Folder() : Window() 
      {}

      Folder(string name, int x_cord, int y_cord, int height, int width)
       : Window(name, x_cord, y_cord, height, width) {}

      void add_content(Grafic_Interface_element* element) {
         this->content.push_back(element); 
      }
      void add_content(vector<Grafic_Interface_element*> new_content) {
         this->content = new_content; 
      }

      
      void info() override {
         Window::info(); 
         cout << "Content: "; 
         for(int i = 0; i < content.size(); i++) {
            content[i]->info(); 
         }
      }

      void delete_allcontent () {
         for(int i = 0; i < content.size(); i++) {
            delete content[i]; 
         }
         content.clear();
      }

      ~Folder() {
         delete_allcontent(); 
      }

      void delete_content(Grafic_Interface_element* need_delete) {
         for(int i = 0; i < this->content.size(); i++) {
            if(need_delete == this->content[i]) {
               delete need_delete; 
               this->content.erase(this->content.begin() + i);
               break;
            }
         }
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

class Window_Interface : Grafic_Interface_element {
   protected: 
      string Text;
      string collour_text; 
   public:
      Window_Interface() : Grafic_Interface_element() , Text("Not Text"), collour_text("Black")
      {}

      Window_Interface(string name, string text = "Not Text", int width = 2, int height = 2, int x_coord = 5, int y_cord = 5, string collour = "Black") 
      : Grafic_Interface_element(name, x_coord, y_cord, height, width), Text(text), collour_text(collour)
      {}

      void change_collourtext(string new_colour) {
         this->collour_text = new_colour; 
      }

      void info() override {
      Grafic_Interface_element::info(); 
      cout << "Text: " << Text; 
      cout << "Colour Text: " << collour_text; 
   }
      void change_text(string new_text) {
         this->Text = new_text; 
      }
};

class Button : public Window_Interface {
   private: 
      string filling_colour; 
   public: 
   
   Button() : Window_Interface("Button"), filling_colour("White") {}

   Button(int x_coord, int y_coord, string ToolText, string colour_t, string Fillcolour, int height = 0, int width = 0) 
   :Window_Interface("Button", ToolText,  x_coord, y_coord, height, width, colour_t), filling_colour(Fillcolour) 
   {}

   void new_fillingcolour(string new_colour) {
      this->filling_colour = new_colour; 
   }
};

class Text_Box : public Window_Interface {
   protected: 
      bool read_only; 
   public: 
      Text_Box() : Window_Interface("TextBox"), read_only(0) 
      {}

      Text_Box(string main_text, int x_cord, int y_cord, int height, int width, string text_colour, bool read_only)
       : Window_Interface("TextBox", main_text, width = 2, height = 2, x_cord = 5, y_cord = 5, text_colour = "Black"), read_only(read_only) 
       {}

      void set_read_only(bool a) {
         read_only = a; 
      }

      void info() override {
         Window_Interface::info(); 
         if(read_only) cout << "Read only: on" << '\n'; 
         else cout << "Read only: off" << '\n';  
      }

      void delete_text() {
         this->Text.clear(); 
      }

      void delete_piece_of_text(string piece) {
         size_t pos = this->Text.find(piece);
            if(pos != string::npos){
               this->Text.erase(pos, piece.length());
            }
      }

      void add_word_in_text(string new_word) {
         this->Text += new_word; 
      }

      void new_text(string new_text) {
         this->Text = new_text; 
      }
};

class HyperLinkLabel : public Window_Interface {
   protected: 
      Window_Interface* connected_object; 
      string URL; 
   public: 
      HyperLinkLabel() : Window_Interface(), connected_object(nullptr) 
      {}

      HyperLinkLabel(string text, Window_Interface* object, string URL, int x, int y, int h, int w, string colour = 0)
      : Window_Interface("HyperLink", text, w, h, x, y ,colour), URL(URL), connected_object(object)  
      {}

      void info() override {
         Window_Interface::info(); 
         cout << "Connected object: "; 
         connected_object->info(); 
         cout << '\n' << "URL: " << URL << '\n'; 
      }

      void set_URL(string new_URL) {
         this->URL = new_URL; 
      }

};


int main() {
   
}