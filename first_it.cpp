#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>

const int    TEST_WRONG        =  0;
const double DELTA             =  1e-5;
const int    GOT_ONE_ARGUMENT  =  1;
const int    TESTS_QUANTITY    =  6;

enum INPUT_STATUS
{
    INPUT_IS_WRONG,
    INPUT_IS_OK
};

enum TEST_SUCCESS
{
    TEST_SUCCESSFUL,
    TEST_UNSUCCESSFUL
};

enum BUFFER_STATUS
{
    BUF_IS_CLEAN = 1,
    BUF_IS_DIRTY = 0
};

enum ROOTS_QUANTITY
{
    INF_NUMOF_ROOTS = -1,
    NO_ROOTS,
    ONE_ROOT,
    TWO_ROOTS
};

struct Mask_Coefs
{
    double a, b, c;
    double right_x1, right_x2;
    int right_number_of_roots;
};

void solve_begin();

void filter_input(double* variable, char c);
void solve_equation(double a, double b, double c, double* x1, double* x2, int* number_of_roots);
void filter_output(int n, double x1, double x2);

void auto_test();
void test_coef(int test_number, Mask_Coefs* test);

int is_zero(double number);

int clean_buf(void);

int main()
{
    printf("square equation solver\n\n");

    auto_test();
    printf("testing completed\n\n");

    solve_begin();

    return 0;
}

void solve_begin(){
    double a = 0, b = 0, c = 0;

    filter_input(&a, 'a');
    filter_input(&b, 'b');
    filter_input(&c, 'c');

    double x1 = 0, x2 = 0;
    int number_of_roots = 0;

    solve_equation(a, b, c, &x1, &x2, &number_of_roots);

    filter_output(number_of_roots, x1, x2);
}


// function that checks input
void filter_input(double* coef_adress, char coef_name)
{
    assert(coef_adress != NULL);

    int isclean_input = INPUT_IS_WRONG;

    printf("Enter coef %c: ", coef_name);

    while (!isclean_input)
    {
        isclean_input = INPUT_IS_OK;

        while (scanf("%lf", coef_adress) != GOT_ONE_ARGUMENT) // first symbol is not a digit
        {
            clean_buf();
            printf("\ninvalid input\n"
                   "enter existing value of %c: ", coef_name);
        }

        isclean_input = clean_buf();

        if (!isclean_input)
            printf("\ninvalid input\nenter existing value of %c: ", coef_name);
    }
}

int is_zero(double number)
{
    return fabs(number) < DELTA;
}

//solves equation, returns number of roots and their values
void solve_equation(double a, double b, double c, double* x1, double* x2, int* number_of_roots)
{
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));

    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(x1 != x2);

    assert(number_of_roots != NULL);

    if (is_zero(a))
    {
        if (is_zero(b))
        {
            if (is_zero(c))
                *number_of_roots = INF_NUMOF_ROOTS;
        }
        else
        {
            *number_of_roots = ONE_ROOT;
            if (is_zero(c))
            {
                *x1 = *x2 = 0;
            }
            else
            {
                *x1 = *x2 = -c / b;
            }

        }
    }
    else
    {
        double discriminant = b * b - 4 * a * c;
        if (is_zero(discriminant))
        {
            *number_of_roots = ONE_ROOT;
            *x1 = *x2 = -b / (2 * a);
        }
        else if (discriminant < 0)
        {
            *number_of_roots = NO_ROOTS;
        }
        else
        {
            *number_of_roots = TWO_ROOTS;        // todo temp var
            *x1 = (-b + sqrt(discriminant)) / (2 * a);
            *x2 = (-b - sqrt(discriminant)) / (2 * a);
        }
    }
}

//prints the answer for the equation
void filter_output(int number_of_roots, double x1, double x2)
{
    switch(number_of_roots)
    {
        case NO_ROOTS:
            printf("no roots\n");
            break;
        case ONE_ROOT:
            printf("one root: %lf\n", x1);
            break;
        case TWO_ROOTS:
            printf("two roots: x1 = %lf, x2 = %lf\n", x1, x2);
            break;
        case INF_NUMOF_ROOTS:
            printf("equation has infinite number of roots");
            break;
        default:
            printf("unknown error\n");
            break;
    }
}

//tests program with prepared coef-s

void auto_test()
{
    printf("auto_testing:\n");             //   a               b               c           right_x1    right_x2    right_number_of_roots

    struct Mask_Coefs tests[TESTS_QUANTITY] = {{1,              2,              1,         -1,         -1,          1},
                                               {0,              0,              0,          0,          0,          INF_NUMOF_ROOTS},
                                               {1,              4,              3,         -1,         -3,          2},
                                               {25.4343,        89.3124,       -64.45,      0.614195,  -4.12569,    2},
                                               {273.1645424,    13797.5455215, -12514.64,   0.891292,  -51.40131,   2},
                                               {0,              2.23432,        0,          0,          0,          1}};


    for (int i = 0; i < TESTS_QUANTITY; i++)
    {
        test_coef(i, &tests[i]);
    }
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

int clean_buf()
{
    int c = 0;

    int is_clean_buf = BUF_IS_CLEAN;

    while ((c = getchar()) != '\n')
    {                                  // todo isspace()
        if (!isspace(c))
        {
            is_clean_buf = BUF_IS_DIRTY;
        }
    }

    return is_clean_buf;
}


