#include <iostream>
#include <string>

int main()
{
	std::string Line;
	long long Sum = 0;

	std::getline(std::cin, Line);

	const char* pBegin = Line.data();
	const char* pEnd = pBegin + Line.size();
	pEnd = (pEnd - pBegin) % 2 == 0 ? pEnd - 2 : pEnd - 1;

	int ForwardIndex = 0;
	int EndSize = *pEnd - '0';

	while(pBegin < pEnd)
	{
		// sum front
		if((pEnd - pBegin) % 2 == 0)
		{
			for(int N = *pBegin - '0'; N > 0; N--, ForwardIndex++)
			{
				auto Val = (pBegin - Line.data()) / 2;
				Sum += ForwardIndex * Val;
			}

		}
			// sum end
		else
		{
			// Amount we can sum;
			for(int N = *pBegin - '0'; N > 0 && pBegin < pEnd; N--, ForwardIndex++)
			{
				if(EndSize == 0)
				{
					pEnd -= 2;
					// if(pEnd < pBegin) {break;}
					EndSize = *pEnd - '0';
				}
				auto Val = (pEnd - Line.data()) / 2;
				Sum += ForwardIndex * Val;
				EndSize--;
			}
		}
		pBegin++;
	}
	for(; EndSize > 0; EndSize--, ForwardIndex++)
	{
		auto Val = (pEnd - Line.data()) / 2;
		Sum += ForwardIndex * Val;
	}
	std::cout << Sum;
}