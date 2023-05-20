#include <iostream>
#include <Windows.h>
#include <thread>
#include <mutex>
#include <vector>
#include <ctime>

#include "TDatValue.h"
#include "TTabRecord.h"
#include "TArrayTable.h"
#include "TScanTable.h"
#include "TSortTable.h"
#include "Parser.h"


double AnySort(TSortTable& sortT, TScanTable& scanT)
{
	clock_t start1 = clock();
	sortT = scanT;
	clock_t end1 = clock();
	return (double)(end1 - start1) / CLOCKS_PER_SEC;
}


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	clock_t start, end;
	

	// ��������������� �������

	//TScanTable st = TScanTable(70000);
	//Parser p(&st);

	//std::cout << "������� �������� � �������:" << std::endl;
	//time(&start);
	//p.TableInsert();
	//time(&end);
	//
	//double seconds = difftime(end, start);
	//std::cout << st;
	//std::cout << "����� ��������: " << seconds << " ������" << std::endl;
	//std::cout << "������: " << st.GetDataCount() << std::endl;
	//while(1)
	//{
	//	std::string str;
	//	std::cout << "�������� ����� ��� ������: ";
	//	std::cin >> str;
	//	if (st.FindRecord(str) != nullptr)
	//	{
	//		std::cout << "�������������: " << st.GetEfficiency() << " ��������: " << *st.FindRecord(str) << std::endl;
	//		std::cout << "������ ������� �����?: ";
	//		std::string ans;
	//		std::cin >> ans;
	//		if (ans == "y")
	//			st.DeleteRecord(str);
	//		else
	//			continue;
	//	}
	//	else
	//	{
	//		std::cout << "�������������: " << st.GetEfficiency() << std::endl;
	//		std::cout << "��� ������ �����." << std::endl;
	//	}
	//}


	
	//����������� �������
	TSortTable bubbleSortTable = TSortTable(70000);
	bubbleSortTable.SetSortMethod(SortMeth::BUBBLESORT);
	TSortTable quickSortTable = TSortTable(70000);
	quickSortTable.SetSortMethod(SortMeth::QUICKSORT);
	TSortTable mergeSortTable = TSortTable(70000);
	mergeSortTable.SetSortMethod(SortMeth::MERGESORT);
	TSortTable insertSortTable = TSortTable(70000);
	insertSortTable.SetSortMethod(SortMeth::INSERTSORT);
	TSortTable freeSortTable = TSortTable(70000);
	freeSortTable.SetSortMethod(SortMeth::FREECHOICE);

	TScanTable st = TScanTable(70000);
	Parser p(&st);
	
	std::cout << "������� �������� � �������:" << std::endl;
	start = clock();
	p.TableInsert();
	//p.FillTable();
	end = clock();
	double seconds = (double)(end - start) / CLOCKS_PER_SEC;
	//std::cout << st;
	std::cout << "����� ��������: " << seconds << " ������" << std::endl;
	std::cout << "������: " << st.GetDataCount() << std::endl;

	auto func = [&]() {
		clock_t start1 = clock();
		insertSortTable = st;
		clock_t end1 = clock();
		std::cout << "���������� ���������: " << (double)(end1 - start1) / CLOCKS_PER_SEC << " ������;" << "\t�������������: " << insertSortTable.GetEfficiency() << std::endl;
	};
	std::thread th(func);
	//std::cout << "���������� ���������: " << AnySort(insertSortTable, st) << " ������;" << "\t�������������: " << insertSortTable.GetEfficiency() << std::endl;

	std::cout << "���������� ���������: " << AnySort(bubbleSortTable, st) << " ������;" << "\t�������������: " << bubbleSortTable.GetEfficiency() << std::endl;
	std::cout << "���������� ��������: " << AnySort(mergeSortTable, st) << " ������;" << "\t�������������: " << mergeSortTable.GetEfficiency() << std::endl;
	std::cout << "������� ����������: " << AnySort(quickSortTable, st) << " ������;" << "\t�������������: " << quickSortTable.GetEfficiency() << std::endl;
	std::cout << "���������� �������: " << AnySort(freeSortTable, st) << " ������;" << "\t�������������: " << freeSortTable.GetEfficiency() << std::endl;
	th.join();

	while(1)
	{
		std::string str;
		std::cout << "�������� ����� ��� ������: ";
		std::cin >> str;
		if (quickSortTable.FindRecord(str) != nullptr)
		{
			std::cout << "�������������: " << quickSortTable.GetEfficiency() << "\n��������: " << *quickSortTable.FindRecord(str) << std::endl;
			std::cout << "������ ������� �����?: ";
			std::string ans;
			std::cin >> ans;
			if (ans == "y")
				quickSortTable.DeleteRecord(str);
			else
				continue;
		}
		else
		{
			std::cout << "�������������: " << quickSortTable.GetEfficiency() << std::endl;
			std::cout << "��� ������ �����." << std::endl;
		}
	}

	return 0;
}