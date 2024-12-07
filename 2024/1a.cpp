#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

int main()
{
	std::vector<int> Left(1000), Right(1000);
	std::string Line;

	// Read input until EOF or an empty line is encountered
	while (std::getline(std::cin, Line) && !Line.empty()) {
		std::stringstream ss(Line);
		int a, b;

		// Extract two integers from the line
		if (ss >> a >> b) {
			Left.push_back(a);  // Store the first integer in Left vector
			Right.push_back(b); // Store the second integer in Right vector
		}
	}

	std::sort(Left.begin(), Left.end());
	std::sort(Right.begin(), Right.end());
	unsigned int Sum = 0;
	for(int a = 0; a < Left.size(); a++)
	{
		Sum += abs(Left[a] - Right[a]);
	}
	std::cout << Sum;
}

