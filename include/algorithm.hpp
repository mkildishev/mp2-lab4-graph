#pragma once
#include "priority_queue.hpp"
#include "binary_search_tree.hpp"
#include "disjoint_set.hpp"
#include "d-heap.hpp"
#include "table.hpp"
#include "graph.hpp"

using namespace std;

template <class KeyType>
class Algorithm
{
public:
	static Graph<KeyType>* Kruskal(Graph<KeyType>*&, Priority_queue<KeyType>*&); 
	static KeyType* Dijkstra(int, KeyType *&, Graph<KeyType>*&);
	static void SortP(D_heap<KeyType>*& a);
};

template <class KeyType>
Graph<KeyType>* Algorithm<KeyType>::Kruskal(Graph<KeyType>*& gr, Priority_queue<KeyType>*& queue)
{
	int n = gr->GetCount();
	int m = gr->GetRealSize();
	Graph<KeyType> *tree = new Graph<KeyType>(n, m);
	Disjoint_set<KeyType> *set = new Disjoint_set<KeyType>(n);
	for (int i = 0; i<n; i++)
		set->CreateSet(i);

	for (int i = 0; i<m;i++)
		queue->Push(gr->GetEdge(i)->weight);

	int treeEdgeSize = 0;
	int x = 0;
	KeyType tmp;

	while (treeEdgeSize < n - 1)
	{
		tmp = queue->Top();
		queue->Pop();

		int u = gr->GetEdge(x)->from;
		int v = gr->GetEdge(x)->to;
		KeyType weight = tmp;

		int An = set->FindSet(u);
		int Ak = set->FindSet(v);
		if (An != Ak)
		{
			set->UnionSet(An, Ak);
			tree->Push(u, v, weight);
			treeEdgeSize++;
		}
		x++;
	}

	return tree;
};

template <class KeyType>
KeyType* Algorithm<KeyType>::Dijkstra(int s, KeyType *&P, Graph<KeyType>*& gr)
{
	int n = gr->GetCount();
	int m = gr->GetRealSize();
	if ((s < 0) || (s >= n))
		throw
		exception("Element doesn't exist"); //test	
	KeyType **graph = new KeyType*[n];
	for (int i = 0; i < n; i++)
		graph[i] = new KeyType[n];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			graph[i][j] = -1;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			if ((gr->GetEdge(j)->from == i) || (gr->GetEdge(j)->to == i))
			{
				graph[gr->GetEdge(j)->from][gr->GetEdge(j)->to] = gr->GetEdge(j)->weight;
				graph[gr->GetEdge(j)->to][gr->GetEdge(j)->from] = gr->GetEdge(j)->weight;
			}
		}

	KeyType *distance = new KeyType[n];
	int *vis = new int[n];
	for (int i = 0; i < n; i++)
		vis[i] = -1;
	vis[0] = s;
	int path;
	int w, min;
	for (int i = 0; i < n; i++)
	{
		if (graph[s][i] == -1)
			distance[i] = max_heap;
		else distance[i] = graph[s][i];
	}
	for (int i = 1; i < n - 1; i++)
	{
		min = max_heap;
		for (int k = 0; k < n; k++) {
			if (distance[k] < min && k != s && !gr->Scan(k, vis))
			{
				w = k;
				min = distance[k];
			}
		}
		if (min == max_heap)
			break;
		vis[i] = w;
		for (int j = 0; j < n; j++)
		{
			if (!gr->Scan(j, vis) && graph[w][j] != -1 && (distance[w] + graph[w][j]) <= distance[j])
			{
				P[j] = w;
				distance[j] = distance[w] + graph[w][j];
			}
		}
	}

	distance[s] = 0;
	return distance;
}



template <class KeyType>
void Algorithm<KeyType>::SortP(D_heap<KeyType>*& a)
{
	int tmp = a->count;
	for (int i = a->count - 1; i > 0; i--)
		a->Remove(0);
	a->count = tmp;
	tmp = 0;
	int tmp2 = a->count - 1;
	while (tmp <= tmp2)
	{
		a->Swap(tmp2, tmp);
		tmp++;
		tmp2--;
	}
}