#include "int_stack.h"
#include<iostream>

int main () {
    try {
        std::cout << "première pile "<< std::endl;
        IntStack st (12); //pile de taille 12
        st.print(); // [[
        st.push(10);
        st.push(20);
        st.push(30);
        st.print(); // [10 20 30 [
        std::cout << st.pop() << std::endl;
        std::cout << "test erreur taille négative "<< std::endl;
        IntStack st1 (-2);
    }
    catch (int i){} // le message d'erreur est déjà dans la définiton de la classe
    try{
    std::cout << "test erreur pile vide "<< std::endl;
    IntStack st2 (5);
    st2.print();
    st2.pop();
    }
    catch (int i){}
    try{
    std::cout << "test erreur pile pleine "<< std::endl;
    IntStack st3 (2);
    st3.push(3);
    st3.push(4);
    st3.print();
    st3.push(10);
    }
    catch (int i){}
    return 0;
}

