
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

  int ndata=11;
//angle
  yy[0]=140.0;
  yy[1]=130.0;
  yy[2]=120.0;
  yy[3]=110.0;
  yy[4]=100.0;
  yy[5]=90.0;
  yy[6]=80.0;
  yy[7]=70.0;
  yy[8]=60.0;
  yy[9]=50.0;
  yy[10]=40.0;
//voltage
  xx[0]=4.44;
  xx[1]=4.59;
  xx[2]=4.75;
  xx[3]=4.90;
  xx[4]=5.05;
  xx[5]=5.21;
  xx[6]=5.36;
  xx[7]=5.52;
  xx[8]=5.68;
  xx[9]=5.83;
  xx[10]=5.99;
>>>>>>> 8d1b6ca8abb92a8f408811304c93b581ad7e4b48

  for(int i=0;i<ndata;i++) {
    xerror[i] = 0.01;
    yerror[i] = 1.0;
  }

  double par[10];  
  TCanvas *cx1 = new TCanvas("cx1"," Linear fit");
  TGraphErrors *gtdata = new TGraphErrors(ndata,xx,yy,xerror,yerror);
  gtdata ->Fit("pol1","R+"," ",0.0,6.0);  //linear fit & fit range is from 0.0 to 5.0
>>>>>>> 8d1b6ca8abb92a8f408811304c93b581ad7e4b48
  gtdata ->GetXaxis()->SetTitle("Voltage (in volt) ");
  gtdata ->GetYaxis()->SetTitle(" Angle (in degree) ");
  gtdata ->Draw("AP");
  
}
  
