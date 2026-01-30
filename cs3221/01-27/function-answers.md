Length of a number in decimal digits:

$$
    f(x) =
    \begin{cases}
    1 & x \le 0 \\
    \lfloor \log_{10}(x) \rfloor & otherwise
    \end{cases}
$$

Full song length function:

$$
    \text{slen}(x) = \sum_{i=1}^{x}(2(f(i))+15)
$$