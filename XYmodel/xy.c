#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_rng.h>

void RandomLattice(int L, gsl_rng*r, double F[][L]) {
	int i,j; 

	for(i=0;i<L;i++) {
		for(j=0;j<L;j++) {
			F[i][j] = 2*M_PI*gsl_rng_uniform(r) - M_PI; 
		}
	}
}

void ColdLattice(int L, double F[][L]) {
	int i,j; 

	for(i=0;i<L;i++) {
		for(j=0;j<L;j++) {
			F[i][j] = 0; 
		}
	}
}

double RandomSpin(gsl_rng*r) { 
	double NewAngle = 2*M_PI*gsl_rng_uniform(r) - M_PI; 
	return NewAngle; 

}

double Energy(int L, int i, int j, double F[][L]) {
	double Site = F[i][j];

	double Left = F[i?(i-1):(L-1)][j]; 
	double Right = F[(i+1)%L][j]; 
	double Up = F[i][j?(j-1):(L-1)]; 
	double Down = F[i][(j+1)%L]; 

	double Energy = cos(Site-Left) + cos(Site-Right) + cos(Site-Up) + cos(Site-Down); 	
	return Energy; 
}

double EnergyFlip(int L, int i, int j, double NewSpin, double F[][L]) {
	double SiteNew = NewSpin;

	double Left = F[i?(i-1):(L-1)][j];
	double Right = F[(i+1)%L][j];
	double Up = F[i][j?(j-1):(L-1)];
	double Down = F[i][(j+1)%L];

	double EnergyNew = cos(SiteNew-Left) + cos(SiteNew-Right) + cos(SiteNew-Up) + cos(SiteNew - Down);
	return EnergyNew; 
}

void MetropolisStep(int L, gsl_rng*r, double T, double F[][L]) {
		int i = (int)gsl_rng_uniform_int(r,L); 
		int j = (int)gsl_rng_uniform_int(r,L); 

		double NewSpin = RandomSpin(r);  
		double DeltaEnergy = Energy(L,i,j,F) - EnergyFlip(L,i,j,NewSpin,F); 
		double Boltzmann = exp(-DeltaEnergy*(1.0)/T); 
		double UniformRandom = gsl_rng_uniform(r); 

		if(DeltaEnergy < 0) {
			F[i][j] = NewSpin; 
		} else if (DeltaEnergy >= 0) {
			if(UniformRandom <= Boltzmann) {
				F[i][j] = NewSpin;
			} else if (UniformRandom > 0) {
				F[i][j] = F[i][j]; 
			}
		}
}

double Magnetization(int L, double F[][L]) {
	int i,j;
	double Sum1 = 0.0; 
	double Sum2 = 0.0;
   	int N = L*L; 	

	for(i=0;i<L;i++) {
		for(j=0;j<L;j++) {
			Sum1 += cos(F[i][j]); 
			Sum2 += sin(F[i][j]); 
		}
	}
	double Total = (Sum1*Sum1 + Sum2*Sum2)/(double)N; 
	return Total/N; 
}

double EnergyFunc(int L, double F[][L]) {
	int i,j;
	int N = L*L; 

	double Site = F[i][j];
	double Left = F[i?(i-1):(L-1)][j];
	double Right = F[(i+1)%L][j];
	double Up = F[i][j?(j-1):(L-1)];
	double Down = F[i][(j+1)%L];
	
	double energy = 0.0; 
	for(i=0;i<L;i++) {
		for(j=0;j<L;j++) {
			energy -= 0.5*(cos(Site-Left) + cos(Site-Right) + cos(Site-Up) + cos(Site-Down)); 			
		}
	}
	return energy/(double)(N); 
}

