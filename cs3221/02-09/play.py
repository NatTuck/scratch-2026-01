#!/usr/bin/env python

def new_game(n):
    return [' ' for _ in range(n)]

def game_is_over(game):
    xes = 0
    for square in game:
        if square == 'X':
            xes += 1
        else:
            xes = 0
        if xes == 3:
            return True
    return False

def legal_moves(game):
    ys = []
    for ii in range(len(game)):
        if game[ii] != 'X':
            ys.append(ii)
    return ys

def make_move(game, move):
    ys = [x for x in game]
    ys[move] = 'X'
    return ys

def whoami(game):
    count = 0
    for sq in game:
        if sq == 'X':
            count += 1
    if count % 2 == 0:
        return 1
    else:
        return 2

def best_move(game):
    if game_is_over(game):
        raise Exception("game over")
   
    player = whoami(game)

    moves = legal_moves(game)

    for move in moves:
        g1 = make_move(game, move)

        if game_is_over(g1):
            print(whoami(game), move)
            return move, player
        else:
            m1, winner = best_move(g1)
            if winner == player:
                return m1, player
    
    return None, None





