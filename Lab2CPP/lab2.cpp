#include <iostream>
#include <fstream>
#include <string>
#include "stack.h"

using namespace std;

bool is_matching(const string &opening, const string &closing) {
    return opening == closing.substr(1, closing.size() - 2);
}

int main(int argc, char** argv) {
    
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    
    ifstream input(argv[1]);
    if (!input.is_open()) {
        cerr << "Error opening file: " << argv[1] << endl;
        return 1;
    }

    
    Stack *stack = stack_create();
    string line;

    
    while (getline(input, line)) {
        if (!line.empty() && line.front() == '<' && line.back() == '>') {
            if (line[1] == '/') { 
                if (stack_empty(stack)) {
                    cout << "NO" << endl;
                    stack_delete(stack);
                    return 0;
                }

                
                string *top_tag = static_cast<string*>(stack_get(stack));
                if (!is_matching(*top_tag, line)) {
                    cout << "NO" << endl;
                    delete top_tag;
                    stack_delete(stack);
                    return 0;
                }
                delete top_tag;
                stack_pop(stack);
            } else { 
                string *tag = new string(line);
                stack_push(stack, static_cast<Data>(tag));
            }
        }
    }

    
    if (!stack_empty(stack)) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
    }


    stack_delete(stack);
    return 0;
}