#pragma once

#include "TTable.h"

class THashTable : public TTable
{
protected:
	virtual unsigned long long HashFunc(const TKey& key)
	{
		//��� ������� ���������� ������ ��� �����
		unsigned long long hv = 0;
		int keySize = key.size();
		for (int i = 1; i < keySize; i++)
		{
			hv += (int)key[i];
		}
		//return (hv % 100 < 0 ? hv % 100 : hv); // 145 ������
		return (hv / -100 > 0 ? hv % 100 / -10 - hv % 10 : hv / -10 - hv % 10); // 464 �������
		//return std::hash<TKey>()(key);
	}
public:
	THashTable() : TTable() {}
};

