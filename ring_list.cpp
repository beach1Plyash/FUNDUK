#include <iostream>
#include "ring_list.h"

// Печать списка
void print_list(Elem* start) {
    if (start == nullptr) {
        std::cout << "Empty list" << std::endl;
        return;
    }

    Elem* current = start;
    do {
        std::cout << current->data << " ";
        current = current->next;
    } while (current != start);
    std::cout << std::endl;
}



// Создание пустого списка
Elem* create_list() {
    return nullptr;
}

// Добавление элемента в список
Elem* add_to_list(Elem* start, int elem) {
    Elem* new_node = new Elem{ elem, nullptr, nullptr };

    if (start == nullptr) {
        new_node->next = new_node; // Указывает на себя
        new_node->prev = new_node; // Указывает на себя
        return new_node;
    }
    else {
        new_node->next = start;
        new_node->prev = start->prev;
        start->prev->next = new_node;
        start->prev = new_node;
    }

    return start; // Возвращаем начальный элемент списка
}

// Проверка наличия элемента в списке
bool in_list(int val, Elem* list_pointer) {
    if (list_pointer == nullptr) return false;

    Elem* current = list_pointer;
    do {
        if (current->data == val) {
            return true;
        }
        current = current->next;
    } while (current != list_pointer);
    return false;
}

// Удаление всех элементов списка
Elem* remove_all(Elem* first_pointer) {
    if (first_pointer == nullptr) return nullptr;

    Elem* current = first_pointer;
    do {
        Elem* temp = current;
        current = current->next;
        delete temp;
    } while (current != first_pointer);

    return nullptr; // Возвращаем nullptr, так как список пуст
}

// Удаление конкретного элемента
Elem* remove_elem(Elem* head, int elem) {
    if (head == nullptr) return nullptr;

    Elem* current = head;
    do {
        if (current->data == elem) {
            if (current->next == current) { // Если элемент единственный в списке
                delete current;
                return nullptr;
            }
            else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
                Elem* temp = current;
                if (current == head) { // Если удаляем голову
                    head = current->next;
                }
                current = current->next;
                delete temp;
            }
        }
        else {
            current = current->next;
        }
    } while (current != head);

    return head; // Возвращаем начальный элемент списка
}