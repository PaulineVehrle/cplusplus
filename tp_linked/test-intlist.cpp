#include"intlist.h"
int main () {
  // création d'une liste vide
  IntList l;
  //l.print();
  
  // ajout de 11 en tête de liste
  l.add_front(11);
  //l.print(); // {11 }

  // ajout de 12 en queue de liste
  l.add_back(12);
  //l.print(); // {11 12 }

  // ajout de 13 en queue de liste
  l.add_back(13);
  //l.print(); // {11 12 13 }

  l.add_back(11);
  l.add_front(15);
  l.add_front(11);
  l.print();
  std::cout << "on enlève 11 de la liste : ";
  l.remove(11);
  l.print();

  bool b1 = l.search(12);
  std::cout << "Y a-t-il 12 dans la liste? " << std::boolalpha << b1 << std::endl;
  bool b2 = l.search(11);
  std::cout << "Y a-t-il 11 dans la liste? " << std::boolalpha << b2 << std::endl;



  return 0;
}