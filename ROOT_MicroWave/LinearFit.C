
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

  yy[0]=0.014;
  yy[1]=0.124;
  yy[2]=0.287;
  yy[3]=0.401;
  yy[4]=0.532;
  yy[5]=0.638;
  yy[6]=0.744;
  yy[7]=0.848;
  yy[8]=0.925;
  yy[9]=0.975;

  for(int i=0;i<ndata;i++) {
    xx[i] = sin(i*5*3.14/180);
    xerror[i] = (1.80*3.14/180)*cos(i*3.14*5/180);
    yerror[i] = (1.91*3.14/180)*cos(asin(yy[i]));
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
  

