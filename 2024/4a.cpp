#include <iostream>
#include <string>
#include <regex>
#include <string_view>

std::vector<std::string> Grid;

unsigned int XMAS(int x, int y)
{
	constexpr std::string Match = "XMAS";
	int Dir[]{1, 1, 1, 1, 1, 1, 1, 1};

	for(int i = 1; i < Match.size(); i++)
	{
		// Forward
		if(Dir[0] == 1 && (x + i >= Grid[y].size() || Grid[y][x + i] != Match[i]))
		{
			Dir[0] = 0;
		}
		// Back
		if(Dir[1] == 1 && (x - i < 0 || Grid[y][x - i] != Match[i]))
		{
			Dir[1] = 0;
		}
		// Down
		if(Dir[2] == 1 && (y + i >= Grid.size() || Grid[y + i][x] != Match[i]))
		{
			Dir[2] = 0;
		}
		// Up
		if(Dir[3] == 1 && (y - 1 < 0 || Grid[y - i][x] != Match[i]))
		{
			Dir[3] = 0;
		}
		// RightUp
		if(Dir[4] == 1 && (y - i < 0 || x + i >= Grid[y - i].size() || Grid[y - i][x + i] != Match[i]))
		{
			Dir[4] = 0;
		}
		// LeftUp
		if(Dir[5] == 1 && (y - i < 0 || x - i < 0 || Grid[y - i][x - i] != Match[i]))
		{
			Dir[5] = 0;
		}
		// LeftDown
		if(Dir[6] == 1 && (y + i >= Grid.size() || x - i < 0 || Grid[y + i][x - i] != Match[i]))
		{
			Dir[6] = 0;
		}
		// RightDown
		if(Dir[7] == 1 && (y + i >= Grid.size() || x + i >= Grid[y + i].size() || Grid[y + i][x + i] != Match[i]))
		{
			Dir[7] = 0;
		}
	}

	int Sum = 0;
	for(const int& i : Dir)
	{
		Sum += i;
	}
	return Sum;
}

int main()
{
	std::string Line;
	long long Sum = 0;

	while (std::getline(std::cin, Line) && !Line.empty())
	{
		Grid.emplace_back(std::move(Line));
	}

	for(int i = 0; i < Grid.size(); i++)
	{
		for(int j = 0; j < Grid[i].size(); j++)
		{
			if(Grid[i][j] == 'X')
			{
				Sum += XMAS(j, i);
			}
		}
	}

	std::cout << Sum;

}