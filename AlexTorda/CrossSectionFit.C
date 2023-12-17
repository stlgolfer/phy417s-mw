
#include "TFile.h"
#include "TCanvas.h"
#include "TMath.h"
#include <math.h>

Double_t Linfit(Double_t *x, Double_t *par)
{
  double fitval=par[0]*x[0]+par[1];  //par0 is slope, par1 is intercept
  return fitval;
}

Double_t CXFit(Double_t *x, Double_t *par) {
    Double_t angle = x[0]*(TMath::Pi()/180);
    Double_t Esoi = 1/(1+(0.662/0.511)*(1-TMath::Cos(angle)));
    return 0.5*TMath::Power(par[0],2)*TMath::Power(Esoi,2)*(Esoi+TMath::Power(Esoi,-1)-TMath::Power(TMath::Sin(angle),2));
}

Double_t CXfunc(double x) {
    double angle = (x)*(TMath::Pi()/180);
    double Esoi = 1/(1+(0.662/0.511)*(1-TMath::Cos(angle)));
    double re = 2.82*(pow(10,-13));
    return 0.5*pow(re,2)*pow(Esoi,2)*(Esoi+pow(Esoi,-1)-pow(TMath::Sin(angle),2));
}

void CrossSectionFit(){
    gStyle ->SetOptFit(11111111);
    double xx[35] = {
        -30,
        -20,
        -10,
        10,
        20,
        30,
        40,
        50,
        60,
        70,
        80,
        90
    };
    double yy[35] = {
        1.24,
        1.426,
        0.993,
        1.498,
        1.46,
        1.26,
        0.82,
        0.889,
        0.775,
        0.587,
        0.6601,
        0.00498
    };
  double yerror[35] = {
    0.23,
    0.22,
    0.18,
    0.14,
    0.22,
    0.19,
    0.19,
    0.189,
    0.232,
    0.178,
    0.129,
    0.135
  };
  double xerror[35];
  //enter data


  int ndata=10;

//   yy[0]=0.014;
//   yy[1]=0.124;
//   yy[2]=0.287;
//   yy[3]=0.401;
//   yy[4]=0.532;
//   yy[5]=0.638;
//   yy[6]=0.744;
//   yy[7]=0.848;
//   yy[8]=0.925;
//   yy[9]=0.975;

  for(int i=0;i<ndata;i++) {
    // xx[i] = sin(i*5*3.14/180);
    xerror[i] = 2;
    // yerror[i] = (1.91*3.14/180)*cos(asin(yy[i]));
  }

  double par[10];  
  TCanvas *cx2 = new TCanvas("cx1"," Linear fit");
  TGraphErrors *gtdata = new TGraphErrors(ndata,xx,yy,xerror,yerror);
  TF1 *myfit = new TF1("cxfit",CXFit,-30,90,1);  //low range, upper range, # of fit parameters
  myfit->SetParameter(0, 1.0);  //initial parameter
  myfit->SetParameter(1, 1.0);
  gtdata ->Fit("cxfit","R"," ",-30,90);  //fit range is from 0.0 to 2.0

  // TF1 *theory = new TF1("theory", "CXfunc(x)", 0, 1.0);

  gtdata->SetTitle("Compton Fit");
  gtdata->GetXaxis()->SetTitle("Theta (in Deg)");
  gtdata->GetYaxis()->SetTitle("Cross-Section (in Milibarns)");
  gtdata ->Draw("AP");
  // theory->SetLineColor(4);
  // theory ->Draw("SAME");
}
  

