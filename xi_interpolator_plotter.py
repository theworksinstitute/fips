import math
import matplotlib.pyplot as plt
import numpy as np

from xi_interpolator import xi_interpolator

#Subroutine for calculating the Phi(omega) function
def phasediff(omega, pars):
  xi     = pars[0];
  Q      = pars[1];
  omega0 = pars[2];
  omegaA = omega0/xi;
  omegaB = omega0*xi;
  ret = -4*math.atan(pow(omegaA/omega,-Q)) + 4*math.atan(pow(omegaB/omega,-Q));
  return ret;

def xi_interpolator_plotter(Q = 0.15, Phi0 = 90):
  print("Running with the following settings:")
  print("Desired average phase shift Phi0 = " + str(Phi0))
  print("Exponent Q = " + str(Q))
  
  #Calculate interpolated xi value
  xi = xi_interpolator(Phi0,Q);
  
  #Target frequency range, where Phi(omega) shall be as constant as possible
  omegamin = 15;
  omegamax = 20000;
  Nomega = 100;
  
  #Geometric mean of the frequency range edges
  omega0 = np.sqrt(omegamin*omegamax);
  
  #Central frequencies of the phase shifter
  omega0A = omega0/xi;
  omega0B = omega0*xi;
  
  #Print results
  print("Optimal central frequencies for Phi0 = " + str(Phi0) + " and Q = " + str(Q) + ": omega0A = " + str(omega0A) + ", omega0B = " + str(omega0B));
  
	#Figure setup
  plt.figure(num=None, figsize=(6, 4), dpi=200, facecolor='w', edgecolor='k')	
  plt.title(r'$\Phi(\omega)$ for $\Phi_{{0}}={:.0f}^\circ$, $Q={:.2f}$, $\omega_{{0,A}}={:.2f}$ Hz, $\omega_{{0,B}}={:.2f}$ kHz'.format(Phi0,Q,omega0A,omega0B/1000.))
  plt.xlabel(r'$\omega$ [Hz]');
  plt.ylabel(r'$\Phi(\omega)$');
  plt.xlim(omegamin,omegamax)
  plt.ylim(-1.1*Phi0*np.pi/180.,-0.9*Phi0*np.pi/180.)
    
  #Defining arrays to plot
  logftab=np.linspace(math.log(omegamin),math.log(omegamax),Nomega);
  ftab=np.exp(logftab);
  phasefunc = np.linspace(0,0,Nomega);
  pars = [xi,Q,omega0];
  for iomega in range(Nomega):
    phasefunc[iomega] = phasediff(ftab[iomega],pars);

  #Actual plotting
  plt.semilogx(ftab, phasefunc, linestyle='-', color='r', label=r'$\Phi$ func');
  ax = plt.subplot(111)
  box = ax.get_position();
  ax.set_position([box.x0, box.y0 + box.height*0.04, box.width, box.height])
  ax.grid(which='major', color='gray', linestyle='--', linewidth = 0.50)
  ax.grid(which='minor', color='gray', linestyle=':',  linewidth = 0.25)
  plt.savefig('xi_interpolator_plotter_Phi0{:.0f}_Q{:.2f}.png'.format(Phi0,Q));

xi_interpolator_plotter(0.05,90)
xi_interpolator_plotter(0.10,90)
xi_interpolator_plotter(0.15,90)
xi_interpolator_plotter(0.20,90)