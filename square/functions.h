#ifndef FUNCTIONS
#define FUNCTIONS

const double DELTA  =  1e-5;

enum BUFFER_STATUS
{
    BUF_IS_CLEAN = 1,
    BUF_IS_DIRTY = 0
};

#ifndef ZERO
#define ZERO
int is_zero(double number);
#endif

#ifndef CLEAN_B
#define CLEAN_B
int clean_buf();
#endif

#endif
