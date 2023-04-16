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
#include "Parser.h"
#include "ThParser.h"


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	time_t start, end;
	
	TScanTable st = TScanTable(480000);
	Parser p(&st);


	
	
	time(&start);
	p.TableInsert();
	time(&end);
	
	double seconds = difftime(end, start);
	std::cout << "Время парсинга: " << seconds << " секунд" << std::endl;
	std::cout << st;

	/*std::string a = "Ред.";
	p.ClearWord(a);
	std::cout << a;*/
	
	return 0;
}