#include "algorithm.hpp"

typedef float KeyType;

void main()
{
	setlocale(LC_CTYPE, "Russian");
	int q;
	cout << "Выбери тип приоритетной очереди" << endl << "1. Основанная на бинарной куче" << endl << "2. Основанная на бинарном поисковом дереве" << endl << "3. Основанная на таблице" << endl;
	cin >> q;
	system("cls");
	int n;
	cout << "Введи количество вершин" << endl;
	cin >> n;
	cout << "Введи количество рёбер" << endl;
	int m;
	cin >> m;
	Graph<KeyType> *graph = new Graph<KeyType>(n, m);
	int type;
	cout << "Выбери тип ввода графа" << endl << "1. Заполнить случайным образом" << endl << "2. Заполнить вручную" << endl;
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
		for (int i = 0; i<m;i++)
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

	cout << "Граф " << endl << endl;
	graph->Print();
	Graph<KeyType> *res = new Graph<KeyType>(n, m);
	graph->Sort();
	Priority_queue<KeyType>* queue;
	int tmp2 = 0;
	if (q == 1)
		tmp2 = n;
	if (q == 3)
		tmp2 = m;
	Create_queue<KeyType>::CreateQueue(queue, q, tmp2);
	res = Algorithm<KeyType>::Kruskal(graph, queue);
	cout << endl << endl;
	res->Print();
}
