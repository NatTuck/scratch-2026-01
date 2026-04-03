
#include <iostream>
#include <memory>
#include <utility>

template <typename T>
class List {
public:
    virtual int len() = 0;
};

template <typename T>
class Empty : public List<T> {
public:
    int
    len()
    {
        return 0;
    }
};

template <typename T>
class Cell : public List<T> {
public:
    T head;
    std::unique_ptr<List<T>> tail;

    Cell(T hd, std::unique_ptr<List<T>> tl)
    {
        this->head = hd;
        this->tail = std::move(tl);
    }

    int
    len()
    {
        return 1 + tail->len();
    }
};

std::unique_ptr<List<int>>
cons(int xx, std::unique_ptr<List<int>> tl)
{
    return std::make_unique<Cell<int>>(xx, std::move(tl));
}

std::unique_ptr<List<int>>
emp()
{
    return std::make_unique<Empty<int>>();
}

int
main(int argc, char* argv[])
{
    std::unique_ptr<List<int>> xs = cons(4, cons(3, cons(2, emp())));

    std::cout << xs->len() << std::endl;

    return 0;
}
