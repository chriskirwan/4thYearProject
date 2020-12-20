set terminal png size 500,500
set output 'autocorrelation_integrated.png'
set title 'Integrated Autocorrelation vs Tau'

a=0
cumulative_sum(x)= 0.5 + (a=a+x,a)
plot "autocorrelation.dat" using 1:(cumulative_sum($2)) with lines

