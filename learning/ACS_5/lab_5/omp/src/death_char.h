#ifndef DEATH_CHARH

#define DEATH_CHAR_H

#define DIGIT_CAPACITY_IN_DECIMAL 10

#define FIRST_CODE_SYMBOL_BY_DIGIT 0x30
#define LAST_CODE_SYMBOL_BY_DIGIT 0x39
#define CONVERT_CODE_SYMBOL_BY_DIGIT_IN_NUMBER 0x0F

int Convert_Char_To_Int(int* value_integer, char value_char[]);

#endif