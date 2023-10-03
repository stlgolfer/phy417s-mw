
#include <iostream>
#include <fstream>
#include <vector>
 
void MWaveDataSim(){
  // read in data
  vector<Double_t> vvx;
  vector<Double_t> vvy;
  Double_t xdat,ydat;
 
  // Read in Data
  fstream infile;
  infile.open("single slit 18cm.txt", ios_base::in);
 while (infile>>xdat>>ydat){
	// use for single slit:
    ydat=ydat+0.09;
    vvx.push_back(xdat) ;
    vvy.push_back(ydat) ;
  
  }
  infile.close();
 
  Int_t vvsize = vvx.size();
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
  hist1->Draw("L");

  double A0=1.0;
  double slope=-64.51;
  double intercept=336.2;
  TCanvas *myc2 =new TCanvas("myc2"); 
  // book histogram - convert x axis to angle
  TProfile *hist2 = new TProfile("hist2","Converted to Angle ",nbin,-90.0,90.0);
  for (Int_t i=0; i!=vvsize; i++) {
    Double_t angle =slope*vvx[i]+intercept;
  hist2->Fill(angle,vvy[i],1.);
      }
  hist2->GetXaxis()->SetTitle("Angle (degree)   ");
  hist2->GetYaxis()->SetTitle("Intensity        ");
  hist2 ->SetMarkerStyle(34);
  hist2->Draw("AL");

///////////////////////////////////////////
// Add the simulation
///////////////////////////////////////////

        double rad =57.2957795;
        double pi  =3.141592;
 
  // wl : wave length
  // rd : distance to the detector
  // rs : distance to the microwave generator
  // sl : distance to the slit (edge, not to the center of the slit) from 0
  // d  : slit width
  // h  : height of the slit
  // for a single slit, treat it a double slit with sl=0
 
        double wl=2.85; // 2.85
        double rd=51.4;
        double rs=47.1;
        double d=18;
        double sl=0;
        double h=18.0;
 
//Define histogram
   TH1F *pattern1 = new TH1F("pattern1","Simulted Diff/Interf Patten",nbin,-90.0,90.0);
 
   double hh=h/2.0;
   double step=wl/10.;
   double dangle = 1.5;
   double stepangle =dangle/5.0;
 
   cout << " wave length           = "<<wl <<endl;
   cout << " distance to source    = "<<rs <<endl;
   cout << " distance to detector  = "<<rd <<endl;
   cout << " slit height           = "<<h  <<endl;
   cout << " dist to slit edge (closest from origin) = "<<sl <<endl;
   cout << " slit width            = "<<d  <<endl;
 
   for (double tangle=-89.5; tangle < 90.0 ; tangle=tangle+1.0)
     { 
       double  sum=0.0;
   for (double angle=tangle-dangle; angle < tangle+dangle+stepangle/2.0; angle=angle+stepangle)
     {
       double theta=angle/rad;
       double zd=rd*cos(theta);
       double xd=rd*sin(theta);
 
//.......t is time.
   for (double t=0.0; t < 2.0*pi+0.25/2.0 ; t=t+0.25)
     {
       double subsum=0.0;
 
   for (double x1= sl; x1 < sl+d+step/2.0  ; x1=x1+step)
     {
   for (double y1=-hh; y1 <  hh+0.5    ; y1=y1+2.0 )
     {
 
     double ds=sqrt(rs*rs+x1*x1+y1*y1);
     double dd=sqrt(zd*zd+y1*y1+(xd-x1)*(xd-x1));
     subsum=subsum+sin(2*pi*(dd+ds)/wl+t);
     }     // end x1
     }     // end y1
 
   for (double x1=-sl; x1 > -sl-d-step/2.0 ; x1=x1-step)
     {
   for (double y1=-hh; y1 <  hh+0.5    ; y1=y1+2.0 )
     {
       double ds=sqrt(rs*rs+x1*x1+y1*y1);
       double dd=sqrt(zd*zd+y1*y1+(xd-x1)*(xd-x1));
       subsum=subsum+sin(2*pi*(dd+ds)/wl+t);
     }      //end x1
     }      //end y1
 
     sum=sum+subsum*subsum;
     }        //t
     }        //angle
 
    sum=sum/10000000.;
    pattern1 ->Fill(tangle,sum);
//  write (13,133) tangle,sum
 
     } //tangle
   TCanvas *myc4 =new TCanvas("myc4"); 
  pattern1->GetXaxis()->SetTitle("Angle (degree)   ");
  pattern1->GetYaxis()->SetTitle("Amplitude        ");
     pattern1 ->Draw();


     //Normalize the data and simulation and plot.
   TCanvas *myc5 =new TCanvas("myc5");
   int binmax = hist2->GetMaximumBin();
   double y1  = hist2->GetBinContent(binmax);
   int binmax = pattern1->GetMaximumBin();
   double y2  = pattern1->GetBinContent(binmax);
   double scale=y1/y2;
   hist2 ->Draw();
   pattern1 ->Scale(scale);
   pattern1 ->Draw("same");
}
 
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
 
