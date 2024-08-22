#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>

const int    TEST_WRONG      =  0;
const double DELTA             =  0.00001;
const int    INPUT_IS_WRONG    =  0;
const int    INPUT_IS_OK       =  1;
const int    SUCCESSFUL        =  1;
const int    UNSUCCESSFUL      =  0;
const int    IS_ZERO           =  0;
const int    IS_NOT_ZERO       =  1;
const int    BUF_IS_CLEAN      =  1;
const int    BUF_IS_DIRTY      =  0;
const int    GOT_ONE_ARGUMENT  =  1;
const int    TEST_SUCCESSFUL   =  1;
const int    TEST_UNSUCCESSFUL =  0;

enum
{
    INF_NUMOF_ROOTS = -1,
    NO_ROOTS,
    ONE_ROOT,
    TWO_ROOTS
};

struct Mask_Coefs
{
    int test_number;
    double a, b, c;
    double right_x1, right_x2;
    int right_number_of_roots;
};

void solve_begin();

void filter_input(double* variable, char c);
void solve_equation(double a, double b, double c, double* x1, double* x2, int* number_of_roots);
void filter_output(int n, double x1, double x2);

void auto_test();
int test_coef(Mask_Coefs test);

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

    while (!isclean_input){
        isclean_input = INPUT_IS_OK;

        while (scanf("%lf", coef_adress) != GOT_ONE_ARGUMENT) //first symbol is not a digit
        {
            clean_buf();
            printf("\ninvalid input\nenter existing value of %c: ", coef_name);
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
            *number_of_roots = TWO_ROOTS;
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
    printf("auto_testing:\n");

    Mask_Coefs test1 = {.test_number = 1, .a = 1, .b = 2, .c = 1, .right_x1 = -1, .right_x2 = -1, .right_number_of_roots = 1};
    Mask_Coefs test2 = {.test_number = 2, .a = 0, .b = 0, .c = 0, .right_x1 = 0, .right_x2 = 0, .right_number_of_roots = INF_NUMOF_ROOTS};
    Mask_Coefs test3 = {.test_number = 3, .a = 1, .b = 4, .c = 3, .right_x1 = -1, .right_x2 = -3, .right_number_of_roots = 2};
    Mask_Coefs test4 = {.test_number = 4, .a = 25.4343, .b = 89.3124, .c = -64.45, .right_x1 = 0.614195, .right_x2 = -4.12569, .right_number_of_roots = 2};
    Mask_Coefs test5 = {.test_number = 5, .a = 273.1645424, .b = 13797.5455215, .c = -12514.64, .right_x1 = 0.891292, .right_x2 = -51.40131, .right_number_of_roots = 2};
    Mask_Coefs test6 = {.test_number = 6, .a = 0, .b = 2.23432, .c = 0, .right_x1 = 0, .right_x2 = 0, .right_number_of_roots = 1};

    test_coef(test1);
    test_coef(test2);
    test_coef(test3);
    test_coef(test4);
    test_coef(test5);
    test_coef(test6);
}

int test_coef(Mask_Coefs test){
    double x1 = 0, x2 = 0;
    int number_of_roots = 0;

    int test_success = SUCCESSFUL;

    solve_equation(test.a, test.b, test.c, &x1, &x2, &number_of_roots);

    if (!is_zero(x1 - test.right_x1))
    {
        printf("error in test %d (a = %lf; b = %lf; c = %lf): x1 = %lf, right_x1 = %lf\n", test.test_number, test.a, test.b, test.c, x1, test.right_x1);
        test_success = UNSUCCESSFUL;
    }
    if (!is_zero(x2 - test.right_x2))
    {
        printf("error in test %d (a = %lf; b = %lf; c = %lf): x2 = %lf, right_x2 = %lf\n", test.test_number, test.a, test.b, test.c, x2, test.right_x2);
        test_success = UNSUCCESSFUL;
    }
    if (number_of_roots != test.right_number_of_roots)
    {
        printf("expected: %d root(s), got: %d root(s)\n", test.right_number_of_roots, number_of_roots);
        test_success = UNSUCCESSFUL;
    }

    return test_success;
}

int clean_buf()
{
    int c = 0;

    int is_clean_buf = BUF_IS_CLEAN;

    while ((c = getchar()) != '\n')
    {
        if (c != ' ' && c != '\t')
        {
            is_clean_buf = BUF_IS_DIRTY;
        }
    }

    return is_clean_buf;
}


