set terminal png size 500,500
set output 'magnetization.png'
set title 'Magnetization (per site) vs. Temperature'
set yrange[0:1]

const = 2.269

set arrow from const,0 to const,1 nohead
plot "magnetization_full_dataset.dat" using 1:7:8 with yerrorbars
