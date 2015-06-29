// author K. Ecklund
#include "pixelROCscurve.h"
#include "TF1.h"
#include "TF2.h"
#include "TFile.h"
#include "TMath.h"
#include <iostream>

using namespace std;

pixelROCscurve::pixelROCscurve(){
  //  cout << "In pixelROCscurve"<<endl;
  for(unsigned int row=0;row<80;row++){
    for(unsigned int col=0;col<52;col++){
      scurve[row][col]=0;
      turnon_[row][col]=0;
    }
  }
}

void pixelROCscurve::init(unsigned int linkid, unsigned int rocid,
			  unsigned int nvcal, unsigned int vcalmin, 
			  unsigned int vcalmax, int ntrig){
  //cout << "\npixelROCscurve::init" << endl;
  linkid_=linkid;
  rocid_=rocid;
  nvcal_=nvcal;
  vcalmin_=vcalmin;
  vcalmax_=vcalmax;
  ntrig_=ntrig;
  TString name="Ln";
  name+=(linkid_);
  name+="ROC";
  name+=(rocid_);
  TString abrev = name+"threshold";

  //cout << "01 " << abrev << " " << name <<endl;
  threshold1d = new TH1F(abrev,name,120,0.,120.);//255,0.,255
  //cout << "02"<<endl;
  abrev+="s";
  //cout << "03"<<endl;
  threshold = new TH2F(abrev,"scurve:mean",
		       kmaxcol_-kmincol_+1,kmincol_-0.5,kmaxcol_+0.5,
		       kmaxrow_-kminrow_+1,kminrow_-0.5,kmaxrow_+0.5);
  //cout << "04"<<endl;
  abrev=name+"noise";
  //cout << "05"<<endl;
  noise1d = new TH1F(abrev,name,50,0.,10.);//100,0.,20.
  //cout << "06"<<endl;
  abrev+="s";
  //cout << "07"<<endl;
  noise =  new TH2F(abrev,"scurve:sigma",
		    kmaxcol_-kmincol_+1,kmincol_-0.5,kmaxcol_+0.5,
		    kmaxrow_-kminrow_+1,kminrow_-0.5,kmaxrow_+0.5);

  //cout << "08"<<endl;
  abrev=name+"fitprob";
  //cout << "09"<<endl;
  fitprob1d = new TH1F(abrev,name,101,0.,1.01);
  //cout << "10"<<endl;
  abrev+="s";
  //cout << "11"<<endl;
  fitprob =  new TH2F(abrev,"scurve:fitprob",
		      kmaxcol_-kmincol_+1,kmincol_-0.5,kmaxcol_+0.5,
		      kmaxrow_-kminrow_+1,kminrow_-0.5,kmaxrow_+0.5);
  //cout << "12"<<endl;
}

bool pixelROCscurve::filled(unsigned int row,unsigned int col){
  return (scurve[row][col]!=0);
}

