
void Channel2Energy(){
 
  gStyle ->SetOptFit(11111111);

  int ndata=6;
  double xx[10]={
    986.4, // cd
    6881, // cs
    12013.2, // co-60
    13584.7,
    5375.9, // na
    13026.1
  }; //channel
  double xerror[10]={
    1.6, // cd
    0.3, //cs 
    0.82, // co-60
    0.8,
    0.26, // na
    1.27
  };
  double yy[10]={
    0.088, // cd
    0.662, // cs
    1.173, // co-60
    1.333,
    0.511, // na
    1.275
  }; //energy
  double yerror[10]={0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

  TCanvas *cx1 = new TCanvas("cx1","linear fit");
  TGraphErrors *gsdata = new TGraphErrors(ndata,xx,yy,xerror,yerror);  
  TF1 *fit1 = new TF1("fit1","pol1", 0,14000);  //polynomial of first degree
  fit1 ->SetParameters(0.0,1.0);
  gsdata ->Fit(fit1, "R");
  gsdata->SetTitle("Channel to Energy calibration");
  gsdata->GetXaxis()->SetTitle(" Channel Number        ");
  gsdata->GetYaxis()->SetTitle(" Energy (MeV)");
  gsdata ->Draw("AP");
}
