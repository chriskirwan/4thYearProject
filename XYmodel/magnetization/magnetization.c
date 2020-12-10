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
	int MonteCarloSteps = 50000;
	int SampleFrequency = 100; 

	double T; 

	double (*F)[L] = malloc(sizeof(double([L][L]))); 

	gsl_rng *r = gsl_rng_alloc(gsl_rng_mt19937);
	unsigned long int seed = (unsigned)time(NULL);
	gsl_rng_set(r, seed);


	for(T=0.1;T<2;T+=0.05) {
		ColdLattice(L,F); 
		double MagSum = 0.0; 
		int NumberSamples = 0;

		for(i=0;i<MonteCarloSteps;i++) {
			for(j=0;j<N;j++) { 
				MetropolisStep(L,r,T,F); 
			}
			if(!(i%SampleFrequency)) {
				MagSum += Magnetization(L,F); 
				NumberSamples++; 
			}
		}
		printf("%lf %lf\n", T, MagSum/(double)NumberSamples); 
	}
free(F); 
}
