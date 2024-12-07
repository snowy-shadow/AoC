#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>

int main()
{
	std::vector<int> Left(1000);
	std::unordered_map<int, int> Right(1000);
	std::string Line;

	// Read input until EOF or an empty line is encountered
	while (std::getline(std::cin, Line) && !Line.empty()) {
		std::stringstream ss(Line);
		int a, b;


		if (ss >> a >> b) {
			Left.push_back(a);
			Right[b] += 1;
		}
	}

	unsigned int Sum = 0;
	for(int a : Left)
	{
		Sum += a * Right[a];
	}
	std::cout << Sum;
}

