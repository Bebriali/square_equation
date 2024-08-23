#ifndef SOLVE_EQ
#define SOLVE_EQ

const int GOT_ONE_ARGUMENT  =  1;

enum INPUT_STATUS
{
    INPUT_IS_WRONG,
    INPUT_IS_OK
};

#ifndef ROOTS_Q
#define ROOTS_Q
enum ROOTS_QUANTITY
{
    INF_NUMOF_ROOTS = -1,
    NO_ROOTS,
    ONE_ROOT,
    TWO_ROOTS
};
#endif

#ifndef ZERO
#define ZERO
int is_zero(double number);
#endif

#ifndef CLEAN_B
#define CLEAN_B
int clean_buf();
#endif

void solve_begin();
void filter_input(double* variable, char c);

#ifndef SOLVE_EQ_FUNC
#define SOLVE_EQ_FUNC
void solve_equation(double a, double b, double c, double* x1, double* x2, int* number_of_roots);
#endif

void filter_output(int n, double x1, double x2);

#endif
