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
	//std::cout << "Вставка значений в таблицу:" << std::endl;
	//start = clock();
	//p.TableInsert();
	////p.FillTable();
	//end = clock();
	//double seconds = (double)(end - start) / CLOCKS_PER_SEC;
	////std::cout << st;
	//std::cout << "Время парсинга: " << seconds << " секунд" << std::endl;
	//std::cout << "Размер: " << st.GetDataCount() << std::endl;

	//auto func = [&]() {
	//	clock_t start1 = clock();
	//	insertSortTable = st;
	//	clock_t end1 = clock();
	//	std::cout << "Сортировка вставками: " << (double)(end1 - start1) / CLOCKS_PER_SEC << " секунд;" << "\tЭффективность: " << insertSortTable.GetEfficiency() << std::endl;
	//};
	//std::thread th(func);
	////std::cout << "Сортировка вставками: " << AnySort(insertSortTable, st) << " секунд;" << "\tЭффективность: " << insertSortTable.GetEfficiency() << std::endl;

	//std::cout << "Сортировка пузырьком: " << AnySort(bubbleSortTable, st) << " секунд;" << "\tЭффективность: " << bubbleSortTable.GetEfficiency() << std::endl;
	//std::cout << "Сортировка слиянием: " << AnySort(mergeSortTable, st) << " секунд;" << "\tЭффективность: " << mergeSortTable.GetEfficiency() << std::endl;
	//std::cout << "Быстрая сортировка: " << AnySort(quickSortTable, st) << " секунд;" << "\tЭффективность: " << quickSortTable.GetEfficiency() << std::endl;
	//std::cout << "Сортировка выбором: " << AnySort(freeSortTable, st) << " секунд;" << "\tЭффективность: " << freeSortTable.GetEfficiency() << std::endl;
	//th.join();

	//while(1)
	//{
	//	std::string str;
	//	std::cout << "Выберите слово для поиска: ";
	//	std::cin >> str;
	//	if (quickSortTable.FindRecord(str) != nullptr)
	//	{
	//		std::cout << "Эффективность: " << quickSortTable.GetEfficiency() << "\nАтрибуты: " << *quickSortTable.FindRecord(str) << std::endl;
	//		std::cout << "Хотите удалить слово?: ";
	//		std::string ans;
	//		std::cin >> ans;
	//		if (ans == "y")
	//			quickSortTable.DeleteRecord(str);
	//		else
	//			continue;
	//	}
	//	else
	//	{
	//		std::cout << "Эффективность: " << quickSortTable.GetEfficiency() << std::endl;
	//		std::cout << "Нет такого слова." << std::endl;
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
	//std::cout << "Время парсинга сортируемых таблиц: " << seconds1 << " секунд" << std::endl;
	//std::cout << "Время парсинга хэш-таблиц c методом цепочек: " << seconds2 << " секунд" << std::endl;
	//std::cout << "Время парсинга хэш-таблиц: " << seconds3 << " секунд" << std::endl;
	//std::string str;
	//while(1)
	//{
	//	std::cout << "Выберите слово для поиска: ";
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
	//		std::cout << "Эффективность поиска в сортируемых таблицах: " << SortTable.GetEfficiency() << " время: " << seconds4 << "\nАтрибуты: " << *fStr1 << std::endl;
	//		std::cout << "Эффективность поиска в хэш-таблицах c методом цепочек: " << tlh.GetEfficiency() << " время: " << seconds5 << "\nАтрибуты: " << *fStr2 << std::endl;
	//		std::cout << "Эффективность поиска в хэш-таблицах: " << tah.GetEfficiency() << " время: " << seconds6 << "\nАтрибуты: " << *fStr3 << std::endl;
	//	}
	//	else
	//	{
	//		std::cout << "Эффективность: " << SortTable.GetEfficiency() << std::endl;
	//		std::cout << "Нет такого слова." << std::endl;
	//	}
	//}
	

	// для хэш-функций 
	//TSortTable SortTable = TSortTable(70000); 1.029 сек.
	TListHashTable tlh = TListHashTable(70000);
	TArrayHashTable tah = TArrayHashTable(70000);
	//Parser p1(&SortTable);
	Parser p2(&tlh);
	Parser p3(&tah);
	//p1.FillTable();
	p2.FillTable();
	p3.FillTable();
	/*std::string str = "Прокрастинация";
	int cu = 0;
	for (int i = 0; i < str.size(); i++)
		cu += (int)str[i];*/
	//std::cout << (cu / -100 > 0 ? cu % 100 - 10 : cu + 10);
	//std::cout << "SortTable time to find every word: " << p1.FindAllWords() << " seconds" << std::endl;
	std::cout << "List Hash table time to find every word: " << p2.FindAllWords() << " seconds" << std::endl;
	std::cout << "Array Hash table time to find every word: " << p3.FindAllWords() << " seconds" << std::endl;
	return 0;
}