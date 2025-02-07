#ifndef RING_LIST_H
#define RING_LIST_H

struct Elem {
    int data;
    Elem* next;
    Elem* prev;
};

void print_list(Elem* start); // Печать списка
Elem* create_list(); // Создание пустого списка
Elem* add_to_list(Elem* start, int Elem); // Добавление элемента в список
Elem* remove_all(Elem* first_pointer); // Удаление всех элементов списка
Elem* remove_elem(Elem* head, int elem); // Удаление конкретного элемента
bool in_list(int val, Elem* list_pointer); // Проверка наличия элемента в списке

#endif
