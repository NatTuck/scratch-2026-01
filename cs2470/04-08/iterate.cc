
#include <iostream>
#include <vector>

int
main(int argc, char* argv[])
{
    // std::vector<int> xs = {1, 2, 4, 8, 35};
    auto xs = { 1, 2, 4, 8, 35 };

    // for (auto it = xs.begin(); it != xs.end(); ++it) {
    // for (auto& item : xs) {
    // for (auto item : xs) {
    for (const auto& item : xs) {
        std::cout << item << std::endl;
    }

    return 0;
}
