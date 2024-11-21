#include <iostream>
#include <fstream>
#include "stack.h"

using namespace std;

int main(int argc, char** argv){
    ifstream input(argv[1]);
    Stack *stack = stack_create();
    string perrem;
    int index = 0;
    while(input.eof() == 0){
        input >> perrem;
        if(perrem[1] != '/'){
            for(char c: perrem){
                stack_push(stack, c);
            }
        } else {
            int i = 0;
            while(true){
                char c = stack_get(stack);
                stack_pop(stack);
                if(c == '<'){
                    break;
                } else if (perrem[perrem.size()-1-i] == '/'){
                    i++;
                    if(c == perrem[perrem.size()-1-i]){
                        break;  
                    } else {
                        index++;
                        break;
                    }
                } else if(c != perrem[perrem.size()-1-i]){
                    index++;
                    break;
                } else {
                    i++;
                }
            }
            i = 0;
        }
    }
    cout << (index ? "NO" : "YES");


stack_delete(stack);
return 0;           
}