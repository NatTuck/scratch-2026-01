#include <stdio.h>

typedef struct list {
    float* data;
    int size;
} list;

float
avg_grade(list* xs)
{
    float sum = 0.0;
    for (int ii = 0; ii < xs->size; ++ii) {
        sum += xs->data[ii];
    }
    return sum / xs->size;
}

int
main(int argc, char* argv[])
{
    float grades[5] = { 97.3, 81.2, 44.3, 94.9, 35.2 };

    list xs;
    xs.data = grades;
    xs.size = 5;

    float avg = avg_grade(&xs);

    printf("Average grade: %.02f\n", avg);

    return 0;
}
