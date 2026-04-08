
#include <algorithm>
#include <iostream>
#include <vector>

int
main(int argc, char* argv[])
{
    auto xs = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::vector<int> evens;

    int yy = 3;

    std::copy_if(xs.begin(), xs.end(),
        std::back_inserter(evens),
        [=](int x) { return x % yy == 0; });

    for (auto x : evens) {
        std::cout << x << std::endl;
    }

    auto add = [](auto aa, auto bb) { return aa + bb; };

    add(1, 2);
    add(1.3, 2.4);

    return 0;
}
