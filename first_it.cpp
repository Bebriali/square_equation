#include <stdio.h>
#include <math.h>
#include <assert.h>

const int INF_NOF_ROOTS = -1;
void enter(double* variable, char c);
void solve_equation(double a, double b, double c, double* x1, double* x2, int* nRoots);
void out(int n, double x1, double x2);

int main(){
    printf("square equation solver\n\n");

    double a = 0, b = 0, c = 0;
    enter(&a, 'a');
    enter(&b, 'b');
    enter(&c, 'c');

    double x1 = 0, x2 = 0;

    int nRoots = 0;
    solve_equation(a, b, c, &x1, &x2, &nRoots);

    out(nRoots, x1, x2);

    return 0;
}

void enter(double* variable, char var){
    printf("Enter coef %c: ", var);
    scanf("%lf", variable);
    printf("\n");
}

void solve_equation(double a, double b, double c, double* x1, double* x2, int* nRoots){
//    assert(std::isfinite(a));
//    assert(std::isfinite(b));
//    assert(std::isfinite(c));

    assert(x1 != NULL);
    assert(x2!= NULL);
    assert(x1 != x2);

    if (a == 0){
        if (b == 0){
            if (c == 0)
                *nRoots = INF_NOF_ROOTS;
        }
        else{
            *nRoots = 1;
            *x1 = *x2 = -c/b;
        }
    }
    else{
        double d = b * b - 4 * a * c;
        if (d == 0){
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
