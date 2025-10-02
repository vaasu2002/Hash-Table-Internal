#include <iostream>
#include <string>
#include <unordered_map>

struct Point {
    int x, y;
    bool operator==(const Point& other) const { return x == other.x && y == other.y; }
};

struct PointHash {
    size_t operator()(const Point& p) const noexcept {
        size_t h1 = std::hash<int>{}(p.x);
        size_t h2 = std::hash<int>{}(p.y);
        return h1 ^ (h2 + 0x9e3779b97f4a7c15ULL + (h1 << 6) + (h1 >> 2));
    }
};

int main() {
    std::unordered_map<Point, std::string, PointHash> map;
    map[{3, 5}] = "hello";

    auto it = map.find(Point{3, 5});
    if (it != map.end()) {
        std::cout << it->second << std::endl;
    } else {
        std::cout << "Key not found\n";
    }
    return 0;
}
