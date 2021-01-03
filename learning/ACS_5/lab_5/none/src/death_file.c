#include "death_file.h"
#include "death_error.h"

#include <stdio.h>
#include <stdlib.h>

int Write_In_Table_Time(int quantity_thread, double value_time)
{
    FILE* file = NULL;
    file = fopen(FILE_NAME_TABLE_TIME_TXT, ADDITIONAL_RECORDING);
    if(file == NULL)
    {
        return ERROR_OPEN_FILE_TABLE_TIME_TXT;
    }
    fprintf(file,"%d\t%lf\n", quantity_thread, value_time);
    fclose(file);
    file = NULL;
    return 0;
}