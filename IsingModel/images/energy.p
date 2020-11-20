set terminal png size 500,500
set output 'energy.png'
set title 'Energy (per site) vs. Temperature'

const = 2.269

set arrow from const,0 to const,1 nohead
plot "energy_full_dataset.dat" using 1:7:8 with yerrorbars
