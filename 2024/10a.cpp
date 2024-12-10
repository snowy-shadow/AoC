#include <iostream>
#include <string>
#include <vector>

std::vector<std::vector<int>> Grid;
std::vector<std::vector<int>> Visited;

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
	if (Visited[Y][X] == 1)
	{
		return 0;
	}
	Visited[Y][X] = 1;
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

void ZeroVisited()
{
	for(auto& I : Visited)
	{
		for(auto& J : I)
		{
			J = 0;
		}
	}
}

int main()
{
	std::string Line;
	long long Sum = 0;

	while(std::getline(std::cin, Line) && !Line.empty())
	{
		auto& Y = Grid.emplace_back();
		auto& V = Visited.emplace_back();
		for(const auto& C : Line)
		{
			Y.emplace_back(C - '0');
			V.emplace_back(0);
		}
	}

	for(int i = 0; i < Grid.size(); i++)
	{
		for(int j = 0; j < Grid[i].size(); j++)
		{
			if(Grid[i][j] == 0)
			{
				ZeroVisited();
				Sum += TrailScore(j, i, -1);
			}

		}
	}

	std::cout << Sum;
}

