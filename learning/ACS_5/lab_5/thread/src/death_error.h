#ifndef DEATH_ERROR_H

#define DEATH_ERROR_H
//macro for error

#define ERROR_ALLOCATION_MEMORY 0b00000001
#define ERROR_PARAMETR_FROM_MAIN 0b00000010
#define ERROR_QUANTITY_ARGUMENT_IN_MAIN 0b00000100
#define ERROR_OPEN_FILE_TABLE_TIME_TXT 0b00001000
#define ERROR_SIZE_MATRIX_TOO_LARGE 0b00010000
#define ERROR_PARAMETR_FOR_CHAR_TO_INT 0b00100000

//macro for constant
#define MINIMAL_QUANTITY_ARGUMENT_IN_MAIN 3

//macro for string and char
#define ADDITIONAL_RECORDING "a"
#define FILE_NAME_FOR_TABLE "table_time.txt"

#endif