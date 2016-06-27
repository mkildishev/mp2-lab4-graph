#pragma once 

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
using namespace std;


template <class KeyType>
class Edge
{
public:
	Edge(int, int, KeyType);
	int from;
	int to;
	KeyType weight;
};

template <class KeyType>
class Graph
{
private:
	int n; //number of vertices
	int m; //number of edges
	Edge<KeyType>** edges;
	int current;
public:
	Graph(int, int);
	~Graph();
	void CreateGraph(KeyType, KeyType);
	void Push(int, int, KeyType);
	void Remove(int, int);
	int GetCount(); //vertices
	int GetEdgeSize();
	int GetRealSize();
	Edge<KeyType>*  GetEdge(int);
	KeyType GetWeight(int, int);
	void Print();
	int FindEdge(int, int);
	void Create(int&, int&);
	bool Scan(int, int*);
	void Sort();
};

template <class KeyType>
Edge<KeyType>::Edge(int f, int t, KeyType w)
{
	from = f;
	to = t;
	weight = w;
}

template <class KeyType>
Graph<KeyType>::Graph(int v, int e)
{
	if (v < 0)
		throw
		exception("Incorrect vertex"); 
	else
		n = v;
	if ((e < 0) || (e > n * (n - 1) / 2))
		throw
		exception("Incorrect edge");
	else
		m = e;
	current = 0;
	edges = new Edge<KeyType>*[m];
}

template <class KeyType>
Graph<KeyType>::~Graph()
{
	for (int i = 0; i < current; i++)
		delete edges[i];
	delete[] edges;
}

template <class KeyType>
void Graph<KeyType>::Push(int f, int t, KeyType w)
{
	if (current == m)
		throw
		exception("Graph is full"); 
	if (f == t)
		throw
		exception("Loops are prohibited");
	if ((f > n) || (t > n))
		throw
		exception("There are no such vertexs"); 
	edges[current] = new Edge<KeyType>(f, t, w);
	current++; //test
}

template <class KeyType>
void Graph<KeyType>::Create(int &f, int &t)
{
	do
	{
		f = rand() % n;
		t = rand() % n;
	} while ((f == t) || (FindEdge(f, t) != -1));
}

template <class KeyType>
void Graph<KeyType>::CreateGraph(KeyType f, KeyType t)
{
	if (f > t)
		throw
		exception("Incorrect distance"); 
	int u, v;
	KeyType newweight;
	srand(time(NULL));
	for (int i = 0; i < m; i++)
	{
		Create(u, v);
		newweight = f + static_cast <KeyType> (rand()) / (static_cast <KeyType> (RAND_MAX / (t - f)));
		edges[i] = new Edge<KeyType>(u, v, newweight);
		current++;
	}
}

template <class KeyType>
int Graph<KeyType>::GetCount()
{
	return n;
}

template <class KeyType>
int Graph<KeyType>::GetEdgeSize()
{
	return m;
}

template <class KeyType>
int Graph<KeyType>::GetRealSize()
{
	return current;
}

template <class KeyType>
KeyType Graph<KeyType>::GetWeight(int f, int t)
{
	if ((f < 0) || (f > n) || (t < 0) || (t > n))
		throw
		exception("Incorrect vertexs"); 
	for (int i = 0; i < current; i++)
		if ((edges[i]->from == f) && (edges[i]->to == t) || (edges[i]->from == t) && (edges[i]->to == f))
			return edges[i]->weight;
	return 0;
}

template <class KeyType>
void Graph<KeyType>::Print()
{
	cout << "От  до " << endl;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < current; j++)
			if (edges[j]->from == i)
				cout << edges[j]->from << " " << edges[j]->to << "(" << edges[j]->weight << ")" << endl;
}

template <class KeyType>
Edge<KeyType>* Graph<KeyType>::GetEdge(int x)
{
	return edges[x];
}

template <class KeyType>
void Graph<KeyType>::Remove(int f, int t)
{
	int tmp = FindEdge(f, t);
	if (tmp == -1)
		throw
		exception("Edge doesn't exist"); 
	delete edges[tmp];
	edges[tmp] = edges[current - 1];
	current--; //test
}

template <class KeyType>
int Graph<KeyType>::FindEdge(int f, int t)
{
	for (int i = 0; i < current; i++)
	{
		if ((edges[i]->from == f) && (edges[i]->to == f) || (edges[i]->from == t) && (edges[i]->to == t))
			return -1;
		if ((edges[i]->from == f) && (edges[i]->to == t) || (edges[i]->to == f) && (edges[i]->from == t))
			return i;
	}
	return -1;

}

template <class KeyType>
void Graph<KeyType>::Sort()
{
	Edge<KeyType> *tmp = new Edge<KeyType>(0, 0, 0);
	for (int i = 0; i < m; i++)
	{
		for (int j = m - 1; j > i; j--)
		{
			if (edges[j]->weight < edges[j - 1]->weight)
			{
				tmp = edges[j];
				edges[j] = edges[j - 1];
				edges[j - 1] = tmp;
			}
		}
	}
}

template <class KeyType>
bool Graph<KeyType>::Scan(int f, int* b)
{
	bool res = false;
	for (int i = 0;i < n; i++)
		if (b[i] == f)
			res = true;
	return res;
}

