#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>

int main()
{
	std::string Line;
	int Sum = 0;
	while (std::getline(std::cin, Line) && !Line.empty())
	{
		std::stringstream SS(Line);
		int Num, Prev;

		SS >> Prev;
		SS >> Num;

		bool Flag = true;
		bool Trend = Num > Prev;
		do
		{
			bool Increasing = Num > Prev;

			uint32_t Ab = abs(Num - Prev);
			if(Ab < 1 || Ab > 3 || Trend != Increasing)
			{
				Flag = false;
				break;
			}

			Prev = Num;
		} while (SS >> Num);

		if (Flag == true)
		{
			Sum++;
		}
	}
	std::cout << Sum;
}

