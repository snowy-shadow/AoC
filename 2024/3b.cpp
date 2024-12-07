#include <iostream>
#include <string>
#include <regex>

int main()
{
	std::string Line;
	std::regex Parser(R"((mul\((\d{1,3}),(\d{1,3})\)|(do\(\)|don't\(\))))");
	std::sregex_iterator End;

	bool Mul = true;
	long long Sum = 0;

	while (std::getline(std::cin, Line) && !Line.empty())
	{
		std::sregex_iterator Match(Line.begin(), Line.end(), Parser);

		for (auto It = Match; It != End; It++)
		{
			auto a = It->str(1);
			if (It->str(1) == "do()")
			{
				Mul = true;
				continue;
			}
			else if (It->str(1) == "don't()")
			{
				Mul = false;
				continue;
			}
			if(Mul)
			{
				auto b = It->str(2);
				auto c = It->str(3);
				Sum += std::stoi(It->str(2)) * std::stoi(It->str(3));
			}

		}
	}

	std::cout << Sum;

}