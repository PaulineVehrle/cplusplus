#include<iostream>
#include<cstdlib>

bool is_operand(char* tab){
    return ((tab[0]>='0') and (tab[0]<='9'));
}

int* new_stack(int n){
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

int operation(int* stack, char a, char b, char c){
    if (c=='+'){
        return a + b;
    }
    else if (c=='x'){
        return a*b;
    }
    else if (c=='-'){
        return b-a;
    }
    else if (c=='/'){
        return b/a;
    }
    return 0;
}

int rpn_eval(int n, char* tab[]){
    int* stack =new_stack(n);
    int top = 0;
    for (int i=0; i<n ; i++){ // partir de 0
        print_stack(&top, stack);
        if (is_operand((tab[i]))){
            int a=atoi(tab[i]);
            push(stack, &top, a);
        }
        else{
            if (tab[i][0]=='!'){
                stack[top - 1]=(-1)*stack[top - 1];
            }
            else{
                (stack)[top-2]=operation(stack,stack[top-1],stack[top-2], *(tab[i]));
                pop(stack, &top);
            }
        }    
    }
    int a = delete_stack(stack, &top);
    return a;
}

int main(int argc, char* argv[]){
    std::cout << rpn_eval(argc-1,argv+1) << std::endl;
    return 0;
}

