#include <iostream>
#include "graph.hpp"
#include "priority_queue.hpp"
#include "algorithm.hpp"

typedef float KeyType; // вот  тип данных
// и вот в этой вещи смысла вообще не вижу Саш, это Лыков

void main()
{
	setlocale(LC_CTYPE, "Russian");
	cout << "Привет. Введи количество вершин:" << endl;
	int n;
	cin >> n;
	cout << "Введи количество рёбер" << endl;
	int m;
	cin >> m;
	Graph<KeyType> *graph = new Graph<KeyType>(n, m);
	KeyType *P = new KeyType[n];



	int type;
	cout << "Выбери тип ввода" << endl << "1. Заполнить случайным образом" << endl << "2. Заполнить вручную" << endl;
	cin >> type;
	switch (type)
	{
	case 1:
	{
		cout << "Введи минимальное и максимальное значение веса ребра" << endl;
		KeyType min, max;
		cin >> min;
		cin >> max;
		graph->CreateGraph(min, max);
		break;
	}
	case 2:
	{
		for (int i = 0; i<m; i++)
		{
			cout << "Введи ""откуда"" следует ребро, потом ""куда"", а потом его вес " << endl;
			int f, t;
			KeyType w;
			cin >> f;
			cin >> t;
			cin >> w;
			graph->Push(f, t, w);
		}
		break;
	}
	}

	system("cls");
	cout << "Граф: " << endl << endl;
	graph->Print();
	cout << "Введи точку входа:" << endl;
	int a;
	cin >> a;
	for (int i = 0; i <= n; i++) // fixed
		P[i] = a;
	KeyType *dist = Algorithm<KeyType>::Dijkstra(a, P, graph);
	cout << "Итог: " << endl << endl;
	for (int i = 0; i<n; i++)
		cout << i << ' ';
	cout << "Вершины " << endl << endl;
	for (int i = 0; i < n; i++)
		if (dist[i] == max_heap)
			cout << 0 << ' ';
		else
			cout << dist[i] << ' ';
	cout << "Кратчайшие пути " << endl << endl;
	for (int i = 0; i<n; i++)
		cout << P[i] << ' ';
	cout << "Предыдущие вершины " << endl << endl;
	
}
