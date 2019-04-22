#pragma once
#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <map>

using namespace std;
class huffman_tree {
public:
	//struct
	//node function

	struct Node {
		int f = 0;
		string ch = "";
		Node* left = nullptr;
		Node* right = nullptr;
	};

	multimap<int, string> myMap;
	vector<Node*> pq;

	Node* nodeFunction1(int freq, string character) {
		Node* newNode = new Node();
		newNode->f = freq;
		newNode->ch = character;
		return newNode;
	}
	Node* parent(int sum, Node* temp_1, Node* temp_2) {
		Node* newNode2 = new Node();
		newNode2->f = sum;
		newNode2->left = temp_1;
		newNode2->right = temp_2;
		return newNode2;
	}

	string recursion_encode(Node* currnode, string s, char c) const;
	string recursion_decode(Node* currnode, string s) const;

	huffman_tree(const string &file_name);
	~huffman_tree();

	string get_character_code(char character) const;
	string encode(const string &file_name) const;
	string decode(const string &string_to_decode) const;
};
