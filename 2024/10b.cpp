#include <iostream>
#include <string>
#include <vector>

std::vector<std::vector<int>> Grid;

int TrailScore(int X, int Y, int StartingVal)
{
	if(X < 0 || Y < 0 || Y >= Grid.size() || X >= Grid[Y].size())
	{
		return 0;
	}
	if (Grid[Y][X] - StartingVal != 1)
	{
		return 0;
	}
	if (Grid[Y][X] == 9)
	{
		return 1;
	}
	auto Left = TrailScore(X - 1, Y, StartingVal + 1);
	auto Right = TrailScore(X + 1, Y, StartingVal + 1);
	auto Up = TrailScore(X, Y - 1, StartingVal + 1);
	auto Down = TrailScore(X, Y + 1, StartingVal + 1);
	return Left + Right + Up + Down;
}

int main()
{
	std::string Line;
	long long Sum = 0;

	while(std::getline(std::cin, Line) && !Line.empty())
	{
		auto& Y = Grid.emplace_back();
		for(const auto& C : Line)
		{
			Y.emplace_back(C - '0');
		}
	}

	for(int i = 0; i < Grid.size(); i++)
	{
		for(int j = 0; j < Grid[i].size(); j++)
		{
			if(Grid[i][j] == 0)
			{
				Sum += TrailScore(j, i, -1);
			}

		}
	}

	std::cout << Sum;
}