#ifndef KCHE_H
#define KCHE_H
#include "ring_list.h"

struct KeyType {
	int series;
	int number;

	bool operator>(const KeyType& other) const {
		return (series > other.series && series != other.series) ||
			(number > other.number && series == other.series);
	};
	bool operator==(const KeyType& other) const {
		return ((series == other.series) && (number == other.number));
	}
};

enum Color { red, black };

struct Node {
	KeyType key;
	Node* RightChild;
	Node* LeftChild;
	Node* Parent;
	Elem* DuplicationList;
	Color color;

	Node(KeyType key, Node* RightChild, Node* LeftChild, Node* Parent, Elem* DuplicationList, Color color) : key{ key },
		RightChild{ RightChild }, LeftChild{ LeftChild }, Parent{ Parent }, DuplicationList{ DuplicationList }, color{ color } {}
};

extern Node* nill;

Node* init(); // инициализация пустого дерева

Node* insert_in_tree(Node* T, KeyType key, int string_num); // добавление в дерево

void straight_write(Node* root, int indent); // печать

Node* search_in_tree(Node* T, KeyType key); // поиск узла в дереве

Node* delete_in_tree(Node* node, KeyType key, int string_num); // удаление (при совпадении номера строки и ключа)

Node* clear_tree(Node* root); // удаление всего дерева (очистка памяти)

#endif