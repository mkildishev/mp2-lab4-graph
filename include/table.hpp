#pragma once

#include <iostream>

using namespace std;


template<class KeyType>
class TabRecord
{
public:
	int key;
	KeyType data;
	TabRecord(int k, KeyType d) { key = k; data = d; }
	int GetKey() { return key; }
	KeyType GetData() { return data; }
};


template<class KeyType>
class Table
{
protected:
	int size;
	int count;
	int pos;
public:
	Table(int);
	virtual TabRecord<KeyType>* FindKey(int) = 0;
	virtual void Push(int, KeyType) = 0;
	virtual void Remove(int) = 0;
	int	IsEmpty();
	int	IsFull();
	virtual int GetCount();
	virtual void Reset();
	virtual int	GoNext();
	virtual int IsTabEnded();
};

template <class KeyType>
Table<KeyType>::Table(int s)
{
	size = s;
	count = 0;
	pos = 0;
}

template <class KeyType>
int Table<KeyType>::IsEmpty()
{
	if (count == 0)
		return 1;
	return 0;
}

template <class KeyType>
int Table<KeyType>::IsFull()
{
	if (count == size)
		return 1;
	return 0;
}

template <class KeyType>
int Table<KeyType>::GetCount()
{
	return count;
}

template <class KeyType>
void Table<KeyType>::Reset()
{
	pos = 0;
}

template <class KeyType>
int Table<KeyType>::GoNext()
{
	if (!IsTabEnded())
	{
		pos++;
		return 1;
	}
	return 0;
}

template <class KeyType>
int Table<KeyType>::IsTabEnded()
{
	if (pos == count)
		return 1;
	return 0;
}


template<class KeyType>
class Scan_table : public Table<KeyType>
{
protected:
	TabRecord<KeyType>** recs;
public:
	Scan_table(int size) : Table<KeyType>(size)
	{
		recs = new TabRecord<KeyType>*[size];
		for (int i = 0; i < size; i++)
			recs[i] = NULL;
	}
	virtual ~Scan_table()
	{
		for (int i = 0; i < size; i++)
			delete recs[i];
		delete[]recs;
	}

	virtual TabRecord<KeyType>* FindKey(int k)
	{
		for (int i = 0; i < count; i++)
			if (k == recs[i]->GetKey())
			{
				pos = i;
				return recs[i];
			}
		return NULL;
	}
	virtual void Push(int k, KeyType d)
	{
		if (IsFull())
			throw
			exception("Table is empty");
		recs[count] = new TabRecord<KeyType>(k, d);
		count++; 
	}
	virtual void Remove(int k)
	{
		if (IsEmpty())
			return;
		if (FindKey(k) == NULL)
			return;
		delete recs[pos];
		recs[pos] = recs[count - 1];
		count--; 
	}
	void Print();
	virtual int GetCount()
	{
		return count;
	}
	int GetSize();
	TabRecord<KeyType>** GetRecs();
};

template <class KeyType>
void Scan_table<KeyType>::Print()
{
	for (int i = 0; i < count; i++)
		cout << recs[i]->GetKey() << " " << recs[i]->GetData() << endl;
}

template <class KeyType>
int Scan_table<KeyType>::GetSize()
{
	return size;
}

template <class KeyType>
TabRecord<KeyType>** Scan_table<KeyType>::GetRecs()
{
	return recs;
}

template<class KeyType>
class Sort_table : public Scan_table<KeyType>
{
public:
	Sort_table(int size) : Scan_table<KeyType>(size) {};
	Sort_table(Scan_table<KeyType>& table) : Scan_table<KeyType>(table) { Sort(); }
	virtual ~Sort_table()
	{
		for (int i = 0; i < size; i++)
			delete recs[i];
		delete[]recs;
	}

	virtual TabRecord<KeyType>* FindKey(int key)
	{
		int left = 0;
		int right = count - 1;
		int mid;
		while (left <= right)
		{
			mid = left + (right - left) / 2;
			if (key < recs[mid]->GetKey())
			{
				right = mid - 1;
				pos = left;
			}
			else if (key > recs[mid]->GetKey())
			{
				left = mid + 1;
				pos = left;
			}
			else
			{
				pos = mid;
				return recs[mid];
			}
		}
		return 0;
	}
	virtual void Push(int k, KeyType d)
	{
		if (IsFull())
			throw
			exception("Table is full"); 
		TabRecord<KeyType> *tmp;
		tmp = FindKey(k);
		for (int i = count + 1; i >= pos + 1; i--)
			recs[i] = recs[i - 1];
		recs[pos] = new TabRecord<KeyType>(k, d);
		count++; 
	};
	virtual void Remove(int k)
	{
		if (IsEmpty())
			return;
		if (FindKey(k) == NULL)
			throw
			exception("Such element doesn't exist");

		for (int i = pos; i < count - 1; i++)
			recs[i] = recs[i + 1];
		recs[count] = NULL;
		count--; 
	}

	void Sort();
	TabRecord<KeyType>* Min();
};

template <class KeyType>
void Sort_table<KeyType>::Sort()
{
	TabRecord<KeyType> *tmp;
	for (int i = 0; i < count; i++)
		for (int j = i + 1; j < count; j++)
			if (recs[i]->GetKey() > recs[j]->GetKey())
			{
				tmp = recs[i];
				recs[i] = recs[j];
				recs[j] = tmp;
			}
}

template <class KeyType>
TabRecord<KeyType>* Sort_table<KeyType>::Min()
{
	return recs[0];
}

