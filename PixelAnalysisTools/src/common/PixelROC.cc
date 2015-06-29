#include "PixelROC.h"
#include "TH1F.h"
#include <iostream>

using namespace std;

pixelROC::pixelROC(){
  cout << "In pixelROC"<<endl;
  for(unsigned int row=0;row<10;row++){
    for(unsigned int col=0;col<10;col++){
      adc_hist[row][col]=0;
    }
  }
}

void pixelROC::init(unsigned int linkid, unsigned int rocid,unsigned int nvcal){
  linkid_=linkid;
  rocid_=rocid;
  nvcal_=nvcal;
}

bool pixelROC::filled(unsigned int row,unsigned int col){
  return (adc_hist[row][col]!=0);
}


void pixelROC::draw(unsigned int row,unsigned int col){
  adc_hist[row][col]->Draw();
}


void pixelROC::fill(unsigned int row,unsigned int col,unsigned int vcal,unsigned int adc){
  TH1F* hist=adc_hist[row][col];
  if (hist==0) {
    TString name="Channel=";
    name+=(linkid_);
    name=name+" ROC=";
    name+=(rocid_);
    name=name+" row=";
    name+=(row);
    name=name+" col=";
    name+=(col);
    hist=adc_hist[row][col]=new TH1F(name,name,nvcal_,0.0,255.0);
  }
  hist->Fill(vcal,adc/256);
}

