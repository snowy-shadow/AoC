#include <iostream>
#include <string>
#include <map>
#include <unordered_set>

int main()
{
	std::string Line;
	long long Sum = 0;

	std::getline(std::cin, Line);

	std::map<int, int, std::greater<>> Blocks;

	for(auto i = 0; i < Line.size(); i += 2)
	{
		Blocks[i / 2] = Line[i] - '0';
	}

	std::unordered_set<uintptr_t> Visited;
	auto ForwardIter = 0;
	for(auto i = Line.begin(); !Blocks.empty(); i += 2)
	{
		// forward sum
		if(!Visited.contains(std::distance(Line.begin(), i) / 2))
		{
			for(auto j = *i - '0'; j > 0; j--, ForwardIter++)
			{
				auto val = std::distance(Line.begin(), i) / 2;
				Sum += ForwardIter * val;
			}
			Blocks.erase(std::distance(Line.begin(), i) / 2);
		}
		else
		{
			ForwardIter += *i - '0';
		}

		// find largest from the back
		auto FreeSpace = *(i + 1) - '0';
		for (auto BlockIter = Blocks.begin(); BlockIter != Blocks.end() && FreeSpace > 0;)
		{
			auto& B = *BlockIter;
			if (B.second <= FreeSpace)
			{
				Visited.insert(B.first);

				Sum += ForwardIter * B.first;
				ForwardIter++;
				FreeSpace--;
				B.second--;

				if (B.second == 0)
				{
					BlockIter = Blocks.erase(BlockIter);
				}
			}
			else
			{
				++BlockIter;
			}

		}
		ForwardIter += FreeSpace;
	}

	std::cout << Sum;
}