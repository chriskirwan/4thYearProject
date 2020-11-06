#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_rng.h>


void init_sum(int L, int F[][L]) {
	int i,j;

	for (i=0;i<L;i++) {
		for (j=0;j<L; j++) {
			F[i][j] = i+j;
		}
	}
}
// Generates an L*L grid of unifomly random unit spins (\sigma = \pm 1)
// Uniformly generated using gsl_rng to get either 0 or 1, cast to (signed) int 
// rather than default unsigned int, x2 to get 0 or 2, -1 to het -1 or 1.
 
void init_rnd(int L, gsl_rng*r, int F[][L]) {
	int i,j;

	for (i=0;i<L;i++) {
		for (j=0;j<L;j++) {
			F[i][j] = 2*(int)gsl_rng_uniform_int(r,2)-1;
		}
	}
}
// Generates an L*L grid of unit spins (\sigma = 1). This acts as a system 
// with T=0 or \Beta=\infty.

void init_cold(int L, int F[][L]) {
	int i,j; 

	for (i=0;i<L;i++) {
		for (j=0;j<L;j++) { 
			F[i][j] = 1;
		}
	}
}


//Computes the change in energy when a spin at site (i,j) is flipped. 
//Periodic boundaries (Therefore torus config space) are done separately for west/noth and east/south
//This is due to getting negative array indices when going west/north in F[i][j] (i and j decrease) which
//causes a segfault (going out of bounds in the array memory)
//East/South uses <>%<> operator (modulo) 
//West/North uses <>?<>:<> (the ternary operator, a compact if-else statement). 

int E_new(int L, int i, int j, int F[][L]) {
	return -2*(F[i][j])*(F[i?(i-1):(L-1)][j] + F[(i+1)%L][j] + F[i][j?(j-1):(L-1)] + F[i][(j+1)%L]);
}

//Computes the (radius dependent) spin-spin correlation of an LxL spin grid. This is
// done using the formula G(r) = <s(k)s(k+r)> - <s(k)><s(k+r)>. This is done by computing the expectation
// value of the spins along the grid directions at a site F[i][j] and F[i\pm r][j\pm r],  

void ss_cor(int L, int r, int F[][L]) {
	int i,j;
	int prod = 0;
	int sum = 0;

	// This part here is an embarrasment. Not proud of this, but it works.
	// Will certainly clean this up at some point 
	int prod_1 = 0;
	int prod_2 = 0;
	int sum_1 = 0; 
	int sum_2 = 0;
   	float prod_3 = 0;
	float sum_3 = 0; 	
	
	//Again, using ?: to avoid the whole segfaulting thing. At least it works 
	for (i=0;i<L;i++) {
		for (j=0;j<L;j++) {
			prod = F[i][j]*( F[i][(j+r)%L] + F[i][(j-r > -1)?(j-r):(L-r)] 
							+F[(i+r)%L][j] + F[(i-r > -1)?(i-r):(L-r)][j]);
			sum += prod;
			
			sum_1 += F[i][j];
			sum_2 += F[i][(j+r)%L] + F[i][(j-r > -1)?(j-r):(L-r)] 
					+F[(i+r)%L][j] + F[(i-r > -1)?(i-r):(L-r)][j];
		}
	}
	sum_3 = (float) sum / (4*L*L);
	prod_3 = ((float)sum_1 / (L*L)) * ((float)sum_2/(4*L*L)); 
	printf("%d %f \n",r, sum_3 - prod_3);
	
}

int main(int argc, char*argv[]) {
	// System Variables
	int L = 20;
	int i,j,c,a;
	double T = 2.7;
	int ncycles = 100000;
	int fsamples = 1000;
	int de;
	double b,x;
	
	// Twised Mersenne generator from the GSL that I took from online
	gsl_rng *r = gsl_rng_alloc(gsl_rng_mt19937);
	unsigned long int Seed = 59626588389;

	gsl_rng_set(r,Seed);
	int N = L*L;
	int (*F)[L] = malloc(sizeof(int[L][L]));
	

	init_rnd(L,r,F);
	T = 1.0/T;

	//Metropolising 
	for(c=0;c<ncycles;c++) {
		for(a=0;a<N;a++) {
			i = (int)gsl_rng_uniform_int(r,L);
			j = (int)gsl_rng_uniform_int(r,L); 

			de = E_new(L,i,j,F); 
			b = exp(de*T); 
			x = gsl_rng_uniform(r); 

			if (x<b) {
				F[i][j] *= -1; 
			}
		}
	}

	//Looping over the correlation function
	for(int rad = 0; rad < L/2 +1; rad++) {
		ss_cor(L,rad,F);
	}
	free(F);
}
