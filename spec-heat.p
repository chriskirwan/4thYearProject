set terminal png size 500,500
set output 'spec-heat.png'
set title 'Specific Heat Capacity'
plot "output.dat" using 1:5
