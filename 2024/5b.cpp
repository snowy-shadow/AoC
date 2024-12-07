#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

std::unordered_map<int, std::unordered_set<int>> Dependency;

// I read the question wrong, this is the more generic version.
// puts everything into correct order and then finds the middle page
// too lazy to fix so i added a hack

int MiddlePage(const std::string& Str)
{
	std::stringstream SS(Str);
	std::unordered_map<int, int> PageUpdates{20};
	std::vector<int> Pages;
	int Page;
	int Index = 1;

	while(SS >> Page)
	{
		Pages.push_back(Page);
		PageUpdates[Page] = Index;
		Index++;
		SS.ignore(1, ',');
	}

	int Flag = false;
	CheckAgain:
	std::unordered_set<int> Visited {20};
	for(const auto i : Pages)
	{
		const auto& DependentPage = Dependency[i];

		// set intersect
		for(const auto j : DependentPage)
		{
			if(PageUpdates[j] != 0 && !Visited.contains(j))
			{
				std::swap(Pages[PageUpdates[i] - 1], Pages[PageUpdates[j] - 1]);

				int Temp = PageUpdates[i];
				PageUpdates[i] = PageUpdates[j];
				PageUpdates[j] = Temp;
				Flag = true;

				goto CheckAgain;
			}
		}

		Visited.insert(i);
	}


	return Flag ? Pages[Pages.size() / 2] : 0;
}

int main()
{
	std::string Line;
	long long Sum = 0;

	while (std::getline(std::cin, Line) && !Line.empty())
	{
		std::stringstream SS(Line);
		int A, B;
		char Delim;
		SS >> A >> Delim >> B;

		// page 0 is no dependency
		Dependency[B].insert(A);
	}

	while (std::getline(std::cin, Line) && !Line.empty())
	{
		Sum += MiddlePage(Line);
	}

	std::cout << Sum;
}

