#include<iostream>
#include<cstdlib>

// vr: tu peux renvoyer directement 
int* init_stack(int n){
  return new int[n];
  // int* stack = new int[n];
  // return stack;
}

// vr: tu n'as pas besoin de l'adresse de top ici juste de sa valeur
void print_stack (int top, int* stack){
    std::cout << "[";
    for (int i=0; i<top; i++){
        std::cout << stack[i] << " ";
    }
    std::cout << "[" << std::endl;
}

// vr: delete_stack delete la stack et ne renvoie rien
void delete_stack(int* stack){
  delete stack; // vr: c'est faux vois-tu pourquoi ?
}

void push(int* stack, int* addresse_top, int operande){
    stack[*addresse_top]=operande;
    *addresse_top= *addresse_top + 1;
}

int pop(int* stack, int* top){// int stack[]=int* stack
    *top = *top -1;
    return stack[*top];
}

