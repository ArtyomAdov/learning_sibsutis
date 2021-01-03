set terminal png size 700, 500 font 'Verdana, 10'
set title 'Graph of execution time versus block size'
set output 'time_for_block.png'
#set xrange [1000:5000]
#set yrange [0:]
set xlabel 'block size'
set ylabel 'time for multiple'
set grid xtics ytics mytics
plot 'opt_block_size.txt' with lines lt rgb 'green','opt_block_size.txt' notitle with points lt rgb 'red'