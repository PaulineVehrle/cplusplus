#include<iostream>
#include<cstdlib>
#include"stack.h"

bool is_operand(const char* tab){
    return ((tab[0]>='0') and (tab[0]<='9'));
}

int operation(int* stack, const char a, const char b, const char c){
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

int rpn_eval(int n, const char* tab[]){
    int* stack =init_stack(n);
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

