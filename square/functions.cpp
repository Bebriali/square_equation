#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include "functions.h"

int is_zero(double number)
{
    return fabs(number) < DELTA;
}

int clean_buf()
{
    int c = 0;

    int is_clean_buf = BUF_IS_CLEAN;

    while ((c = getchar()) != '\n')
    {
        if (!isspace(c))
        {
            is_clean_buf = BUF_IS_DIRTY;
        }
    }

    return is_clean_buf;
}
