#ifndef ISING_H 

#define ISING_H

void random_lattice(int L, gsl_rng*r, int F[][L]);
void cold_lattice(int L, int F[][L]); 
int flip_energy(int L, int i, int j, int F[][L]); 
void sample(int L, double *mag, double *ergy, int F[][L]);
void metropolis_step(int L, gsl_rng*r, double T, int F[][L]); 
void spin_spin_correlation(int L, int d, int F[][L]); 

#endif 
