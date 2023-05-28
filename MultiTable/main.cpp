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
#include "TListHashTable.h"
#include "TArrayHashTable.h"
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
	//TSortTable bubbleSortTable = TSortTable(70000);
	//bubbleSortTable.SetSortMethod(SortMeth::BUBBLESORT);
	//TSortTable quickSortTable = TSortTable(70000);
	//quickSortTable.SetSortMethod(SortMeth::QUICKSORT);
	//TSortTable mergeSortTable = TSortTable(70000);
	//mergeSortTable.SetSortMethod(SortMeth::MERGESORT);
	//TSortTable insertSortTable = TSortTable(70000);
	//insertSortTable.SetSortMethod(SortMeth::INSERTSORT);
	//TSortTable freeSortTable = TSortTable(70000);
	//freeSortTable.SetSortMethod(SortMeth::FREECHOICE);

	//TScanTable st = TScanTable(70000);
	//Parser p(&st);
	//
	//std::cout << "������� �������� � �������:" << std::endl;
	//start = clock();
	//p.TableInsert();
	////p.FillTable();
	//end = clock();
	//double seconds = (double)(end - start) / CLOCKS_PER_SEC;
	////std::cout << st;
	//std::cout << "����� ��������: " << seconds << " ������" << std::endl;
	//std::cout << "������: " << st.GetDataCount() << std::endl;

	//auto func = [&]() {
	//	clock_t start1 = clock();
	//	insertSortTable = st;
	//	clock_t end1 = clock();
	//	std::cout << "���������� ���������: " << (double)(end1 - start1) / CLOCKS_PER_SEC << " ������;" << "\t�������������: " << insertSortTable.GetEfficiency() << std::endl;
	//};
	//std::thread th(func);
	////std::cout << "���������� ���������: " << AnySort(insertSortTable, st) << " ������;" << "\t�������������: " << insertSortTable.GetEfficiency() << std::endl;

	//std::cout << "���������� ���������: " << AnySort(bubbleSortTable, st) << " ������;" << "\t�������������: " << bubbleSortTable.GetEfficiency() << std::endl;
	//std::cout << "���������� ��������: " << AnySort(mergeSortTable, st) << " ������;" << "\t�������������: " << mergeSortTable.GetEfficiency() << std::endl;
	//std::cout << "������� ����������: " << AnySort(quickSortTable, st) << " ������;" << "\t�������������: " << quickSortTable.GetEfficiency() << std::endl;
	//std::cout << "���������� �������: " << AnySort(freeSortTable, st) << " ������;" << "\t�������������: " << freeSortTable.GetEfficiency() << std::endl;
	//th.join();

	//while(1)
	//{
	//	std::string str;
	//	std::cout << "�������� ����� ��� ������: ";
	//	std::cin >> str;
	//	if (quickSortTable.FindRecord(str) != nullptr)
	//	{
	//		std::cout << "�������������: " << quickSortTable.GetEfficiency() << "\n��������: " << *quickSortTable.FindRecord(str) << std::endl;
	//		std::cout << "������ ������� �����?: ";
	//		std::string ans;
	//		std::cin >> ans;
	//		if (ans == "y")
	//			quickSortTable.DeleteRecord(str);
	//		else
	//			continue;
	//	}
	//	else
	//	{
	//		std::cout << "�������������: " << quickSortTable.GetEfficiency() << std::endl;
	//		std::cout << "��� ������ �����." << std::endl;
	//	}
	//}

	//TSortTable SortTable = TSortTable(70000);
	//TListHashTable tlh = TListHashTable(70000);
	//TArrayHashTable tah = TArrayHashTable(70000);
	//Parser p1(&SortTable);
	//Parser p2(&tlh);
	//Parser p3(&tah);
	//start = clock();
	//p1.FillTable();
	////p1.TableInsert();
	//end = clock();
	//double seconds1 = (double)(end - start) / CLOCKS_PER_SEC;
	//start = clock();
	//p2.FillTable();
	////p2.TableInsert();
	//end = clock();
	//double seconds2 = (double)(end - start) / CLOCKS_PER_SEC;
	//start = clock();
	//p3.FillTable();
	////p3.TableInsert();
	//end = clock();
	//double seconds3 = (double)(end - start) / CLOCKS_PER_SEC;
	//std::cout << "����� �������� ����������� ������: " << seconds1 << " ������" << std::endl;
	//std::cout << "����� �������� ���-������ c ������� �������: " << seconds2 << " ������" << std::endl;
	//std::cout << "����� �������� ���-������: " << seconds3 << " ������" << std::endl;
	//std::string str;
	//while(1)
	//{
	//	std::cout << "�������� ����� ��� ������: ";
	//	std::cin >> str;
	//	start = clock();
	//	PTDatValue fStr1 = SortTable.FindRecord(str);
	//	end = clock();
	//	double seconds4 = (double)(end - start) / CLOCKS_PER_SEC;
	//	start = clock();
	//	PTDatValue fStr2 = SortTable.FindRecord(str);
	//	end = clock();
	//	double seconds5 = (double)(end - start) / CLOCKS_PER_SEC;
	//	start = clock();
	//	PTDatValue fStr3 = SortTable.FindRecord(str);
	//	end = clock();
	//	double seconds6 = (double)(end - start) / CLOCKS_PER_SEC;
	//	if (fStr1 != nullptr)
	//	{
	//		std::cout << "������������� ������ � ����������� ��������: " << SortTable.GetEfficiency() << " �����: " << seconds4 << "\n��������: " << *fStr1 << std::endl;
	//		std::cout << "������������� ������ � ���-�������� c ������� �������: " << tlh.GetEfficiency() << " �����: " << seconds5 << "\n��������: " << *fStr2 << std::endl;
	//		std::cout << "������������� ������ � ���-��������: " << tah.GetEfficiency() << " �����: " << seconds6 << "\n��������: " << *fStr3 << std::endl;
	//	}
	//	else
	//	{
	//		std::cout << "�������������: " << SortTable.GetEfficiency() << std::endl;
	//		std::cout << "��� ������ �����." << std::endl;
	//	}
	//}
	

	// ��� ���-������� 
	//TSortTable SortTable = TSortTable(70000); 1.029 ���.
	TListHashTable tlh = TListHashTable(70000);
	TArrayHashTable tah = TArrayHashTable(70000);
	//Parser p1(&SortTable);
	Parser p2(&tlh);
	Parser p3(&tah);
	//p1.FillTable();
	p2.FillTable();
	p3.FillTable();
	/*std::string str = "��������������";
	int cu = 0;
	for (int i = 0; i < str.size(); i++)
		cu += (int)str[i];*/
	//std::cout << (cu / -100 > 0 ? cu % 100 - 10 : cu + 10);
	//std::cout << "SortTable time to find every word: " << p1.FindAllWords() << " seconds" << std::endl;
	std::cout << "List Hash table time to find every word: " << p2.FindAllWords() << " seconds" << std::endl;
	std::cout << "Array Hash table time to find every word: " << p3.FindAllWords() << " seconds" << std::endl;
	return 0;
}