#include "TArrayHashTable.h"

TArrayHashTable::TArrayHashTable(size_t size, int hStep): tabSize(size), hashStep(hStep)
{
	pData = new PTTabRecord[size];
	for (int i = 0; i < size; i++)
	{
		pData[i] = nullptr;
	}
	pMark = new TTabRecord("", nullptr);

}

TArrayHashTable::~TArrayHashTable()
{
	for (int i = 0; i < tabSize; i++)
	{
		if (pData[i] != nullptr && pData[i] != pMark) delete pData[i];
	}
	delete[] pData;
	delete pMark;
}

PTDatValue TArrayHashTable::FindRecord(TKey key)
{
	PTDatValue ptmp = nullptr;
	freePos = -1;
	Efficiency = 0;
	curPos = HashFunc(key) % tabSize;
	for (int i = 0; i < tabSize; i++)
	{
		Efficiency++;
		if (pData[curPos] == nullptr)
		{
			break;
		}
		else if (pData[curPos] == pMark)
		{
			if (freePos == -1)
				freePos = curPos;
		}
		else if (pData[curPos]->GetKey() == key)
		{
			ptmp = pData[curPos]->GetValue();
			break;
		}
		curPos = GetNextPosition(curPos);
	}
	if (ptmp == nullptr) SetRetCode(TAB_NO_RECORD);
	else SetRetCode(TAB_OK);

	return ptmp;
}

bool TArrayHashTable::InsertRecord(TKey key, PTDatValue value)
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
			if (freePos != -1) curPos = freePos;
			pData[curPos] = new TTabRecord(key, value);
			DataCount++;
			return true;
		}
	}
	return false;
}

void TArrayHashTable::DeleteRecord(TKey key)
{
	PTDatValue tmp = FindRecord(key);
	if (tmp == nullptr)
		SetRetCode(TAB_NO_RECORD);
	else
	{ 
		SetRetCode(TAB_OK);
		delete pData[curPos];
		pData[curPos] = pMark;
		DataCount--;
	}

}

int TArrayHashTable::Reset()
{
	curPos = 0;
	while(curPos < tabSize)
	{
		if (pData[curPos] != nullptr && pData[curPos] != pMark) break;
		curPos++;
	}
	return IsTabEnded();
}

int TArrayHashTable::IsTabEnded() const
{
	return curPos >= tabSize;
}

int TArrayHashTable::GoNext()
{
	if (!IsTabEnded())
	{
		//??? 
		while (curPos < tabSize)
		{
			if (pData[curPos] != nullptr && pData[curPos] != pMark) break;
		}
	}
	return IsTabEnded();
}

TKey TArrayHashTable::GetKey() const
{
	if (curPos >= 0 && curPos < tabSize)
		return pData[curPos]->GetKey();
	return "";
}

PTDatValue TArrayHashTable::GetValuePTR() const
{
	if (curPos >= 0 && curPos < tabSize)
		return pData[curPos]->GetValue();
	return nullptr;
}
