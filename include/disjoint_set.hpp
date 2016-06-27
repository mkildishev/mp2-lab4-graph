#pragma once


#include "priority_queue.hpp"
#include "graph.hpp"
#include "d-heap.hpp"
#include <stack>

template <class KeyType>
class Disjoint_set
{
private:
	int *parent;
	int *height;
	int n;
public:
	Disjoint_set(int);
	~Disjoint_set();
	void CreateSet(int);
	int FindSet(int);
	void UnionSet(int, int);
	void Print();
	int* GetSet(int);
};

template <class KeyType>
Disjoint_set<KeyType>::Disjoint_set(int a)
{
	if (a < 0)
		throw
		exception("Size must be positive"); 
	parent = new int[a];
	for (int i = 0; i < a; i++)
		parent[i] = -1;
	height = new int[a];
	n = a;
}

template <class KeyType>
Disjoint_set<KeyType>::~Disjoint_set()
{
	delete[] parent;
	delete[] height;
}

template <class KeyType>
void Disjoint_set<KeyType>::CreateSet(int a)
{
	if ((a > n) || (a < 0))
		throw
		exception("Incorrect element"); 
	if (parent[a] != -1)
		return;
	parent[a] = a;
	height[a] = 0;
}

template <class KeyType>
int Disjoint_set<KeyType>::FindSet(int a)
{
	if ((a > n) || (a < 0))
		throw
		exception("Incorrect element"); 
	if (parent[a] == -1)
		return -1;
	while (parent[a] != a)
		a = parent[a];
	return a;
}

template <class KeyType>
void Disjoint_set<KeyType>::UnionSet(int a, int b)
{
	if ((a > n) || (a < 0) || (b > n) || (b < 0))
		throw
		exception("Incorrect element"); 
	if ((parent[a] == -1) || (parent[b] == -1))
		throw
		exception("Set is empty"); 
	a = FindSet(a);
	b = FindSet(b);
	if (height[a] > height[b])
		parent[b] = a;
	else if (height[a] < height[b])
		parent[a] = b;
	else
	{
		parent[b] = a;
		height[a]++;
	}
}

template <class KeyType>
int* Disjoint_set<KeyType>::GetSet(int a)
{
	if ((a > n) || (a < 0))
		throw
		exception("Incorrect element"); 
	if (parent[a] != a)
		throw
		exception("Incorrect element"); 
	stack<int> st;
	int *res = new int;
	for (int i = 0; i<n; i++)
	{
		if (parent[i] == a)
			st.push(i);
	}
	res[0] = st.size();
	int j = 1;
	while (!st.empty())
	{
		res[j] = st.top();
		st.pop();
		j++;
	}
	return res;
}

template <class KeyType>
void Disjoint_set<KeyType>::Print()
{
	KeyType*tmp = new KeyType;
	for (int i = 0; i<n;i++)
	{
		if (parent[i] == i)
		{
			tmp = GetSet(i);
			if (tmp[0] > 1)
			{
				cout << '{';
				for (int k = 1; k <= tmp[0]; k++)
					cout << tmp[k] << ' ';
				cout << "} ";
			}
			else
				cout << '{' << tmp[1] << "} ";
		}
	}
	cout << endl;
}

template <class KeyType>
class DataEdge : public Prior<KeyType>
{
public:
	DataEdge(Edge<KeyType>*);
	Edge<KeyType> *e;
};

template <class KeyType>
DataEdge<KeyType>::DataEdge(Edge<KeyType> *a)
{
	e = a;
	pr = e->weight;
}

