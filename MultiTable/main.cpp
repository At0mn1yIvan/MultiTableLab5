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
	

	// Просматриваемые таблицы

	//TScanTable st = TScanTable(70000);
	//Parser p(&st);

	//std::cout << "Вставка значений в таблицу:" << std::endl;
	//time(&start);
	//p.TableInsert();
	//time(&end);
	//
	//double seconds = difftime(end, start);
	//std::cout << st;
	//std::cout << "Время парсинга: " << seconds << " секунд" << std::endl;
	//std::cout << "Размер: " << st.GetDataCount() << std::endl;
	//while(1)
	//{
	//	std::string str;
	//	std::cout << "Выберите слово для поиска: ";
	//	std::cin >> str;
	//	if (st.FindRecord(str) != nullptr)
	//	{
	//		std::cout << "Эффективность: " << st.GetEfficiency() << " Атрибуты: " << *st.FindRecord(str) << std::endl;
	//		std::cout << "Хотите удалить слово?: ";
	//		std::string ans;
	//		std::cin >> ans;
	//		if (ans == "y")
	//			st.DeleteRecord(str);
	//		else
	//			continue;
	//	}
	//	else
	//	{
	//		std::cout << "Эффективность: " << st.GetEfficiency() << std::endl;
	//		std::cout << "Нет такого слова." << std::endl;
	//	}
	//}


	
	//Сортируемые таблицы
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
	
	std::cout << "Вставка значений в таблицу:" << std::endl;
	start = clock();
	p.TableInsert();
	//p.FillTable();
	end = clock();
	double seconds = (double)(end - start) / CLOCKS_PER_SEC;
	//std::cout << st;
	std::cout << "Время парсинга: " << seconds << " секунд" << std::endl;
	std::cout << "Размер: " << st.GetDataCount() << std::endl;

	auto func = [&]() {
		clock_t start1 = clock();
		insertSortTable = st;
		clock_t end1 = clock();
		std::cout << "Сортировка вставками: " << (double)(end1 - start1) / CLOCKS_PER_SEC << " секунд;" << "\tЭффективность: " << insertSortTable.GetEfficiency() << std::endl;
	};
	std::thread th(func);
	//std::cout << "Сортировка вставками: " << AnySort(insertSortTable, st) << " секунд;" << "\tЭффективность: " << insertSortTable.GetEfficiency() << std::endl;

	std::cout << "Сортировка пузырьком: " << AnySort(bubbleSortTable, st) << " секунд;" << "\tЭффективность: " << bubbleSortTable.GetEfficiency() << std::endl;
	std::cout << "Сортировка слиянием: " << AnySort(mergeSortTable, st) << " секунд;" << "\tЭффективность: " << mergeSortTable.GetEfficiency() << std::endl;
	std::cout << "Быстрая сортировка: " << AnySort(quickSortTable, st) << " секунд;" << "\tЭффективность: " << quickSortTable.GetEfficiency() << std::endl;
	std::cout << "Сортировка выбором: " << AnySort(freeSortTable, st) << " секунд;" << "\tЭффективность: " << freeSortTable.GetEfficiency() << std::endl;
	th.join();

	while(1)
	{
		std::string str;
		std::cout << "Выберите слово для поиска: ";
		std::cin >> str;
		if (quickSortTable.FindRecord(str) != nullptr)
		{
			std::cout << "Эффективность: " << quickSortTable.GetEfficiency() << "\nАтрибуты: " << *quickSortTable.FindRecord(str) << std::endl;
			std::cout << "Хотите удалить слово?: ";
			std::string ans;
			std::cin >> ans;
			if (ans == "y")
				quickSortTable.DeleteRecord(str);
			else
				continue;
		}
		else
		{
			std::cout << "Эффективность: " << quickSortTable.GetEfficiency() << std::endl;
			std::cout << "Нет такого слова." << std::endl;
		}
	}

	return 0;
}