#include <iostream>
#include <string>
#include <sstream>
#include <vector>

int main()
{
	std::string Line;
	std::vector<std::string> Grid;
	Grid.reserve(50);

	int x = 0, y = 0;
	unsigned int Counter = 0;
	while (std::getline(std::cin, Line) && !Line.empty())
	{
		auto Find = Line.find('^');
		if(Find != std::string::npos)
		{
			// grid is not bigger than int
			x = Find;
			y = Counter;
		}
		Counter++;
		Grid.emplace_back(std::move(Line));
	}

	long long Sum = 0;
	char CurrentDir = Grid[y][x];
	while(x > 0 && x < Grid[y].size() - 1 && y > 0 && y < Grid.size() - 1)
	{
		Again:
		int NewX, NewY;
		switch (CurrentDir)
		{
			case '^':
				NewX = x;
				NewY = y - 1;
				break;
			case '>':
				NewX = x + 1;
				NewY = y;
				break;
			case '<':
				NewX = x - 1;
				NewY = y;
				break;
			case 'v':
				NewX = x;
				NewY = y + 1;
				break;
		}

		if (Grid[NewY][NewX] == '#')
		{
			switch(CurrentDir)
			{
				case '^':
					CurrentDir = '>';
					break;
				case '>':
					CurrentDir = 'v';
					break;
				case '<':
					CurrentDir = '^';
					break;
				case 'v':
					CurrentDir = '<';
					break;
			}
			goto Again;
		}
		Grid[y][x] = 'X';

		if(Grid[NewY][NewX] != 'X')
		{
			Sum++;
		}
		x = NewX;
		y = NewY;
	}

	// the last step where guard exit wasn't simulated
	std::cout << Sum + 1;
}

