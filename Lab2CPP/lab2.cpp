#include <fstream>
#include <iostream>
#include "stack.h"

using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        return 1;
    }

    ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        cerr << "Ошибка при открытии файла: " << argv[1] << endl;
        return 1;
    }

    Stack *tagStack = stack_create();
    string currentLine;
    bool isValid = true;

    while (getline(inputFile, currentLine)) {
        if (currentLine[1] == '/') {
            int index = 0;
            while (true) {
                if (stack_is_empty(tagStack)) {
                    isValid = false;
                    break;
                }
                char topChar = stack_get(tagStack);
                stack_pop(tagStack);
                
                if (topChar == '<') {
                    break;
                } else if (currentLine[currentLine.size() - 1 - index] == '/') {
                    index++;
                    if (topChar == currentLine[currentLine.size() - 1 - index]) {
                        break;  
                    } else {
                        isValid = false;
                        break;
                    }
                } else if (topChar != currentLine[currentLine.size() - 1 - index]) {
                    isValid = false;
                    break;
                } else {
                    index++;
                }
            }
        } else {
            for (char c : currentLine) {
                stack_push(tagStack, c);
            }
        }
    }

    cout << (isValid ? "YES" : "NO") << endl;

    stack_delete(tagStack);
    return 0;           
}