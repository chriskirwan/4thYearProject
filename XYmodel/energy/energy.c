#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <gsl/gsl_rng.h>
#include "../xy.h"

void EnergyPerSpin(int L, double *energy, double F[][L]) {
	int i,j;
	int N = L*L; 

	*energy = 0.0; 
	for(i=0;i<L;i++) {
		for(j=0;j<L;j++) {
			*energy -=0.5*Energy(L,i,j,F); 
		}
	}
	*energy /= N;
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


	for(T=0.1;T<2.1;T+=0.1) {
		ColdLattice(L,F);
	   	double energy = 0.0; 	
		double energy_sum = 0.0; 
		int number_samples = 0;

		for(i=0;i<monte_carlo_steps;i++) {
			for(j=0;j<N;j++) { 
				MetropolisStep(L,r,T,F); 
			}
			if(!(i%sample_frequency)) {
				EnergyPerSpin(L,&energy,F);
			   	energy_sum += energy; 	
				number_samples++; 
			}
		}
		printf("%lf %lf\n", T, energy_sum/number_samples); 
	}
free(F);
}
