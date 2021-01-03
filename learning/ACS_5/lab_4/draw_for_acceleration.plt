set terminal png size 700, 500 font 'Verdana, 10'
set title 'Graph of acceleration versus matrix size'
set output 'acceleration.png'
#set xrange [1000:5000]
#set yrange [0:]
set xlabel 'length square matrix'
set ylabel 'acceleration'
set grid xtics ytics mytics
plot 'acc_1.txt' with lines lt rgb 'red', 'acc_1.txt' notitle with points lt rgb 'red', 'acc_2.txt' with lines lt rgb 'blue', 'acc_2.txt' notitle with points lt rgb 'blue'