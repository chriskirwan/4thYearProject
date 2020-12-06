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
			F[i][j] = 0; 
		}
	}
}

double random_flip(gsl_rng*r) {
	double new_flip = 2*M_PI*gsl_rng_uniform(r) - M_PI;  
	return new_flip;
}	


double flip_energy(int L, int i, int j, double rnd, double F[][L]) {
	double da = F[i][j] - rnd;
	double a = F[i][j];
   	double b = F[i?(i-1):(L-1)][j]; 
	double c = F[(i+1)%L][j];
	double d = F[i][j?(j-1):(L-1)]; 
	double e = F[i][(j+1)%L];

	double sum = sin(a-b + da/2) + sin(a-c + da/2) + sin(a-d + da/2) + sin(a-e + da/2); 
	double delta_energy = -2*sin(da/2)*sum; 	
	return delta_energy;     
}

void metropolis_step(int L, gsl_rng*r, double T, double F[][L]) {
	int i = (int)gsl_rng_uniform_int(r,L); 
	int j = (int)gsl_rng_uniform_int(r,L); 

	double rnd = random_flip(r); 

	int de = flip_energy(L,i,j,rnd,F); 
	double b = exp(de*(1.0)/T); 
	double x = gsl_rng_uniform(r); 

	if (b < 0) {
		F[i][j] = rnd;
	} else { 
		if (x<b) { 
			F[i][j] = rnd;
		}	
	}
}
