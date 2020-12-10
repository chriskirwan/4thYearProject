#ifndef XY_H

#define XY_H

void RandomLattice(int L, gsl_rng*r, double F[][L]);
void ColdLattice(int L, double F[][L]);
double RandomSpin(gsl_rng*r);
double Energy(int L, int i, int j, double F[][L]);
double EnergyFlip(int L, int i, int j, double NewSpin, double F[][L]);
void MetropolisStep(int L, gsl_rng*r, double T, double F[][L]);
double Magnetization(int L, double F[][L]);
double EnergyFunc(int L, double F[][L]); 
#endif
