#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <gsl/gsl_rng.h>
#include "xy.h"


//double magnetization_squared(int L, double F[][L]) {
//	int i,j;
//	double sum1 = 0.0;
//	double sum2 = 0.0;
//
//	for(i=0;i<L;i++) {
//		for(j=0;j<L;j++) {
//			sum1 += cos(F[i][j]); 
//			sum2 += sin(F[i][j]); 
//			
//}

int main(int argc, char*argv[]) {
	int L = 100;
	double T = 0.1; 
	int i,j;
	int N = L*L;

	double (*F)[L] = malloc(sizeof(double([L][L]))); 

	gsl_rng *r = gsl_rng_alloc(gsl_rng_mt19937);
	unsigned long int seed = (unsigned)time(NULL); 
	gsl_rng_set(r, seed); 	

	cold_lattice(L,F);
	
	FILE *fp;
	fp = fopen("random_lattice.dat", "w");
	for(i=0;i<L;i++) {
		for(j=0;j<L;j++) { 
			fprintf(fp, "%lf ", F[i][j]); 
		}
		fprintf(fp,"\n"); 
	} 
	fclose(fp);


	int monte_carlo_steps = 1000000; 
	int sample_frequency = 100; 

	for(i=0;i<monte_carlo_steps;i++) {
		for(j=0;j<N;j++) { 
			metropolis_step(L,r,T,F); 
		}
	}

     FILE *fp_new;
     fp_new = fopen("new_lattice.dat", "w");
     for(i=0;i<L;i++) {
         for(j=0;j<L;j++) {
             fprintf(fp_new, "%lf ", F[i][j]);
         }
         fprintf(fp_new,"\n");
     }
     fclose(fp_new);


free(F); 
}

