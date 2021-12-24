#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;
class BinaryNode { //이진 노드 그자체 의미
	friend class BinarySearchTree;
private:
	string key;
	int value;
	BinaryNode* left;
	BinaryNode* right;
public:
	BinaryNode(string key = NULL, int value = 0, BinaryNode* left = nullptr, BinaryNode* right = nullptr)
	{
		this->key = key;
		this->value = value;
		this->left = left;
		this->right = right;
	}
	bool isleaf() {
		return this->left == nullptr && this->right == nullptr;
	}
	bool hasTwoChildren() {
		return this->left != nullptr && this->right != nullptr;
	}
	bool hasOneChild()
	{
		bool hasonlyleft = this->left != nullptr && this->right == nullptr;
		bool hasonlyright = this->left == nullptr && this->right != nullptr;
		return hasonlyleft || hasonlyright;
	}
};

class Binarytree {
protected:
	BinaryNode* root = nullptr;
	int treesize = 0;
public:
	Binarytree()
	{
		root = nullptr;
	}
	bool empty()
	{
		return this->root == nullptr;
	}
	void print_emtpy()
	{
		if (this->empty() == true)
		{
			cout << "empty" << endl;
		}
		else {
			cout << "not empty" << endl;
		}
	}
	int addsize()
	{
		return treesize+=1;
	}
	int subsize()
	{
		return treesize-=1;
	}
	int size()
	{
		return treesize;
	}
};

Binarytree tree;
class BinarySearchTree :public Binarytree {
private:
	BinaryNode* leftmost(BinaryNode* node)
	{
		while (node->left != nullptr)
			node = node->left;
		return node;
	}
	BinaryNode* search(BinaryNode* node, string key)
	{
		if (node == nullptr || key == node->key)
		{
			return node;
		}
		else if (key < node->key)
		{
			return search(node->left, key);
		}
		else
		{
			return search(node->right, key);
		}
	}
	void insert(BinaryNode* node, string key, int value) {
		if (key == node->key) {
			node->value = value;
		}
		else if (key < node->key) {
			if (node->left == nullptr) {
				node->left = new BinaryNode(key, value);
			}
			else {
				insert(node->left, key, value);
			}
		}
		else {
			if (node->right == nullptr) {
				node->right = new BinaryNode(key, value);
			}
			else {
				insert(node->right, key, value);
			}
		}
	}
	BinaryNode* remove(BinaryNode* node, BinaryNode* parent, string key) {
		if (node == nullptr)
		{
			return nullptr;
		}
		if (key < node->key)
		{
			return remove(node->left, node, key);
		}
		else if (key > node->key)
		{
			return remove(node->right, node, key);
		}
		else { // key == node->key
			if (node->hasTwoChildren()) {
				BinaryNode* succ = leftmost(node->right);
				node->key = succ->key;
				node->value = succ->value;
				succ = this->remove(node->right, node, succ->key);
				return succ;// do something for case 3
			}
			else if (node->hasOneChild()) {
				BinaryNode* child = (node->left != nullptr) ? node->left : node->right;
				if (node == this->root)
				{
					this->root = child;
				}
				else {
					if (parent->left == node)
						parent->left = child;
					else
						parent->right = child;
				}
				return node;// do something for case 2
			}
			else if (node->isleaf()) {
				if (node == this->root)
					this->root = nullptr;
				else {
					if (parent->left == node)
						parent->left = nullptr;
					else
						parent->right = nullptr;
				}
				return node;// do something for case 1
			}
		}
	}
public:
	void insert(string key, int value)
	{
		if (empty() == true)
		{
			this->root = new BinaryNode(key, value);
		}
		else {
			insert(this->root, key, value);
		}
	}
	void search(string key)
	{
		BinaryNode* node = this->search(this->root, key);
		if (node == nullptr)
		{
			cout << "out-of-key" << endl;
		}
		else {
			cout << node->value << endl;
		}
	}
	void remove(string key)
	{
		BinaryNode* node = remove(this->root, nullptr, key);
		if (node == nullptr) {
			cout << "out-of-key" << endl;
		}
		else {
			tree.subsize();
			delete node;
		}
	}
};
int main()
{
	int num = 0;
	cin >> num;
	cin.ignore();

	string line, token;
	vector<string> expr;
	BinarySearchTree BST;
	
	for (int i = 0; i < num; i++)
	{
		getline(cin, line);
		stringstream ss(line);

		while (getline(ss, token, ' '))
		{
			expr.push_back(token);
		}
		if (expr[0] == "insert")
		{
			BST.insert(expr[1], stoi(expr[2]));
			tree.addsize();
		}
		else if (expr[0] == "search")
		{
			BST.search(expr[1]);
		}
		else if (expr[0] == "remove")
		{
			BST.remove(expr[1]);
		}
		else if (expr[0] == "empty")
		{
			BST.print_emtpy();
		}
		else if (expr[0] == "size")
		{
			cout << tree.size() << endl;
		}
		expr.clear();
	}

	return 0;
}