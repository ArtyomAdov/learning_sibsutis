#!/usr/bin/gnuplot
set terminal png size 1000, 600 enhanced font 'Arial, 16'


set style line 1 linecolor rgb 'red' linetype 1 linewidth 2
set style line 2 linecolor rgb 'blue' linetype 1 linewidth 2
set style line 3 linecolor rgb 'green' linetype 1 linewidth 2
set style line 4 linecolor rgb 'black' linetype 0 linewidth 2




set border linewidth 1
set key top left
set grid
set mytics 1


set yrange [0:10]
set xrange [0:8]




# set logscale y
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





set title "MonteCarlo"
set output 'MonteCarlo.png'

plot [*:*] [*:*] "data.txt" using 1:2 title "10^7" with linespoints ls 1,\
	"data.txt" using 1:3 title "10^8" with linespoints ls 2,\
	"data.txt" using 1:1 title "linear" with linespoints ls 4







set title "Runge"
set output 'Runge.png'

plot [*:*] [*:*] "data_runge.txt" using 1:2 title "10^7" with linespoints ls 1,\
	"data_runge.txt" using 1:1 title "linear" with linespoints ls 4

