#pragma once

#include <iostream>
#include <fstream>
#include <string>


#include "TScanTable.h"
#include "Statistic.h"

class Parser
{
private:
	std::string _path;
	std::ifstream _fin;
	
public:
	Parser() :_path("ho.txt") // "War-N-Peace-Full.txt"
	{
		_fin.open(_path);
		if (!_fin.is_open())
		{
			throw "Cannot open the file.";
		}
	}

	~Parser() {
		_fin.close();
	}

	void TScanTableInsert(TScanTable& st) {
		std::string str;
		
		while (!_fin.eof())
		{
			str = "";
			_fin >> str;
			st.InsertRecord(str, new Statistic(this->WordAllTimes(str), this->WordInPart(str, 1), this->WordInPart(str, 2), this->WordInPart(str, 3), this->WordInPart(str, 4)));
		}
	}


	int WordAllTimes(const std::string toFind)  // Во всем произв.
	{
		std::string str;
		int count = 0;
		while (!_fin.eof())
		{	
			str = "";
			_fin >> str;
			if (str == toFind)
				count++;
		}
		return count;
	}

	int WordInPart(const std::string toFind, int part)
	{
		std::string str = "";
		part++;
		const std::string partName = "Том " + std::to_string(part);
		int count = 0;
			_fin >> str;
			if (str == toFind)
				count++;
			std::getline(_fin, str);
			if (str == partName)
				return count;
		}
		return count;
	}

	

	


};

