#include <iostream>
#include <ranges>
#include <string>
#include <sstream>
#include <utility>
#include <unordered_set>
#include <unordered_map>

using IntPair = std::pair<int, int>;

struct IntPairHash {
    static_assert(sizeof(int) * 2 == sizeof(size_t));

    size_t operator()(IntPair p) const noexcept {
        return size_t(p.first) << 32 | p.second;
    }
};

int MapX = 0, MapY = 0;
std::unordered_map<char, std::unordered_set<std::pair<int, int>, IntPairHash>> Garden;


unsigned int TotalFence(const std::unordered_set<std::pair<int, int>, IntPairHash>& Pos)
{
    auto Surrounding = [&Pos](int X, int Y)
    {
        return Pos.contains({X + 1, Y}) + Pos.contains({X - 1, Y}) + Pos.contains({X, Y + 1}) +
               Pos.contains({X, Y - 1});
    };

    auto Sum = 0;
    for (const auto& P : Pos)
    {
        Sum += 4 - Surrounding(P.first, P.second);
    }
    return Sum;
}


int FindGroup(int X, int Y, std::unordered_set<std::pair<int, int>, IntPairHash>& NotVisited, std::unordered_set<std::pair<int, int>, IntPairHash>& Visited)
{
    if (X < 0 || Y < 0 || Y >= MapY || X >= MapX || !NotVisited.contains({X, Y}))
    {
        return 0;
    }
    NotVisited.erase({X, Y});
    Visited.insert({X, Y});
    return 1 + FindGroup(X + 1, Y, NotVisited, Visited) + FindGroup(X - 1, Y, NotVisited, Visited) + FindGroup(X, Y + 1, NotVisited, Visited) + FindGroup(X, Y - 1, NotVisited, Visited);
}

int main()
{
    std::string Line;

    while (std::getline(std::cin, Line) && !Line.empty())
    {
        for (MapX = 0; MapX < Line.size(); MapX++)
        {
            Garden[Line[MapX]].insert({MapX, MapY});
        }
        MapY++;
    }

    std::cout << MapX << ' ' << MapY << std::endl;
    // Sum = A u B - A n B
    unsigned int Sum = 0;
    for (auto& G : Garden | std::views::values)
    {
        auto NotVisited = G;
        while (!NotVisited.empty())
        {
            const auto[X, Y] = *NotVisited.cbegin();
            std::unordered_set<std::pair<int, int>, IntPairHash> Visited;
            const auto Area = FindGroup(X, Y, NotVisited, Visited);
            Sum += TotalFence(Visited) * Area;
        }
    }

    std::cout << Sum;
}