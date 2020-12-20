#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <gsl/gsl_rng.h>
#include "../xy.h"

void MagnetizationSquaredPerSpin(int L, double *magnetization, double F[][L]) { 
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
	*magnetization = (sum1*sum1 + sum2*sum2);
	*magnetization /= N*N; 
}

double EnergyPerSpin(int L, double F[][L]) {
	int i,j; 
	int N = L*L; 

	double energy = 0.0; 
	for(i=0;i<L;i++) {
		for(j=0;j<L;j++) {
			energy -=-0.5*Energy(L,i,j,F); 
		}
	}
	return energy/N;
}

double Variance(int L, double F[][L], int tmax, double array[tmax]) {
	int i;
	int number_terms = 0; 
   	double term1 = 0.0, term2 = 0.0; 	

	for(i=0;i<tmax;i++) {
		term1 += array[i]*array[i]; 
		term2 += array[i]; 
	   	number_terms++; 	
	}
return term1/number_terms - (term2/number_terms)*(term2/number_terms); 
}

int main(int argc, char*argv[]) {
	int L = 20;
	int N = L*L; 	
	int i,j; 
	int thermalization = 5000; 

	double T = 0.4; 

	double (*F)[L] = malloc(sizeof(double([L][L]))); 

	gsl_rng *r = gsl_rng_alloc(gsl_rng_mt19937);
	unsigned long int seed = (unsigned)time(NULL);
	gsl_rng_set(r, seed);

	RandomLattice(L,r,F); 

	for(i=0;i<thermalization;i++) {
		for(j=0;j<N;j++) { 
			MetropolisStep(L,r,T,F); 
		}
	}

	int tmax = 5000;
	int t;
	int number_terms = 0; 	
	double array[tmax]; 
	double term1 = 0.0, term2 = 0.0, term3 = 0.0; 
	double magnetization = 0.0;

	for(i=0;i<tmax;i++) {
		MagnetizationSquaredPerSpin(L,&magnetization,F);
	   	array[i] = magnetization; 	
		for(j=0;j<N;j++) {
			MetropolisStep(L,r,T,F); 
		}
	}

	for(t=0;t<tmax;t++) {
		for(i=0;i<tmax-t;i++) {
			term1 += array[i+t]*array[i];
			term2 += array[i+t]; 
			term3 += array[i]; 
			number_terms++; 
		}
		
		double autocorrelation = term1/number_terms - (term2/number_terms)*(term3/number_terms); 
		printf("%d %lf\n", t, fabs(autocorrelation/Variance(L,F,tmax,array))); 
	}

free(F); 
return 0; 
}
