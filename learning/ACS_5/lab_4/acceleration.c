#include <stdio.h>

int main()
{
    FILE* file_r0 = NULL;
    FILE* file_r1 = NULL;
    FILE* file_r2 = NULL;
    FILE* file_w1 = NULL;
    FILE* file_w2 = NULL;
    double time_0 = 0.0;
    double time_1 = 0.0;
    double time_2 = 0.0;
    int size = 0;
    file_r0 = fopen("opt_0.txt","r");
    if(file_r0 == NULL)
    {
        return -1;
    }
    file_r1 = fopen("opt_1.txt","r");
    if(file_r1 == NULL)
    {
        return -1;
    }
    file_r2 = fopen("opt_2.txt","r");
    if(file_r2 == NULL)
    {
        return -1;
    }
    file_w1 = fopen("acc_1.txt","w");
    if(file_w1 == NULL)
    {
        return -1;
    }
    file_w2 = fopen("acc_2.txt","w");
    if(file_w2 == NULL)
    {
        return -1;
    }
    while(getc(file_r0) != '\n');
    while(getc(file_r1) != '\n');
    while(getc(file_r2) != '\n');
    do
    {
        fscanf(file_r0,"%d",&size);
        fscanf(file_r1,"%d",&size);
        fscanf(file_r2,"%d",&size);
        getc(file_r0);
        getc(file_r1);
        getc(file_r2);
        fscanf(file_r0,"%lf",&time_0);
        fscanf(file_r1,"%lf",&time_1);
        fscanf(file_r2,"%lf",&time_2);
        getc(file_r0);
        getc(file_r1);
        getc(file_r2);
        fprintf(file_w1,"%d %lf\n", size, (time_0/time_1));
        fprintf(file_w2,"%d %lf\n", size, (time_0/time_2));
    }while(!feof(file_r0));
    fclose(file_w1);
    fclose(file_w2);
    fclose(file_r0);
    fclose(file_r1);
    fclose(file_r2);
}