#pragma once

#include "TTable.h"

class THashTable : public TTable
{
protected:
	virtual size_t HashFunc(const TKey& key)
	{
		//��� ������� ���������� ������ ��� �����
		//unsigned long long hv = 0; // hashValue
		//int keySize = key.size();
		return std::hash<TKey>()(key);
	}
public:
	THashTable() : TTable() {}
};

