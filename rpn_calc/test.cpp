#include<iostream>
#include<cstdlib>
#include"rpn_calc.h"

void test_rpn_calc(){
    const char* expr [] = {"5", "6", "+", "7", "x", "9", "!", "+"};
    std::cout << rpn_eval(8,expr) << std::endl;
}

int main(int argc, char* argv[]){
    test_rpn_calc();
    return 0;
}


