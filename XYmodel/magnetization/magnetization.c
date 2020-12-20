#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <gsl/gsl_rng.h>
#include "../xy.h"

void MagnetizationSquaredPerSpin(int L, double *total, double F[][L]) { 
	int i,j; 
	double sum1 = 0.0; 
	double sum2 = 0.0; 
	int N = L*L;

	for(i=0;i<L;i++) {
		for(j=0;j<L;j++) {
			sum1 += cos(F[i][j]);
		   	sum2 += sin(F[i][j]); 
		}
	}	
	*total = (sum1*sum1 + sum2*sum2);
	*total /= N*N; 
}

int main(int argc, char*argv[]) {
	int L = 20;
	int N = L*L; 	
	int i,j; 
	int thermalization = 5000; 
	int monte_carlo_steps = 50000;
	int sample_frequency = 100; 

	double T; 

	double (*F)[L] = malloc(sizeof(double([L][L]))); 

	gsl_rng *r = gsl_rng_alloc(gsl_rng_mt19937);
	unsigned long int seed = (unsigned)time(NULL);
	gsl_rng_set(r, seed);


	for(T=0.1;T<2;T+=0.05) {
		ColdLattice(L,F); 
		double mag_sum = 0.0; 
		double mag_sqrd_sum = 0.0; 
		int number_samples = 0;

		for(i=0;i<thermalization;i++) {
			for(j=0;j<N;j++) { 
				MetropolisStep(L,r,T,F); 
			}
		}
		
		for(i=0;i<monte_carlo_steps;i++) {
			for(j=0;j<N;j++) { 
				MetropolisStep(L,r,T,F); 
			}
			if(!(i%sample_frequency)) {
				MagnetizationSquaredPerSpin(L,&mag_sum, F); 
				mag_sqrd_sum += mag_sum; 
				number_samples++; 
			}
		}
		printf("%lf %lf\n", T, mag_sqrd_sum/number_samples); 
	}
free(F); 
}
