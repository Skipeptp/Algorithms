#include <iostream>
#include <fstream>
#include <string>
#include "stack.h"

using namespace std;

int main(int argc, char** argv) {
    ifstream input(argv[1]);
    Stack *stack = stack_create();
    string line;
    bool isValid = true;

    while (getline(input, line)) {
        if (line.empty()) {
            continue;
        }

        if (line[0] == '<' && line[1] != '/') {
            if (line.size() < 2 || line[0] != '<' || line[line.size() - 1] != '>') {
                isValid = false;
                break;
            }
            string tagName = line.substr(1, line.size() - 2);
            stack_push(stack, tagName);
        } else if (line[0] == '<' && line[1] == '/') {
            if (line.size() < 3 || line[2] != ' ') {
                isValid = false;
                break;
            }
            string closingTagName = line.substr(2, line.size() - 3);
            if (stack_is_empty(stack) || stack_top(stack) != closingTagName) {
                isValid = false;
                break;
            }
            stack_pop(stack);
        } else {
            isValid = false;
            break;
        }

        if (!isValid) {
            break;
        }
    }

    if (!stack_is_empty(stack)) {
        isValid = false;

    cout << (isValid ? "YES" : "NO");

    stack_delete(stack);
    return 0;
}