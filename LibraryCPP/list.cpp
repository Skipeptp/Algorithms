#include <cstddef>
#include "list.h"
#include <stdexcept>

struct ListItem
{
    ListItem *previous_item = nullptr;
    ListItem *next_item = nullptr;
    Data value;
};

struct List
{
    ListItem *first = nullptr;
};

List *list_create()
{
    return new List;
}

void list_delete(List *list)
{
    while (list->first)
        list_erase_first(list);

    delete list;
}

ListItem *list_first(List *list)
{
    return list->first;
}

Data list_item_data(const ListItem *item)
{
    return item->value;
}

ListItem *list_item_next(ListItem *item)
{
    return item->next_item;
}

ListItem *list_item_prev(ListItem *item)
{
    return item->previous_item;
}

ListItem *list_insert(List *list, Data data)
{
    ListItem *ptr = new ListItem;

    ptr->previous_item = nullptr;
    ptr->next_item = list->first;
    ptr->value = data;

    if (list->first) {
        list->first->previous_item = ptr;
    }

    list->first = ptr;

    return ptr;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    ListItem *ptr = new ListItem;
    ptr->previous_item = item;
    ptr->next_item = item->next_item;
    ptr->value = data;

    if (item->next_item) 
        item->next_item->previous_item = ptr;
    item->next_item = ptr;

    return ptr;
}

ListItem *list_erase_first(List *list)
{

    ListItem *temp_ptr;
    temp_ptr = list->first->next_item;
    if (temp_ptr) temp_ptr->previous_item = nullptr;
    delete list->first;
    list->first = temp_ptr;

    return list->first;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    ListItem *temp_ptr;
    temp_ptr = item->next_item->next_item;
    if (temp_ptr) temp_ptr->previous_item = item;
    delete item->next_item;
    item->next_item = temp_ptr;

    return temp_ptr;
}