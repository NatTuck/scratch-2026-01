import math

def beer_song(nn):
    text = ""

    for ii in range(0, nn):
        text += f"{ii} beers, {ii} beers\n"

    return text

def song_len(nn):
    return len(beer_song(nn))

def gifts_song(nn):
    text = ""

    for ii in range(1, nn + 1):
        text += f"on day {ii}"
        for jj in range(ii, 0, -1):
            text += f"item {jj}; "
        text += "\n"

    return text


for ii in range(20):
    xx = 2**ii
    print(xx, len(beer_song(xx)), len(gifts_song(xx)))



