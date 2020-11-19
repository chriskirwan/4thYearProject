#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <gsl/gsl_rng.h>
#include "ising.h"

double mgt(double M, double N) {
	return fabs(M)/N;
}

double enr(double E, double N) {
	return E/N;
}

double spec_h(double T, double E, double E2, int N) {
	double E_avg = E/N;
	double E2_avg = E2/N;
	return 1.0/(T*T)*(E2_avg - (E_avg*E_avg));
}

double mag_sus(double T, double M, double M2, int N) {
	double M_avg = fabs(M)/N;
	double M2_avg = M2/N;
	return 1.0/(T)*(M2_avg - (M_avg*M_avg));
}


int main(int argc, char*argv[]) {
	int L = 20;
	int i,j;
	double T;
	int N = L*L; 
	int monte_carlo_steps= 40000;
	int sample_frequency = 100;

	int (*F)[L] = malloc(sizeof(int([L][L]))); 

	gsl_rng *r = gsl_rng_alloc(gsl_rng_mt19937);
	unsigned long int seed = (unsigned)time(NULL); 
	gsl_rng_set(r, seed); 	
	
	for (T=0.05;T<5;T+=0.05) {
		cold_lattice(L,F);
		double mag = 0.0, mag_sum = 0.0, mag_sum_sqr = 0.0; 
		double ene = 0.0, ene_sum = 0.0, ene_sum_sqr = 0.0;
		int ns = 0;


		for(i=0;i<monte_carlo_steps;i++) {
			for(j=0;j<N;j++) {
				metropolis_step(L,r,T,F);
			}
			if(!(i%sample_frequency)) {
				sample(L,&mag,&ene,F);
				mag_sum += mag, ene_sum += ene;
				mag_sum_sqr += mag*mag, ene_sum_sqr += ene*ene;
				ns++;
			}
		}
	   	printf("%f %f %f ", T,mgt(mag_sum, ns), enr(ene_sum, ns));
		printf("%f %f \n", spec_h(T,ene_sum, ene_sum_sqr, ns),mag_sus(T,mag_sum, mag_sum_sqr, ns));	
	}
free(F); 
}

