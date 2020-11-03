#include<iostream>
#include<cstdlib>

int* init_stack(int n){
    int* stack = new int[n];
    return stack;
}

void print_stack (int* top, int* stack){
    std::cout << "[";
    for (int i=0; i<*top; i++){
        std::cout << stack[i] << " ";
    }
    std::cout << "[" << std::endl;
}

int delete_stack(int* stack, int* top){
    int a = stack[*top -1];
    delete stack;
    return a;
}

void push(int* stack, int* addresse_top, int operande){
    stack[*addresse_top]=operande;
    *addresse_top= *addresse_top + 1;
}

int pop(int* stack, int* top){// int stack[]=int* stack
    *top = *top -1;
    return stack[*top];
}

