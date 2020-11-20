set terminal png size 500,500
set output 'auto_corr.png'
set title 'Autocorrelation vs Monte-Carlo time'


plot "auto_corr_full_dataset.dat" using 1:7:8 with yerrorbars
