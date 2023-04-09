#include <iostream>
#include <Windows.h>


#include "TDatValue.h"
#include "TTabRecord.h"
#include "TArrayTable.h"
#include "TScanTable.h"
#include "TMarks.h"
#include "Parser.h"


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	TScanTable scan = TScanTable();

	Parser p;
	p.TScanTableInsert(scan);
	std::cout << scan;
	return 0;
}