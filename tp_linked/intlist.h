#include<iostream>
// Integer[4] {12,56}
class IntCell { 
   friend class IntList; //Aide mémoire pour où le mettre: on choisit ses copains 
   ~IntCell(){}
private:
   // IntCell (int val): value(val),next(nullptr),prev(nullptr) {}
   IntCell (int value, IntCell* next=nullptr, IntCell* prev=nullptr): value(value),next(next),prev(prev){}
   IntCell (const IntCell& addresse): value(addresse.value),next(addresse.next),prev(addresse.prev){}
   int value;
   IntCell* next;
   IntCell* prev;
    // tout le code de la IntCell en private
    // le constructeur et ses 3 attributs
    // il n'y a aucune autre méthode en dehors du constructeur
};

class IntList {
public:    
   // constructeur et destructeur
   IntList () : top(nullptr),bottom(nullptr),t(0){}

   void add_front (int a) {
      IntCell* p=new IntCell(a, top);
      if (is_empty()){
         top = p;
         bottom = p;
      }
      else {
         top->prev = p; // ajoute une addresse precédente à l'ancien premier
         top = p;//devient la pemière, sa suivante c'est top       
      }
   }

   void add_back (int a) {
      IntCell* p = new IntCell (a,nullptr, bottom);
      if (is_empty()){
         top = p;
         bottom=p;
      }
      else{
         bottom->next = p;
         bottom = p;
      }
   }

   void remove_front () {
      if (is_empty()){
         std::cout << "il n'y a rien a enlever" << std::endl;
      }
      else if (top==bottom){
         delete top;
         top=0;
         bottom=0;
      }
      else {
         top = top->next;
         delete top->prev;
         top->prev = 0;
      }
   }

   void remove_back () {
      if (is_empty()){
         std::cout << "il n'y a rien a enlever" << std::endl;
      }
      else if (top==bottom){
         delete top;
         top=0;
         bottom=0;
      }
      else {
         bottom = bottom->prev;
         delete bottom->next;
         bottom->next = 0;
      }
   }

   void remove (int a) {
      int i = 0;
      IntCell* current = top; // comme pour print, on parcourt toute la liste
      while (current!=0){ //current est une addresse
         i=i+1;
         if (current->value==a){
            if (current==top){
               if (top==bottom){//la liste a une seule case //il va enlever la case ou l'addresse locle current??? il n'enlève pas 2 fois
                  top=0;
                  bottom =0;
                  delete current;
                  current=0;
               }
               else {
                  top =current->next;
                  current=top;
                  delete current->prev;
                  current->prev=0;
               }
            }
            else if (current==bottom) {
               if (top==bottom){}//on ne fait rien car ça aura déjà été fait avant
               else {
                  bottom =current->prev;
                  current=bottom;
                  delete current->next;
                  current->next=0;
               }
            }
            else{
               (current->next)->prev = current->prev;
               current = current->next;
               delete (current->prev)->next;
               (current->prev)->next =current;
            }
         }
         else {
            current=current->next;
         }
      }
   }

   bool search (int a) {
      IntCell* current = top;
      while (current!=0){ 
         if (current->value==a){
            return 1;
         }
         current=current->next;
      }
      return 0;
   }

   void print () {
      IntCell* current = top;
      std::cout << "{";
      while (current!=0){ //current est une addresse
         std::cout << current->value << " ";//=(*current).value
         current=current->next;
      }
      std::cout << "}" << std::endl;
   }

   bool is_empty (){
      return (top==0) && (bottom==0);
   }

   int len (){
      IntCell* current = top;
      int i = 0;
      while (current!=0){
         i=i+1;
         current=current->next;
      }
      return i;
   }

   ~IntList(){
      while(top!=0){
         if (len()==1){
            delete top;
            top = 0;
         }
         else {
            top = top->next;
            delete top->prev;
         }
      }
   }
private:
   IntCell* top;
   IntCell* bottom;
   int t; // numero de prochaine case
   // les attributs de la liste
};