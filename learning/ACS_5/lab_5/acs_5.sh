#!/bin/bash
echo '#Quantity Thread | Time_Execute' > none/table_time.txt;
echo '#Quantity Thread | Time_Execute' > omp/table_time.txt;
echo '#Quantity Thread | Time_Execute' > thread/table_time.txt;
cd none;
# rm table_time.txt
make clean;
make;
cd ../omp;
# rm table_time.txt
make clean;
make;
cd ../thread;
# rm table_time.txt
make clean;
make;
cd ..;
for((i=2;i<9;i=i+1))
do
echo 'iteration start'
./none/bin/key 2000
echo 'none okey'
./omp/bin/key 2000 $i;
echo 'omp okey'
./thread/bin/key 2000 $i;
echo 'iteration end';
done
gcc -Wall -Werror -o keyacel acceleration.c
./keyacel
gnuplot draw_for_acceleration.plt
xdg-open acceleration.png