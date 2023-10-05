
#include "TFile.h"
#include "TCanvas.h"

Double_t Linfit(Double_t *x, Double_t *par)
{
  double fitval = par[0] * x[0] + par[1]; // par0 is slope, par1 is intercept
  return fitval;
}

void LinearFit()
{

  gStyle->SetOptFit(11111111);
  double xx[35], yy[35];
  double xerror[35];
  double yerror[35];
  // enter data

  int ndata = 10;

  xx[0] = 0;
  xx[1] = 5;
  xx[2] = 10;
  xx[3] = 15;
  xx[4] = 20;
  xx[5] = 30;
  xx[6] = 40;
  xx[7] = 50;
  xx[8] = 60;
  xx[9] = 65;

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

  yerror[0] = 0.00018;
  yerror[1] = 0.00017;
  yerror[2] = 0.00018;
  yerror[3] = 0.00021;
  yerror[4] = 0.00026;
  yerror[5] = 0.000009;
  yerror[6] = 0.0002;
  yerror[7] = 0.0003;
  yerror[8] = 0.0001;
  yerror[9] = 0.000009;

  // for(int i=0;i<ndata;i++) {
  //   xx[i] = sin(i*5*3.14/180);
  //   xerror[i] = (1.80*3.14/180)*cos(i*3.14*5/180);
  //   yerror[i] = (1.91*3.14/180)*cos(asin(yy[i]));
  // }

  double par[10];
  TCanvas *cx2 = new TCanvas("cx1", " Linear fit");
  TGraphErrors *gtdata = new TGraphErrors(ndata, xx, yy, xerror, yerror);
  // TF1 *myfit = new TF1("myfit", Linfit, 0.0, 90, 2); // low range, upper range, # of fit parameters
  // myfit->SetParameter(0, 1.0);                       // initial parameter
  // myfit->SetParameter(1, 1.0);
  // // gtdata->Fit("myfit", "R", " ", 0.0, 60); // fit range is from 0.0 to 2.0

  // TF1 *theory = new TF1("theory", "1.442*x", 0, 1.0);

  gtdata->SetTitle("Snell's Law");
  gtdata->GetXaxis()->SetTitle("Sine of Incident Angle       ");
  gtdata->GetYaxis()->SetTitle("Sine of Refracted Angle      ");
  gtdata->Draw("AP");
  // theory->SetLineColor(4);
  // theory->Draw("SAME");
}
