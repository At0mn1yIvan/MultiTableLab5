#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <mutex>
#include <vector>


#include "TScanTable.h"
#include "Statistic.h"

class Parser
{
private:
	std::string _path;
	std::ifstream _fin;
	//std::string _strFile;
	int _numOfWords; // число слов в файле
	TTable* _table;
	std::vector<std::pair<std::string, std::vector<int>>> _attrVector;

public:
	Parser(TTable* table) :_path("War-N-Peace-Full.txt"), _numOfWords(0), _table(table) // "War-N-Peace-Full.txt" _strFile(""),
	{
		//std::string str;
		_fin.open(_path);
		if (!_fin.is_open())
		{
			throw "Cannot open the file.";
		}
		/*while (!_fin.eof())
		{
			str = "";
			_fin >> str;
			_numOfWords++;
		}
		_fin.close();*/

	}


	// Геттеры
	//std::string GetStrFile() const { return _strFile; }
	int GetNumOfWords() const { return _numOfWords; }

	void FillTable() {
		std::ifstream fin;
		fin.open("Table.txt");
		while (!fin.eof()) {
			TKey key;
			fin >> key;
			if (key == "") break;
			size_t prop[5];
			for (int i = 0; i < 5; i++) {
				fin >> prop[i];
			}
			_table->InsertRecord(key, new Statistic(prop[0], prop[1], prop[2], prop[3], prop[4]));
		}
	}


	double FindAllWords()
	{
		std::ifstream fin;
		fin.open("Table.txt");
		std::vector<TKey> allWords;
		double allTime = 0;
		time_t start, end;
		while (!fin.eof()) {
			TKey key;
			fin >> key;
			if (key == "") break;
			size_t prop[5];
			for (int i = 0; i < 5; i++) {
				fin >> prop[i];
			}
			allWords.push_back(key);
		}
		for (auto word = allWords.begin(); word != allWords.end(); word++)
		{ 
			start = clock();
			_table->FindRecord(*word);
			end = clock();
			allTime += (double)(end - start) / CLOCKS_PER_SEC;
		}
		return allTime;
	}


	// Вариант 1
	void TableInsert()
	{
		std::string tmp = "";
		
		int partNum = 0;
		
		bool vectorIsNull = true;
		bool newInVect = true;
		//_fin.open(_path);
		//while (!_fin.eof()) 
		for (int i = 0; i < 10000; i++)
		{
			int a1 = 0;
			int a2 = 0;
			int a3 = 0;
			int a4 = 0;
			int a5 = 0;
			newInVect = true;
			tmp = "";
			_fin >> tmp;
			if (tmp == "") break;
					
			std::cout << ++_numOfWords << std::endl;


			if (!ClearWord(tmp)) continue;
				

			if (tmp == "Том")
				partNum++;

			if (_attrVector.size() == 0)
			{
				a1++;
				_attrVector.push_back(std::pair<std::string, std::vector<int>>(tmp, {a1,a2,a3,a4,a5}));
				vectorIsNull = false;
			}
			else
			{
				for (int i = 0; i < _attrVector.size(); i++)
				{
					if (tmp == _attrVector[i].first)
					{
						newInVect = false;
						_attrVector[i].second[0]++;
						switch (partNum)
						{
						case 1: _attrVector[i].second[1]++; break;
						case 2: _attrVector[i].second[2]++; break;
						case 3: _attrVector[i].second[3]++; break;
						case 4: _attrVector[i].second[4]++; break;
						default: break;
						}
						break;
					}
				}
				if (newInVect)
				{
					a1++;
					switch (partNum)
					{
					case 1: a2++; break;
					case 2: a3++; break;
					case 3: a4++; break;
					case 4: a5++; break;
					default: break;
					}
					_attrVector.push_back(std::pair<std::string, std::vector<int>>(tmp, { a1,a2,a3,a4,a5 }));
				}
			}
		}
		_fin.close();
		for (int i = 0; i < _attrVector.size(); i++)
		{
			_table->InsertRecord(_attrVector[i].first, new Statistic(_attrVector[i].second));
		}
	}


	int ClearWord(std::string& word)
	{
		bool flag1;
		bool flag2;
		std::vector<char> symb = { '!', '"', '`', '(', ')', ',', '.', '-', '/', ':', ';', '<', '>', '?', '=', '_', '[', ']', '{', '}', '*', '\''};
		
		if (word.size() == 1)
			return 1;


		while (!((57 >= word[0] && word[0] >= 48) || (90 >= word[0] && word[0] >= 65) || (122 >= word[0] && word[0] >= 97) || ( 0 > word[0])) || !((57 >= word[word.size() - 1] && word[word.size() - 1] >= 48) || (90 >= word[word.size() - 1] && word[word.size() - 1] >= 65) || (122 >= word[word.size() - 1] && word[word.size() - 1] >= 97) || ( 0 > word[word.size() - 1])))
		{
			flag1 = false;
			flag2 = false;
			for (int i = 0; i < symb.size(); i++)
			{
				if (!flag1)
					if (word[0] == symb[i])
					{
						if (word.size() == 1)
							return 0;
						word.replace(0, 1, "");
						flag1 = true;
					}
				if (!flag2)
					if (word[word.size() - 1] == symb[i])
					{
						if (word.size() == 1)
							return 0;
						word.replace(word.size() - 1, 1, "");
						flag2 = true;
					}
				if (flag1 && flag2)
					break;
			}
		}
		return 1;


	}

};

