#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void*
realloc(void* oldptr, long newsz)
{
}

// also, how to free?

char*
read_word(int fd)
{
    char* word = sbrk(4);
    long wlen = 4;

    char temp = 0;
    int ii = 0;
    do {
        if (ii >= wlen) {
            wlen = wlen * 2;
            word = realloc(word, wlen);
        }

        int count = read(fd, &temp, 1);
        if (count == 0) {
            free(word);
            return 0;
        }

        word[ii] = temp;

        ++ii;
    } while (temp != '\n');

    word[ii - 1] = 0;
    return word;
}

int
main(int argc, char* argv[])
{
    char* empty = "";
    char* top5[5] = { empty, empty, empty, empty, empty };

    int fd = open("/usr/share/dict/words", 0);

    while (1) {
        char* word = read_word(fd);
        if (!word) {
            break;
        }
        printf("word is %s\n", word);

        int min_idx = strlen(top5[0]);
        for (int ii = 1; ii < 5; ++ii) {
            if (strlen(top5[ii]) < min_idx) {
                min_idx = ii;
            }
        }

        if (strlen(top5[min_idx]) < strlen(word)) {
            if (top5[min_idx] != empty) {
                free(top5[min_idx]);
            }
            top5[min_idx] = word;
        }
    }

    close(fd);

    for (int ii = 0; ii < 5; ++ii) {
        printf("%d: %s\n", ii, top5[ii]);
    }

    return 0;
}
