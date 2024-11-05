#include "headers.h"



Node::Node()
{
	for (int i = 0; i < ALPH_SIZE; ++i)
		children[i] = nullptr;
	count = 0;
}

Node::~Node()
{
	clear();
}

void Node::clear()
{
	for (int i = 0; i < ALPH_SIZE; ++i)
		if (children[i] != nullptr)
		{
			delete children[i];
			children[i] = nullptr;
		}
}

void Node::print(std::string word)
{
	if (count > 0)
		std::cout << word << "  " <<  count << std::endl;
	for (int i = 0; i < ALPH_SIZE; ++i)
	{
		if (children[i]) children[i]->print(word + (char)(START_SYM + i));
	}
}

void Node::add(std::string word, int level)
{
	if (level == word.size())
		count++;
	else
	{
		int index = (int)(word[level] - START_SYM);
		if (index >= 0 && index < ALPH_SIZE)
		{
			if (!children[index])
				children[index] = new Node();
			children[index]->add(word, level + 1);
		}
	}
	
}

bool Node::find(std::string word, int level)
{
	if (level == word.size())
		return count;
	int index = (int)(word[level] - START_SYM);
	if (index >= 0 && index < ALPH_SIZE)
	{
		if (!children[index])
			return false;
		return children[index]->find(word, level + 1);
	}
	else return false;	
}

bool Node::del(std::string word, int level)
{
	if (level == word.size())
		count = 0;
	else
	{
		int index = (int)(word[level] - START_SYM);
		if (index >= 0 && index < ALPH_SIZE)
			if (!children[index])
				return false;
		children[index]->del(word, level + 1);
		if (!children[index]->count && children[index]->is_children_null())
		{
			delete children[index];
			children[index] = nullptr;
		}
		else return false;
	}
	return true;

}

bool Node::is_children_null()
{
	for (int i = 0; i < ALPH_SIZE; ++i)
		if (children[i] != nullptr)
			return false;

	return true;
}





TrieTree::TrieTree()
{
	root = nullptr;
}

TrieTree::~TrieTree()
{
	clear();
}

void TrieTree::clear()
{
	if (root)
		root->clear();
}

void TrieTree::print()
{
	if (root)
		root->print("");
	else
		std::cout << "Tree is empty\n";
}

void TrieTree::add(std::string word)
{
	if (!root)
		root = new Node();
	root->add(word, 0);

}

bool TrieTree::find(std::string word)
{
	if (root)
		return root->find(word, 0);
	return false;
}

bool TrieTree::del(std::string word)
{
	if (root)
	{
		bool res = root->del(word, 0);
		if (res && root->is_children_null())
			root = nullptr;
	}
	return false;
}


int main()
{
	std::string file_name = "tree.txt";
	std::ifstream file(file_name);

	TrieTree* tree = new TrieTree();
	while (!file.eof())
	{
		std::string str;
		file >> str;
		tree->add(str);
	}

	file.close();
	tree->print();
	std::cout << std::endl;

}