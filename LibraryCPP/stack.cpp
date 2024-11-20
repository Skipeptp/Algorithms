#include "stack.h"
#include "list.h"
#include <stdexcept>

struct Stack
{
    List *internalList = nullptr;
};

Stack *stack_create()
{
    Stack *stackInstance = new Stack;
    stackInstance->internalList = list_create();
    return stackInstance;
}

void stack_delete(Stack *stack)
{
    list_delete(stack->internalList);
    delete stack;
}

void stack_push(Stack *stack, Data data)
{
    list_insert(stack->internalList, data);
}

Data stack_get(const Stack *stack)
{
    return list_item_data(list_first(stack->internalList));
}

void stack_pop(Stack *stack)
{
    (void)list_erase_first(stack->internalList);
}

bool stack_empty(const Stack *stack)
{
    return (list_first(stack->internalList) == nullptr);
}