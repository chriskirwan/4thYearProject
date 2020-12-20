set terminal png size 500,500
set output 'energy.png'
set title 'Energy vs Temperature'

plot "energy.dat" using 1:2 with lines
