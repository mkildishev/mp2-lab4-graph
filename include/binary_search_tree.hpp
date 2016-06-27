#pragma once

#include <iostream>
#include <queue>
#include <stack>

using namespace std;


template <class KeyType>
class Node
{
public:
	int balance;
	KeyType key;
	Node<KeyType> *left;
	Node<KeyType> *right;
	Node<KeyType> *parent;
	Node() { left = NULL; right = NULL; parent = NULL; balance = 0; };
	Node(const KeyType& k) { key = k; left = NULL; right = NULL; parent = NULL; balance = 0; };
};

template <class KeyType>
class Binary_search_tree
{
public:
	int size;
	Node<KeyType> *root;
	Binary_search_tree();
	~Binary_search_tree();
	Binary_search_tree(const Binary_search_tree<KeyType> &);
	Node<KeyType>* Copy(Node<KeyType> *);
	virtual void Push (Node<KeyType>*&, const Node<KeyType> *);
	virtual void Remove(Node<KeyType>*&, const KeyType &);
	Node<KeyType>* FindKey(Node<KeyType>*, const KeyType &);
	Node<KeyType>* FindMax(Node<KeyType>*);
	Node<KeyType>* FindMin(Node<KeyType>*);
	Node<KeyType>* FindNext(Node<KeyType>*, Node<KeyType>*);
	Node<KeyType>* FindPrevious(Node<KeyType>*, Node<KeyType>*);
	void WorkAroundWidth(Node<KeyType>*); //based on queue
	void WorkAroundForward(Node<KeyType>*);
	void WorkAroundReverse(Node<KeyType>*);
	void WorkAroundSymmetric(Node<KeyType>*);
	void WorkAroundDepth(Node<KeyType>*); //based on stack
	int operator==(const Binary_search_tree<KeyType>&) const;
	int GetSize();
	int GetHeight(Node<KeyType>*);
};

template <class KeyType>
Binary_search_tree<KeyType>::Binary_search_tree()
{
	root = NULL;
	size = 0;
};

template <class KeyType>
Binary_search_tree<KeyType>::~Binary_search_tree()
{
	delete root;
};

template <class KeyType>
Binary_search_tree<KeyType>::Binary_search_tree(const Binary_search_tree<KeyType> &tree)
{
	root = Copy(tree.root);
	size = tree.size;
};

template <class KeyType>
Node<KeyType>* Binary_search_tree<KeyType>::Copy(Node<KeyType> *newroot)
{
	if (newroot == NULL)
		return NULL;
	Node<KeyType>* l = Copy(newroot->left);
	Node<KeyType>* r = Copy(newroot->right);
	Node<KeyType>* newtree = new Node<KeyType>;
	newtree->key = newroot->key;
	newtree->left = l;
	newtree->right = r;
	root = newtree;
	return newtree;
};

template <class KeyType>
void Binary_search_tree<KeyType>::Push(Node<KeyType>* &tree, const Node<KeyType> *node)
{
	KeyType newkey = node->key;
	if (tree == NULL)
	{
		tree = new Node<KeyType>;
		tree->key = newkey;
		size++;
		return;
	}
	Node<KeyType>* tmp = tree;
	Node<KeyType>* previous = new Node<KeyType>;
	while (tmp != NULL)
	{
		previous = tmp;
		if (tmp->key <= newkey)
			tmp = tmp->right;
		else
			tmp = tmp->left;
	}
	if (previous->key <= newkey)
		previous->right = new Node<KeyType>(newkey);
	else
		previous->left = new Node<KeyType>(newkey);
	size++;
};

template <class KeyType>
void Binary_search_tree<KeyType>::Remove(Node<KeyType>*& tree, const KeyType &k)
{
	Node<KeyType>* x = FindKey(tree, k);
	if (x == NULL)
		//return;
		throw
		exception("Key doesn't exist"); 
	if ((x->left == NULL) && (x->right == NULL))
	{
		delete x;
		return;
	}
	if ((x->left == NULL) && (x->right != NULL))
	{
		Node<KeyType>* y = x->right;
		y->parent = x->parent;
		if (x->parent == NULL)
		{
			tree = y;
			return;
		}
		if (x->parent->right == x)
			x->parent->right = y;
		else
			x->parent->left = y;
		tree = y;
		return;
	}
	if ((x->left != NULL) && (x->right == NULL))
	{
		Node<KeyType>* y = x->left;
		y->parent = x->parent;
		if (x->parent->right == x)
			x->parent->right = y;
		else
			x->parent->left = y;
		delete x;
		return;
	}
	Node<KeyType>* y = FindMin(x->right);
	x->key = y->key;
	y->parent->left = y->right;
	if (y->right != NULL)
		y->right->parent = y->parent;
	delete y;
};

template <class KeyType>
Node<KeyType>* Binary_search_tree<KeyType>::FindKey(Node<KeyType> *tree, const KeyType &k)
{
	while ((tree != NULL) && (tree->key != k))
	{
		if (k < tree->key)
			tree = tree->left;
		if (k > tree->key)
			tree = tree->right;
	}
	return tree;
};

template <class KeyType>
Node<KeyType>* Binary_search_tree<KeyType>::FindMin(Node<KeyType> *tree)
{
	if (tree == NULL)
		throw
		exception("Tree is empty"); 
	while (tree->left != NULL)
		tree = tree->left;
	return tree;
};

