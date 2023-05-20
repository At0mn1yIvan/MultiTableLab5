#include "TListHashTable.h"

TListHashTable::TListHashTable(size_t size)
{
	pList = new std::list<PTTabRecord>[size];
	for (int i = 0; i < size; i++)
	{
		pList[i] = std::list<PTTabRecord>();
	}
}

TListHashTable::~TListHashTable()
{
	delete[] pList;
}

PTDatValue TListHashTable::FindRecord(TKey key)
{
	PTDatValue tmp = nullptr;
	curList = HashFunc(key) % tabSize;
	Efficiency = 0;
	auto iterator = pList[curList].begin();

	for (; iterator != pList[curList].end(); iterator++)
	{
		Efficiency++;
		if ((*iterator)->GetKey() == key)
		{
			tmp = (*iterator)->GetValue();
			curElem = *iterator;
			break;
		}
	}
	if (tmp == nullptr)
		SetRetCode(TAB_NO_RECORD);
	else
		SetRetCode(TAB_OK);
	return tmp;
}

bool TListHashTable::InsertRecord(TKey key, PTDatValue value)
{
	if (IsFull())
	{
		SetRetCode(TAB_FULL);
	}
	else
	{
		PTDatValue tmp = FindRecord(key);
		if (tmp != nullptr)
		{
			SetRetCode(TAB_REC_DOUBLE);
		}
		else
		{
			SetRetCode(TAB_OK);
			DataCount++;
			pList[curList].push_front(new TTabRecord(key, value));
			return true;
		}
	}
	return false;
}

void TListHashTable::DeleteRecord(TKey key)
{
	PTDatValue tmp = FindRecord(key);
	if (tmp == nullptr)
	{
		SetRetCode(TAB_NO_RECORD);
	}
	else
	{
		SetRetCode(TAB_OK);
		pList[curList].remove(curElem);
		DataCount--;
	}
}

int TListHashTable::Reset()
{
	curList = 0;
	iter = pList[curList].begin();
	return IsTabEnded();
}

int TListHashTable::IsTabEnded() const
{
	return curList >= tabSize;
}

int TListHashTable::IsListEnded() const
{
	auto tmp = iter;
	return ++tmp == pList[curList].end();
}

int TListHashTable::GoNext()
{
	if (!IsListEnded())
	{ 
		iter++;
	}
	else if (IsTabEnded())
	{
		while (pList[++curList].empty() && !IsTabEnded());
		iter = pList[curList].begin();
	}
	return IsTabEnded();
}

TKey TListHashTable::GetKey() const
{
	return (*iter)->GetKey();

}

PTDatValue TListHashTable::GetValuePTR() const
{
	return (*iter)->GetValue();
}
