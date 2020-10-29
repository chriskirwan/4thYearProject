# 4thYearProject
Code and report repository for my 4th Year final project

Compile the code using\
`gcc -o ising ising.c -lm -lgsl -lcblas`\
The last option is possibly optional. I needed it as BLAS from the GSL wouldn't link.\
The python script (to be changed to a `Bash` script at some point) is then used to iterate over the temperatures and then produce output.\
It is invoked by `python3 script.py`\
(Ensure that `numpy` is installed, but that may not be necessay in future revisions)\
To supress output and put it into a file, the script can be run as \
`python3 script.py > output.dat`\
`output.dat` is then used by `gnuplot` to plot the graphs.

To Do List:
- Get the Spin-Spin Correlation function plotting (I believe my function is correct)
- Remove the python dependency by invoking Bash (or better yet, make the temperature loop inside the code)
- Automate `gnuplot` plotting (invoke it in the code, removes extra comman line entry)
- Clean up the Git repo and my own directories
- Add links to notes/pdfs/lectures etc.
