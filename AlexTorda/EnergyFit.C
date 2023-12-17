
#include "TFile.h"
#include "TCanvas.h"
#include "TMath.h"

Double_t Linfit(Double_t *x, Double_t *par)
{
  double fitval=par[0]*x[0]+par[1];  //par0 is slope, par1 is intercept
  return fitval;
}

Double_t ComptonFit(Double_t *x, Double_t *par) {
    Double_t angle = x[0]*(TMath::Pi()/180);
    return par[0]/(1+par[0]*(1-TMath::Cos(angle))/0.511);
}

void EnergyFit(){
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
        0.544,
        0.59,
        0.628,
        0.626,
        0.594,
        0.538,
        0.478,
        0.4323,
        0.39,
        0.34,
        0.306,
        0.237
    };
  double xerror[35] = {
    0.0027,
    0.0017,
    0.00247,
    0.00084,
    0.0021,
    0.003,
    0.003,
    0.0036,
    0.0038,
    0.0031,
    0.0012,
    0.0014,
    0.0025,
    0.00177,
    0.0026
  };
  double yerror[35];
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
  TF1 *myfit = new TF1("comptonfit",ComptonFit,-30,90,1);  //low range, upper range, # of fit parameters
  myfit->SetParameter(0, 1.0);  //initial parameter
  myfit->SetParameter(1, 1.0);
  gtdata ->Fit("comptonfit","R"," ",-30,90);  //fit range is from 0.0 to 2.0

//   TF1 *theory = new TF1("theory", "1.442*x", 0, 1.0);

  gtdata->SetTitle("Compton Fit");
  gtdata->GetXaxis()->SetTitle("Theta (in Deg)");
  gtdata->GetYaxis()->SetTitle("Scattered Photon Energy (in MeV)");
  gtdata ->Draw("AP");
//   theory->SetLineColor(4);
//   theory ->Draw("SAME");
}
  

