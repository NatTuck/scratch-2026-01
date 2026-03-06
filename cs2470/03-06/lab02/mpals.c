#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

#define BLOCK_SIZE 512
#define MAX_WORD_LEN 1024

int
isPalindrome(char* word)
{
    int len = strlen(word);
    if (len <= 1)
        return len == 1;

    int left = 0;
    int right = len - 1;

    while (left < right) {
        if (tolower(word[left]) != tolower(word[right])) {
            return 0;
        }
        left++;
        right--;
    }
    return 1;
}

int
main()
{
    // (Q1) Read "man fopen". What does the "r" argument do below?
    // (Q2) Read "man open". How do you get the same behavior as "r"?
    int fd = open("words.txt", 0);
    if (fd == -1) {
        perror("Failed to open words.txt");
        return 1;
    }

    long size = 985084;
    char* words = mmap(0, size, PROT_READ, MAP_SHARED, fd, 0);
    if ((long)words == -1) {
        perror("Failed to mmap");
        return 1;
    }

    char buffer[BLOCK_SIZE + 1];
    char word[MAX_WORD_LEN];
    int word_len = 0;
    size_t bytes_read;

    long offset = 0;

    for (size_t i = 0; i < size; i++) {
        if (words[i] == '\n' || words[i] == '\r') {
            if (word_len > 0) {
                word[word_len] = '\0';
                if (isPalindrome(word)) {
                    // (Q3) What's the "a" argument to fopen doing?
                    // (Q4) How do you get the same behavior as "a" with open?
                    FILE* out = fopen("output.txt", "a");
                    if (out) {
                        fwrite(word, 1, strlen(word), out);
                        fwrite("\n", 1, 1, out);
                        fclose(out);
                    }
                }
                word_len = 0;
            }
        }
        else {
            if (word_len < MAX_WORD_LEN - 1) {
                word[word_len++] = words[i];
            }
        }
    }

    if (word_len > 0) {
        word[word_len] = '\0';
        if (isPalindrome(word)) {
            FILE* out = fopen("output.txt", "a");
            if (out) {
                fwrite(word, 1, strlen(word), out);
                fwrite("\n", 1, 1, out);
                fclose(out);
            }
        }
    }

    close(fd);
    return 0;
}
