
#include "TFile.h"
#include "TCanvas.h"

Double_t Linfit(Double_t *x, Double_t *par)
{
  double fitval=par[0]*x[0]+par[1];  //par0 is slope, par1 is intercept
  return fitval;
}

void LinearFitDistance(){

  gStyle ->SetOptFit(11111111);
  double xx[35],yy[35];
  double xerror[35];
  double yerror[35];
  //enter data


  int ndata=14;

  xx[0]=1;
  xx[1]=2;
  xx[2]=3;
  xx[3]=4;
  xx[4]=5;
  xx[5]=6;
  xx[6]=7;
  xx[7]=8;
  xx[8]=9;
  xx[9]=10;
  xx[10]=11;
  xx[11]=12;
  xx[12]=13;
  xx[13]=14;

  yy[0]=20.92;
  yy[1]=22.25;
  yy[2]=23.65;
  yy[3]=25.18;
  yy[4]=26.61;
  yy[5]=27.98;
  yy[6]=29.98;
  yy[7]=30.81;
  yy[8]=32.2;
  yy[9]=33.65;
  yy[10]=35;
  yy[11]=36.54;
  yy[12]=37.82;
  yy[13]=39.24;

  for(int i=0;i<ndata;i++) {
    //xx[i] = sin(i*5*3.14/180);
    // xerror[i] = 0.1;
    yerror[i] = 0.2;
  }

  double par[10];  
  TCanvas *cx2 = new TCanvas("cx1"," Linear fit");
  TGraphErrors *gtdata = new TGraphErrors(ndata,xx,yy,xerror,yerror);
  TF1 *myfit = new TF1("myfit",Linfit,0.0,90,2);  //low range, upper range, # of fit parameters
  myfit->SetParameter(0, 1.0);  //initial parameter
  myfit->SetParameter(1, 1.0);
  gtdata ->Fit("myfit","R"," ",0.0,60);  //fit range is from 0.0 to 2.0

  // TF1 *theory = new TF1("theory", "1.442*x", 0, 1.0);

  gtdata->SetTitle("Interferometer fit");
  gtdata->GetXaxis()->SetTitle("Peak Location (n)");
  gtdata->GetYaxis()->SetTitle("Distance between plates (cm)");
  gtdata ->Draw("AP");
  // theory->SetLineColor(4);
  // theory ->Draw("SAME");
  
}
  

