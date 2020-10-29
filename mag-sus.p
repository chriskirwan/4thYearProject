set terminal png size 500,500
set output 'magsus.png'
set title 'Magnetic Susceptibility'
plot "output.dat" using 1:4
