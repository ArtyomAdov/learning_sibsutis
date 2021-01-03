#ifndef SET_H
#define SET_H

using namespace std;

template <class Type>
class Set
{
protected:
	struct Node
	{
		Type value;
		Node *next;
		Node *parent;
	};
	//int size;
	//int capacity;
public:
	virtual void add_element (Type, int) = 0;
	virtual void delete_element (int) = 0;
	virtual Type lookup_element (int) = 0;
	virtual int get_capacity () = 0;
	virtual int get_size () = 0;
	virtual void print () = 0;
};

#endif