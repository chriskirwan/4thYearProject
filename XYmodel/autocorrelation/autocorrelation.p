set terminal png size 500,500
set output 'autocorrelation.png'
set title 'Autocorrelation vs Tau'

plot "autocorrelation.dat" using 1:2 with lines
