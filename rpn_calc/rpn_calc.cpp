#include<iostream>
#include<cstdlib>
#include"stack.h"

bool is_operand(const char* tab){
    return ((tab[0]>='0') and (tab[0]<='9'));
}

//vr: pour la lisibilité du code mets a et b dans le même ordre
// mets des noms plus parlant que a, b et a
int operation(int* stack, const char expr1, const char expr2, const char op){
    if (op=='+'){
        return expr1+expr2;
    }
    else if (op=='x'){
        return expr1*expr2;
    }
    else if (op=='-'){
        return expr2-expr1;
    }
    else if (op=='/'){
        return expr2/expr1;
    }
    return 0;
}

// vr: fais la fonction pop et utilise-la
int rpn_eval(int n, const char* tab[]){
    int* stack =init_stack(n);
    int top = 0;
    for (int i=0; i<n ; i++){ // partir de 0
        print_stack(top, stack);
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
    int a = stack[0];
    delete_stack(stack);
    return a;
}

