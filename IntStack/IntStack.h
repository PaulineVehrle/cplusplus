#include<iostream>

class IntStack{

public:
    IntStack (int s) : size(s), top(0){// variable dans le privé (non de la variable)
        if (s>0){
            tab = new int [size];
        } 
        else {
            std::cout << "la taille est inférieur a 0\n";
            throw(1);
        }
    }

    //constructeur de copie
    IntStack (const IntStack& rst) : size(rst.size), top(rst.top), tab(new int[size]) {}

    ~IntStack (){
        delete [] tab;
    }

    bool is_full(){
        return top==size;
    }

    void push(int e){
        if (not(is_full())){
            tab[top]=e;
            top = top + 1;
        }
        else {
            std::cout << "la pile est pleine\n";
            throw(2);
        }
    }    
    
    int pop(){
        if (not(is_empty())){
            top = top-1;
            return tab[top];
        }
        else {
            std::cout << "la pile est vide\n";
            throw(3);
        }
    }

    void print(){
        std::cout << "[";
        for (int i=0; i<top; i++){
            std::cout << tab[i] << " ";
    }
    std::cout << "[" << std::endl;
    }


    bool is_empty(){
        return top==0;
    }


private:
    int top;
    int* tab;
    int size;

};



int* init_stack(int n);
void print_stack (int* top, int* stack);
int delete_stack(int* stack, int* top);
void push(int* stack, int* addresse_top, int operande);
int pop(int* stack, int* top);