

def min_cost(costs, grid, ii, jj, N, M):
    if (jj, ii) not in costs:

        if ii == 0 and jj == 0:
            costs[(jj,ii)] = grid[0][0]
        elif ii < 0 or jj < 0:
            costs[(jj,ii)] = float('inf')
        else:
            cost_left = min_cost(costs, grid, ii-1, jj, N, M)
            cost_up = min_cost(costs, grid, ii, jj-1, N, M)

            costs[(jj,ii)] = grid[jj][ii] + min(cost_left, cost_up)

    return costs[(jj, ii)]

def cost_get(costs, jj, ii):
    if ii < 0 or jj < 0:
        return float('inf')
    
    return costs[(jj, ii)]

def min_path(grid, ii, jj, N, M):
    costs = {}
    _ = min_cost(costs, grid, ii, jj, N, M)

    print(costs)

    path = []
    while ii != 0 or jj != 0:
        path.append((ii, jj))

        up = cost_get(costs, jj, ii - 1)
        le = cost_get(costs, jj - 1, ii)

        if le < up:
            ii = ii - 1
        else:
            jj = jj - 1

    return path
        


def main():
    grid = [
        [1,  10, 100, 100],
        [20,  4,   8,  16],
        [49, 31,   0,  33],
    ]

    print(min_path(grid, 3, 2, 4, 3))

if __name__ == '__main__':
    main()
