
#include <iostream>
#include <fstream>
#include <vector>

Double_t Pol2(Double_t *x, Double_t *par)
//Polynomial 
{ 
  Double_t arg1= 0; 
  arg1=par[0]+ par[1]*x[0]+ par[2]*x[0]*x[0] ; 
  Double_t fitval = arg1 ; 
  /* 
  cout <<par[0]<<" "<<par[1]<<" "<<par[2]<<"\n"; 
  cout <<par[3]<<" "<<par[4]<<" "<<par[5]<<"\n"; 
  cout <<x[0]<<" "<<arg1<<" "<<arg2<<" "<<arg3<<" "<<fitval<<" "<<"\n"; 
  */ 
  return fitval; 
}

Double_t DGauss(Double_t *x, Double_t *par)  
//Derivative of Gauss 
{
    Double_t xnew=(x[0]-par[1]);
    Double_t fitval=par[0]*(-xnew)/par[2]/par[2];
    fitval=fitval*exp(-xnew*xnew/2.0/par[2]/par[2]);
    return fitval;
}

Double_t DLorentz(Double_t *x, Double_t *par) 
//Derivative of Lorentz
{
  Double_t amp=par[0];
  Double_t avg=par[1];
  Double_t halfs=(par[2]/2.)*(par[2]/2.);
  Double_t fitval=2.0*amp*halfs/( pow( (x[0]-avg)*(x[0]-avg)+halfs, 2.0));
  fitval=(x[0]-avg)*fitval;
  return fitval;
}

Double_t Gauss(Double_t *x, Double_t *par)  
//Gauss fitting 
{
    Double_t xnew=(x[0]-par[1]);
    Double_t fitval=par[0]*exp(-xnew*xnew/2.0/par[2]/par[2]);
    return fitval;
}
Double_t DoubleGauss(Double_t *x, Double_t *par)  
//Two-Gaussian fitting with an extra constant term.
{
    Double_t xnew1=(x[0]-par[1]);
    Double_t xnew2=(x[0]-par[4]);
    Double_t fitval=par[0]*exp(-xnew1*xnew1/2.0/par[2]/par[2])+par[3]*exp(-xnew2*xnew2/2.0/par[5]/par[5])+par[6];
    return fitval;
}
Double_t GaussPoly(Double_t *x, Double_t *par)  
//Gauss+Pol3 fitting 
{
    Double_t xnew=(x[0]-par[1]);
    Double_t fitval=par[0]*exp(-xnew*xnew/2.0/par[2]/par[2]);
    fitval=fitval+par[3]+par[4]*xnew+par[5]*xnew*xnew+par[6]*xnew*xnew*xnew;
    return fitval;
}

Double_t GaussPoly2(Double_t *x, Double_t *par)  
//Gauss+Pol2 fitting 
{
    Double_t xnew=(x[0]-par[1]);
    Double_t fitval=par[0]*exp(-xnew*xnew/2.0/par[2]/par[2]);
    fitval=fitval+par[3]+par[4]*xnew+par[5]*xnew*xnew;
    return fitval;
}

