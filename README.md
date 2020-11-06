# 4th Year Project
Code and report repository for my 4th Year final project (as of yet untitled)

Compile the code using\
`gcc -o ising ising.c -lm -lgsl -lcblas`\
The last option is possibly optional. I needed it as BLAS from the GSL wouldn't link.\
The python script (to be changed to a `Bash` script at some point) is then used to iterate over the temperatures and then produce output.\
It is invoked by `python3 script.py`\
(Ensure that `numpy` is installed, but that may not be necessay in future revisions)\
To supress output and put it into a file, the script can be run as \
`python3 script.py > graphs.dat`\
`graphs.dat` is then used by `gnuplot` to plot the graphs.

To Do List:
- Spin-Spin Correlation functions (both G(r) and G(t)) for various lattice sizes (20x20 done) and temperatures
- Jackknife errors (Currently using Binder & Heerman and converting example `R` code to `C`)
- Merge the changes to allocating memory made in `sscor.c`to `ising.c`
- Clean up code (making headers for the spin models)
- Remove the python dependency by invoking Bash (or better yet, make the temperature loop inside the code)
- Automate `gnuplot` plotting (invoke it in the code, removes extra comman line entry)
- Clean up the Git repo and my own directories
- Add links to notes/pdfs/lectures etc.
