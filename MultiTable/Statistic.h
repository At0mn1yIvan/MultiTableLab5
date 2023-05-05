#pragma once

#include <vector>

#include "TDatValue.h"

class Statistic : public TDatValue
{
private:
	int _stats[5];
public:
	Statistic(int s1, int s2, int s3, int s4, int s5)
	{
		_stats[0] = s1;
		_stats[1] = s2;
		_stats[2] = s3;
		_stats[3] = s4;
		_stats[4] = s5;
	}

	Statistic(int* stats){
		for (int i = 0; i < 5; i++)
			_stats[i] = stats[i];
	}

	Statistic(std::vector<int> v) {
		for (int i = 0; i < 5; i++)
			_stats[i] = v[i];
	}

	void Print(std::ostream& os) override // const
	{
		std::string str;
		for (size_t i = 0; i < 5; i++)
			os << _stats[i] << '\t';

	}

	TDatValue* GetCopy() override {
		return new Statistic(_stats[0], _stats[1], _stats[2], _stats[3], _stats[4]);
	}

	friend class Parser;
	friend class ThParser;
};

