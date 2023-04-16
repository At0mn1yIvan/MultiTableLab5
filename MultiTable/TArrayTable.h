#pragma once


#include "TTable.h"


enum class Position
{
	FIRST,
	CURRENT,
	LAST,
};

class TArrayTable: public TTable {
protected:
	PTTabRecord* pData;
	size_t size;
	size_t curPos;
public:
	TArrayTable(size_t size = 50) : size(size), curPos(0) {
		pData = new PTTabRecord[this->size];
		for (int i = 0; i < this->size; i++) {
			pData[i] = nullptr;
		}
	}

	virtual ~TArrayTable() {
		for (int i = 0; i < this->size; i++) {
			delete pData[i];
		}
		delete[] pData;
	}

	virtual bool isFull() const override {
		return DataCount >= size;
	}

	size_t GetSize() const { return size; }
	
	virtual TKey GetKey(Position pos) const;
	virtual TKey GetKey() const { return GetKey(Position::CURRENT); }

	virtual PTDatValue GetValuePTR(Position pos) const;
	virtual PTDatValue GetValuePTR() const { return GetValuePTR(Position::CURRENT); }

	//virtual PTDatValue FindRecord(TKey key) = 0;
	//virtual bool InsertRecord(TKey key, PTDatValue value) = 0; // передача value по ссылке
	//virtual void DeleteRecord(TKey key) = 0;

	virtual int Reset(void) // установить на первую запись
	{
		this->curPos = 0;
		return this->IsTabEnded();
	}
	virtual int IsTabEnded(void) const // таблица завершена?
	{	
		return this->curPos >= DataCount;
	}
	virtual int GoNext(void)
	{
		if (!this->IsTabEnded())
			this->curPos++;
		return this->IsTabEnded();
	}

	virtual int SetCurrentPos(int pos)// установить текущую запись
	{
		if (pos < 0 || pos > DataCount)
			curPos = 0;
		else
			curPos = pos;
		return IsTabEnded();
	}
	int GetCurrentPos(void) const
	{
		return curPos;
	}

	friend class TSortTable;
};