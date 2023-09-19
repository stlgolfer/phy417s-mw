
#include <iostream>
#include <fstream>
#include <string>
#include "stdlib.h"
#include "TH2.h"
#include "TF1.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TFile.h"
#include "TRandom.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "math.h"
#include "TStyle.h"
#include "TFile.h"
#include "TCanvas.h"

  

Double_t MYFUN(Double_t *x, Double_t *par)
{
  double angle=x[0]/57.3;
  double fitval=par[0]*(TMath::Power(cos(angle),par[1]))+par[2];  //A(cos(angle))^n+B
  return fitval;
}

void FitPolarization(){

  gStyle ->SetOptFit(11111111);
  double xx[19] = {0.,5., 10.,15., 20.,25., 30.,35., 40.,45., 50.,55., 60.,65., 70.,75., 80.,85., 90.};
  double yy[19] = {0.849,0.838,0.814,0.78,0.74,0.689,0.617,0.531,0.43,0.276,0.19,0.131,0.08,0.056,0.031,0.02,0.026,0.03,0.03};
  double xerror[19], yerror[19];
  int ndata=19;

  //double xx[10] = {0., 10., 20., 30., 40., 50., 60., 70., 80., 90.};
  //double yy[10] = {0.85, 0.81, 0.74, 0.61, 0.43, 0.19, 0.08, 0.03, 0.026, 0.03};
  //double xerror[12], yerror[12];
  //int ndata=10;
  
  for(int jj=0; jj<ndata; jj++){
    xerror[jj]=1.0; //error in degree
    yerror[jj]=0.05; //error in amplitude
    cout<< xx[jj]<<"+/-"<<xerror[jj]<<"  "<<yy[jj]<<"+/-"<<yerror[jj]<<endl;
  }
  //A(cos(angle))^n+B
  TCanvas *cx4 = new TCanvas("cx4","A(cos(angle))^n+b fit");
  TGraphErrors *gtdata = new TGraphErrors(ndata,xx,yy,xerror,yerror);
  TF1 *myfit = new TF1("myfit",MYFUN,0.0,90.0,3);
  myfit ->SetParameters(1.0,3.0,0.0);
  gtdata ->Fit("myfit","R"," ",0.0,90.0);  //fit range is from 0.0 to 90
  gtdata->SetTitle(" Polarization data");
  gtdata->GetXaxis()->SetTitle("Polarizer Orientation Angle (degree)");
  gtdata->GetYaxis()->SetTitle("Intensity (V)");
  gtdata->SetMarkerStyle(21);
  gtdata ->Draw("AP");

  TF1 *theory = new TF1("theory", "0.85*(cos(x/57.3))^2", 0, 90.0);
  theory->SetLineColor(4);  //blue
  theory ->Draw("SAME");

}



