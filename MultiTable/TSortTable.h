#pragma once

#include "TScanTable.h"

enum class SortMeth
{
	BUBBLESORT,
	QUICKSORT,
	MERGESORT,
	INSERTSORT,
	FREECHOICE // Наш выбор

};

class TSortTable : public TScanTable
{
protected:
	SortMeth _sortMethod;
	void SortData();
	void InsertSort(PTTabRecord* data, int size);
	void MergeSort(PTTabRecord* data, int size);
	void MergeSorter(PTTabRecord *&pData, PTTabRecord *&pBuf, int size); // Нужны для сортировки слиянием
	void MergeData(PTTabRecord*& pData, PTTabRecord*& pBuf, int n1, int n2);
	void QuickSort(PTTabRecord* data, int size);
	void QuickSplit(PTTabRecord* data, int size, int &pivot); //pivot - опорный элемент
	void BubbleSort(PTTabRecord* data, int size);
	void FreeChoice(PTTabRecord* data, int size); // Сортировка на выбор
public:
	TSortTable(int size = 50) : TScanTable(size) {}
	TSortTable(const TScanTable& st)
	{
		*this = st;
	}

	TSortTable& operator=(const TScanTable& st);

	virtual PTDatValue FindRecord(TKey key) override; 
	virtual bool InsertRecord(TKey key, PTDatValue) override;
	virtual void DeleteRecord(TKey key) override;

	SortMeth GetSortMethod()
	{
		return _sortMethod;
	}

	void SetSortMethod(SortMeth sm)
	{	
		_sortMethod = sm;
	}
};

