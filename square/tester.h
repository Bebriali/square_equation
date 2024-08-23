#ifndef TESTER
#define TESTER

const int TESTS_QUANTITY =  7;

struct Mask_Coefs
{
    double a, b, c;
    double right_x1, right_x2;
    int right_number_of_roots;
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


void auto_test();

void test_coef(int test_number, Mask_Coefs* test);

#ifndef SOLVE_EQ_FUNC
#define SOLVE_EQ_FUNC
void solve_equation(double a, double b, double c, double* x1, double* x2, int* number_of_roots);
#endif

#endif
