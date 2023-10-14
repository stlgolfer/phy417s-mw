
#include "TFile.h"
#include "TCanvas.h"
#include "TMath.h"

Double_t Linfit(Double_t *x, Double_t *par)
{
  double fitval=par[0]*x[0]+par[1];  //par0 is slope, par1 is intercept
  return fitval;
}

void LinearFitRefraction(){

  gStyle ->SetOptFit(11111111);
  double xx[35],yy[35];
  double xerror[35];
  double yerror[35];
  //enter data


  int ndata=8;

  xx[0] = TMath::Sin(0);
  xx[1] = TMath::Sin(5 * TMath::Pi()/180);
  xx[2] = TMath::Sin(10 * TMath::Pi()/180);
  xx[3] = TMath::Sin(15 * TMath::Pi()/180);
  xx[4] = TMath::Sin(20 * TMath::Pi()/180);
  xx[5] = TMath::Sin(25 * TMath::Pi()/180);
  xx[6] = TMath::Sin(30 * TMath::Pi()/180);
  xx[7] = TMath::Sin(35 * TMath::Pi()/180);

  yy[0] = TMath::Sin(-0.783 * TMath::Pi()/180);
  yy[1] = TMath::Sin(6.964 * TMath::Pi()/180);
  yy[2] = TMath::Sin(14.64 * TMath::Pi()/180);
  yy[3] = TMath::Sin(24.1 * TMath::Pi()/180);
  yy[4] = TMath::Sin(33.3 * TMath::Pi()/180);
  yy[5] = TMath::Sin(43.28 * TMath::Pi()/180);
  yy[6] = TMath::Sin(51.29 * TMath::Pi()/180);
  yy[7] = TMath::Sin(61.35 * TMath::Pi()/180);

  yerror[0] = TMath::Sin(4 * TMath::Pi()/180);
  yerror[1] = TMath::Sin(4.6 * TMath::Pi()/180);
  yerror[2] = TMath::Sin(7.4 * TMath::Pi()/180);
  yerror[3] = TMath::Sin(6.8 * TMath::Pi()/180);
  yerror[4] = TMath::Sin(5.5 * TMath::Pi()/180);
  yerror[5] = TMath::Sin(7.7 * TMath::Pi()/180);
  yerror[6] = TMath::Sin(6.3 * TMath::Pi()/180);
  yerror[7] = TMath::Sin(6.5 * TMath::Pi()/180);
  
  
  for(int i=0;i<ndata;i++) {
    xerror[i] = TMath::Sin(2 * TMath::Pi()/180);
  }

  double par[10];  
  TCanvas *cx2 = new TCanvas("cx1"," Linear fit");
  TGraphErrors *gtdata = new TGraphErrors(ndata,xx,yy,xerror,yerror);
  TF1 *myfit = new TF1("myfit",Linfit,0.0,90,2);  //low range, upper range, # of fit parameters
  myfit->SetParameter(0, 1.0);  //initial parameter
  myfit->SetParameter(1, 1.0);
  gtdata ->Fit("myfit","R"," ",0.0,60);  //fit range is from 0.0 to 2.0

  TF1 *theory = new TF1("theory", "1.442*x", 0, 1.0);

  gtdata->SetTitle("Snell's Law");
  gtdata->GetXaxis()->SetTitle("Sine of Incident Angle       ");
  gtdata->GetYaxis()->SetTitle("Sine of Refracted Angle      ");
  gtdata ->Draw("AP");
  theory->SetLineColor(4);
  theory ->Draw("SAME");
  
}
  

