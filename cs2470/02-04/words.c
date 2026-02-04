
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char*
read_line(FILE* fh)
{
    char line[100];
    char* rv = fgets(line, 100, fh);

    printf("line = '%s'\n", line);

    char* word = malloc(strlen(line));
    for (int jj = 0; jj < strlen(line); ++jj) {
        word[jj] = line[jj];
        if (jj == strlen(line) - 1) {
            word[jj] = '\0';
        }
    }

    return word;
}

int
main(int argc, char* argv[])
{
    FILE* fh = fopen("/usr/share/dict/words", "r");

    char** words = malloc(5 * sizeof(char*));

    for (int ii = 0; ii < 5; ++ii) {
        words[ii] = read_line(fh);
    }

    for (int ii = 0; ii < 5; ++ii) {
        printf("word #%d = %s\n", ii, words[ii]);
        free(words[ii]);
    }

    free(words);

    fclose(fh);
    return 0;
}
