set terminal png size 700, 500 font 'Verdana, 10'
set title "Cache-misses for difference method"
set output 'cache.png'
set xrange [0:5]
set yrange [0:]
set xlabel "method optimization"
set ylabel "quantity cache-masses"
set grid xtics ytics mytics
set style fill solid 0.8 border -1
plot 'cach_missese.txt' notitle with boxes