#ifndef VECTOR_H
#define VECTOR_H

#include "set.h"

template <class Type>
class Vector: public Set<Type> {
	typename Set<Type>::Node *my_vector = NULL;
	int capacity = 0;
	int size = 0;
public:
	Vector ();
	Vector (int);
	Type operator [] (int);
	typename Set<Type>::Node *create_node(typename Set<Type>::Node*,
										  typename Set<Type>::Node*, 
										  typename Set<Type>::Node*);
	void add_element (Type, int);
	void delete_element (int);
	typename Set<Type>::Node *lookup (int);
	Type lookup_element (int);
	int get_capacity () {return capacity;}
	int get_size () {return size;}
	void print ();
};

template <class Type>
Vector<Type>::Vector ()
{
	typename Set<Type>::Node *node, *parent = NULL;
	size = 10;
	for (int i = 0; i < size; i++)
	{
		node = create_node(node, parent, NULL);
		if (parent != NULL)
			node->parent->next = node;
		if (my_vector == NULL)
			my_vector = node;
		parent = node;
		node = node->next;
	}
}

template <class Type>
Vector<Type>::Vector (int user_size)
{
	typename Set<Type>::Node *node, *parent = NULL;
	size = user_size;
	for (int i = 0; i < size; i++)
	{
		node = create_node(node, parent, NULL);
		if (parent != NULL)
			node->parent->next = node;
		if (my_vector == NULL)
			my_vector = node;
		parent = node;
		node = node->next;
	}
}

template <class Type>
Type Vector<Type>::operator [] (int index)
{
	if (index >= size) {
		cout << "Array out of bounds" << endl;
		return 0;
	}
	return lookup_element(index);
}

template <class Type>
typename Set<Type>::Node* Vector<Type>::create_node(typename Set<Type>::Node *node,
													typename Set<Type>::Node *parent, 
													typename Set<Type>::Node *next)
{
	node = new (typename Set<Type>::Node);
	if (node == NULL) {
		return NULL;
	}
	node->parent = parent;
	node->next = next;
	return node;
}

template <class Type>
void Vector<Type>::add_element (Type value, int i)
{
	typename Set<Type>::Node *node;
	
	node = lookup(i);
	node->value = value;
	capacity++;

	/*
	typename Set<Type>::Node *node, *parent, *node_new;
	node = my_vector;
	parent = NULL;
	node_new = NULL;

	while (node != NULL && i != 0) {
		parent = node;
		node = node->next;
		i--;
	}

	if (node != NULL && node->parent == NULL && node->next != NULL) {
		node_new = create_node(node_new, parent, my_vector, value);
		my_vector->parent = node_new;
		my_vector = node_new;
	} else if (node != NULL && node->parent != NULL && node->next == NULL) {
		node_new = create_node(node_new, parent, node, value);
		parent->next = node_new;
	} else if (node != NULL && node->parent != NULL && node->next != NULL) {
		node_new = create_node(node_new, parent, node, value);
		parent->next = node_new;
		node->parent = node_new;
	} else if (node == NULL) {
		node = create_node(node, parent, NULL, value);
		if (my_vector == NULL) {
			my_vector = node;
		} else if (parent != NULL) {
			parent->next = node;
		}
	}
	capacity++;
	*/
}

template <class Type>
void Vector<Type>::delete_element (int i)
{
	typename Set<Type>::Node *node, *node_new = NULL;
	node = lookup(i);
	if (node == NULL) {
		cout << "Error: Item not found for deletion" << endl;
		return;
	}
	node_new = create_node(node_new, node->parent, node->next);
	if (node->parent != NULL) {
		node->parent->next = node_new;
	} else {
		my_vector = node_new;
	}
	if (node->next != NULL)
		node->next->parent = node_new;
	/*if (node->parent != NULL) {
		node->parent->next = node->next;
	} else {
		my_vector = node->next;
		my_vector->parent = NULL;
	}
	if (node->next != NULL)
		node->next->parent = node->parent;*/
	delete node;
	capacity--;
}

template <class Type>
typename Set<Type>::Node* Vector<Type>::lookup (int i)
{
	typename Set<Type>::Node *node = my_vector;
	while (node != NULL && i != 0) {
		node = node->next;
		i--;
	}
	return node;
}

template <class Type>
Type Vector<Type>::lookup_element (int i)
{
	typename Set<Type>::Node *node = lookup(i);
	if (node == NULL) {
		cout << "Error: Item not found" << endl;
		return 0;
	}
	return node->value;
}

template <class Type>
void Vector<Type>::print ()
{
	typename Set<Type>::Node *node = my_vector;
	for (int i = 0; i < size && node != NULL; i++) {
		cout << node->value << " ";
		node = node->next;
	}
	cout << endl;
}

#endif