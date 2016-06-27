#pragma once

#include "d-heap.hpp"
#include "binary_search_tree.hpp"
#include "table.hpp"

template <class KeyType>
class Priority_queue
{
public:
	Priority_queue(void) {};
	virtual ~Priority_queue() {};
	virtual void Push(const KeyType) = 0;
	virtual void Pop() = 0;
	virtual int IsEmpty() = 0;
	virtual int GetSize() = 0;
	virtual KeyType Top() = 0;
};

template <class KeyType>
class Queue_on_heap : public Priority_queue<KeyType>
{
private:
	D_heap<KeyType> *heap;
public:
	Queue_on_heap(int);
	virtual ~Queue_on_heap() { delete heap; }
	void Push(const KeyType);
	void Pop();
	KeyType Top();
	int IsEmpty();
	virtual int GetSize() { return heap->GetCount(); };
};

template <class KeyType>
Queue_on_heap<KeyType>::Queue_on_heap(int arity)
{
	if (arity < 0)
		throw
		exception("Arity must be positive");
	heap = new D_heap<KeyType>(arity, 0);
}

template <class KeyType>
void Queue_on_heap<KeyType>::Pop()
{
	if (IsEmpty())
		throw
		exception("Queue is empty"); 
	heap->RemoveMin();
}

template <class KeyType>
int Queue_on_heap<KeyType>::IsEmpty()
{
	return heap->GetCount() == 0;
};

template <class KeyType>
void Queue_on_heap<KeyType>::Push(const KeyType x)
{
	heap->Push(x);
	heap->Sort();
}

template <class KeyType>
KeyType Queue_on_heap<KeyType>::Top()
{
	if (IsEmpty())
		throw
		exception("Queue is empty");
	return heap->GetKey(0)->pr;
}



template <class KeyType>
class Queue_on_tree : public Priority_queue <KeyType>
{
private:
	Binary_search_tree<KeyType> *tree;
public:
	Queue_on_tree();
	virtual ~Queue_on_tree() { delete tree; };
	virtual void Push(const KeyType x)
	{
		Node<KeyType> *tmp = new Node<KeyType>(x);
		tree->Push(tree->root, tmp);
	}
	virtual void Pop()
	{
		tree->Remove(tree->root, tree->root->key);
	}
	virtual int IsEmpty() { return tree->GetSize() == 0; };
	virtual KeyType Top() { return tree->root->key; };
	virtual int GetSize() { return tree->GetSize(); };
	int operator==(const Queue_on_tree<KeyType>&)const;
};

template <class KeyType>
Queue_on_tree<KeyType>::Queue_on_tree()
{
	tree = new Binary_search_tree<KeyType>;
}

template <class KeyType>
int Queue_on_tree<KeyType>::operator==(const Queue_on_tree<KeyType>& newtree)const
{
	return *tree == *newtree.tree;
}


template <class KeyType>
class Queue_on_table : public Priority_queue <KeyType>
{
private:
	Sort_table<KeyType>* table;
	int s;
public:
	Queue_on_table(int);
	~Queue_on_table();
	void Push(KeyType);
	void Pop();
	KeyType Top();
	int IsEmpty();
	int GetSize();
};

template <class KeyType>
Queue_on_table<KeyType>::Queue_on_table(int x)
{
	if (x < 0)
		throw
		exception("Error"); 
	table = new Sort_table<KeyType>(x);
	s = 0;
}

template <class KeyType>
Queue_on_table<KeyType>::~Queue_on_table()
{
	delete table;
}

template <class KeyType>
void Queue_on_table<KeyType>::Push(KeyType x)
{
	table->Push(s, x);
	s++; 
}

template <class KeyType>
void Queue_on_table<KeyType>::Pop()
{
	if (IsEmpty())
		throw
		exception("Table is empty");
	table->Remove(table->Min()->GetKey());
	s--;
}

template <class KeyType>
KeyType Queue_on_table<KeyType>::Top()
{
	return table->Min()->GetData();
}

template <class KeyType>
int Queue_on_table<KeyType>::GetSize()
{
	return table->GetCount();
}

template <class KeyType>
int Queue_on_table<KeyType>::IsEmpty()
{
	if (table->GetCount() == 0)
		return 1;
	return 0;
}

template <class KeyType>
class Create_queue
{
public:
	static bool CreateQueue(Priority_queue<KeyType>*&, const int, const int);
};

template <class KeyType>
bool Create_queue<KeyType>::CreateQueue(Priority_queue<KeyType>*& q, const int a, const int b)
{
	if (a == 1)
	{
		q = new Queue_on_heap<KeyType>(b);
		return true;
	}
	if (a == 2)
	{
		q = new Queue_on_tree<KeyType>();
		return true;
	}
	if (a == 3)
	{
		q = new Queue_on_table<KeyType>(b);
		return true;
	}
	return false;
}

