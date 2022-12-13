//g++ xi_interpolator.cc -o xi_interpolator.exe
#include "xi_interpolator.h"

int main()
{
  //Parameters to be set: Q (exponent) and Phi0 (desired average phase shift)
  double Q = 0.1;
  double Phi0 = 90;
  
  //Calculate interpolated xi value
  double xi = xi_interpolator(Phi0,Q);
  
  //Target frequency range, where Phi(omega) shall be as constant as possible
  double omegamin = 15;
  double omegamax = 20000;
  
  //Geometric mean of the frequency range edges
  double omega0 = sqrt(omegamin*omegamax);
  
  //Central frequencies of the phase shifter
  double omega0A = omega0/xi;
  double omega0B = omega0*xi;
  
  //Print results
  cerr << "Optimal central frequencies for Phi0 = " << Phi0 << " and Q = " << Q << ": omega0A = " << omega0A << ", omega0B = " << omega0B << endl;
}