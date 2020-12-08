#ifndef XY_H 

#define XY_H

void random_lattice(int L, gsl_rng*r, double F[][L]);
void cold_lattice(int L, double F[][L]); 
double random_flip(double a, gsl_rng*r); 
double flip_energy(int L, int i, int j, gsl_rng*r, double F[][L]); 
void metropolis_step(int L, gsl_rng*r, double T, double F[][L]); 

#endif 
