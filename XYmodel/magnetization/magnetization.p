set terminal png size 500,500
set output 'magnetization.png'
set title 'Magnetization Squared <M^2> vs MCS'

plot "magnetization.dat" using 1:2 with lines
