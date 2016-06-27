#include <iostream>
#include "graph.hpp"
#include "priority_queue.hpp"
#include "algorithm.hpp"

typedef float KeyType; // ���  ��� ������
// � ��� � ���� ���� ������ ������ �� ���� ���, ��� �����

void main()
{
	setlocale(LC_CTYPE, "Russian");
	cout << "������. ����� ���������� ������:" << endl;
	int n;
	cin >> n;
	cout << "����� ���������� ����" << endl;
	int m;
	cin >> m;
	Graph<KeyType> *graph = new Graph<KeyType>(n, m);
	KeyType *P = new KeyType[n];



	int type;
	cout << "������ ��� �����" << endl << "1. ��������� ��������� �������" << endl << "2. ��������� �������" << endl;
	cin >> type;
	switch (type)
	{
	case 1:
	{
		cout << "����� ����������� � ������������ �������� ���� �����" << endl;
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
			cout << "����� ""������"" ������� �����, ����� ""����"", � ����� ��� ��� " << endl;
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
	cout << "����: " << endl << endl;
	graph->Print();
	cout << "����� ����� �����:" << endl;
	int a;
	cin >> a;
	for (int i = 0; i <= n; i++) // fixed
		P[i] = a;
	KeyType *dist = Algorithm<KeyType>::Dijkstra(a, P, graph);
	cout << "����: " << endl << endl;
	for (int i = 0; i<n; i++)
		cout << i << ' ';
	cout << "������� " << endl << endl;
	for (int i = 0; i < n; i++)
		if (dist[i] == max_heap)
			cout << 0 << ' ';
		else
			cout << dist[i] << ' ';
	cout << "���������� ���� " << endl << endl;
	for (int i = 0; i<n; i++)
		cout << P[i] << ' ';
	cout << "���������� ������� " << endl << endl;
	
}
