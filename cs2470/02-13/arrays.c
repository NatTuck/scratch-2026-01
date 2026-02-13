#include <stdio.h>

typedef struct five_floats {
    float xs[5];
} five_floats;

float
avg_grade(five_floats item)
{
    float sum = 0.0;
    for (int ii = 0; ii < 5; ++ii) {
        sum += item.xs[ii];
    }
    return sum / 5;
}

int
main(int argc, char* argv[])
{
    float grades[5] = { 97.3, 81.2, 44.3, 94.9, 35.2 };
    int nn = 5;

    five_floats item;
    for (int ii = 0; ii < 5; ++ii) {
        item.xs[ii] = grades[ii];
    }

    float avg = avg_grade(item);

    printf("Average grade: %.02f\n", avg);

    return 0;
}
