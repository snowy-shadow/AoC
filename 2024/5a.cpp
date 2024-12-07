#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

std::unordered_map<int, std::unordered_set<int>> Dependency;

int MiddlePage(const std::string& Str)
{
	std::stringstream SS(Str);
	std::unordered_set<int> Visited {0}, Updates;
	std::vector<int> Pages;
	int Page;

	while(SS >> Page)
	{
		Pages.push_back(Page);
		Updates.insert(Page);
		SS.ignore(1, ',');
	}

	for(const auto& i : Pages)
	{
		auto DependentPage = Dependency[i];

		// set intersect
		for(const auto& j : DependentPage)
		{
			if(Updates.contains(j) && !Visited.contains(j))
			{
				return 0;
			}
		}

		Visited.insert(i);
	}

	return Pages[Pages.size() / 2];
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