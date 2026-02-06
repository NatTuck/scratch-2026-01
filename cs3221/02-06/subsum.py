#!/usr/bin/env python

import random

def subsum(x, ys):
    if len(ys) == 0:
        if x == 0:
            return []
        else:
            return None

    head = ys[0]
    tail = ys[1:]

    zs1 = subsum(x, tail)
    zs2 = subsum(x - head, tail)

    if zs2 != None:
        return [head] + zs2
    else:
        return zs1

def gen_instance(n):
    ys = [random.randint(1, n) for _ in range(n)]
    if random.random() < 0.75:
        k = random.randint(0, len(ys))
        x = sum(random.sample(ys, k))
    else:
        ys = [y * 2 for y in ys]
        k = random.randint(1, len(ys))
        x = sum(random.sample(ys, k)) + 1

    return x, ys





