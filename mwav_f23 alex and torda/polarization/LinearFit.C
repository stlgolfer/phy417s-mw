
#include "TFile.h"
#include "TCanvas.h"
#include "TMath.h"

Double_t Linfit(Double_t *x, Double_t *par)
{
  double fitval = par[0] * x[0] + par[1]; // par0 is slope, par1 is intercept
  return fitval;
}

Double_t IntensityFitSquare(Double_t *theta, Double_t *par) {
	return par[0]*TMath::Power(TMath::Cos((TMath::Pi() / 180)*theta[0]),2);
}

Double_t IntensityFitFourth(Double_t *theta, Double_t *par) {
	return par[0]*TMath::Power(TMath::Cos((TMath::Pi() / 180)*theta[0]),4);
}

void LinearFit()
{

  gStyle->SetOptFit(11111111);
  double xx[35], yy[35];
  double xerror[35];
  double yerror[35];
  // enter data

  int ndata = 10;

  //xx[0] = 0;
  //xx[1] = 5;
  //xx[2] = 10;
  //xx[3] = 15;
  //xx[4] = 20;
  //xx[5] = 30;
  //xx[6] = 40;
  //xx[7] = 50;
  //xx[8] = 60;
  //xx[9] = 65;
  
  xx[0] = 90;
  xx[1] = 85;
  xx[2] = 80;
  xx[3] = 75;
  xx[4] = 70;
  xx[5] = 60;
  xx[6] = 50;
  xx[7] = 40;
  xx[8] = 30;
  xx[9] = 25;

  yy[0] = 0.0075;
  yy[1] = 0.01719;
  yy[2] = 0.02208;
  yy[3] = 0.02259;
  yy[4] = 0.07386;
  yy[5] = 0.271;
  yy[6] = 0.5947;
  yy[7] = 0.7393;
  yy[8] = 0.9579;
  yy[9] = 1.001;

  yerror[0] = 0.11018;
  yerror[1] = 0.11017;
  yerror[2] = 0.11018;
  yerror[3] = 0.11021;
  yerror[4] = 0.11026;
  yerror[5] = 0.110009;
  yerror[6] = 0.1102;
  yerror[7] = 0.1103;
  yerror[8] = 0.1101;
  yerror[9] = 0.110009;
  
  xerror[0] = 2;
  xerror[1] = 2;
  xerror[2] = 2;
  xerror[3] = 2;
  xerror[4] = 2;
  xerror[5] = 2;
  xerror[6] = 2;
  xerror[7] = 2;
  xerror[8] = 2;
  xerror[9] = 2;

  // for(int i=0;i<ndata;i++) {
  //   xx[i] = sin(i*5*3.14/180);
  //   xerror[i] = (1.80*3.14/180)*cos(i*3.14*5/180);
  //   yerror[i] = (1.91*3.14/180)*cos(asin(yy[i]));
  // }

  double par[10];
  TCanvas *cx2 = new TCanvas("cx1", " Linear fit");
  TGraphErrors *gtdata = new TGraphErrors(ndata, xx, yy, xerror, yerror);
  
  TF1 *myfit = new TF1("myfit", IntensityFitSquare, 0,10, 1); // low range, upper range, # of fit parameters
  TF1 *fourthfit = new TF1("fourthfit", IntensityFitFourth, 0, 1, 1);
  //myfit->SetParameter(0, 3);                       // initial parameter
  //myfit->SetParameter(1, 1.0);
  //gtdata->Fit("fourthfit", "R", " ", 25, 90); // fit domain is from 0.0 to 2.0
  gtdata->Fit("fourthfit", "R", " ", 25, 90);
  //TF1 *theory = new TF1("theory", "TMath::Power(TMath::Cos((TMath::Pi() / 180)*theta[0]),2)", 25, 90);

  gtdata->SetTitle("Polarization");
  gtdata->GetXaxis()->SetTitle("Incident Angle (Degrees)");
  gtdata->GetYaxis()->SetTitle("Intensity");
  gtdata->Draw("AP");
  //theory->SetLineColor(4);
  //theory->Draw("SAME");
  
  // would also like to do a 4th power fit to see if it's any better
}
