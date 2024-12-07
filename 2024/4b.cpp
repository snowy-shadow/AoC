#include <iostream>
#include <string>
#include <regex>
#include <string_view>

std::vector<std::string> Grid;

bool XMAS(int x, int y)
{
	// std::set for 3 char is over kill
	// M, A, S
	bool BackBlade[]{true, true, true};
	bool ForwardBlade[]{true, true, true,};

	constexpr auto CharToIndex = [](char C)
	{
		switch(C)
		{
			case 'M':
				return 0;
			case 'A':
				return 1;
			case 'S':
				return 2;
			default:
				return -1;
		}
	};

	// center
	int Index = CharToIndex(Grid[y][x]);
	if(Index < 0){return false;}
	BackBlade[Index] = ForwardBlade[Index] = false;

	// top left
	Index = CharToIndex(Grid[y - 1][x - 1]);
	if(Index < 0 || !BackBlade[Index])
	{
		return false;
	}
	else
	{
		BackBlade[Index] = false;
	}
	// bottom right
	Index = CharToIndex(Grid[y + 1][x + 1]);
	if(Index < 0 || !BackBlade[Index])
	{
		return false;
	}

	// bottom left
	Index = CharToIndex(Grid[y + 1][x - 1]);
	if(Index < 0 || !ForwardBlade[Index])
	{
		return false;
	}
	else
	{
		ForwardBlade[Index] = false;
	}
	// top right
	Index = CharToIndex(Grid[y - 1][x + 1]);
	if(Index < 0 || !ForwardBlade[Index])
	{
		return false;
	}
	return true;
}

int main()
{
	std::string Line;
	long long Sum = 0;

	while (std::getline(std::cin, Line) && !Line.empty())
	{
		Grid.emplace_back(std::move(Line));
	}

	// y axis
	for(int i = 1; i < Grid.size() - 1; i++)
	{
		// x axis
		for(int j = 1; j < Grid[i].size() - 1; j++)
		{
			if(Grid[i][j] == 'A' && XMAS(j, i))
			{
				Sum += 1;
			}
		}
	}

	std::cout << Sum;

}