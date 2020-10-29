set terminal png size 500,500
set output 'spont-magn.png'
set title '(Spontaneous) Magnetization vs Temperature'
plot "output.dat" using 1:2 w lp
