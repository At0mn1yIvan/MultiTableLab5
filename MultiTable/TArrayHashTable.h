#pragma once

#include "THashTable.h"
class TArrayHashTable : public THashTable
{
protected:
	PTTabRecord* pData;
	size_t tabSize;
	size_t freePos;
	size_t curPos;
	PTTabRecord pMark;
	int hashStep;
	int GetNextPosition(size_t pos)
	{
		//??? подментованный кот
		return (pos + hashStep) % tabSize;
	}
public:
	TArrayHashTable(size_t size = 50, int hashStep = 7);
	virtual ~TArrayHashTable();
	virtual bool isFull() const
	{
		return DataCount >= tabSize;
	}
	virtual PTDatValue FindRecord(TKey key) override;
	virtual bool InsertRecord(TKey key, PTDatValue value) override;
	virtual void DeleteRecord(TKey key) override;

	virtual int Reset() override;
	virtual int IsTabEnded() const override;
	virtual int GoNext() override;

	virtual TKey GetKey() const override;
	virtual PTDatValue GetValuePTR() const override;
};

