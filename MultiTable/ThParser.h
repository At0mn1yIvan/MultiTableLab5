#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <mutex>
#include <vector>

#include "TScanTable.h"
#include "Statistic.h"


#define MAX_THREADS 200


class ThParser
{
private:
	std::string _path; // путь файла 
	std::ifstream _fin; // путь чтения из файла
	std::string _strFile; // строка, содержащая весь файл
	std::mutex _mtxBuf; // мьютекс для блокировки потоков при доступе к общему ресурсу для внесений изменений в этот ресурс
	std::mutex _mtxTable;
	int _numOfWords; // число слов в файле
	std::vector<std::thread> _threads1; // Буфер потоков 
	std::vector<std::thread> _threads2; // Буфер потоков 
	std::vector<std::string> _wordsVector1; // Буфер слов для многопоточности для внесения в таблицу
	std::vector<std::string> _wordsVector2; // Вектор слов для многопоточности при нахождении атрибутов слова
	std::vector<std::pair<std::string, int*>> _attrVector; // Вектор для указателей на массивы атрибутов слов
	TTable* _table;

public:
	ThParser(TTable* table) :_path("War-N-Peace-Full.txt"), _strFile(""), _numOfWords(0), _table(table) // "War-N-Peace-Full.txt"
	{
		int count = 0;
		_fin.open(_path);
		if (!_fin.is_open())
		{
			throw "Cannot open the file.";
		}
		std::string str;
		while (!_fin.eof())
		{
			str = "";
			_fin >> str;
			count++;
			if (count <= MAX_THREADS * 2) {
				_wordsVector1.push_back(str);
				_wordsVector2.push_back(str);
			}
			_strFile += str + " ";
		}
		_fin.close();
	}

	// Геттеры
	std::string GetStrFile() const { return _strFile; }
	int GetNumOfWords() const { return _numOfWords; }

	// Потоки

	void Parse()
	{
		std::string str;
		_fin.open(_path);
		if (!_fin.is_open())
			std::cout << "Cannot open the file.";
		else
		{
			/*for (int i = 0; i < MAX_THREADS * 2; i++)
			{
				_fin >> str;
				_wordsVector.push_back(str);
			}*/

			for (int i = 0; i < MAX_THREADS; i++) {
				_threads1.push_back(std::thread([&]() {this->InsertToTable(); }));
				_threads2.push_back(std::thread([&]() {this->WordAttributes(); }));
			}

			while (!_fin.eof())
			{
				if (_wordsVector1.size() < MAX_THREADS * 2 && _wordsVector2.size() < MAX_THREADS * 2)
				{
					str = "";
					_mtxBuf.lock();
					_fin >> str;
					_wordsVector1.push_back(str);
					_wordsVector2.push_back(str);
					_mtxBuf.unlock();
				}
			}
			
			for (int i = 0; i < MAX_THREADS; i++) {
				_threads1[i].join();
				_threads2[i].join();
			}
		
		}
		_fin.close();
	}

	void WordAttributes()
	{
		std::string toFind, str;
		int partCounter;
		while (true)
		{
			int stats[5] = {0};
			partCounter = 0;
			_mtxBuf.lock();
			if (_wordsVector2.empty())
			{
				_mtxBuf.unlock();
				return;
			}

			toFind = _wordsVector2.back();
			_wordsVector2.pop_back();
			_mtxBuf.unlock();


			for (int i = 0; i < _strFile.size(); i++)
			{
				str = "";
				while (_strFile[i] != ' ')
				{
					str += _strFile[i];
					i++;
				}

				if (str == "Том")
				{
					partCounter++;
				}

				if (toFind == str)
				{
					stats[0]++;
					switch (partCounter)
					{
					case 1: stats[1]++; break;
					case 2: stats[2]++; break;
					case 3: stats[3]++; break;
					case 4: stats[4]++; break;
					default: break;
					}
				}
			}
			_mtxBuf.lock();
			_attrVector.push_back(std::pair<std::string, int*>(toFind, stats));
			_mtxBuf.unlock();
		}
	}

	void InsertToTable()
	{
		std::string toFind, str;
		int partCounter;

		while (true)
		{	
			int stats[5] = { 0 };
			partCounter = 0;

			_mtxBuf.lock(); // ?
			if (_wordsVector1.empty()) {
				_mtxBuf.unlock();
				return;
			}

			if (_table->GetRetCode() == TAB_FULL)
			{
				_mtxBuf.unlock();
				return;
			}

			toFind = _wordsVector1.back();
			_wordsVector1.pop_back();
			for (int i = 0; i < _attrVector.size(); i++)
			{
				if (toFind == _attrVector[i].first) {
					std::copy_n(_attrVector[i].second, 5, stats);
					std::erase(_attrVector, _attrVector[i]);
					break;
				}
					
			}
			_mtxBuf.unlock();


			if (_table->FindRecord(toFind) == nullptr) {
				_mtxTable.lock();
				_table->InsertRecord(toFind, new Statistic(stats));
				_mtxTable.unlock();
			}
			// Вывод числа обработанных слов ;
			_mtxBuf.lock();
			std::cout << ++_numOfWords << std::endl;
			_mtxBuf.unlock();
		}
	}

};

