#pragma once

#include "TArrayTable.h"

class TScanTable : public TArrayTable
{
public:
	TScanTable(size_t size = 50) : TArrayTable(size) {}

	virtual PTDatValue FindRecord(TKey key);
	virtual bool InsertRecord(TKey key, PTDatValue value); // передача value по ссылке
	virtual void DeleteRecord(TKey key);
};