template <class KeyType>
Node<KeyType>* Binary_search_tree<KeyType>::FindMax(Node<KeyType> *tree)
{
	if (tree == NULL)
		throw
		exception("Tree is empty"); 
	while (tree->right != NULL)
		tree = tree->right;
	return tree;
};

template <class KeyType>
Node<KeyType>* Binary_search_tree<KeyType>::FindNext(Node<KeyType> *tree, Node<KeyType> *node)
{
	if (tree == NULL)
		throw
		exception("Tree is empty"); 
	if (node == NULL)
		throw
		exception("Node is empty"); 
	node = FindKey(tree, node->key);
	if (node->right != NULL)
		return FindMin(node->right);
	while ((node->parent != NULL) && (node->parent->right == node))
		node = node->parent;
	if (node->parent == NULL)
		throw
		exception("Parent doesn't exist"); 
	return node->parent;
};

template <class KeyType>
Node<KeyType>* Binary_search_tree<KeyType>::FindPrevious(Node<KeyType> *tree, Node<KeyType> *node)
{
	if (tree == NULL)
		throw
		exception("Tree is empty"); 
	if (node == NULL)
		throw
		exception("Node is empty"); 
	node = FindKey(tree, node->key);
	if (node->right != NULL)
		return FindMax(node->left);
	while ((node->parent != NULL) && (node->parent->left == node))
		node = node->parent;
	if (node->parent == NULL)
		throw
		exception("Parent doesn't exist");
	return node->parent;
}

template <class KeyType>
void Binary_search_tree<KeyType>::WorkAroundWidth(Node<KeyType> *tree)
{
	if (tree == NULL)
		return;
	queue <Node<KeyType>*> q;
	q.push(tree);
	while (q.empty() == 0)
	{
		Node<KeyType>* tmp = q.front();
		cout << tmp->key << '(' << tmp->balance << ')';
		q.pop();
		if (tmp->left != NULL)
			q.push(tmp->left);
		if (tmp->right != NULL)
			q.push(tmp->right);
	}
}

template <class KeyType>
void Binary_search_tree<KeyType>::WorkAroundDepth(Node<KeyType> *tree)
{
	if (tree == NULL)
		return;
	stack<Node<KeyType>*> s;
	s.push(tree);
	while (!s.empty())
	{
		Node<KeyType>* tmp = s.top();
		cout << tmp->key << '(' << tmp->balance << ')';
		s.pop();
		if (tmp->right != NULL)
			s.push(tmp->right);
		if (tmp->left != NULL)
			s.push(tmp->left);
	}
}

template <class KeyType>
void Binary_search_tree<KeyType>::WorkAroundForward(Node<KeyType> *tree)
{
	if (tree == NULL)
		return;
	cout << tree->key << '(' << tree->balance << ')';
	WorkAroundForward(tree->left);
	WorkAroundForward(tree->right);
}

template <class KeyType>
void Binary_search_tree<KeyType>::WorkAroundSymmetric(Node<KeyType> *tree)
{
	if (tree == NULL)
		return;
	WorkAroundSymmetric(tree->left);
	cout << tree->key << '(' << tree->balance << ')';
		workAroundSymmetr(tree->right);
}

template <class KeyType>
void Binary_search_tree<KeyType>::WorkAroundReverse(Node<KeyType> *tree)
{
	if (tree == NULL)
		return;
	WorkAroundReverse(tree->left);
	WorkAroundReverse(tree->right);
	cout << tree->key << '(' << tree->balance << ')';
}

template <class KeyType>
int Binary_search_tree<KeyType>::operator==(const Binary_search_tree<KeyType>& tree)const
{
	if ((root == NULL) && (tree.root == NULL))
		return 1;
	if (size != tree.size)
		return 0;
	int *z = new int[size];
	int *b = new int[tree.size];
	queue <Node<KeyType>*> q;
	queue <Node<KeyType>*> p;
	q.push(root);
	int tmp1 = 0;
	int tmp2 = 0;
	while (q.empty() == 0)
	{
		Node<KeyType>* tmp = q.front();
		z[tmp1] = tmp->key;
		q.pop();
		if (tmp->left != NULL)
			q.push(tmp->left);
		if (tmp->right != NULL)
			q.push(tmp->right);
		tmp1++;
	}
	p.push(root);
	while (p.empty() == 0)
	{
		Node<KeyType>* tmp3 = p.front();
		b[tmp2] = tmp3->key;
		p.pop();
		if (tmp3->left != NULL)
			p.push(tmp3->left);
		if (tmp3->right != NULL)
			p.push(tmp3->right);
		tmp2++;
	}
	for (int i = 0; i<size; i++)
		if (z[i] != b[i])
			return 0;
	return 1;
}




template <class KeyType>
int Binary_search_tree<KeyType>::GetSize()
{
	return size;
}

template <class KeyType>
int Binary_search_tree<KeyType>::GetHeight(Node<KeyType> *tree)
{
	if (tree == NULL)
		return 0;
		int l, r;
	if (tree->left != NULL)
	{
		l = GetHeight(tree->left);
	}
	else
		l = -1;
	if (tree->right != NULL)
	{
		r = GetHeight(tree->right);
	}
	else
		r = -1;
	int max = l > r ? l : r;
	return max + 1;
};