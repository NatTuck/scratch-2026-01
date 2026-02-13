
import random

def maximize_loot(xs):
    if len(xs) == 0:
        return 0
    loot0 = xs[0] + maximize_loot(xs[2:])
    loot1 = maximize_loot(xs[1:])
    return max(loot0, loot1)

def gen_instance(n):
    return [random.randint(0, n) for _ in range(0, n)]

for ii in range(100):
    print(ii, maximize_loot(gen_instance(ii)))
