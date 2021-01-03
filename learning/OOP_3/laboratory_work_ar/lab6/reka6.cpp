#include <iostream>

using namespace std;

class Set
{
protected:
	struct Node
	{
		int value;
		Node *next;
		Node *parent;
	};
public:
	virtual void add_element (int) = 0;
	virtual void delete_element () = 0;
	virtual int line () = 0;
	virtual void print () = 0;
};

class Queu: public Set
{
	Node *root = NULL;
public:
	Node *create_node (Node *node, Node *parent, int value)
	{
		node = new Node;
		if (node == NULL) {
			return NULL;
		}
		node->value = value;
		node->next = NULL;
		node->parent = parent;

		return node;
	}
	void add_element (int value)
	{
		Node *node = root, *parent = NULL;

		while (node != NULL) {
			parent = node;
			node = node->next;
		}

		node = create_node(node, parent, value);

		if (root == NULL) {
			root = node;
		} else {
			parent->next = node;
		}
	}
	void delete_element ()
	{
		Node *node = root;
		if (line() <= 0) {
			cout << "Error: not elem for delete" << endl;
			return;
		}
		if (node->next != NULL) {
			node->next->parent = NULL;
			root = node->next;
			delete node;
		} else {
			delete root;
			root = NULL;
		}
	}
	int line ()
	{
		Node *node = root;
		int i = 0;
		while (node != NULL) {
			node = node->next;
			i++;
		}
		return i;
	}
	void print ()
	{
		Node *node = root;
		cout << "Queu:\t";
		if (line() <= 0) {
			cout << "void" << endl;
			return;
		}
		while (node != NULL) {
			cout << node->value << "\t";
			node = node->next;
		}
		cout << endl;
	}
	~Queu ()
	{
		Node *node = root;
		while (root != NULL) {
			node = root->next;
			delete root;
			root = node;
		}
		delete node;
	}
};

class Stack: public Set
{
	Node *root = NULL;
public:
	Node *create_node (Node *node, Node *parent, int value)
	{
		node = new Node;
		if (node == NULL) {
			return NULL;
		}
		node->value = value;
		node->next = NULL;
		node->parent = parent;

		return node;
	}
	void add_element (int value)
	{
		Node *node = root, *parent = NULL;

		while (node != NULL) {
			parent = node;
			node = node->next;
		}

		node = create_node(node, parent, value);

		if (root == NULL) {
			root = node;
		} else {
			parent->next = node;
		}
	}
	void delete_element ()
	{
		Node *node = root;
		if (line() <= 0) {
			cout << "Error: not elem for delete" << endl;
			return;
		}
		while (node->next != NULL) {
			node = node->next;
		}
		if (node->parent != NULL) {
			node->parent->next = NULL;
			delete node;
		} else {
			root = NULL;
		}

		return;
	}
	int line ()
	{
		Node *node = root;
		int i = 0;
		while (node != NULL) {
			node = node->next;
			i++;
		}
		return i;
	}
	void print ()
	{
		Node *node = root;
		cout << "Stack:\t";
		if (line() <= 0) {
			cout << "void" << endl;
			return;
		}
		while (node != NULL) {
			cout << node->value << "\t";
			node = node->next;
		}
		cout << endl;
	}
	~Stack ()
	{
		Node *node = root;
		while (root != NULL) {
			node = root->next;
			delete root;
			root = node;
		}
		delete node;
	}
};

int main()
{
	Stack stack;
	Queu queu;
	int line;

	cout << "Input line stack and queu: ";
	cin >> line;
	cout << endl;

	for (int i = 0; i < line; ++i)
	{
		stack.add_element(i);
		queu.add_element(i);
	}
	stack.print();
	stack.delete_element();
	stack.print();
	stack.delete_element();
	stack.print();

	queu.print();
	queu.delete_element();
	queu.print();
	queu.delete_element();
	queu.print();

	return 0;
}
