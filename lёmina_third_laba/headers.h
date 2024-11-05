#pragma once
#include <iostream>
#include <fstream>


const int ALPH_SIZE = 26;
const char START_SYM = 'a';

struct Node {
	int count = 0;
	Node* children[ALPH_SIZE];

	Node();
	~Node();

	void clear();
	void print(std::string word);
	void add(std::string word, int level);
	bool find(std::string word, int level);
	bool del(std::string word, int level);
	bool is_children_null();
};

struct TrieTree
{
	Node* root;
	TrieTree();
	~TrieTree();

	void clear();
	void print();
	void add(std::string word);
	bool find(std::string word);
	bool del(std::string word);


};