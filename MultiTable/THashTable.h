#pragma once

#include "TTable.h"

class THashTable : public TTable
{
protected:
	virtual unsigned long long HashFunc(const TKey& key)
	{
		//хэш функция генерирует индекс для ключа
		unsigned long long hv = 0; // hashValue
		int keySize = key.size();
		for (int i = 0; i < keySize; i++)
		{
			hv = (hv << 3) + key[i];
		}
		return hv;
	}
public:
	THashTable() : TTable() {}
};

