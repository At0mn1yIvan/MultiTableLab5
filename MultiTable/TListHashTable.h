#pragma once

#include <list>
#include "THashTable.h"

class TListHashTable : public THashTable
{
protected:
	size_t tabSize;
	size_t curList; // индекс текущего листа, в который мы смотрим
	PTTabRecord curElem;
	std::list<PTTabRecord>::iterator iter;
	std::list<PTTabRecord>* pList;
public:
	TListHashTable(size_t size = 50);
	virtual ~TListHashTable();

	virtual bool isFull() const
	{
		return pList == nullptr;
	}

	virtual PTDatValue FindRecord(TKey key) override;
	virtual bool InsertRecord(TKey key, PTDatValue value) override;
	virtual void DeleteRecord(TKey key) override;

	virtual int Reset() override;
	virtual int IsTabEnded() const override;
	virtual int IsListEnded() const;
	virtual int GoNext() override;

	virtual TKey GetKey() const override;
	virtual PTDatValue GetValuePTR() const override;
};

