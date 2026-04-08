
#include <algorithm>
#include <iostream>
#include <vector>

int
main(int argc, char* argv[])
{
    std::vector<std::string> names = { "Alice", "bob", "Carol", "dave" };

    std::sort(names.begin(), names.end(), [](auto& aa, auto& bb) {
        std::lexicographical_compare(
            aa.begin(), aa.end(), bb.begin(), bb.end(),
            [](char ch0, char ch1) {
                return std::tolower(ch0) < std::tolower(ch1);
            });
    });

    for (auto name : names) {
        std::cout << name << std::endl;
    }

    return 0;
}
