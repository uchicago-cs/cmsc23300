#include <stdlib.h>
#include <stdio.h>
#include "handlers.h"

typedef int (*handler_function)(int a, int b, int *x);

struct handler_entry
{
    char *name;
    handler_function func;
};

#define HANDLER_ENTRY(NAME) { #NAME, handle_ ## NAME}

struct handler_entry handlers[] = {
                                     HANDLER_ENTRY(ADD), 
                                     HANDLER_ENTRY(SUB), 
                                     HANDLER_ENTRY(MLT), 
                                     HANDLER_ENTRY(DIV), 
                                  };

int num_handlers = sizeof(handlers) / sizeof(struct handler_entry);

int main(int argc, char **argv)
{
    char *code;
    int a, b, x, rc, i;

    if(argc!=4)
    {
        fprintf(stderr, "Usage: %s strcode a b\n", argv[0]);
        return 1;
    }

    code = argv[1];   
    a = atoi(argv[2]);   
    b = atoi(argv[3]);   

    for(i=0; i<num_handlers; i++)
        if (!strcmp(handlers[i].name, code))
        {
            rc = handlers[i].func(a, b, &x);
            printf("Result: %i (rc = %i)\n", x, rc);
            break;
        }

    if(i == num_handlers)
    {
        fprintf(stderr, "Unknown handler code %s\n", code);
        return 2;
    }

    return 0;
}
