//make xi_interpolator_plotter.exe
#include "xi_interpolator.h"
#include "TF1.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TStyle.h"

//Subroutine for calculating the Phi(omega) function
double phasediff(const double *x, const double *pars)
{
  double omega  = x[0];
  double xi     = pars[0];
  double Q      = pars[1];
  double omega0 = pars[2];
  double omegaA = omega0/xi;
  double omegaB = omega0*xi;
  double ret = -4*atan(pow(omegaA/omega,-Q)) + 4*atan(pow(omegaB/omega,-Q));
  return ret;
}

int main(int argc, char *argv[])
{
  //Parameters to be set: Q (exponent) and Phi0 (desired average phase shift)
  double Q = 0.15;
  double Phi0 = 90;
  //Parameters can be overwritten by the command line input
  if(argc>1) Phi0 = atof(argv[1]);
  if(argc>2) Q = atof(argv[2]);
  cout << "Possible command line arguments: <desired phase shift in degrees> <Q value>" << endl;
  cout << "Running with the following settings:" << endl;
  cout << "Desired average phase shift Phi0 = " << Phi0 << endl;
  cout << "Exponent Q = " << Q << endl;
  
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
  
  //Creating a canvas for plotting
  TCanvas *c = new TCanvas("c","c",1024,768);
  gStyle->SetOptStat(0);
  c->SetGrid(1,1);
  
  //Creating a frame for plotting
  TH1* frame = new TH1F("frame",Form("#Phi versus #omega for #Phi_{0}=%.0f, Q=%.2f, #omega_{0,A}=%.2f Hz, #omega_{0,B}=%.2f kHz",Phi0,Q,omega0A,omega0B/1000.),100,15,20000);
  frame->GetXaxis()->SetTitle("#omega [Hz]");
  frame->GetYaxis()->SetTitle("#Phi(#omega)");
  frame->SetMaximum(-0.9*Phi0*M_PI/180.);
  frame->SetMinimum(-1.1*Phi0*M_PI/180.);
  frame->Draw();
  
  //Creating a ROOT function for Phi(omegA), setting its parameters and plotting it
  TF1* phasefunc = new TF1("phasediff",phasediff,0.1,30000,3);
  phasefunc->SetParameters(xi,Q,omega0);
  phasefunc->SetLineColor(2);
  phasefunc->Draw("SAME");
  
  //Setting a logarithmic axis and saving the plot in png
  c->SetLogx(1);
  c->Modified();
  c->Print(Form("pngplots/phasefunc_ave%.0f_Q%.2f.png",Phi0,Q));
}