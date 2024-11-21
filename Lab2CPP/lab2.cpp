#include <iostream>
#include <fstream>
#include <string>
#include "stack.h"

using namespace std;

// Функция для проверки соответствия открывающего и закрывающего тега
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
    bool flag = false;

    while (getline(input, line)) {
        if (!line.empty() && line.front() == '<' && line.back() == '>') {
            if (line[1] == '/') {
                if (stack_empty(stack)) {
                    flag = true;
                    break;
                }

                // Изменение: убрал static_cast, так как stack_get возвращает Data, который должен быть std::string*
                string *top_tag = static_cast<string*>(stack_get(stack));
                if (!is_matching(*top_tag, line)) {
                    flag = true;
                    delete top_tag; // Освобождаем память
                    break;
                }
                delete top_tag; // Освобождаем память
                stack_pop(stack);
            } else {
                // Изменение: убрал static_cast, так как tag уже является std::string*
                string *tag = new string(line);
                stack_push(stack, tag); // без static_cast
            }
        }
    }

    // Проверка на наличие ошибок
    if (flag || !stack_empty(stack)) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
    }

    stack_delete(stack); // Освобождаем память
    return 0;
}