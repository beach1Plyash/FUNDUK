#include <iostream>
#include <string>
#include "kche.h"

KeyType nill_key = { 0, 0 };
Node* nill = new Node(nill_key, nullptr, nullptr, nullptr, nullptr, black);

Node* init() {
	return nullptr;
}


void add_node(Node*& root, Node*& new_node) {
	Node* y = nullptr;
	Node* x = root;

	while (x != nill) {
		y = x;
		if (y->key > new_node->key) {
			x = x->LeftChild;
		}
		else {
			x = x->RightChild;
		}
	}
	new_node->Parent = y;
	if (y == nill) {
		root = new_node;
	}
	else if (y->key > new_node->key) {
		y->LeftChild = new_node;

	}
	else {
		y->RightChild = new_node;
	}

}

void left_rotate(Node*& T, Node* x) {
	Node* y = x->RightChild;
	x->RightChild = y->LeftChild;

	if (y->LeftChild != nill) {
		y->LeftChild->Parent = x;
	}
	y->Parent = x->Parent;
	if (x->Parent == nill) {
		T = y;

	}
	else if (x == x->Parent->LeftChild) {
		x->Parent->LeftChild = y;
	}
	else {
		x->Parent->RightChild = y;
	}
	y->LeftChild = x;
	x->Parent = y;

}
void right_rotate(Node*& T, Node* x) {
	Node* y = x->LeftChild;
	x->LeftChild = y->RightChild;

	if (y->RightChild != nill) {
		y->RightChild->Parent = x;
	}
	y->Parent = x->Parent;
	if (x->Parent == nill) {
		T = y;
	}
	else if (x == x->Parent->RightChild) {
		x->Parent->RightChild = y;
	}
	else {
		x->Parent->LeftChild = y;
	}
	y->RightChild = x;
	x->Parent = y;
}

Node* rb_insert(Node* T, Node* x) {
	add_node(T, x);
	x->color = red;
	Node* y = nill;
	while ((x != T) && (x->Parent->color == red)) {
		if (x->Parent == x->Parent->Parent->LeftChild) {
			y = x->Parent->Parent->RightChild;
			if (y->color == red) {
				x->Parent->color = black;
				y->color = black;
				x->Parent->Parent->color = red;
				x = x->Parent->Parent;
			}
			else {
				if (x == x->Parent->RightChild) {
					x = x->Parent;
					left_rotate(T, x);
				}
				x->Parent->color = black;
				x->Parent->Parent->color = red;
				right_rotate(T, x->Parent->Parent);
			}
		}
		else if (x->Parent == x->Parent->Parent->RightChild) {
			y = x->Parent->Parent->LeftChild;
			if (y->color == red) {
				x->Parent->color = black;
				y->color = black;
				x->Parent->Parent->color = red;
				x = x->Parent->Parent;
			}
			else {
				if (x == x->Parent->LeftChild) {
					x = x->Parent;
					right_rotate(T, x);
				}
				x->Parent->color = black;
				x->Parent->Parent->color = red;
				left_rotate(T, x->Parent->Parent);
			}
		}
	}
	T->color = black;
	return T;
}
void rb_delete_fixup(Node*& T, Node*& x) {
	while ((x != T) && (x->color == black)) {
		if (x == x->Parent->LeftChild) {
			Node* w = x->Parent->RightChild;
			if (w->color == red) {
				w->color = black;
				x->Parent->color = red;
				left_rotate(T, x->Parent);
				w = x->Parent->RightChild;
			}
			else if ((w->LeftChild->color == black) && (w->RightChild->color == black)) {
				w->color = red;
				x = x->Parent;

			}
			else if (w->RightChild->color == black) {
				w->LeftChild->color = black;
				w->color = red;
				right_rotate(T, w);
				w = x->Parent->RightChild;
			}
			else {
				w->color = x->Parent->color;
				x->Parent->color = black;
				w->RightChild->color = black;
				left_rotate(T, x->Parent);
				x = T;
			}
		}
		else {
			Node* w = x->Parent->LeftChild;
			if (w->color == red) {
				w->color = black;
				x->Parent->color = red;
				right_rotate(T, x->Parent);
				w = x->Parent->LeftChild;
			}
			else if ((w->RightChild->color == black) && (w->LeftChild->color == black)) {
				w->color = red;
				x = x->Parent;

			}
			else if (w->LeftChild->color = black) {
				w->RightChild->color = black;
				w->color = red;
				left_rotate(T, w);
				w = x->Parent->LeftChild;
			}
			else {
				w->color = x->Parent->color;
				x->Parent->color = black;
				w->LeftChild->color = black;
				right_rotate(T, x->Parent);
				x = T;
			}
		}
	}
	x->color = black;
}
void print(Node* root, int indent) {
	if (root != nill && root != nullptr) {
		indent -= 2;
		if (indent < 0) indent = 0;
		std::string stuff(indent, ' ');
		int cl = 0;
		if (root->color == red) cl = 1;
		std::cout << stuff << root->key.series << ' ' << root->key.number << ' ' << cl << ' ';
		print_list(root->DuplicationList);
		print(root->LeftChild, indent - (2 + indent / 4));
		print(root->RightChild, indent + (2 + indent / 4));
	}
}

