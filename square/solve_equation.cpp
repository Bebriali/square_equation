#include <assert.h>
#include <stdio.h>
#include <math.h>
#include "solve_equation.h"


void solve_begin()
{
    double a = 0, b = 0, c = 0;

    printf("Enter coeffitions for a * x^2 + b * x + c = 0 equation\n\n");

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
            printf("invalid input\n"
                   "enter existing value of %c: ", coef_name);
        }

        isclean_input = clean_buf();

        if (!isclean_input)
            printf("invalid input\n"
                   "enter existing value of %c: ", coef_name);
    }
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
            printf("no roots\n\n");
            break;
        case ONE_ROOT:
            printf("one root: %lf\n\n", x1);
            break;
        case TWO_ROOTS:
            printf("two roots: x1 = %lf, x2 = %lf\n\n", x1, x2);
            break;
        case INF_NUMOF_ROOTS:
            printf("equation has infinite number of roots\n\n");
            break;
        default:
            printf("unknown error\n\n");
            break;
    }
}