void ComptonPlot(){
  // read in data
  vector<Double_t> vx;
  vector<Double_t> vy;
  Double_t xdat,ydat;

  // Read in Data
  fstream infile1;
  infile1.open("ba calibration.TKA", ios_base::in);
  while (infile1>>ydat){
    //cout <<ydat<<"\n"; 
    vy.push_back(ydat) ;
  }
  infile1.close();

  Int_t vsize = vy.size();
  //cout <<" Here I am "<<vsize<<"\n";

  // Read in Background
  fstream infile2;
  infile2.open("BlankBackground.TKA", ios_base::in);// bg-70degtka
  while (infile2>>xdat){
    //cout <<xdat<<"\n"; 
    vx.push_back(xdat) ;
  }
  infile2.close();
  vsize = vy.size();
  //cout <<" Here I am "<<vsize<<"\n";


 
  // histogram parameters
  Int_t ntbin = 16000;       // number of total bins in the data
  Int_t nbin = 200;       // number of  bins in the final plot

  // book histogram
  TH1F *hist1 = new TH1F("hist1","Signal",          nbin,0.0,16000.0);
  TH1F *hist2 = new TH1F("hist2","Background",      nbin,0.0,16000.0);
  TH1F *hist3 = new TH1F("hist3","  Sig - Background",nbin,0.0,16000.0);
  TH1F *hist4 = new TH1F("hist4","Sig - Bg - Poly",nbin,0.0,16000.0);

  hist1 ->Sumw2();  //take care of error properly
  hist2 ->Sumw2(); 
  hist3 ->Sumw2();  
  hist4 ->Sumw2();  

  //plot histogram
  for (Int_t i=0; i!=16000; i++)
    { 
  Double_t xx=i+0.5;
  hist1->Fill(xx,vy[i]);
  hist2->Fill(xx,vx[i]);
    }
  //enter the proper error0
  for (Int_t i=0; i!=nbin; i++)
    {
  double entry1= hist1->GetBinContent(i);
  hist1->SetBinError(i,sqrt(entry1)); //poisson error
  double entry2= hist2->GetBinContent(i);
  hist2->SetBinError(i,sqrt(entry2)); //poisson error
    }
  hist1->SetStats(kFALSE);
  hist1->GetXaxis()->SetTitle("X axis title");
  hist1->GetYaxis()->SetTitle("Y axis title");
  TCanvas *myc1 =new TCanvas("myc1","Sig");
  hist1->Draw("He");

  hist2->SetStats(kFALSE);
  hist2->GetXaxis()->SetTitle("X axis title");
  hist2->GetYaxis()->SetTitle("Y axis title");
  TCanvas *myc2 =new TCanvas("myc2","Back");
  hist2->Draw("He");

  //Get the signal minus background
  hist3 ->Add(hist1,hist2,1.0,-1.0);
  TCanvas *myc3 =new TCanvas("myc3","Final");
  hist3->Draw();

  /*
  //fitting
  Double_t par[7];  //par[0]= peak, par[1]=mean, par[2]=width, par[3]->par[6] for poly

  //define fit
  TF1 *fit1 = new TF1("fit1",DoubleGauss, 000.,16000.,7); // range & number of parameters 
  fit1 ->SetParameters(100000., 5000., 200.0, 100.0, 0.0, 0.0, 0.0); 
  Double_t xl1=4000.;
  Double_t xh1=9000.;
  hist3  ->Fit("fit1","R"," ",xl1,xh1);
  hist3->Draw();
  */

 //fitting
  Double_t par[6];  //par[0]= peak, par[1]=mean, par[2]=width, par[3]->par[6] for poly or 2nd Gaussian

  //define fit
  TF1 *fit1 = new TF1("fit1",GaussPoly2, 0.,16000.,7); // range & number of parameters 
  //These are the guesses for the values of the parameters. Enter values close to what you expect.  
  fit1 ->SetParameters(1000., 6000., 250.0, 100.0, 0.0., 0.0, 0.0); 
  //Edit these values to change the range of values included in the fit.
  Double_t xl1=4000.;
  Double_t xh1=12000.;

  hist3  ->Fit("fit1","R"," ",xl1,xh1);
  gStyle->SetOptFit(1111111);
  gStyle->SetOptStat(1111111);

  TCanvas *c0 = new TCanvas("c0","data",10,10,700,500);
  c0->cd(1);
  hist3->Draw("He");
  fit1->GetParameters(&par[0]);

	Double_t xmax=16000.0;
	Double_t xmin=0.0;
	Double_t sc = (xmax-xmin)/nbin;
  //Use this one for Gauss+Poly
     TH1F *polyhist = new TH1F("polyhist","bg poly",nbin,xmin,xmax);
     for(Int_t bin=1;bin<nbin;bin++) {
      //double wt =par[3]+par[4]*sc*bin+par[5]*sc*bin*sc*bin+par[6]*sc*bin*sc*bin*sc*bin;
      double xx=(sc*bin-sc/2.0)-par[1];
      double wt =par[3]+par[4]*xx+par[5]*xx*xx;

	polyhist->Fill(sc*bin,wt);
	polyhist->SetBinError(bin,1.0);
	}
	TCanvas *myc4 = new TCanvas("myc4","Sig-Polynomial");
	hist4->Add(hist3, polyhist,1.0,-1.0);
	hist4->Draw("He");


	//TF1 *myfit = hist3->GetFunction("fit1");
	//Double_t p0 = myfit->GetParamter(0);
	//polynom3 = new TF1("polynom3","p3+p4*x+p5*x*x+p6*x*x*x",xl1,xh1);
	//polynom3->Draw();  

}

