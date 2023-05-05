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


	
	std::cout << "Вставка значений в таблицу:" << std::endl;
	time(&start);
	p.TableInsert();
	time(&end);
	
	double seconds = difftime(end, start);
	std::cout << st;
	std::cout << "Время парсинга: " << seconds << " секунд" << std::endl;
	std::cout << "Размер: " << st.GetDataCount() << std::endl;
	while(1)
	{
		std::string str;
		std::cout << "Выберите слово для поиска: ";
		std::cin >> str;
		if (st.FindRecord(str) != nullptr)
		{
			std::cout << "Эффективность: " << st.GetEfficiency() << " Атрибуты: " << *st.FindRecord(str) << std::endl;
			std::cout << "Хотите удалить слово?: ";
			std::string ans;
			std::cin >> ans;
			if (ans == "y")
				st.DeleteRecord(str);
			else
				continue;
		}
		else
		{
			std::cout << "Эффективность: " << st.GetEfficiency() << std::endl;
			std::cout << "Нет такого слова." << std::endl;
		}

		

	}


	/*std::string a = "Ред.";
	p.ClearWord(a);
	std::cout << a;*/
	
	return 0;
}