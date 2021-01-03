#include "cpu.h"

#include <string.h>

int CU()
{
	int value = 0;
	int command = 0;
	int operand = 0;
	int local_value = 0;

	sc_memoryGet(instructionCounter, &value);

	if (sc_commandDecode(value, &command, &operand)) {
		sc_regSet(E, 1);
		sc_regSet(T, 1);
		return 1;
	}

//	#if 0
	mt_gotoXY(23, 1);
	printf("Value %d\n", value);
	printf("Command %.2x\n", command);
	printf("Operand %.2x\n", operand);
	sleep(2);
//	#endif
	int f = 0;
	if (command >= 0x30 && command <= 0x33) {
		ALU(command, operand);
	} else {
		// #if 0
		mt_gotoXY(23, 1);
		printf("___________________\n");
		printf("___________________\n");
		printf("___________________\n");
		printf("___________________\n");
		printf("___________________\n");
		// #endif
//НОТ Двоичная инверсия слова в аккумуляторе и занесение результата в указанную ячейку памяти
//ЭНД Логическая операция И между содержимым аккумулятора и словом по указанному адресу
// (результат в аккумуляторе)
//ОР Логическая операция ИЛИ между содержимым аккумулятора и словом по указанному адресу
// (результат в аккумуляторе)
		f = 0;
		switch (command)
		{
			case (READ):
			{	
				printf("> ");
            	char inputValue[30]; 
             	scanf("%s", inputValue);
            	int check = 0, num = 0;
            	if(inputValue[0] == '+' || inputValue[0] == '-') check = 1; 
            	for(int i = check; i < strlen(inputValue); i++){ 
					if(!(inputValue[i] >= '0' && inputValue[i] <= '9')) 
						f = 1; //
				}
				num = atoi(inputValue);
				printf("num10 %d == num16 %x",num,num);
				fflush(stdout);
				sleep(5); 
				if(!check && num <= 8191) 
				{	printf("ONE");
					sc_memorySet(operand, ((num & 8191))); 
				}
				if(check && num < 0 && abs(num) <= 8191) 
				{	printf("TWO");
					sc_memorySet(operand,((abs(num) & 8191) + 24576)); 
				}
				if(check && num > 0 && num <= 16383) 
					{printf("THREE");
					sc_memorySet(operand, ((num & 8191) + ( 1 << 14))); 
					}
					if(!f) instructionCounter++;
				break;
			}
			case (WRITE):
			{
				printf("< ");
				sc_memoryGet(operand, &local_value);
				if((local_value >> 13) & 1) { 
					printf("-%d\n", local_value & 8191);
				} else
				{
					printf("%d\n", local_value & 8191);
					fflush(stdout);
					sleep(5);
				}
				break;
			}
			case (LOAD):
			{
				sc_memoryGet(operand, &accumulator);
				break;
			}
			case (STORE):
			{
				sc_memorySet(operand, accumulator);
				accumulator = 0;
				break;
			}
			case (JUMP):
			{
				if((operand - 1 < 0) || (operand - 1 > 99 ))
				{
					sc_regSet(M,1);
				}
				instructionCounter = operand - 1;
				break;
			}
			case (JNEG):
			{
				if((accumulator >> 14) == 1){
					if(((accumulator >> 13 ) & 1) == 1){
						if(operand-1 < 64){
							instructionCounter=operand-1;
						}
						else{
							sc_regSet(M, 1);
						}
					}
				}
				break;
			}
			case (JZ):
			{
				if((accumulator >> 14)==1){
					if(((accumulator >> 13) & 1) == 0){
						if((accumulator & 8191) == 0){
							if((operand-1) < 64){
								instructionCounter=operand-1;
							}
							else{
								sc_regSet(M, 1);
							}
						}
					}
				}
				break;
			}
			case (HALT):
			{
				sc_regSet(T, 0);
				return 1;
				break;
			}
		}
	}
	return 0;
}



int ALU(int command, int operand)
{
    int local_value, a, b;
    sc_memoryGet(operand, &local_value);
    switch (command) {
    case (ADD): {
        if (local_value >> 14 == 1 && accumulator >> 14 == 1) {
            b = local_value >> 13 & 1;
            a = accumulator >> 13 & 1;
            if (a == b) {
                if ((accumulator & 8191) + (local_value & 8191) > 8191) {
                    sc_regSet(P, 1);
                    return -1;
                } else {
                    accumulator = (accumulator & 8191) + (local_value & 8191)
                            + (1 << 14) + (a << 13);
                    break;
                }
            } else {
                if ((accumulator & 8191) > (local_value & 8191)) {
                    accumulator = (accumulator & 8191) - (local_value & 8191)
                            + (1 << 14) + (a << 13);
                    break;
                }
                if ((accumulator & 8191) < (local_value & 8191)) {
                    accumulator = (local_value & 8191) - (accumulator & 8191)
                            + (1 << 14) + (b << 13);
                    break;
                }
                if ((accumulator & 8191) == (local_value & 8191)) {
                    accumulator = (local_value & 8191) - (accumulator & 8191)
                            + (1 << 14);
                    break;
                }
            }
        }
        return -1;
    }
    case (SUB): {
        if (local_value >> 14 == 1 && accumulator >> 14 == 1) {
            a = accumulator >> 13 & 1;
            b = local_value >> 13 & 1;
            if (a == b) {
                if (b == 0) {
                    b = 1;
                } else {
                    b = 0;
                }
                if ((accumulator & 8191) > (local_value & 8191)) {
                    accumulator = (accumulator & 8191) - (local_value & 8191)
                            + (1 << 14) + (a << 13);
                    break;
                }
                if ((accumulator & 8191) < (local_value & 8191)) {
                    accumulator = (local_value & 8191) - (accumulator & 8191)
                            + (1 << 14) + (b << 13);
                    break;
                }
                if ((accumulator & 8191) == (local_value & 8191)) {
                    accumulator = (local_value & 8191) - (accumulator & 8191)
                            + (1 << 14);
                    break;
                }
            } else {
                if ((accumulator & 8191) + (local_value & 8191) > 8191) {
                    sc_regSet(P, 1);
                    return -1;
                } else {
                    accumulator = (accumulator & 8191) + (local_value & 8191)
                            + (1 << 14) + (a << 13);
                    break;
                }
            }
        }
        return -1;
    }
    case (MUL): {
        if (local_value >> 14 == 1 && accumulator >> 14 == 1) {
            a = accumulator >> 13 & 1;
            b = local_value >> 13 & 1;
            if ((accumulator & 8191) * (local_value & 8191) > 8191) {
                sc_regSet(P, 1);
                return -1;
            } else {
                if (a == b) {
                    accumulator = (accumulator & 8191) * (local_value & 8191)
                            + (1 << 14);
                    break;
                } else {
                    accumulator = (accumulator & 8191) * (local_value & 8191)
                            + (3 << 13);
                    break;
                }
            }
        }
        return -1;
    }
    case (DIVIDE): {
        if ((local_value >> 14 == 1) && (accumulator >> 14 == 1)) {
            if ((local_value & 8191) == 0) {
                sc_regSet(O, 1);
                return -1;
            } else if (((local_value >> 13) & 1) == ((accumulator >> 13) & 1)) {
                accumulator = (accumulator & 8191) / (local_value & 8191)
                        + (1 << 14);
            } else
                accumulator = (accumulator & 8191) / (local_value & 8191)
                        + (1 << 13) + (1 << 14);
        } else
            return -1;
        break;
    }
    }
    return 1;
}
