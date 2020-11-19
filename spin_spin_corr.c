#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <gsl/gsl_rng.h>
#include "ising.h"

double spin_spin_corr(int L, int d, int F[][L]) {
	int i,j; 
	int sigma_i = 0, sigma_j = 0; 
	int sum_1 = 0, sum_2 = 0, sum_3 = 0;
   	double avg_1, avg_2; 		

	for(i=0;i<L;i++) { 
		for(j=0;j<L;j++) {
			sigma_i = F[i][j];
			sigma_j = F[i][(j+d)%L] + F[i][((j-d)>-1)?(j-d):(L-d)]
					+ F[(i+d)%L][j] + F[((i-d)>-1)?(i-d):(L-d)][j];

			sum_1 += sigma_i*sigma_j;
			sum_2 += sigma_i;
			sum_3 += sigma_j;
		}
	}	
	avg_1 = (float)sum_1 / (4*L*L); 
	avg_2 = ((float)sum_2/(L*L))*((float)sum_3/(4*L*L)); 
	
	return avg_1 - avg_2; 
}

int main(int argc, char*argv[]) {
	int L = 40;
	int i,j;
	double T = 2.7;
	int N = L*L; 
	int monte_carlo_steps= 100000;
	int sample_frequency = 100;

	int (*F)[L] = malloc(sizeof(int([L][L]))); 

	gsl_rng *r = gsl_rng_alloc(gsl_rng_mt19937);
	unsigned long int seed = (unsigned)time(NULL); 
	gsl_rng_set(r, seed); 	
	
	cold_lattice(L,F);
	
	for(i=0;i<monte_carlo_steps;i++) {
		for(j=0;j<N;j++) {
			metropolis_step(L,r,T,F);
		}
	}

	int d;
   	for(d=0;d<(L/2);d++) {	
		double ans = spin_spin_corr(L,d,F);
		printf("radius=%d corr=%f \n",d,ans);
	}
free(F); 
}

