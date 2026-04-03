
#include <iostream>

template <typename T>
class List {
public:
    virtual int len() = 0;
    virtual ~List() { };
};

template <typename T>
class Empty : public List<T> {
public:
    int
    len()
    {
        return 0;
    }

    ~Empty() { }
};

template <typename T>
class Cell : public List<T> {
public:
    T head;
    List<T>* tail;

    Cell(T hd, List<T>* tl)
    {
        this->head = hd;
        this->tail = tl;
    }

    int
    len()
    {
        return 1 + tail->len();
    }

    ~Cell()
    {
        delete this->tail;
    }
};

int
main(int argc, char* argv[])
{
    List<int>* xs = new Cell(4, new Cell(3, new Cell(2, new Empty<int>())));

    std::cout << xs->len() << std::endl;

    delete xs;

    return 0;
}
