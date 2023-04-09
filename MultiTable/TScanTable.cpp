#include "TScanTable.h"

PTDatValue TScanTable::FindRecord(TKey key)
{
    int i;
    SetRetCode(TAB_OK);
    for (i = 0; i < DataCount; i++)
    {
        if (pData[i]->_key == key)
            break;
    }
    Efficiency = i + 1;

    if (i < DataCount)
    {
        curPos = i;
        return pData[curPos]->_value;
    }
    SetRetCode(TAB_NO_RECORD);
    return nullptr;
}

bool TScanTable::InsertRecord(TKey key, PTDatValue value)
{
    if (this->isFull())
    {
        SetRetCode(TAB_FULL);
        return false;
    }

    pData[DataCount] = new TTabRecord(key, value);
    DataCount++;
    SetRetCode(TAB_OK);
    return true;
}

void TScanTable::DeleteRecord(TKey key)
{
    PTDatValue t =  this->FindRecord(key);
    if (t == nullptr)
        SetRetCode(TAB_NO_RECORD);
    else
    {
        SetRetCode(TAB_OK);
        pData[curPos] = pData[DataCount - 1];
        pData[--DataCount] = nullptr;
    }
}
