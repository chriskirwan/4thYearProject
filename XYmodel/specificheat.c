#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <gsl/gsl_rng.h>
#include "../xy.h"

int main(int argc, char*argv[]) {
	int L = 20;
	int N = L*L; 	
	int i,j; 
	int MonteCarloSteps = 10000;
	int SampleFrequency = 100; 

	double T; 

	double (*F)[L] = malloc(sizeof(double([L][L]))); 

	gsl_rng *r = gsl_rng_alloc(gsl_rng_mt19937);
	unsigned long int seed = (unsigned)time(NULL);
	gsl_rng_set(r, seed);


	for(T=0.1;T<2.1;T+=0.1) {
		ColdLattice(L,F); 
		double EnergySum = 0.0; 
		int NumberSamples = 0;

		for(i=0;i<MonteCarloSteps;i++) {
			for(j=0;j<N;j++) { 
				MetropolisStep(L,r,T,F); 
			}
			if(!(i%SampleFrequency)) {
				EnergySum += SpecificHeat(L,T,F); 
				NumberSamples++; 
			}
		}
		printf("%lf %lf\n", T, EnergySum/(double)NumberSamples); 
	}
free(F); 
}
