#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <utility>

struct pair_hash {
	template <typename T1, typename T2>
	size_t operator ()(const std::pair<T1, T2>& p) const {
		return std::hash<T1>()(p.first) ^ std::hash<T2>()(p.second);
	}
};

std::pair<float, float> LineEq(std::pair<int, int> A, std::pair<int, int> B)
{
	float m = (float)(B.second - A.second) / (float)(B.first - A.first);

	// X1 * m - y1 = mx - y
	float Constant = (float)A.first * m - (float)A.second;

	return {m, Constant};
}


std::vector<std::pair<int, int>> FindAntiNodes(std::vector<std::pair<int, int>> Antennas, int BoundX, int BoundY)
{
	// line and their corresponding points
	std::unordered_map<std::pair<float, float>, std::unordered_set<std::pair<int, int>, pair_hash>, pair_hash> Lines;

	for(int i = 0; i < Antennas.size(); i++)
	{
		for(int j = i + 1; j < Antennas.size(); j++)
		{
			const auto& K = LineEq(Antennas[i], Antennas[j]);
			Lines[K].insert(Antennas[j]);
			Lines[K].insert(Antennas[i]);
		}
	};

	std::vector<std::pair<int, int>> Solutions;
	// for each line
	for(const auto& L : Lines)
	{
		// for all points
		for(auto i = L.second.begin(); i != L.second.end(); i++)
		{
			for(auto j = L.second.begin(); j != L.second.end(); j++)
			{
				if(i == j){continue;}
				auto Dy = (j->first - i->first);
				auto Dx = (j->second - i->second);

				int TargetX = j->second + Dx;
				int TargetY = j->first + Dy;
				if(TargetX > -1 && TargetX < BoundX && TargetY > -1 && TargetY < BoundY)
				{
					Solutions.emplace_back(TargetX, TargetY);
				}
			}
		}
	}

	return Solutions;
}


int main()
{
	std::string Line;
	std::vector<std::string> Grid;
	Grid.reserve(50);
	std::unordered_map<char, std::vector<std::pair<int, int>>> Antennas;

	int x = 0, y = 0;
	while (std::getline(std::cin, Line) && !Line.empty())
	{
		for(int i = 0; i < Line.size(); i++)
		{
			if(Line[i] != '.')
			{
				Antennas[Line[i]].emplace_back(y, i);
			}
		}
		y++;
		x = Line.size();
	}

	std::unordered_set<std::pair<int, int>, pair_hash> AntiNodes;
	for(const auto& A : Antennas)
	{
		for(const auto& S : FindAntiNodes(A.second, x, y))
		{
			AntiNodes.insert(S);
		}
	}

	std::cout << AntiNodes.size();
}

