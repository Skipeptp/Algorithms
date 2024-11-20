#include <cstddef>
#include "list.h"
#include <stdexcept>


struct ListItem
{
    ListItem *previous = nullptr;
    ListItem *next = nullptr;
    Data value;
};

struct List
{
    ListItem *head = nullptr;
};

List *list_create()
{
    
}

void list_delete(List *list)
{
    while (list->head)
        list_erase_first(list);

    delete list;
}

ListItem *list_first(List *list)
{
    return list->head;
}

Data list_item_data(const ListItem *item)
{
    return item->value;
}

ListItem *list_item_next(ListItem *item)
{
    return item->next;
}

ListItem *list_item_prev(ListItem *item)
{
    return item->previous;
}

ListItem *list_insert(List *list, Data data)
{
   ListItem *new_item = new ListItem;
    new_item->previous = nullptr;
    new_item->next = list->head;
    new_item->value = data;

    if (list->head) {
        list->head->previous = new_item;
    }
    list->head = new_item;
    return new_item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    ListItem *new_item = new ListItem;
    new_item->previous = item;
    new_item->next = item->next;
    new_item->value = data;

    if (item->next) 
        item->next->previous = new_item;
    item->next = new_item;
    return new_item;
}

ListItem *list_erase_first(List *list)
{
     ListItem *temp_item= list->head->next;
    if (temp_item) temp_item->previous = nullptr;
    delete list->head;
    list->head = temp_item;
    return list->head;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    ListItem *temp_item= item->next->next;
    if (temp_item) temp_item->previous = item;
    delete item->next;
    item->next = temp_item;
    return temp_item;
}