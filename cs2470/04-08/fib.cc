
constexpr int
fib(int n)
{
    if (n < 1) {
        return 1;
    }
    else {
        return fib(n - 1) + fib(n - 2);
    }
}

constexpr int fib10 = fib(10);
