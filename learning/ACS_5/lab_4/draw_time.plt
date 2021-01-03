set terminal png size 700, 500 font 'Verdana, 10'
set title 'Graph of execution time versus matrix size'
set output 'time_for_multiple.png'
#set xrange [1000:5000]
#set yrange [0:]
set xlabel 'length square matrix'
set ylabel 'time for multiple'
set grid xtics ytics mytics
plot 'opt_0.txt' with lines lt rgb 'red', 'opt_0.txt' notitle with points lt rgb 'red', 'opt_1.txt' with lines lt rgb 'blue', 'opt_1.txt' notitle with points lt rgb 'blue', 'opt_2.txt' with lines lt rgb 'purple', 'opt_2.txt' notitle with points lt rgb 'purple'