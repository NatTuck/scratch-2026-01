
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

List<int>*
cons(int hd, List<int>* tl)
{
    return new Cell<int>(hd, tl);
}

List<int>*
emp()
{
    return new Empty<int>();
}

int
main(int argc, char* argv[])
{
    List<int>* xs = cons(4, cons(3, cons(2, emp())));
    List<int>* ys = cons(6, cons(5, xs));
    List<int>* zs = cons(10, cons(11, cons(14, xs)));

    std::cout << xs->len() << std::endl;
    std::cout << ys->len() << std::endl;
    std::cout << zs->len() << std::endl;

    delete ys;
    delete zs;

    return 0;
}
