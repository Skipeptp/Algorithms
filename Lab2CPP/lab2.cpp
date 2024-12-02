#include <iostream>
#include <fstream>
#include "stack.h"

using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Файл ввода не предоставлен." << endl;
        return 1;
    }

    ifstream input(argv[1]);
    Stack *stack = stack_create();
    string tag;
    int index = 0;

    while (input >> tag) {
        if (tag[0] == '<' && tag[tag.size() - 2] != '/') {
            stack_push(stack, tag);
        } else if (tag[0] == '<' && tag[1] == '/') {
            if (stack_empty(stack)) {
                index++;
                break;
            }
            string openingTag = stack_get(stack);
            stack_pop(stack);
            string expectedClosingTag = "</" + openingTag.substr(1);
            if (tag != expectedClosingTag) {
                index++;
                break;
            }
        }
    }

    cout << (index ? "NO" : "YES") << endl;

    stack_delete(stack);
    return 0;
}