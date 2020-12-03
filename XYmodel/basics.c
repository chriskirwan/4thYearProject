#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <gsl/gsl_rng.h>
#include "xy.h"

int main(int argc, char*argv[]) {
	int L = 64;
	int i,j;
	int N = L*L;

	double (*F)[L] = malloc(sizeof(double([L][L]))); 

	gsl_rng *r = gsl_rng_alloc(gsl_rng_mt19937);
	unsigned long int seed = (unsigned)time(NULL); 
	gsl_rng_set(r, seed); 	

	random_lattice(L,r,F); 
	
	FILE *fp;
	fp = fopen("random_lattice.dat", "w");
	for(i=0;i<L;i++) {
		for(j=0;j<L;j++) { 
			fprintf(fp, "%lf ", F[i][j]); 
		}
		fprintf(fp,"\n"); 
	} 
	fclose(fp);

	FILE *fp_new; 
	fp_new = fopen("new_random_lattice.dat", "w"); 
	for(i=0;i<L;i++) {
		for(j=0;j<L;j++) { 
			F[i][j] = random_flip(r); 
			fprintf(fp_new, "%lf ", F[i][j]); 
		}
		fprintf(fp_new, "\n"); 
	}
	fclose(fp_new); 

free(F); 
}

