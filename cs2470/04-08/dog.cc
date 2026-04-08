
#include <optional>
#include <string>

class Dog {
public:
    std::string name;

    Dog(std::string nn)
        : name(nn)
    {
    }
};

int
main(int argc, char* argv[])
{
    std::optional<Dog> fido = std::optional<Dog>("Fido");

    return 0;
}
