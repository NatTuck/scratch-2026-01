
#include <iostream>
#include <memory>

template <typename T>
class List {
public:
    virtual int len() = 0;
};

template <typename T>
using list = std::shared_ptr<List<T>>;

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
    list<T> tail;

    Cell(T hd, list<T> tl)
    {
        this->head = hd;
        this->tail = tl;
    }

    int
    len()
    {
        return 1 + tail->len();
    }
};

list<int>
cons(int hd, list<int> tl)
{
    return std::make_shared<Cell<int>>(hd, tl);
}

list<int>
emp()
{
    return std::make_shared<Empty<int>>();
}

int
main(int argc, char* argv[])
{
    list<int> xs = cons(4, cons(3, cons(2, emp())));
    list<int> ys = cons(6, cons(5, xs));
    list<int> zs = cons(10, cons(11, cons(14, xs)));

    std::cout << xs->len() << std::endl;
    std::cout << ys->len() << std::endl;
    std::cout << zs->len() << std::endl;

    return 0;
}
