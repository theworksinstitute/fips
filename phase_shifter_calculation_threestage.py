import math
import matplotlib.pyplot as plt
import numpy as np

#Linestyles
linestyles = [
  (0, ()),                     #('solid',       

  (0, (1, 1)),                 #('densely dotted',        
  (0, (1, 2)),                 #('dotted',                
  (0, (1, 5)),                 #('intermediately dotted', 
  (0, (1, 10)),                #('loosely dotted',  

  (0, (5, 1)),                 #('densely dashed',        
  (0, (5, 2)),                 #('dashed',                
  (0, (5, 5)),                 #('intermediately dashed', 
  (0, (5, 10)),                #('loosely dashed',        
  (0, (3, 10, 1, 10)),         #('loosely dashdotted',  

  (0, (3, 5, 1, 5)),           #('dashdotted',            
  (0, (3, 1, 1, 1)),           #('densely dashdotted',    
  (0, (3, 5, 1, 5, 1, 5)),     #('dashdotdotted',         
  (0, (3, 10, 1, 10, 1, 10)),  #('loosely dashdotdotted', 
  (0, (3, 1, 1, 1, 1, 1)),     #('densely dashdotdotted', 

  (5, (10, 3))                 #('long dash with offset', 
  ]

#Frequency range in focus and frequency array size
omegamin = 15;
omegamax = 20000;
Nomega = 100;

#Basic filter
def BandFilter(Q, f0, f):
  return -4*math.atan(pow(f0/f,-Q));

#Three-stage filter with five parameters: Q1, Q2, xi1, xi2 and omega01
def phasediff(x, pars):
  #Frequency (sometimes denoted omega)
  f = x;
  
  #Q exponent values
  Q1 = pars[0];
  Q2 = pars[1];
  Q3 = Q1; #Based intuitively on symmetry principles
  
  #xi values
  xi1 = pars[2];
  xi2 = pars[3];
  xi3 = xi1; #Based intuitively on symmetry principles
  
  #omega0 mean frequencies
  f01 = pars[4];
  f02 = f01*xi2/xi1; #Based intuitively on symmetry principles
  f03 = f01*xi2*xi2; #Based intuitively on symmetry principles
  
  #Central frequencies (sometimes denoted as e.g. omega_{0,A,1})
  f0A1 = f01/xi1;
  f0A2 = f02/xi2;
  f0A3 = f03/xi3;
  f0B1 = f01*xi1;
  f0B2 = f02*xi2;
  f0B3 = f03*xi3;
  
  #Three stages
  ret1 = BandFilter(Q1,f0A1,f) - BandFilter(Q1,f0B1,f);
  ret2 = BandFilter(Q2,f0A2,f) - BandFilter(Q2,f0B2,f);
  ret3 = BandFilter(Q3,f0A3,f) - BandFilter(Q3,f0B3,f);
  
  return ret1 + ret2 + ret3;

#Deviation from Phi0
def phasediff_phi0(x, pars):
  #The desired average
  Phi0 = pars[5];
  return (phasediff(x,pars) - Phi0)*180./np.pi;

#Empirical formula for Q2(Phi0) based on numerical calculations
def Q2func(Phi0):
  return -0.066607677026*Phi0;

#Empirical formula for xi1(Phi0) based on numerical calculations
def xi1func(Phi0):
  return 1+(-0.0066800473*Phi0*Phi0*Phi0 + 0.0023085812*Phi0*Phi0 + 0.0006379221*Phi0);

#Empirical formula to correct for residual effects in the average
def Phi0mod(Phi0):
  return 0.0054919*Phi0*Phi0*Phi0 - 0.0030961*Phi0*Phi0 + 0.98601*Phi0 - 0.00044568;

#Example plots
def createplot():
  global omegamin, omagemax;
  
  #Empirical values based on numerical calculations
  Q1  =  0.873465;
  xi2 = 44.595068890;
  f01 = 10.667937950;

  #Figure setup for Phi(omega)
  plt.figure(num=None, figsize=(6, 4), dpi=100, facecolor='w', edgecolor='k')
  plt.title(r'$\Phi(\omega)$ for various $\Phi_{0}$ values')
  plt.xlabel(r'$\omega$ [Hz]');
  plt.ylabel(r'$\Phi(\omega)$');
  plt.xlim(omegamin,omegamax)
  plt.ylim(-6*np.pi/10,0)
  
  for iPhi0 in range(12):
    Phi0 = (iPhi0-11)*np.pi/20.
		
    #Parameter array
    pars = [Q1,Q2func(Phi0mod(Phi0)),xi1func(Phi0mod(Phi0)),xi2,f01,Phi0];
    
    #Defining arrays to plot
    logftab=np.linspace(math.log(omegamin),math.log(omegamax),Nomega);
    ftab=np.exp(logftab);
    phasefunc = np.linspace(0,0,Nomega);
    for iomega in range(Nomega):
      phasefunc[iomega] = phasediff(ftab[iomega],pars);
  
    #Actual plotting
    plt.semilogx(ftab, phasefunc, linestyle=linestyles[iPhi0], color=(1-(iPhi0+0.5)/12,0.3,(iPhi0+0.5)/12), label=r'$\Phi_0={:.2f}$'.format(Phi0));
  
  ax = plt.subplot(111)
  box = ax.get_position();
  ax.set_position([box.x0, box.y0 + box.height*0.04, box.width * 0.8, box.height * 0.96])
  plt.legend(loc='center left',bbox_to_anchor=(1, 0.5));
  plt.savefig('phase_shifter_threestage_python.png');
  
  #Figure setup for Phi(omega)-Phi0
  plt.figure(num=None, figsize=(6, 4), dpi=100, facecolor='w', edgecolor='k')
  plt.title(r'$\Phi(\omega)-\Phi_{0}$ for various $\Phi_{0}$ values')
  plt.xlabel(r'$\omega$ [Hz]');
  plt.ylabel(r'$\Phi(\omega)-\Phi_{0}$');
  plt.xlim(omegamin,omegamax)
  plt.ylim(-0.01,0.01)
  
  for iPhi0 in range(12):
    Phi0 = (iPhi0-11)*np.pi/20.
		
    #Parameter array
    pars = [Q1,Q2func(Phi0mod(Phi0)),xi1func(Phi0mod(Phi0)),xi2,f01,Phi0];
    
    #Defining arrays to plot
    logftab=np.linspace(math.log(omegamin),math.log(omegamax),Nomega);
    ftab=np.exp(logftab);
    phasefunc_diff = np.linspace(0,0,Nomega);
    for iomega in range(Nomega):
      phasefunc_diff[iomega] = phasediff_phi0(ftab[iomega],pars)*np.pi/180.; #Convert back to radians
  
    #Actual plotting
    plt.semilogx(ftab, phasefunc_diff, linestyle=linestyles[iPhi0], color=(1-iPhi0/20.,0.1,iPhi0/20), label=r'$\Phi_0={:.2f}$'.format(Phi0));

  ax = plt.subplot(111)
  box = ax.get_position();
  ax.set_position([box.x0 + box.width * 0.05, box.y0 + box.height*0.04, box.width * 0.75, box.height * 0.96])
  plt.legend(loc='center left',bbox_to_anchor=(1, 0.5));
  plt.savefig('phase_shifter_threestage_diff_python.png');

createplot()
