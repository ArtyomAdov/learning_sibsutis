#include "death_arg.h"
#include "death_error.h"

int Check_Argc(int argc)
{
    if(argc < MINIMAL_QUANTITY_ARGUMENT_IN_MAIN)
    {
        return 0;
    }
    return ERROR_QUANTITY_ARGUMENT_IN_MAIN;
}