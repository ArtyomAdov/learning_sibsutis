#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

#define MAX_CATEGORY_NUMBER_INT 11
#define QUANTITY_DIGIT 10
// #define 

int Determination_Quantity_Digit(int temp)
{   
    int g = 1;// все хуйня надо сравнивать именно с 100 и если меньше то реттерн 2
    for(short int i = 1; i < MAX_CATEGORY_NUMBER_INT; i++)
    {
        g = (g * QUANTITY_DIGIT); // заменить на макросы цифры
        //g = (g * 10 + 9);// на один разряд убегает вперед мб попробовать 9999 а не 1000 че нить такое с больше и равно
        // printf("%d == %d\n", temp, g);
        if(temp < g) // if(!(temp / (10 * i))) nado 10 ^ i
        {
            return i;
        }
    }
    return 0;
}

int Convert_Index(char** index, int temp)
{//можно сделать конверт через файл типо записать число фврайт и потом считать фридом или даже путсом
    // do
    // {
    //     number = (temp % 10);
    //     temp = (temp / 10);
    // } while(temp != NULL);
    int category_number = 0;
    category_number = Determination_Quantity_Digit(temp);
    *index = (char*) calloc (category_number, sizeof(char));
    // printf("%d\n", category_number);
    for(short int i = category_number - 1; i >= 0; i--) // этот цикл нуждается в ускорении
    {
        // printf("zahel\n");
        for(short int j = 0; j < QUANTITY_DIGIT; j++)
        {
            // printf("zaheljjjj\n");
            if((temp % QUANTITY_DIGIT) == j)
            {
                (*index)[i] = ('0' + j);
                break;
            }
        }
        temp = (temp / QUANTITY_DIGIT);
        // printf("%c", (*index)[i]);
        // switch ((temp / 10))
        // {
        
        // case (1):
        //     /* code */
        //     break;
        
        // default:
        //     break;
        // }

    }
    printf("\n");
    return 0;
}

int main()
{
    pid_t parent_pid;
    pid_t child_pid;
    // char* index = NULL;
    char index[4];
    index[0] = 'k';
    index[1] = 'e';
    index[2] = 'y';
    int error_flag = 0b0;
    int temp = 0;
    temp = (int)getpid();
    // error_flag = (error_flag | Convert_Index(&index, temp));
    fprintf(stdout, "%s\n", index);
    // child_pid = fork();
    // int index_2 = (int)getpid();
    // Convert_index(index_2);
// index - convert to char arr 
    // fprintf(stdout,"%s !!! %s\n",index_1, index_2);
    system("ps -p \"^$index\" -o command="); // сделать как то так чтобы он не считал кавычки как кавычки т.е. намутить кавычки в кавычках типо "1"3\"4"2
    system("ps -p 3694");
    printf("\n");
    // system("ps | grep -o \"^$index\"");//
    // system("ps | grep -o \"^$index\"");
    // system("ps -o user,args,group -p \"^$temp\"");
    // system("ps | grep -o ^$index");
    // system("ps | grep 'key'");
    //  kill(parent_pid,SIGTERM);
    // system("ps");
    // fprintf(stdout,"clear");
    return error_flag;
}
