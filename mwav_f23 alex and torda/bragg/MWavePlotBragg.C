
#include <iostream>
#include <fstream>
#include <vector>
 
void MWavePlotBragg(){
  // read in data
  vector<Double_t> vvx;
  vector<Double_t> vvy;
  Double_t xdat,ydat;
 
  // Read in Data
  fstream infile;
  TString *fname = new TString("100 bragg");
  infile.open(*fname, ios_base::in);
 while (infile>>xdat>>ydat){
	// use for single slit:
    ydat=ydat+0.125;
    vvx.push_back(xdat) ;
    vvy.push_back(ydat) ;
  
  }
  infile.close();
 
  Int_t vvsize = vvx.size();
  cout<<"Data size = "<<vvsize<< endl;
  // histogram parameters
  Int_t nbin = 360;       // number of bins in the final plot
 
  Double_t xmi = vvx[0], xma = vvx[0], ymi = vvy[0], yma = vvy[0];   //check the x and y range
  for (Int_t i=0; i!=vvsize; i++){
    if (vvx[i] > xma) xma = vvx[i]; 
    if (vvx[i] < xmi) xmi = vvx[i]; 
    if (vvy[i] > yma) yma = vvy[i]; 
    if (vvy[i] < ymi) ymi = vvy[i]; 
  }
  Double_t dxrange = (xma-xmi);
  Double_t dyrange = (yma-ymi);

  Double_t hrange = xma-xmi;
  Double_t binwidth = hrange/nbin;
  
  cout << "Data X range        = "<< dxrange  << endl; 
  cout << "Data Y range        = "<< dyrange  << endl; 
  cout << "Histogram bins      = "<< nbin     << endl; 
  cout << "Histogram range     = "<< hrange   << endl; 
  
  TCanvas *myc1 =new TCanvas("myc1"); 
  // book histogram
  TProfile *hist1 = new TProfile("hist1","Raw Data",nbin,xmi,xma);
 
  for (Int_t i=0; i!=vvsize; i++) {
  hist1->Fill(vvx[i],vvy[i],1.0);}
  hist1->GetXaxis()->SetTitle("X axis title");
  hist1->GetYaxis()->SetTitle("Y axis title");
  hist1->Draw();

  //calibration and plot in terms of angle
  double intercept=336.2;
  double slope=-64.51;
  double Yerror=0.01;

  TH1F *hist2 = new TH1F("hist2",*fname, 1800,-90.0, 90.0);
  for(int jx=1; jx<vvsize; jx++){
    double angle =slope*vvx[jx] + intercept;  //conversion to Angle
    int binloc=hist2 ->FindBin(angle);
    double yvalue= hist2 ->GetBinContent(binloc); //duplicated data - remove
    if(yvalue != 0.0) continue;
    hist2 -> Fill(angle,vvy[jx]);
    hist2 ->SetBinError(binloc,Yerror);
  }

  TCanvas *myc2 =new TCanvas("myc2");  
  hist2->GetXaxis()->SetTitle("Angle (degree)   ");
  hist2->GetYaxis()->SetTitle("Intensity        ");
  hist2 ->SetMarkerStyle(20);
  hist2->Draw();

}
 
