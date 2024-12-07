#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <regex>
#include <string_view>

int main()
{
	std::string Line;
	std::regex Parser(R"(mul\((\d{1,3}),(\d{1,3}\)))");
	std::sregex_iterator End;

	long long Sum = 0;

	while (std::getline(std::cin, Line) && !Line.empty())
	{
		std::sregex_iterator Match(Line.begin(), Line.end(), Parser);

		for (auto It = Match; It != End; It++)
		{
			Sum += std::stoi(It->str(1)) * std::stoi(It->str(2));
		}
	}

	std::cout << Sum;

}

