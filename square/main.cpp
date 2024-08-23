#include <stdio.h>
#include "solve_equation.h"
#include "tester.h"

int main(int argc, char *argv[])
{
    printf("\n\n"
            "square equation solver\n\n");

    for (int i = 1; i < argc; i++)
    {
        switch(*argv[i])
        {
            case 'u':
                auto_test();
                break;
            case 's':
                solve_begin();
                break;
            default:
                printf("unknown command: %c\n\n", *argv[i]);
                break;
        }

    }

    return 0;
}




