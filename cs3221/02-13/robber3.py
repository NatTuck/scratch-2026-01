
import random

def maximize_loot(xs, nn):
    if nn == 0:
        return 0

    prev2 = xs[0]
    
    if nn == 1:
        return prev2

    prev1 = max(xs[0], xs[1])

    if nn == 2:
        return prev1

    for ii in range(2, nn):
        include = xs[ii] + prev2
        exclude = prev1
        curr = max(include, exclude)

        prev2 = prev1
        prev1 = curr

    return prev1

def gen_instance(n):
    return [random.randint(0, n) for _ in range(0, n)]

for ii in range(10):
    xs = gen_instance(ii)
    print("")
    print(xs)
    print(ii, maximize_loot(xs, len(xs)))


