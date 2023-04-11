#include "TSortTable.h"

TSortTable& TSortTable::operator=(const TScanTable& st)
{
    if (pData != nullptr)
    {
        for (int i = 0; i < this->DataCount; i++)
        {
            delete pData[i];
        }
        delete[] pData;
        pData = nullptr;
    }

    size = st.GetSize();
    DataCount = st.GetDataCount();
    pData = new PTTabRecord[this->size];
    for (int i = 0; i < DataCount; i++)
    {
        pData[i] = (PTTabRecord)st.pData[i]->GetCopy();
    }
    SortData();
    curPos = 0;

    return *this;
}

void TSortTable::SortData()
{
    Efficiency = 0;
    switch (_sortMethod)
    {
        case SortMeth::BUBBLESORT:
            BubbleSort(pData, DataCount);
            break;
        case SortMeth::QUICKSORT:
            QuickSort(pData, DataCount);
            break;
        case SortMeth::MERGESORT:
            MergeSort(pData, DataCount);
            break;
        case SortMeth::INSERTSORT:
            InsertSort(pData, DataCount);
            break;
        default:
            FreeChoice(pData, DataCount);
            break;
    }
}

void TSortTable::InsertSort(PTTabRecord* data, int size)
{
    PTTabRecord curElem;
    Efficiency = DataCount;
    for (int i = 1, j; i < DataCount; i++)
    {
        curElem = data[i];
        for (int j = i - 1; j > -1; j--)
        {
            if (data[i]->GetKey() > curElem->GetKey())
            {
                data[j + 1] = data[j];
                Efficiency;
            }
            else break;
        }
        data[j + 1] = curElem;
    }
}
