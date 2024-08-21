#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>

#define LIM 100
const int INF_NOF_ROOTS = -1;
void enter(double* variable, char c);
void solve_equation(double a, double b, double c, double* x1, double* x2, int* nRoots);
void out(int n, double x1, double x2);

int test_coef(int test_num, double a, double b, double c, double right_x1, double right_x2, int right_nRoots);

int main(){
    printf("square equation solver\n\n");

// tests
    printf("auto_testing:\n");

    int success = 1;

    success = test_coef(1, 1, 2, 1, -1, -1, 1);
    if (!success){
        printf("unsuccessful test 1\n");
        return 0;
    }
    success = test_coef(2, 0, 0, 0, 0, 0, INF_NOF_ROOTS);
    if (!success){
        printf("unsuccessful test 2\n");
        return 0;
    }
    success = test_coef(3, 1, 4, 3, -1, -3, 2);
    if (!success){
        printf("unsuccessful test 3 \\'_'/\n");
        return 0;
    }
    success = test_coef(4, 25.4343, 89.3124, -64.45, 0.614195, -4.12569, 2);
    if (!success){
        printf("unsuccessful test 4 \\'_'/\n");
        return 0;
    }
    success = test_coef(5, 273.1645424, 13797.5455215, -12514.64, 0.891292, -51.40131, 2);
    if (!success){
        printf("unsuccessful test 5 \\'-'/\n");
        return 0;
    }

    printf("successful\n\n");
 // tests ending

    double a = 0.0/0.0, b = 0.0/0.0, c = 0.0/0.0;
    enter(&a, 'a');
    enter(&b, 'b');
    enter(&c, 'c');

    double x1 = 0, x2 = 0;

    int nRoots = 0;
    solve_equation(a, b, c, &x1, &x2, &nRoots);

    out(nRoots, x1, x2);

    return 0;
}

// function that checks input
void enter(double* variable, char var){
    int fl = 1;
    printf("Enter coef %c: ", var);
    int c = 0;
    while (fl){
        fl = 0;
        while (scanf("%lf", variable) != 1) // first symbol is not a digit
        {
            while((c = getchar()) != '\n'); //skip all symbols to the next line
            printf("\ninvalid input\nenter existing value of %c: ", var);
        }
        while((c = getchar()) != '\n')  // first symbol is a digit (scanf read it)
        {
            if (c != '\t' && c != ' ') // checking full input except for the number read by scanf
            {
                fl = 1;
            }
        }
        if (fl)
            printf("\ninvalid input\nenter existing value of %c: ", var);
    }
}

//solves equation, returns number of roots and their values
void solve_equation(double a, double b, double c, double* x1, double* x2, int* nRoots){
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));

    assert(x1 != NULL);
    assert(x2!= NULL);
    assert(x1 != x2);

    double delta = 0.00001;

    if (a > -delta && a < delta){
        if (b > -delta && a < delta){
            if (c > -delta && c < delta)
                *nRoots = INF_NOF_ROOTS;
        }
        else{
            *nRoots = 1;
            *x1 = *x2 = -c/b;
        }
    }
    else{
        double d = b * b - 4 * a * c;
        if (d > -delta && d < delta){
            *nRoots = 1;
            *x1 = *x2 = -b / 2 / a;
        }
        else if (d < 0){
            *nRoots = 0;
        }
        else{
            *nRoots = 2;
            *x1 = (-b + sqrt(d)) / 2 / a;
            *x2 = (-b - sqrt(d)) / 2 / a;
        }
    }
}

//prints the answer for the equation
void out(int nRoots, double x1, double x2){
    switch(nRoots){
        case 0:
            printf("no roots\n");
            break;
        case 1:
            printf("one root: %lf\n", x1);
            break;
        case 2:
            printf("two roots: x1 = %lf, x2 = %lf\n", x1, x2);
            break;
        case INF_NOF_ROOTS:
            printf("equation has infinite number of roots");
            break;
        default:
            printf("unknown error");
            break;
    }
}

//tests program with prepared coef-s
int test_coef(int test_num, double a, double b, double c, double right_x1, double right_x2, int right_nRoots){
    double x1 = 0, x2 = 0;
    int nRoots = 0;
    int test_success;
    solve_equation(a, b, c, &x1, &x2, &nRoots);
    int nerror = 1;
    double delta = 0.00001;
    if (x1 - right_x1 < -delta || x1 - right_x1 > delta){
        printf("error %d in test %d (a = %lf; b = %lf; c = %lf): x1 = %lf, right_x1 = %lf\n", nerror++, test_num, a, b, c, x1, right_x1);
        test_success = 0;
    }
    if (x2 - right_x2 < -delta || x2 - right_x2 > delta){
        printf("error %d in test %d (a = %lf; b = %lf; c = %lf): x2 = %lf, right_x2 = %lf\n", nerror++, test_num, a, b, c, x2, right_x2);
        test_success = 0;
    }
    if (nRoots != right_nRoots){
        printf("expected: %d root(s), got: %d root(s)\n", right_nRoots, nRoots);
        test_success = 0;
    }

    return test_success;
}
