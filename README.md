# 4th Year Project
Code and report repository for my 4th Year final project (as of yet untitled)

Compile the code using\
`gcc -o ising main_function.c ising.c -lm -lgsl -lcblas`\
The last option is possibly optional. I needed it as BLAS from the GSL wouldn't link.\
Pipe the output of each program to a `.dat` file for plotting in `gnuplot`.\

To Do List:
- Jackknife errors (Done, just need to get it working with `gnuplot`)
- Redo the graphs so that they are organized properly (Labels, cleanliness etc.)
- Finite Lattice Size Effects
- Project Layout
- Add links to notes/pdfs/lectures etc.
- Other Spin Models (Discussion on what ones)
