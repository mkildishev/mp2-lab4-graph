#pragma once

#include <iostream>
#include <cmath>

#define max_heap 10000

using namespace std;

template <class KeyType>
class Prior
{
public:
	KeyType pr;
};

template <class KeyType>
class Distance : public Prior<KeyType>
{
public:
	int vertice;
	Distance(int, KeyType);
};

template <class KeyType>
class D_heap
{
public:
	int d;
	Prior<KeyType>** keys;
	int count;
public:
	D_heap(int, int);
	D_heap(const D_heap<KeyType>&);
	~D_heap();
	int GetParent(int);
	void Swap(const int, const int);
	void SiftUp(int);
	void SiftDown(int);
	int MinChild(int);
	void RemoveMin();
	void Remove(int);
	void Push(KeyType);
	void Heapify();
	void GetHeap();
	int operator==(const D_heap<KeyType>&) const;
	D_heap& operator=(const D_heap<KeyType>&);
	int GetCount();
	Prior<KeyType>* GetKey(int);
	void Sort();
	void Print();
	void changeKey(int pos, int newkey);
	KeyType GetKeyPr(int);
};

template <class KeyType>
Distance<KeyType>::Distance(int v, KeyType w)
{
	vertice = v;
	pr = w;
}

template <class KeyType>
D_heap<KeyType>::D_heap(const int arity, const int s)
{
	if (arity <= 0)
		throw
		exception("Arity must be positive"); 
	if ((s < 0) || (s > max_heap))
		throw
		exception("Size can't be negative or bigger than max size"); 
	d = arity;
	count = s;
	keys = new Prior<KeyType>*[max_heap];
};

template <class KeyType>
D_heap<KeyType>::D_heap(const D_heap &heap)
{
	d = heap.d;
	count = heap.count;
	keys = new Prior<KeyType>*[max_heap];
	for (int i = 0; i <= count - 1; i++)
		keys[i] = heap.keys[i];
};

template <class KeyType>
D_heap<KeyType>::~D_heap()
{
	delete[]keys;
}

template <class KeyType>
int D_heap<KeyType>::GetParent(int x)
{
	int p;
	return p = (x - 1) / d;
}

template <class KeyType>
void D_heap<KeyType>::Swap(const int x, const int y)  
{
	if ((x > count - 1) || (y > count - 1))
		throw
		exception("Incorrect index");
	Prior<KeyType> *tmp = new Prior<KeyType>;
	tmp->pr = keys[x]->pr;
	keys[x]->pr = keys[y]->pr;
	keys[y]->pr = tmp->pr;
}

template <class KeyType>
void D_heap<KeyType>::SiftUp(int x)
{
	if (x > count - 1)
		throw
		exception("Incorrect index"); 
	int p = GetParent(x);
	while ((p >= 0) && (keys[p]->pr > keys[x]->pr))
	{
		if (p == 0)
		{
			Swap(x, p);
			return;
		}
		Swap(x, p);
		x = p;
		p = GetParent(x);
	}
}

template <class KeyType>
int D_heap<KeyType>::MinChild(int x)
{
	if (x * d + 1 > count - 1)
		return -1;
	int minc = x * d + 1;
	int maxc;
	if (x * d + d < count - 1)
		maxc = x * d + d;
	else
		maxc = count - 1;
	for (int i = minc; i <= maxc; i++)
		if (keys[i]->pr < keys[minc]->pr)
			minc = i;
	return minc;
}

template <class KeyType>
void D_heap<KeyType>::SiftDown(int x)
{
	if (x > count)
		throw
		exception("Incorrect index");
	int c = MinChild(x);
	while ((c != -1) && (keys[c]->pr < keys[x]->pr))
	{
		Swap(c, x);
		x = c;
		c = MinChild(x);
	}
}

template <class KeyType>
void D_heap<KeyType>::RemoveMin()
{
	keys[0] = keys[count - 1];
	count--;
	SiftDown(0);
}

template <class KeyType>
void D_heap<KeyType>::Remove(int x)
{
	if (x >= count)
		throw
		exception("Incorrect index"); 
	Swap(x, count - 1);
	count--; 
	if (keys[x]->pr < keys[GetParent(x)]->pr)
		SiftUp(x);
	else SiftDown(x);
}

template <class KeyType>
void D_heap<KeyType>::Push(KeyType x)
{
	Prior<KeyType>* tmp2 = new Prior<KeyType>;
	tmp2->pr = x;
	count++; 
	if (count > max_heap)
		throw
		exception("Heap is full"); 
	Prior<KeyType>** tmp = new Prior<KeyType>*[max_heap];
	for (int i = 0; i < count - 1; i++)
		tmp[i] = keys[i];
	tmp[count - 1] = tmp2;
	keys = tmp;
}

template <class KeyType>
void D_heap<KeyType>::Heapify()
{
	if (count == 0)
		throw
		exception("Heap is empty"); 
	for (int i = count - 1; i >= 0; i--)
		SiftDown(i);
}

template <class KeyType>
int D_heap<KeyType>::operator==(const D_heap<KeyType>& heap) const
{
	if (heap.count != count)
		return 0;
	for (int i = 0; i < heap.count; i++)
		if (keys[i]->pr != heap.keys[i]->pr)
			return 0;
	return 1;
}

template <class KeyType>
void D_heap<KeyType>::GetHeap()
{
	int level = 0;
	int tmp = 0;
	while (tmp < count)
	{
		tmp += pow(d, level);
		level++;
	}
	int k = 1, z = 0;
	cout << ' ' << keys[0]->pr << endl;
	for (int i = 1; i < level; i++)
	{
		for (int j = k; (j < k + pow(d, i)) && (j < count); j++)
			cout << keys[j]->pr << ' ';
		cout << endl;
		if (k + pow(d, i) > count)
			k = count;
		else
			k += pow(d, i);
	}
}

template <class KeyType>
D_heap<KeyType>& D_heap<KeyType>::operator=(const D_heap<KeyType>& heap)
{
	d = heap.d;
	count = heap.count;
	for (int i = 0; i < count; i++)
		keys[i] = heap.keys[i];
	return *this;
}

template <class KeyType>
int D_heap<KeyType>::GetCount()
{
	return count;
}

template <class KeyType>
Prior<KeyType>* D_heap<KeyType>::GetKey(int x)
{
	return keys[x];
}


template <class KeyType>
void D_heap<KeyType>::Sort()
{
	int tmp = count;
	for (int i = count - 1; i > 0; i--)
		Remove(0);
	count = tmp;
	tmp = 0;
	int tmp2 = count - 1;
	while (tmp <= tmp2)
	{
		Swap(tmp2, tmp);
		tmp++;
		tmp2--;
	}
}


template <class KeyType>
void D_heap<KeyType>::Print()
{
	int level = 0, tmp = 0;
	while (tmp < count)
	{
		tmp += pow(d, level);
		level++;
	}
	int k = 1, z = 0;
	cout << " " << keys[0]->pr << " ";
	for (int i = 1; i < level; i++)
	{
		for (int j = k; (j < k + pow(d, i)) && (j < count); j++)
			cout << keys[j]->pr << " ";
		if (k + pow(d, i) > count)
			k = count;
		else k += pow(d, i);
	}
}

template<class KeyType>
void D_heap<KeyType>::changeKey(int pos, int newkey)
{
	if (pos >= count || pos < 0)
		throw pos;
	keys[pos]->pr = newkey;
}

template<class KeyType>
KeyType D_heap<KeyType>::GetKeyPr(int a)
{
	return keys[a]->pr;
}
