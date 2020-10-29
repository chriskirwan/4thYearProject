set terminal png size 500,500
set output 'energy.png'
set title 'Energy vs. Temperature'
plot "output.dat" using 1:3
