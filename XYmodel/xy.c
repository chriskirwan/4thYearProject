#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include <gsl/gsl_rng.h>



void random_lattice(int L, gsl_rng*r, double F[][L]) { 
	int i,j; 

	for(i=0;i<L;i++) {
		for(j=0;j<L;j++) {
			F[i][j] = 2*M_PI*gsl_rng_uniform(r) - M_PI; 
		}
	}
}

void cold_lattice(int L, double F[][L]) {
	int i,j;

	for(i=0;i<L;i++) {
		for(j=0;j<L;j++) {
			F[i][j] = 1; 
		}
	}
}

double random_flip(gsl_rng*r) {
	double new_flip = 2*M_PI*gsl_rng_uniform(r) - M_PI; 
	return new_flip;
}	


double flip_energy(int L, int i, int j, double F[][L]) { 
}

void metropolis_step(int L, gsl_rng*r, double T, double F[][L]) {
	int i = (int)gsl_rng_uniform_int(r,L); 
	int j = (int)gsl_rng_uniform_int(r,L); 

	int de = flip_energy(L,i,j,F); 
	double b = exp(de*(1.0)/T); 
	double x = gsl_rng_uniform(r); 

	if(x < b) {
		F[i][j] == random_flip(r); 
	}
}
