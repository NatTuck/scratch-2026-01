import sys
import random

sys.setrecursionlimit(10000)


def lis(memo, xs, idx, prev):
    if (idx, prev) in memo:
        return memo[(idx, prev)]

    if idx == len(xs):
        return []
    include = []
    if xs[idx] > prev:
        include = [xs[idx]] + lis(memo, xs, idx + 1, xs[idx])
    exclude = lis(memo, xs, idx + 1, prev)

    ys = include if len(include) > len(exclude) else exclude
    memo[(idx, prev)] = ys
    return ys


def main():
    n = int(sys.argv[1])
    arr = [random.randint(1, n) for _ in range(n)]
    print(f"Array: {arr}")
    result = lis({}, arr, 0, 0)
    print(f"LIS: {result}")


if __name__ == "__main__":
    main()
