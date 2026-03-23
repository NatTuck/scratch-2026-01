from math import log2


def logstar(n):
    if n <= 1:
        return 0
    else:
        return 1 + logstar(log2(n))


# Ackerman Function
def A(m, n):
    if m == 0:
        return n + 1
    if n == 0:
        return A(m - 1, 1)
    return A(m - 1, A(m, n - 1))


# One arg Ackerman
def AA(x):
    return A(x, x)


# Inverse Ackerman Functoin
def InvAA(x):
    i = 0
    while True:
        if AA(i) > x:
            return i
