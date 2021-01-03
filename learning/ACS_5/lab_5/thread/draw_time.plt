set terminal png size 700, 500 font 'Verdana, 10'
set title 'Graph of execution time versus quantity thread'
set output 'graphic_time.png'
#set xrange [1000:3000]
#set yrange [0:]
set xlabel 'quantity thread'
set ylabel 'time for multiple'
set grid xtics ytics mytics
plot 'table_time.txt' with lines lt rgb 'red', 'table_time.txt' notitle with points lt rgb 'red'