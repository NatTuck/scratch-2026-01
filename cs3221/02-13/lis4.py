import sys
import random

sys.setrecursionlimit(10000)


def lis(xs):
    xs = [0] + xs
    nn = len(xs)

    tab = {}

    for ii in range(0, xs):
        for jj in range(0, xs):
        ## What order are these probelms in?
            

    if ii == 0 and pi == 0:
        return lis(memo, [0] + xs, 1, 0)

    if (ii, pi) in memo:
        return memo[(ii, pi)]

    if ii == len(xs):
        return []

    include = []

    if xs[ii] > xs[pi]:
        include = [xs[ii]] + lis(memo, xs, ii + 1, ii)

    exclude = lis(memo, xs, ii + 1, pi)

    ys = include if len(include) > len(exclude) else exclude
    memo[(ii, pi)] = ys
    return ys


def main():
    n = int(sys.argv[1])
    arr = [random.randint(1, n) for _ in range(n)]
    print(f"Array: {arr}")
    result = lis(arr)
    print(f"LIS: {result}")


if __name__ == "__main__":
    main()
