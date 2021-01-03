#!/bin/bash
rm opt_0.txt;
rm opt_1.txt;
rm opt_2.txt;
rm key;
touch opt_0.txt;
touch opt_1.txt;
touch opt_2.txt;
echo '#Size_Matrix | Time_Execute' >> opt_0.txt;
echo '#Size_Matrix | Time_Execute' >> opt_1.txt
echo '#Size_Matrix | Time_Execute' >> opt_2.txt;
gcc -Wall -Werror -o key acs_4.c;
for((i=1000;i<6000;i=i+1000))
do
./key $i N;
./key $i L;
./key $i B 125;
echo 'iteration end';
done
gnuplot draw_time.plt
xdg-open time_for_multiple.png