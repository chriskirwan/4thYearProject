#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_rng.h>

void random_lattice(int L, gsl_rng*r, int F[][L]) {
	int i,j;

	for(i=0;i<L;i++) {
		for(j=0;j<L;j++) {
			F[i][j] = 2*(int)gsl_rng_uniform_int(r,2)-1;
		}
	}
}

void cold_lattice(int L, int F[][L]) {
	int i,j;

	for (i=0;i<L;i++) {
		for(j=0;j<L;j++) {
			F[i][j] = 1;
		}
	}
}

int flip_energy(int L, int i, int j, int F[][L]) {
	return -2*(F[i][j])*(F[i?(i-1):(L-1)][j] + F[(i+1)%L][j] + F[i][j?(j-1):(L-1)] + F[i][(j+1)%L]);
}

void sample(int L, double *mag, double *enrgy, int F[][L]) {
	int i,j; 

	*mag = 0.0;
	*enrgy = 0.0;

	for(i=0;i<L;i++) {
		for(j=0;j<L;j++) {
		*mag+= F[i][j];
	   	*enrgy-= F[i][j]*(F[(i+1)%L][j] + F[i][(j+1)%L]);
		}
	}
	*mag/=(L*L);
	*enrgy/=(L*L);
}


void metropolis_step(int L, gsl_rng*r, double T, int F[][L]) {	
	int i = (int)gsl_rng_uniform_int(r,L);
	int j = (int)gsl_rng_uniform_int(r,L); 

	int de = flip_energy(L,i,j,F);
	double b = exp(de*(1.0)/T); 
	double x = gsl_rng_uniform(r);

	if(x<b) {
		F[i][j] *= -1;
	}
}
