
#include "TFile.h"
#include "TCanvas.h"

Double_t Linfit(Double_t *x, Double_t *par)
{
  double fitval=par[0]*x[0]+par[1];  //par0 is slope, par1 is intercept
  return fitval;
}

void FitV2Angle(){
//find the relationship between V and Angle
  gStyle ->SetOptFit(11111111);
  double xx[35],yy[35];
  double xerror[35];
  double yerror[35];
  //enter data


  int ndata=6;
//angle
  yy[0]=5.0;
  yy[1]=23.0;
  yy[2]=40.0;
  yy[3]=80.0;
  yy[4]=100.0;
  yy[5]=120.0;
//voltage
  xx[0]=0.014;
  xx[1]=0.124;
  xx[2]=0.287;
  xx[3]=0.401;
  xx[4]=0.532;
  xx[5]=0.638;

  for(int i=0;i<ndata;i++) {
    xerror[i] = 0.01;
    yerror[i] = 1.0;
  }

  double par[10];  
  TCanvas *cx1 = new TCanvas("cx1"," Linear fit");
  TGraphErrors *gtdata = new TGraphErrors(ndata,xx,yy,xerror,yerror);
  gtdata ->Fit("pol1","R+"," ",0.0,5.0);  //linear fit & fit range is from 0.0 to 5.0
  gtdata ->GetXaxis()->SetTitle("Voltage (in volt) ");
  gtdata ->GetYaxis()->SetTitle(" Angle (in degree) ");
  gtdata ->Draw("AP");
  
}
  

