
import random

def maximize_loot(memo, xs, ii):
    """
    Return the maximum value of non-adjacent
    items for the prefix 0 <= index <= ii
    """
    if ii in memo:
        return memo[ii]

    if ii <= 0:
        return 0

    # Max if we include xs[ii]
    include = xs[ii] + maximize_loot(memo, xs, ii - 2)
    exclude = maximize_loot(memo, xs, ii - 1)
    yy = max(include, exclude)
    memo[ii] = yy
    return yy

def gen_instance(n):
    return [random.randint(0, n) for _ in range(0, n)]

for ii in range(10000):
    xs = gen_instance(ii)
    print(ii, maximize_loot({}, xs, len(xs) - 1))


