#include "death_char.h"
#include "death_error.h"

int Convert_Char_To_Int(int* value_integer, char value_char[])
{
    for(short int i = 0; value_char[i] != '\0'; i++)
    {
        if((value_char[i] >= FIRST_CODE_SYMBOL_BY_DIGIT) && (value_char[i] <= LAST_CODE_SYMBOL_BY_DIGIT))
        {
            (*value_integer) = ((*value_integer) + (int)(value_char[i] & CONVERT_CODE_SYMBOL_BY_DIGIT_IN_NUMBER));
            (*value_integer) = ((*value_integer) * DIGIT_CAPACITY_IN_DECIMAL);
        }
    }
    (*value_integer) = ((*value_integer) / DIGIT_CAPACITY_IN_DECIMAL);
    if((*value_integer) > 0)
    {
        return 0;
    }
    return ERROR_PARAMETR_FOR_CHAR_TO_INT;
}