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


	
	std::cout << "������� �������� � �������:" << std::endl;
	time(&start);
	p.TableInsert();
	time(&end);
	
	double seconds = difftime(end, start);
	std::cout << st;
	std::cout << "����� ��������: " << seconds << " ������" << std::endl;
	std::cout << "������: " << st.GetDataCount() << std::endl;
	while(1)
	{
		std::string str;
		std::cout << "�������� ����� ��� ������: ";
		std::cin >> str;
		if (st.FindRecord(str) != nullptr)
		{
			std::cout << "�������������: " << st.GetEfficiency() << " ��������: " << *st.FindRecord(str) << std::endl;
			std::cout << "������ ������� �����?: ";
			std::string ans;
			std::cin >> ans;
			if (ans == "y")
				st.DeleteRecord(str);
			else
				continue;
		}
		else
		{
			std::cout << "�������������: " << st.GetEfficiency() << std::endl;
			std::cout << "��� ������ �����." << std::endl;
		}

		

	}


	/*std::string a = "���.";
	p.ClearWord(a);
	std::cout << a;*/
	
	return 0;
}