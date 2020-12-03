set terminal png size 512,512

set output 'rnd_lat_hm.png'
set title 'Random Lattice for XY model (as heatmap)'

set border linewidth 0
unset key
unset colorbox
unset tics
set lmargin screen 0.1
set rmargin screen 0.9
set tmargin screen 0.9
set bmargin screen 0.1

plot 'random_lattice.dat' matrix with image
