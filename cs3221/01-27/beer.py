import math

def beer_song(nn):
    text = ""

    for ii in range(0, nn):
        text += f"{ii} beers, {ii} beers\n"

    return text

def song_len(nn):
    return len(beer_song(nn))

def num_len(nn):
    return len(str(nn))

def num_len_math(nn):
    if nn <= 0:
        return 1
    else:
        return math.floor(1 + math.log10(nn))

#def song_len_math(nn):
#    sum = 0
#    for ii in range(0, nn):
#        sum += 15 + 2 * num_len_math(ii)
#    return sum

def song_len_math(nn):
    if nn <= 0:
        return 0
    else:
        rest = song_len_math(nn - 1)
        ours = 15 + 2 * num_len_math(nn)
        print(nn, ours, rest)
        return ours + rest

for ii in range(0, 5):
    xx = 2**ii
    print(xx, "\t", song_len(xx), "\t", song_len_math(xx))





