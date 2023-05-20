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

PTDatValue TSortTable::FindRecord(TKey key)
{
    int first = 0, last = DataCount - 1, mid;
    Efficiency = 0;
    this->SetRetCode(TAB_OK);
    while (first < last)
    {
        Efficiency++;
        mid = (first + last) >> 1;
        if (pData[mid]->GetKey() == key)
        {
            first = mid + 1;
            last = mid - 1;
        }
        else if (pData[mid]->GetKey() > key)
            last = mid - 1;
        else
            first = mid + 1;
    }
    if (last < 0 || pData[last]->GetKey() < key)
    {
        last++;
    }
    curPos = last;
    if (last < DataCount && (pData[last]->GetKey() == key))
    {
        this->SetRetCode(TAB_OK);
        return pData[last]->GetValue();
    }

    this->SetRetCode(TAB_NO_RECORD);
    return nullptr;
}

bool TSortTable::InsertRecord(TKey key, PTDatValue value)
{
    if (this->isFull())
    {
        this->SetRetCode(TAB_FULL);
    }
    else
    {
        PTDatValue tmp = FindRecord(key);
        if (RetCode == TAB_OK)
        {
            this->SetRetCode(TAB_REC_DOUBLE);
            return false;
        }
        else
        {
            this->SetRetCode(TAB_OK);
            for (int i = DataCount; i > curPos; i--)
            {
                pData[i] = pData[i - 1];
            }
            pData[curPos] = new TTabRecord(key, value);
            DataCount++;
            return true;
        }
    }
}

void TSortTable::DeleteRecord(TKey key)
{
    FindRecord(key);
    if (RetCode == TAB_OK)
    {
        for (int i = curPos; i < DataCount - 1; i++)
        {
            pData[i] = pData[i + 1];
        }
        pData[--DataCount] = nullptr;
    } // Проблема с утечкой памяти. Доказать
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
        for (j = i - 1; j > -1; j--)
        {
            if (pData[j]->GetKey() > curElem->GetKey())
            {
                data[j + 1] = data[j];
                Efficiency++; // ?
            }
            else break;
        }
        data[j + 1] = curElem;
    }
}

void TSortTable::MergeSort(PTTabRecord* data, int size)
{
    PTTabRecord* ppData = data;
    PTTabRecord* pBuf = new PTTabRecord[size];
    PTTabRecord* ppBuf = pBuf;
    MergeSorter(ppData, pBuf, size);
    if (ppData == ppBuf)
    {
        for (int i = 0; i < size; i++)
        {
            pBuf[i] = ppData[i];
        }
    }
    delete ppBuf;
}

void TSortTable::MergeSorter(PTTabRecord*& pData, PTTabRecord*& pBuf, int size)
{
    int n1 = (size + 1) >> 1;
    int n2 = size - n1;
    if (size > 2)
    {
        PTTabRecord* pd = pData + n1, *pb = pBuf + n1;
        MergeSorter(pData, pBuf, n1);
        MergeSorter(pd, pb, n2);
    }
    MergeData(pData, pBuf, n1, n2); // Слияние 2 отсортированных частей в одну
}

void TSortTable::MergeData(PTTabRecord*& pData, PTTabRecord*& pBuf, int n1, int n2)
{
    int ind = 0, ind1 = 0, ind2 = 0;
    PTTabRecord* pData1 = pData, * pData2 = pData + n1;
    while (ind1 < n1 && ind2 < n2)
    {
        if (pData1[ind1]->GetKey() < pData2[ind2]->GetKey())
        {
            pBuf[ind++] = pData1[ind1++];
        }
        else
        {
            pBuf[ind++] = pData[ind2++];
        }
    }

    // Что быстрее: 2 while-a или std::copy
    while (ind1 < n1)
    {
        pBuf[ind++] = pData1[ind1++];
    }
    while (ind2 < n2)
    {
        pBuf[ind++] = pData2[ind2++];
    }
    pData = pBuf;
    pBuf = pData1;
    Efficiency += n1 + n2;

}

void TSortTable::QuickSort(PTTabRecord* data, int size)
{
    int pivot, n1, n2;
    if (size < 2) return;
    QuickSplit(data, size, pivot);
    n1 = pivot + 1;
    n2 = size - n1;
    QuickSort(data, n1 - 1);
    QuickSort(data + n1, n2);
}

// проверить, как работает while первый- ДЗ
void TSortTable::QuickSplit(PTTabRecord* data, int size, int& pivot)
{
    PTTabRecord ppivot = data[0];
    PTTabRecord tmp = nullptr;
    int ind1 = 1, ind2 = size - 1;
    while (ind1 <= ind2)
    {
        while (ind1 < size && !(data[ind1]->GetKey() > ppivot->GetKey())) ind1++;
    
        while (data[ind2]->GetKey() > ppivot->GetKey())  ind2--;
      
        if (ind1 < ind2)
        {
            tmp = data[ind1];
            data[ind1] = data[ind2];
            data[ind2] = tmp;
        }
    }
    data[0] = data[ind2];
    data[ind2] = ppivot;
    pivot = ind2;
    Efficiency += size;
}

void TSortTable::BubbleSort(PTTabRecord* data, int size)
{
    Efficiency = DataCount;
    for (int step = 0; step < size; step++) {

        for (int i = 0; i < size - step - 1; i++) {

            if (data[i]->GetKey() > data[i + 1]->GetKey()) {

                PTTabRecord tmp = data[i];
                data[i] = data[i + 1];
                data[i + 1] = tmp;
                Efficiency++;
            }
        }
    }
}

void TSortTable::FreeChoice(PTTabRecord* data, int size) // selection sort
{
    Efficiency = DataCount;
    for (int step = 0; step < size - 1; step++) {
        int min_ind = step;
        for (int i = step + 1; i < size; i++) {

           
            if (data[i]->GetKey() < data[min_ind]->GetKey())
                min_ind = i;
        }

        PTTabRecord tmp = data[min_ind];
        data[min_ind] = data[step];
        data[step] = tmp;
        Efficiency++;
    }
}
