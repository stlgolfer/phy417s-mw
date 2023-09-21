
#include "TFile.h"
#include "TCanvas.h"

Double_t Linfit(Double_t *x, Double_t *par)
{
  double fitval=par[0]*x[0]+par[1];  //par0 is slope, par1 is intercept
  return fitval;
}

void LinearFit(){

  gStyle ->SetOptFit(11111111);
  double xx[35],yy[35];
  double xerror[35];
  double yerror[35];
  //enter data


  int ndata=10;
  xx[0] = 10;
  xx[1] = 15;
  xx[2] = 20;
  xx[3] = 25;
  xx[4] = 30;
  xx[5] = 35;
  xx[6] = 40;
  xx[7] = 45;
  xx[8] = 50;
  xx[9] = 55;

  yy[0]=8.814;
  yy[1]=12.7;
  yy[2]=18.48;
  yy[3]=23.37;
  yy[4]=28.5;
  yy[5]=33.39;
  yy[6]=38.19;
  yy[7]=42.97;
  yy[8]=47.17;
  yy[9]=51.99;
  
  yerror[0]=8;
  yerror[1]=5;
  yerror[2]=12;
  yerror[3]=12;
  yerror[4]=11;
  yerror[5]=7;
  yerror[6]=12;
  yerror[7]=13;
  yerror[8]=14;
  yerror[9]=10;

  for(int i=0;i<ndata;i++) {
    xerror[i] = 2.22; // basically just constant error in angle
    // yerror[i] = // reflection angle varies though
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
  

