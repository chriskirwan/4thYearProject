#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <gsl/gsl_rng.h>
#include "../xy.h"


double magnetization_squared(int L, double F[][L]) {
	int i,j;
	int N = L*L; 
	double sum1 = 0.0;
	double sum2 = 0.0;

	for(i=0;i<L;i++) {
		for(j=0;j<L;j++) {
			sum1 += cos(F[i][j]); 
			sum2 += sin(F[i][j]); 
		}
	}		
	double avg = (sum1*sum1 + sum2*sum2)/(L*L); 
	return avg; 
}

int main(int argc, char*argv[]) {
	int L = 30;
	double T; 
	int i,j;
	int N = L*L;

	double (*F)[L] = malloc(sizeof(double([L][L]))); 

	gsl_rng *r = gsl_rng_alloc(gsl_rng_mt19937);
	unsigned long int seed = (unsigned)time(NULL); 
	gsl_rng_set(r, seed); 	

	
	int monte_carlo_steps = 100000; 
	int sample_frequency = 100; 

	for(T=0.2;T<1.4;T+=0.01) {
		cold_lattice(L,F); 
		double mag_sum = 0.0; 
		int ns = 0; 

		for(i=0;i<monte_carlo_steps;i++) {	
			for(j=0;j<L;j++) {
				metropolis_step(L,r,T,F); 
			}
			if(!(i%sample_frequency)) {
				mag_sum += magnetization_squared(L,F);
			   	ns++;	
			}
		}
		printf("%f %f\n", T, mag_sum/ns);
	}

free(F); 
}