bool pixelROCscurve::fit(unsigned int row, unsigned int col) {  
  if(scurve[row][col]==0) return false;  // only fit if filled
  //cout << "fitting " << rocid_ << " " << row << " " << col << endl;

  double kevents = (double) ntrig_;
//   double effo = 0.5/nevents;
//   for (int j=0; j<scurve[row][col]->GetNbinsX();j++){
//     scurve[row][col]->SetBinError(j,TMath::Sqrt(effo*(1.0-effo)/nevents));
//   }
  double effo ;
  for ( int i = 1; i < scurve[row][col]->GetNbinsX()+1; i++ ){
    effo = scurve[row][col]->GetBinContent(i);
    if (effo == 0) {
      //effo = 0.5/(double)kevents;
    } else  {
      if (effo >= 1) {
	effo = 1. - 0.5/(double)kevents;
      }
    }     
    scurve[row][col]->SetBinError(i, TMath::Sqrt(effo*(1.0-effo)/((double)kevents)));
  }
  
  // set up fit range
  //  double vmin = 40; 
  //  double vmax = 140;
  //  Double_t (*function)(Double_t*,Double_t*) = &pixelROCscurve::fitfcn;
//   TF1 fit = TF1("myscurve",&fitfcn,vcalmin_,vcalmax_,4);
  TF1 fit = TF1("myscurve",&fitfcn,vcalmin_,vcalmax_,2);

  // set up fit parameters
  fit.SetParNames("mean","sigma","coeff");
  //  Double_t coeff=1.0;

  int lowBin  = 0 ;
  int highBin = 0 ;
  int topBin  = 0 ;
  int effBin  = 0 ;
  
  int nBins = scurve[row][col]->GetNbinsX() ;
  
  // Determine where the threshold curve reaches the top
  
//   int    minBin   = scurve[row][col]->GetMinimumBin() ;
  int    maxBin   = scurve[row][col]->GetMaximumBin() ;
//   double minValue = scurve[row][col]->GetBinContent(minBin) ;
  double maxValue = scurve[row][col]->GetBinContent(maxBin) ;
  
  // Determine the starting point of the threshold curve   
  lowBin = 1; 
  for (int bin=1; bin<=nBins; bin++) {
    if( scurve[row][col]->GetBinContent(bin) > 0 ) {
      lowBin = bin ;
      break ;
    } 
  }
  lowBin -= 1 ;
  
  // Find the saturation level begins, starting from the end point backwardsfillthr
  topBin = nBins ;
  for (int bin=nBins; bin>0; bin--) {
    if( scurve[row][col]->GetBinContent(bin) > 0 ) {
      topBin = bin ;
      break ;
    } 
  }
  topBin += 1;
  
  // Finalize the search
  highBin = nBins -1 ;
  for (int bin=topBin; bin>0; bin--) {
    if( scurve[row][col]->GetBinContent(bin) == maxValue ) {
      highBin = bin ;
      break ;
    } 
  }
  
  // Search first bin reaching saturation
  effBin = 0 ;
  for (int bin=highBin; bin>0; bin--) {
    if( scurve[row][col]->GetBinContent(bin) < maxValue ) {
      effBin = bin ;
      break ;
    } 
  }
  effBin += 1 ;
  
  effBin = maxBin + 3; // temporary patch (remove)
  
  if( lowBin > effBin ) {
    int temp = lowBin ;
    lowBin = effBin ;
    effBin = temp ;
  }
  if( lowBin == effBin ) {
    lowBin -= 1 ;
    effBin += 1 ;
  }
  
  // Define the starting values of the fit parameters
  double mean  = (double)(effBin + lowBin) / 2.  ;
  double sigma = (double)(effBin - lowBin) / 3; //2.2 ;
  
  
  //   Double_t sigma = 2;
  Double_t thresh = mean;//84.;//turnon_[row][col]+2;
  //   fit.SetParameters(thresh,sigma,coeff);
  fit.SetParameters(thresh,sigma);
  //   Double_t max=scurve[row][col]->GetMaximum(); 
  //   Double_t min=0;  // should fix this parameter
  //   Double_t sigma = 2;
  //   Double_t thresh = turnon_[row][col]+2;
  //   fit.SetParameters(min,max,sigma,thresh);
  //  scurve[row][col]->Fit("myscurve","RQL");// N = no plots; 0= no draw
  scurve[row][col]->Fit("myscurve","QR");// N = no plots; 0= no draw

  //if(fit->Good()) {    // save results to histogram
//   std::cout << "c=" <<col << " r="<< row 
// // 	    << " threshold=" << fit.GetParameter(3)
// // 	    << " sigma=" << fit.GetParameter(2) 
// 	    << " threshold=" << fit.GetParameter(0)
// 	    << " sigma=" << fit.GetParameter(1) 
// 	    << " prob="<< fit.GetProb() << std::endl;
    threshold1d->Fill(fit.GetParameter(0));
    threshold->Fill(col,row,fit.GetParameter(0));
    noise1d->Fill(fit.GetParameter(1));
    noise->Fill(col,row,fit.GetParameter(1));
    fitprob1d->Fill(fit.GetProb());
    fitprob->Fill(col,row,fit.GetProb());
    if (fit.GetParameter(1)>4) noisyCells.push_back(std::make_pair<unsigned int, unsigned int>(row,col));
    if (fit.GetParameter(1)<0.3) errorCells.push_back(std::make_pair<unsigned int, unsigned int>(row,col));

    //cout << "end"<<endl;
//     threshold1d->Fill(fit.GetParameter(3));
//     threshold->Fill(col,row,fit.GetParameter(3));
//     noise1d->Fill(fit.GetParameter(2));
//     noise->Fill(col,row,fit.GetParameter(2));
//     fitprob1d->Fill(fit.GetProb());
//     fitprob->Fill(col,row,fit.GetProb());
//     if (fit.GetParameter(2)>4) noisyCells.push_back(std::make_pair<unsigned int, unsigned int>(row,col));
    //  }
    return true;
}


