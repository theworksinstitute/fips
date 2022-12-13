#include <iostream>
#include <fstream>
#include "TF1.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TStyle.h"

using namespace std;

//Frequency range in focus
double omegamin = 15;
double omegamax = 20000;

//Basic filter
double BandFilter(double Q, double f0, double f)
{
  return -4*atan(pow(f0/f,-Q));
}

//Three-stage filter with five parameters: Q1, Q2, xi1, xi2 and omega01
double phasediff(const double *x, const double *pars)
{
  //Frequency (sometimes denoted omega)
  double f = x[0];
  
  //Q exponent values
  double Q1 = pars[0];
  double Q2 = pars[1];
  double Q3 = Q1; //Based intuitively on symmetry principles
  
  //xi values
  double xi1 = pars[2];
  double xi2 = pars[3];
  double xi3 = xi1; //Based intuitively on symmetry principles
  
  //omega0 mean frequencies
  double f01 = pars[4];
  double f02 = f01*xi2/xi1; //Based intuitively on symmetry principles
  double f03 = f01*xi2*xi2; //Based intuitively on symmetry principles
  
  //Central frequencies (sometimes denoted as e.g. omega_{0,A,1})
  double f0A1 = f01/xi1;
  double f0A2 = f02/xi2;
  double f0A3 = f03/xi3;
  double f0B1 = f01*xi1;
  double f0B2 = f02*xi2;
  double f0B3 = f03*xi3;
  
  //Three stages
  double ret1 = BandFilter(Q1,f0A1,f) - BandFilter(Q1,f0B1,f);
  double ret2 = BandFilter(Q2,f0A2,f) - BandFilter(Q2,f0B2,f);
  double ret3 = BandFilter(Q3,f0A3,f) - BandFilter(Q3,f0B3,f);
  
  return ret1 + ret2 + ret3;
}

//Deviation from Phi0
double phasediff_phi0(const double *x, const double *pars)
{
  //The desired average
  double Phi0 = pars[5];

  return (phasediff(x,pars) - Phi0)*180./M_PI;
}

//Empirical formula for Q2(Phi0) based on numerical calculations
double Q2func(double Phi0)
{
  return -0.066607677026*Phi0;
}

//Empirical formula for xi1(Phi0) based on numerical calculations
double xi1func(double Phi0)
{
  return 1+(-0.0066800473*Phi0*Phi0*Phi0 + 0.0023085812*Phi0*Phi0 + 0.0006379221*Phi0);
}

//Empirical formula to correct for residual effects in the average
double Phi0mod(double Phi0)
{
  return 0.0054919*Phi0*Phi0*Phi0 - 0.0030961*Phi0*Phi0 + 0.98601*Phi0 - 0.00044568;
}

//Main routine
int main()
{
  
  //Empirical values based on numerical calculations
  double Q1  =  0.873465;
  double xi2 = 44.595068890;
  double f01 = 10.667937950;
  
  //Declaring a canvas and its options
  TCanvas *c = new TCanvas("c","c",1024,768);
  gStyle->SetOptStat(0);
  c->SetGrid(1,1);
  
  //Setting the plotting frame, labels and titles - for Phi(omega)
  TH1* frame = new TH1F("frame","#Phi(#omega) for various #Phi_{0} values",100,omegamin,omegamax);
  frame->GetXaxis()->SetTitle("#omega [Hz]");
  frame->GetYaxis()->SetTitle("#Phi(#omega)");
  frame->SetMinimum(-6*M_PI/10);
  frame->SetMaximum(0);
    
  //Setting the plotting frame, labels and titles - for Phi(omega)-Phi0
  TH1* frame2 = new TH1F("frame2","#Phi(#omega)-#Phi_{0} shown for various #Phi_{0} values",100,omegamin,omegamax);
  frame2->GetXaxis()->SetTitle("#omega [Hz]");
  frame2->GetYaxis()->SetTitle("#Phi(#omega)-#Phi_{0} [deg]");
  frame2->SetMinimum(-0.5);
  frame2->SetMaximum(0.5);
  
  //Drawing the Phi(omega) functions
  frame->Draw();
  TF1* phasefunc = new TF1("phasediff",phasediff,0.1,30000,5);
  //Looping over Phi0 values from -99 to -9 degrees
  int iPhi0 = 0;
  for(double Phi0 = -11*M_PI/20; Phi0<0; Phi0 += M_PI/20)
  {
    //Set function parameters (utilizing residual correction as well)
    phasefunc->SetParameters(Q1,Q2func(Phi0mod(Phi0)),xi1func(Phi0mod(Phi0)),xi2,f01);
    //Set function styles and draw
    phasefunc->SetLineColor(kOrange+iPhi0);
    phasefunc->SetLineStyle((iPhi0%4)+1);
    phasefunc->SetLineWidth(2+iPhi0/4);
    phasefunc->DrawCopy("SAME");
    //Calculate average to control remaining residual effects
    double thisavePhi0 = 0;
    int Nf = 100;
    double dfmult = pow(20000./15., 1./Nf);
    for(double f = omegamin; f<omegamax; f *= dfmult)
      thisavePhi0 += phasefunc->Eval(f)/Nf;
    cerr << Phi0 << " -> average: " << thisavePhi0 << " , ratio: " << thisavePhi0/Phi0 << endl;
    iPhi0++;
  }
  //Printing the canvas
  c->SetLogx(1);
  c->Modified();
  c->Print("pngplots/threestage/phasefunc_threestage_many.png");
  
  //Drawing the Phi(omega)-Phi0 functions
  frame2->Draw();
  //TF1 object to be plotted
  TF1* phasefunc_diff = new TF1("phasediff_phi0",phasediff_phi0,0.1,30000,6); 
  //Looping over Phi0 values from -99 to -9 degrees
  iPhi0 = 0;
  for(double Phi0 = -11*M_PI/20; Phi0<0; Phi0 += M_PI/20)
  {
    //Set function parameters (utilizing residual correction as well)
    phasefunc_diff->SetParameters(Q1,Q2func(Phi0mod(Phi0)),xi1func(Phi0mod(Phi0)),xi2,f01,Phi0);
    //Set function styles and draw
    phasefunc_diff->SetLineColor(kOrange+iPhi0);
    phasefunc_diff->SetLineStyle((iPhi0%4)+1);
    phasefunc_diff->SetLineWidth(2+iPhi0/4);
    phasefunc_diff->DrawCopy("SAME");
    iPhi0++;
  }
  //Printing the canvas
  c->SetLogx(1);
  c->Modified();
  c->Print("pngplots/threestage/phasefunc_threestage_many_diff.png");

  return 0;
} 
