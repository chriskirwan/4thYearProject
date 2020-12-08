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
			F[i][j] = M_PI; 
		}
	}
}

double random_flip(double a, gsl_rng*r) {
	double new_flip = 2*M_PI*gsl_rng_uniform(r) - M_PI;  
	double new_flip_r = new_flip/a;
	return new_flip_r;
}	


double flip_energy(int L, int i, int j, double rnd, double F[][L]) {
	double da = rnd - F[i][j];
	double a = F[i][j];
   	double b = F[i?(i-1):(L-1)][j]; 
	double c = F[(i+1)%L][j];
	double d = F[i][j?(j-1):(L-1)]; 
	double e = F[i][(j+1)%L];

	double sum = 2*sin(da/2)*sin(a+da/2 - b) +
				2*sin(da/2)*sin(a+da/2 - c) +
				2*sin(da/2)*sin(a+da/2 - d) +
				2*sin(da/2)*sin(a+da/2 - e);
	return sum;     
}

void metropolis_step(int L, gsl_rng*r, double T, double F[][L]) {
	int i = (int)gsl_rng_uniform_int(r,L); 
	int j = (int)gsl_rng_uniform_int(r,L); 

	double a = 1.0; 
	double rnd = random_flip(a,r); 

	int de = flip_energy(L,i,j,rnd,F); 
	double b = exp(-de/T); 
	double x = gsl_rng_uniform(r); 

	if (b < 0) {
		F[i][j] = rnd;
	} else { 
		if (x<b) { 
			F[i][j] = rnd;
		} else { 
			F[i][j] = F[i][j]; 
		}
	}
}
