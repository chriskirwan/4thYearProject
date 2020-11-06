//compile using "gcc -o ising ising.c -lm -lgsl"
//runs as "./ising -L <sidelength> -T <temp> -nc <numcycles> -fs <samplefreq>"
//Eg: ./ising -L 20 -T 0.5 -nc 1e7 -fs 100
//Hamiltonian is H = J_{ij} \Sum_{i,j} \sigma_i \sigma_j    

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_rng.h>

//This function computes and returns the change in
//system energy when spin (i,j) is flipped.  The
//modulo arithmetic (the % operator) ensures 
//periodic boundaries. i?: is the terneary operator

int E (int **F,int L,int i,int j) {
	return -2*(F[i][j])*(F[i?(i-1):(L-1)][j]+F[(i+1)%L][j]+
		F[i][j?(j-1):(L-1)]+F[i][(j+1)%L]);
}

//Sample the system; compute the average magnetization
//and the average energy per spin 

double samp (int ** F,int L,double *s,double *e) {
	int i,j;

	*s=0.0;
	*e=0.0;

	//Visit each position (i,j) in the lattice 
	for (i=0;i<L;i++) {
		for (j=0;j<L;j++) {
			*s+=(double)F[i][j];
			*e-=(double)(F[i][j])*(F[i][(j+1)%L]+F[(i+1)%L][j]);
    	}
	}
	*s/=(L*L);
	*e/=(L*L);
}

//Randomly assigns all spins 
void init (int **F,int L,gsl_rng*r) {
	int i,j;

	//Visit each position (i,j) in the lattice
	for (i=0;i<L;i++) {
		for (j=0;j<L;j++) {
			//2*x-1, where x is randomly 0,1
			F[i][j]=2*(int)gsl_rng_uniform_int(r,2)-1;
    	}
  	}
}

void init_cold (int **F,int L,gsl_rng*r) {
	int i,j;

	for (i=0;i<L;i++) {
		for(j=0;j<L;j++) {
			F[i][j] = 1;
		}
	}
}


int main (int argc, char * argv[]) {

	//System parameters 
	int ** F;       //The 2D array of spins
	int L = 20;     //The sidelength of the array 
	int N;          //The total number of spins = L*L 
	double T = 1.0; //Dimensionless temperature = (T*k)/J

	//Run parameters 
	int nCycles = 1000000;	//number of MC cycles to run; one cycle is N 
							//consecutive attempted spin flips
	int fSamp = 1000;		//Frequency with which samples are taken 

	//Computational variables 
	int nSamp;      //Number of samples taken 
	int de;         //energy change due to flipping a spin 
	double b;       //Boltzman factor
	double x;       //random number 
	int i,j,a,c;    //loop counters 

	//Observables 
	double s=0.0, ssum=0.0, ssumsq = 0.0,
		   abssum=0.0, savg = 0.0, s2mom = 0.0;    //average magnetization 
	double e=0.0, esum=0.0, esumsq = 0.0, 
		   eavg = 0.0, e2mom =0.0;    //average energy per spin 

	//This line creates a random number generator
	//of the "Mersenne Twister" type, which is much
	//better than the default random number generator.
	// Shamelessly copied from online */
	gsl_rng * r = gsl_rng_alloc(gsl_rng_mt19937);
	unsigned long int Seed = 23410981;

	//command line arguments
	for (i=1;i<argc;i++) {
		if (!strcmp(argv[i],"-L")) L=atoi(argv[++i]);
		else if (!strcmp(argv[i],"-T")) T=atof(argv[++i]);
		else if (!strcmp(argv[i],"-nc")) nCycles = atoi(argv[++i]);
		else if (!strcmp(argv[i],"-fs")) fSamp = atoi(argv[++i]);
		else if (!strcmp(argv[i],"-s")) Seed = (unsigned long)atoi(argv[++i]);
	}
  
	//Seed the random number generator 
	gsl_rng_set(r,Seed);

	//Compute the number of spins 
	N=L*L;

	//Allocate memory for the system 
	F=(int**)malloc(L*sizeof(int*));
	for (i=0;i<L;i++) {
		   	F[i]=(int*)malloc(L*sizeof(int));
	}

	//Generate an initial state 
	init_cold(F,L,r);

	double T_cur = T;
	T=1.0/T;

	s = 0.0;
	e = 0.0;
	nSamp = 0;

	for (c=0;c<nCycles;c++) {
		// Make N flip attempts 
		for (a=0;a<N;a++) {
			//randomly select a spin
			i=(int)gsl_rng_uniform_int(r,L);
			j=(int)gsl_rng_uniform_int(r,L);
		
			//get the "new" energy as the incremental change due to flipping spin (i,j)
			de = E(F,L,i,j);
			//compute the Boltzmann factor; T is now reciprocal temperature 
			b = exp(de*T);
			//pick a random number between 0 and 1
			x = gsl_rng_uniform(r);
		
			//accept or reject this flip 
			if (x<b) { // accept
				//flip it 
				F[i][j]*=-1;
			}
		}
		
		// Sample and accumulate averages 
		if (!(c%fSamp)) {
			samp(F,L,&s,&e);
		//fprintf(stdout, "%i %.51f %.51f \n", c,s,e);
		//fflush(stdout);
			ssum+=s;
			esum+=e;
			ssumsq+=s*s;
			esumsq+=e*e;
			nSamp++;
		}
	}
	abssum = fabs(ssum);
	savg = abssum/nSamp;
	eavg = esum/nSamp;
	s2mom = (ssumsq/nSamp - savg*savg)/(T_cur);
	e2mom = (esumsq/nSamp - eavg*eavg)/(T_cur*T_cur);

	//fprintf(stdout, "%.5f %.5f \n", T_cur, savg, eavg);
	fprintf(stdout,"%.5f %.5f %.5f %.5f %.5f \n",T_cur,savg, eavg, s2mom, e2mom);
}
