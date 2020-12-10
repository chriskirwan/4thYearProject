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
	int NumberSamples = 100; 

	double T = 0.02; 

	double (*F)[L] = malloc(sizeof(double([L][L]))); 

	gsl_rng *r = gsl_rng_alloc(gsl_rng_mt19937);
	unsigned long int seed = (unsigned)time(NULL);
	gsl_rng_set(r, seed);

	RandomLattice(L,r,F); 

	for(i=0;i<MonteCarloSteps;i++) {
		for(j=0;j<N;j++) { 
			MetropolisStep(L,r,T,F); 
		}
		printf("%d %lf\n", i, Magnetization(L,F)); 
	}

free(F); 
}
