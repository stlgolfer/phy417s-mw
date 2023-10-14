
#include "TFile.h"
#include "TCanvas.h"

Double_t Linfit(Double_t *x, Double_t *par)
{
  double fitval=par[0]*x[0]+par[1];  //par0 is slope, par1 is intercept
  return fitval;
}

void LinearFitInter(){

  gStyle ->SetOptFit(11111111);
  double xx[35],yy[35];
  double xerror[35];
  double yerror[35];
  //enter data


  int ndata=5;

  xx[0]=1.61;
  xx[1]=2.97;
  xx[2]=4.28;
  xx[3]=5.58;
  xx[4]=7.32;

  yy[0]=21.1;
  yy[1]=31.5;
  yy[2]=41.5;
  yy[3]=51.5;
  yy[4]=64.6;

  for(int i=0;i<ndata;i++) {
    //xx[i] = sin(i*5*3.14/180);
    xerror[i] = 0.1;
    yerror[i] = 1;
  }

  double par[10];  
  TCanvas *cx2 = new TCanvas("cx1"," Linear fit");
  TGraphErrors *gtdata = new TGraphErrors(ndata,xx,yy,xerror,yerror);
  TF1 *myfit = new TF1("myfit",Linfit,0.0,90,2);  //low range, upper range, # of fit parameters
  myfit->SetParameter(0, 1.0);  //initial parameter
  myfit->SetParameter(1, 1.0);
  gtdata ->Fit("myfit","R"," ",0.0,60);  //fit range is from 0.0 to 2.0

  TF1 *theory = new TF1("theory", "1.442*x", 0, 1.0);

  gtdata->SetTitle("Interferometer fit");
  gtdata->GetXaxis()->SetTitle("Voltage");
  gtdata->GetYaxis()->SetTitle("Distance between plates");
  gtdata ->Draw("AP");
  theory->SetLineColor(4);
  theory ->Draw("SAME");
  
}
  

