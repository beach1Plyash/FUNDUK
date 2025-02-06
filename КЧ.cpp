#include<iostream>
#include"kche.h"
#include<fstream>
#include<sstream>
#include<string>
using namespace std;

int main() {
	ifstream file("C:\\Users\\Kirill\\Desktop\\Pasporta.txt");
	if (file.is_open() == false) {
		cout << "File is not open :(\n";
		return 1;
	}
	
	Node* tree = init();
	int string_num=0;
	string line;
	KeyType passport;
	while (!file.eof()) {
		file >> passport.series;
		file >> passport.number;
		string_num++;
		tree=insert_in_tree(tree, passport, string_num);
		
	}
	passport.series = 3000;
	passport.number = 300000;
	tree = delete_in_tree(tree, passport, 3);
	straight_write(tree,70);
	tree = clear_tree(tree);
	file.close();
	return 0;
}