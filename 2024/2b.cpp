#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

bool IsSafe(const std::vector<int>& Levels)
{
	int Trend = 0;
	int Prev = Levels[0];
	bool Damper = true;
	int Counter = 0;

	for(int i = 1; i < Levels.size(); i++)
	{
		if(Levels[i] > Prev)
		{
			Trend++;
		}
		else if(Levels[i] < Prev)
		{
			Trend--;
		}
		Prev = Levels[i];
		Counter++;
	}
	if(Counter - 2 > abs(Trend))
	{
		return false;
	}

	bool Increasing = Trend > 0;
	Prev = Levels[0];

	for(int i = 1; i < Levels.size(); i++)
	{
		const auto Abs = abs(Prev - Levels[i]);

		if (Abs < 1 || 3 < Abs || Increasing != (Levels[i] > Prev))
		{
			if(Damper)
			{
				Damper = false;
				continue;
			}
			else
			{
				return false;
			}
		}
		Prev = Levels[i];
	}
	return true;
}

int main()
{
	std::string Line;
	int Sum = 0;
	std::vector<std::vector<int>> Failed;

	while (std::getline(std::cin, Line) && !Line.empty())
	{
		std::stringstream SS(Line);
		std::vector<int> Level, ReverseLevel;
		int Num;

		while (SS >> Num)
		{
			Level.emplace_back(Num);
			ReverseLevel.emplace_back(Num);
		}
		std::reverse(ReverseLevel.begin(), ReverseLevel.end());

		if (IsSafe(Level) || IsSafe(ReverseLevel))
		{
			Sum++;
		}
		else
		{
			Failed.push_back(Level);
		}
	}

	std::cout << Sum;
}