void pixelROCscurve::draw(unsigned int row,unsigned int col){
  scurve[row][col]->Draw();
}

void pixelROCscurve::drawThresholds(){
  threshold->SetStats(false);
  threshold->GetXaxis()->SetTitle("col");
  threshold->GetYaxis()->SetTitle("row");
  threshold->SetMinimum(50.);
  threshold->SetMaximum(150.);
  threshold->Draw("colz");
}
void pixelROCscurve::drawNoises(){
  noise->SetStats(false);
  noise->GetXaxis()->SetTitle("col");
  noise->GetYaxis()->SetTitle("row");
  noise->SetMinimum(0.);
  noise->SetMaximum(10.);
  noise->Draw("colz");
}
void pixelROCscurve::drawFitProbs(){
  fitprob->SetStats(false);  
  fitprob->GetXaxis()->SetTitle("col");
  fitprob->GetYaxis()->SetTitle("row");
  fitprob->SetMinimum(0.);
  fitprob->SetMaximum(1.);
  fitprob->Draw("colz");
}

void pixelROCscurve::drawThreshold(){
  threshold1d->GetXaxis()->SetTitle("Vcal");
  threshold1d->Draw();
}
void pixelROCscurve::drawNoise(){
  //std::cout << "noise1d=" << noise1d << std::endl;
  noise1d->GetXaxis()->SetTitle("Vcal");
  noise1d->Draw();
}
void pixelROCscurve::drawFitProb(){
  fitprob1d->Draw();
}

void pixelROCscurve::fill(unsigned int row,unsigned int col,unsigned int vcal){
  if(row<kminrow_ || row>kmaxrow_ || col<kmincol_ || col>kmaxcol_ ) return;
  TH1F* hist=scurve[row][col];
  if (hist==0) {
    TString name="Channel=";
    name+=(linkid_);
    name=name+" ROC=";
    name+=(rocid_);
    name=name+" row=";
    name+=(row);
    name=name+" col=";
    name+=(col);
    TString cname="Ch";
    cname+=(linkid_);
    cname+="ROC";
    cname+=(rocid_);
    cname+="Row";
    cname+=(row);
    cname+="Col";
    cname+=(col);

    //cout << "pixelROCscurve creating " << name << " at Vcal=" << vcal << endl;
    hist=scurve[row][col]=new TH1F(cname,name,255,0.0,255.0);

    turnon_[row][col]=vcal;
  }
  hist->Fill(vcal, 1./((double)(ntrig_)));
  //hist->Fill(vcal, 1.);
}

Double_t pixelROCscurve::fitfcn(Double_t *x, Double_t *par)
{
  Double_t my_erf = 0.5*(1+TMath::Erf((x[0]-par[0])/(par[1]*sqrt(2.))));
// par[0] = mean
// par[1] = sigmam
// par[2] = coef
//   Double_t my_erf = 0.5*par[2]*(1+TMath::Erf((x[0]-par[0])/(par[1]*sqrt(2.))));
  //Double_t my_erf = par[0]+0.5*(par[1]-par[0])*(1+TMath::Erf( (x[0]-par[3])/(sqrt(2.0)*par[2])));
  return my_erf;
// par[0] = minimum
// par[1] = maximum
// par[2] = sigma (noise or slope near threshold)
// par[3] = mean  (threshold)

}

void pixelROCscurve::write(TFile* file){
  TString name="Link";
  name+=(linkid_);
  name+="ROC";
  name+=(rocid_);
  file->mkdir(name);
  file->cd(name);
  threshold->Write();
  noise->Write();
  fitprob->Write();
  threshold1d->Write();
  noise1d->Write();
  fitprob1d->Write();

  for(unsigned int row=kminrow_; row<kmaxrow_; row++) {
    for(unsigned int col=kmincol_; col<kmaxcol_; col++) {
      if(filled(row,col)) scurve[row][col]->Write();
    }
  }
}
