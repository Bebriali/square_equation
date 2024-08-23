#include <stdio.h>
#include "tester.h"

void auto_test()
{
    printf("auto_testing:\n");             //   a               b               c           right_x1    right_x2    right_number_of_roots

    struct Mask_Coefs tests[TESTS_QUANTITY] = {{1,              2,              1,         -1,          -1,        ONE_ROOT},
                                               {0,              0,              0,          0,        0,        INF_NUMOF_ROOTS},
                                               {1,              4,              3,         -1,         -3,          TWO_ROOTS},
                                               {25.4343,        89.3124,       -64.45,      0.614195,  -4.12569,    TWO_ROOTS},
                                               {273.1645424,    13797.5455215, -12514.64,   0.891292,  -51.40131,   TWO_ROOTS},
                                               {0,              2.23432,        0,          0,          0,        ONE_ROOT},
                                               {3,              4,              3,          0,        0,        NO_ROOTS}};


    for (int i = 0; i < TESTS_QUANTITY; i++)
    {
        test_coef(i, &tests[i]);
    }

    printf("testing completed\n\n");
}

void test_coef(int test_number, Mask_Coefs* test){
    double x1 = 0, x2 = 0;
    int number_of_roots = 0;

    solve_equation(test->a, test->b, test->c, &x1, &x2, &number_of_roots);

    if (!is_zero(x1 - test->right_x1))
    {
        printf("error in test %d (a = %lf; b = %lf; c = %lf): x1 = %lf, right_x1 = %lf\n", test_number, test->a, test->b, test->c, x1, test->right_x1);
    }
    if (!is_zero(x2 - test->right_x2))
    {
        printf("error in test %d (a = %lf; b = %lf; c = %lf): x2 = %lf, right_x2 = %lf\n", test_number, test->a, test->b, test->c, x2, test->right_x2);
    }
    if (number_of_roots != test->right_number_of_roots)
    {
        printf("expected: %d root(s), got: %d root(s)\n", test->right_number_of_roots, number_of_roots);
    }
}
