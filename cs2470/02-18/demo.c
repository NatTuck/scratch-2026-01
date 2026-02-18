#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

typedef struct slice {
    const char* ptr;
    long len;
} slice;

typedef struct scell {
    slice item;
    struct scell* next;
} scell;

scell*
scons(slice item, scell* next)
{
    scell* xs = malloc(sizeof(scell));
    xs->item = item;
    xs->next = next;
    return xs;
}

void
free_scell(scell* xs)
{
    if (xs) {
        // don't need to free the slice
        free_scell(xs->next);
        free(xs);
    }
}

long
slength(scell* xs)
{
    if (!xs) {
        return 0;
    }
    return 1 + slength(xs->next);
}

void
print_slice(slice sl)
{
    printf("slice: [%s]\n", sl.ptr);
}

scell*
split_words(const char* text)
{
    scell* ys = 0;

    slice cur;
    cur.ptr = text;
    cur.len = 0;

    for (int ii = 0; text[ii]; ii++) {
        if (text[ii] == '\n') {
            ys = scons(cur, ys);
            cur.ptr = text + ii;
            cur.len = 0;
        }
        else {
            cur.len += 1;
        }
    }

    return ys;
}

long
file_size(const char* path)
{
    struct stat st;
    int rv = stat(path, &st);
    assert(rv != -1);
    return st.st_size;
}

int
main(int argc, char* argv[])
{
    if (argc != 2) {
        fprintf(stderr, "What file?\n");
        return 1;
    }

    const char* path = argv[1];

    // Figure out size, allocate buffer.
    long sz = file_size(path);
    char* data = malloc(sz + 1);
    data[sz] = 0;

    printf("file %s is size %ld\n", path, sz);

    // Read the whole file.
    FILE* fh = fopen(path, "r");
    assert(fh != 0);

    long rv = fread(data, 1, sz, fh);
    assert(rv == sz);

    fclose(fh);

    // Split into list of words (slices).
    scell* words = split_words(data);
    printf("Built list of %ld words.\n", slength(words));

    for (scell* it = words; it != 0; it = it->next) {
        print_slice(it->item);
    }

    free_scell(words);

    free(data);
    return 0;
}
