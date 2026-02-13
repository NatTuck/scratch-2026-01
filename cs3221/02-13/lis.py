import sys
import random


def lis(xs, idx, prev):
    if idx == len(xs):
        return []
    include = []
    if xs[idx] > prev:
        include = [xs[idx]] + lis(xs, idx + 1, xs[idx])
    exclude = lis(xs, idx + 1, prev)
    return include if len(include) > len(exclude) else exclude


def main():
    n = int(sys.argv[1])
    arr = [random.randint(1, n) for _ in range(n)]
    print(f"Array: {arr}")
    result = lis(arr, 0, 0)
    print(f"LIS: {result}")


if __name__ == "__main__":
    main()
