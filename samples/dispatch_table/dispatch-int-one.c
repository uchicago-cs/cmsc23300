#include <stdlib.h>
#include <stdio.h>
#include "handlers.h"

int main(int argc, char **argv)
{
    int code, a, b, x, rc;

    if(argc!=4)
    {
        fprintf(stderr, "Usage: %s intcode a b\n", argv[0]);
        return 1;
    }

    code = atoi(argv[1]);   
    a = atoi(argv[2]);   
    b = atoi(argv[3]);   

    switch(code)
    {
        case 0:
            rc = handle_ADD(a, b, &x);
            break;
        case 1:
            rc = handle_SUB(a, b, &x);
            break;
        case 2:
            rc = handle_MLT(a, b, &x);
            break;
        case 3:
            rc = handle_DIV(a, b, &x);
            break;
        default:
            fprintf(stderr, "Unknown handler code %i\n", code);
            return 2;
            break;            
    }

    printf("Result: %i (rc = %i)\n", x, rc);

    return 0;
}
