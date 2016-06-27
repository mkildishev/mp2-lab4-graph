#include "algorithm.hpp"

typedef float KeyType;

void main()
{
	setlocale(LC_CTYPE, "Russian");
	int q;
	cout << "������ ��� ������������ �������" << endl << "1. ���������� �� �������� ����" << endl << "2. ���������� �� �������� ��������� ������" << endl << "3. ���������� �� �������" << endl;
	cin >> q;
	system("cls");
	int n;
	cout << "����� ���������� ������" << endl;
	cin >> n;
	cout << "����� ���������� ����" << endl;
	int m;
	cin >> m;
	Graph<KeyType> *graph = new Graph<KeyType>(n, m);
	int type;
	cout << "������ ��� ����� �����" << endl << "1. ��������� ��������� �������" << endl << "2. ��������� �������" << endl;
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
		for (int i = 0; i<m;i++)
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

	cout << "���� " << endl << endl;
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
