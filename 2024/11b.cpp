#include <iostream>
#include <string>
#include <sstream>
#include <utility>
#include <vector>
#include <span>
#include <future>
#include <ranges>
#include <unordered_map>

unsigned long DigitCount(unsigned long long Value)
{
    auto Count = 0;
    while (Value != 0)
    {
        Value = Value / 10;
        Count++;
    }
    return Count;
}

std::pair<unsigned long long, unsigned long long> SplitEven(const unsigned long long Value,
                                                            const unsigned long Count)
{
    auto Divisor = 1;
    for (int i = 0; i < Count / 2; i++)
    {
        Divisor *= 10;
    }
    const auto First = Value / Divisor;
    return { First, Value - (Value / Divisor) };
}

unsigned long long LookAtRock(std::span<int> Rocks, const int Amount)
{
    std::unordered_map<unsigned long long, unsigned long long> Map, MapNext;
    for (const auto& R : Rocks)
    {
        Map.emplace(R, 1);
    }

    for (int i = 0; i < Amount; i++)
    {
        MapNext.clear();
        for (auto& [Key, Val] : Map)
        {
            if (Key == 0)
            {
                MapNext[1] += Val;
                continue;
            }

            const auto& Count = DigitCount(Key);
            if (Count % 2 == 0)
            {
                const auto& [First, Second] = SplitEven(Key, Count);
                MapNext[First] += Val;
                MapNext[Second] += Val;
            }
            else
            {
                MapNext[Key * 2024] += Val;
            }
        }
        std::swap(Map, MapNext);
    }
    unsigned long long Sum = 0;
    for (const auto& V : Map | std::views::values)
    {
        Sum += V;
    }
    return Sum;
}

int main()
{
    std::string Line;
    std::getline(std::cin, Line);
    std::vector<int> Stones;

    std::stringstream ss(Line);
    int Num;
    while (ss >> Num)
    {
        Stones.emplace_back(Num);
    }

    std::cout << LookAtRock(Stones, 75);
}