Node* search_in_tree(Node* T, KeyType key) {
	Node* cur_node = T;
	while (cur_node != nill && cur_node != nullptr) {
		if (cur_node->key == key) {
			return cur_node;
		}
		if (cur_node->key > key) {
			cur_node = cur_node->LeftChild;
		}
		else {
			cur_node = cur_node->RightChild;
		}
	}
	return nullptr;
}
void transplant(Node*& T, Node*& u, Node*& v) {
	if (u->Parent == nill) {
		T = v;
	}
	else if (u == u->Parent->LeftChild) {
		u->Parent->LeftChild = v;
	}
	else {
		u->Parent->RightChild = v;
	}
	v->Parent = u->Parent;
}
Node* tree_minimum(Node* node) {
	while (node->LeftChild != nill) {
		node = node->LeftChild;
	}
	return node;
}
Node* delete_node(Node* node, KeyType key) {
	Node* z = search_in_tree(node, key); 
	Node* x, * y;

	y = z;
	Color originalColor = y->color;

	if (z->LeftChild == nill) {
		x = z->RightChild;
		transplant(node, z, z->RightChild);
	}
	else if (z->RightChild == nill) {
		x = z->LeftChild;
		transplant(node, z, z->LeftChild);
	}
	else {
		y = tree_minimum(z->RightChild);
		originalColor = y->color;
		x = y->RightChild; 

		if (y->Parent == z) {
			x->Parent = y;
		}
		else {
			transplant(node, y, y->RightChild); 
			y->RightChild = z->RightChild; 
			y->RightChild->Parent = y;
		}

		transplant(node, z, y); 
		y->LeftChild = z->LeftChild; 
		y->LeftChild->Parent = y;
		y->color = z->color; 
	}

	delete z; 

	
	if (originalColor == black) {
		rb_delete_fixup(node, x);
	}

	return node;
}

Node* clear_tree(Node* root) {
	if (root != nullptr) {
		clear_tree(root->LeftChild);
		clear_tree(root->RightChild);
		root = nullptr;
	}
	return root;
}

Node* insert_in_tree(Node* root, KeyType key, int string_num) {
	if ((key.series > 999 && key.series < 10000) && (key.number > 99999 && key.number < 1000000)) {
		auto* new_node = new Node(key, nill, nill, nill, nullptr, red);
		new_node->DuplicationList = add_to_list(new_node->DuplicationList, string_num);
		if (root == nullptr) {
			new_node->color = black;
			return new_node;
		}
		else {
			Node* exist_node = search_in_tree(root, new_node->key);
			if (exist_node == nullptr) {
				root = rb_insert(root, new_node);
			}
			else {
				Elem* updated_list = add_to_list(exist_node->DuplicationList, string_num);
				exist_node->DuplicationList = updated_list;
				delete new_node;
			}
			return root;
		}
	}
	else {
		return nullptr;
	}
}
Node* delete_in_tree(Node* root, KeyType key, int string_num) {
	if (root != nullptr) {
		Node* exist_node = search_in_tree(root, key);
		if (exist_node != nullptr) {
			if ((exist_node->DuplicationList == exist_node->DuplicationList->next) && (exist_node->DuplicationList->data == string_num)) {
				root = delete_node(root, key);
			}
			else if (in_list(string_num, exist_node->DuplicationList)) {
				Elem* updated_list = remove_elem(exist_node->DuplicationList, string_num);
				exist_node->DuplicationList = updated_list;
			}
			else {
				std::cout << "String in node is not found!" << std::endl;
			}
		}
		else {
			std::cout << "Node is not found!" << std::endl;
		}
	}
	return root;
}
void straigh(Node* root) {
	if (root == nullptr or root->key.series == 0) return;
	std::cout << root->key.series << " "<< root->key.number<<'\n';
	straigh(root->LeftChild);
	straigh(root->RightChild);
}
