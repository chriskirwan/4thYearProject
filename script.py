import numpy as np
import subprocess
x = np.arange(0.1,5.0,0.01)
for i in x:
    output = subprocess.run(["./ising", "-L", "20", "-T", "%.5f" %i, "-nc", "20000", "-fs", "100"])
