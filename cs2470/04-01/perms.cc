
#include <algorithm>
#include <iostream>
#include <vector>

int
main(int argc, char* argv[])
{
    std::vector<int> xs({ 1, 2, 3, 4 });

    do {
        for (int ii = 0; ii < 4; ++ii) {
            std::cout << xs.at(ii) << " ";
        }

        std::cout << std::endl;
    } while (std::next_permutation(xs.begin(), xs.end()));

    return 0;
}
