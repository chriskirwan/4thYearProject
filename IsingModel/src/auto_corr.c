#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <gsl/gsl_rng.h>
#include "ising.h"

double auto_corr(int L, int F[][L], int G[][L]) {
	int i,j;
	int a_k = 0, a_t = 0; 
	int sum_1 = 0, sum_2 = 0, sum_3 = 0, sum_4 = 0;
	double avg_1 = 0.0, avg_2 = 0.0, avg_3 = 0.0, avg_4 = 0.0; 

	for(i=0;i<L;i++) {
		for(j=0;j<L;j++) {
			a_k = F[i][j];
			a_t = G[i][j]; 

			sum_1 += a_k*a_t;
			sum_2 += a_k;
			sum_3 += a_t;
			sum_4 += a_k*a_k;
		}
	}
	avg_1 = (float)sum_1/(L*L);
	avg_2 = fabs(sum_2)/(L*L);
	avg_3 =	fabs(sum_3)/(L*L); 
	avg_4 = (float)sum_4/(L*L); 

	return (1.0/(avg_4 - avg_2*avg_2))*(avg_1 - avg_2*avg_3); 
}


int main(int argc, char*argv[]) {
	int L = 20;
	int i,j;
	double T = 5.0;
	int N = L*L; 
	int monte_carlo_steps= 1000000;
	int sample_frequency = 100;

	int (*F)[L] = malloc(sizeof(int([L][L]))); 
	int (*G)[L] = malloc(sizeof(int([L][L])));

	gsl_rng *r = gsl_rng_alloc(gsl_rng_mt19937);
	unsigned long int seed = (unsigned)time(NULL); 
	gsl_rng_set(r, seed); 	
	
	cold_lattice(L,F);

	for(i=0;i<monte_carlo_steps;i++) {
		for(j=0;j<N;j++) {
			metropolis_step(L,r,T,F);
		}		
	}

	for(i=0;i<L;i++) {
		for(j=0;j<L;j++) {
			G[i][j] = F[i][j];
		}
	}
	int c = 0;
	printf("%d %f \n", c, auto_corr(L,F,G));
	for(i=0;i<5000;i++) {
		metropolis_step(L,r,T,G);
		c++;
		double ans = auto_corr(L,F,G); 
		printf("%d %f \n",c, ans);
	}

free(F); 
free(G); 
}

