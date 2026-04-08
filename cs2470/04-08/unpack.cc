
#include <iostream>
#include <map>

int
main(int argc, char* argv[])
{
    std::map<std::string, int> scores;
    scores["Alice"] = 35;
    scores["Bob"] = 41;

    for (const auto& [name, score] : scores) {
        std::cout << name << ": " << score << std::endl;
    }

    return 0;
}
