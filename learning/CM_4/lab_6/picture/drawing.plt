set terminal png size 1000, 700 font 'Verdana, 10'
set output 'picture/out.png'
set yrange [0:10]
set xrange [0:10]
set grid xtics ytics mytics
plot sqrt(x) lw 3 lt rgb 'red','picture/out.txt' using 1:2 with lines lw 5 lt rgb 'purple','picture/point.txt' using 1:2 with linespoints lw 5 lt rgb 'purple'
