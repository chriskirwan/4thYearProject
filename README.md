# 4th Year Project
Code and report repository for my 4th Year final project (as of yet untitled)

Compile the code using\
`gcc -o ising main_function.c ising.c -lm -lgsl -lcblas`\
The last option is possibly optional. I needed it as BLAS from the GSL wouldn't link.\
Pipe the output of each program to a `.dat` file for plotting in `gnuplot`.\
Or use the `bash` and `awk` scripts to automatically plot it.

To Do List:
- XY Model Susceptibility, Energy, Autocorrelations.
- Finite Lattice Size Effects
- Continue working on Report
- Other Spin Models (Discussion on what ones)
