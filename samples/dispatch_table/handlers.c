#include <stdio.h>

int handle_ADD(int a, int b, int *x)
{
    printf("Addition Handler: %i + %i\n", a, b);
    *x = a + b;
    return 0;
}

int handle_SUB(int a, int b, int *x)
{
    printf("Subtraction Handler: %i - %i\n", a, b);
    *x = a - b;
    return 0;
}

int handle_MLT(int a, int b, int *x)
{
    printf("Multiplication Handler: %i * %i\n", a, b);
    *x = a * b;
    return 0;
}

int handle_DIV(int a, int b, int *x)
{
    printf("Division Handler: %i / %i\n", a, b);
    if (b == 0)
        return 1;
    else if (a % b != 0)
        return 2;
    else
    {
        *x = a / b;
        return 0;
    }    
}

int handle_MOD(int a, int b, int *x)
{
    printf("Modulus Handler: %i %% %i\n", a, b);
    if (b == 0)
        return 1;
    else
    {
        *x = a % b;
        return 0;
    }    
}
