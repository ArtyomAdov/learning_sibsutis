#!/usr/bin/gnuplot
set terminal png size 1000, 600 enhanced font 'Arial, 16'


set style line 1 linecolor rgb 'red' linetype 1 linewidth 2
set style line 2 linecolor rgb 'blue' linetype 1 linewidth 2
set style line 3 linecolor rgb 'green' linetype 1 linewidth 2
set style line 5 linecolor rgb 'yellow' linetype 1 linewidth 2
set style line 6 linecolor rgb 'brown' linetype 1 linewidth 2
set style line 4 linecolor rgb 'black' linetype 0 linewidth 2




set border linewidth 1
set key top left
set grid
set mytics 1


set yrange [0.1:3]
set xrange [0:8]




set logscale y
set format y "%.3f"
# set format y "%.2f"
set xlabel "Количество потоков" font "Arial, 16"
# set format x "%.f" 
set format x "%.0f"
set ylabel "Ускорение" font "Arial, 16"


set xtics font "Arial, 12"
set ytics font "Arial, 12"


set rmargin 4
set tmargin 2
set mxtics





set title "cmp"
set output 'cmp.png'

plot [*:*] [*:*] "data.txt" using 1:2 title "1 крит секция" with linespoints ls 1,\
	"data.txt" using 1:3 title "6 atomic" with linespoints ls 2,\
	"data.txt" using 1:4 title "n блокировок" with linespoints ls 3,\
	"data.txt" using 1:5 title "no block избыто вычис" with linespoints ls 5,\
	"data.txt" using 1:6 title "no block лока хране век" with linespoints ls 6
	# "data.txt" using 1:1 title "linear" with linespoints ls 4