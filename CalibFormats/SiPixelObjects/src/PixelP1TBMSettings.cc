//
// This class provide a base class for the
// pixel ROC DAC data for the pixel FEC configuration
//
//
//
//

#include "CalibFormats/SiPixelObjects/interface/PixelP1DACNames.h"
#include "CalibFormats/SiPixelObjects/interface/PixelDACNames.h"
#include "CalibFormats/SiPixelObjects/interface/PixelP1TBMSettings.h"
#include "CalibFormats/SiPixelObjects/interface/PixelTimeFormatter.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <ios>
#include <assert.h>
#include <stdexcept>


using namespace pos;


PixelP1TBMSettings::PixelP1TBMSettings(std::vector < std::vector< std::string> > &tableMat){
  assert(0);
/*
  std::string mthn = "]\t[PixelP1TBMSettings::PixelP1TBMSettings()]\t\t\t    " ;
  std::vector< std::string > ins = tableMat[0];
  std::map<std::string , int > colM;
  std::vector<std::string > colNames;

  

     EXTENSION_TABLE_NAME:     (VIEW:)

     CONFIG_KEY 			       NOT NULL VARCHAR2(80)
     KEY_TYPE				       NOT NULL VARCHAR2(80)
     KEY_ALIAS  			       NOT NULL VARCHAR2(80)
     VERSION						VARCHAR2(40)
     KIND_OF_COND			       NOT NULL VARCHAR2(40)
     TBM_NAME						VARCHAR2(200):
     MODULE_NAME			       NOT NULL VARCHAR2(200)
     HUB_ADDRS  					NUMBER(38)
     TBM_MODE						VARCHAR2(200)
     ANLG_INBIAS_ADDR					NUMBER(38)
     ANLG_INBIAS_VAL			       NOT NULL NUMBER(38)
     ANLG_OUTBIAS_ADDR  				NUMBER(38)
     ANLG_OUTBIAS_VAL			       NOT NULL NUMBER(38)
     ANLG_OUTGAIN_ADDR  				NUMBER(38)
     ANLG_OUTGAIN_VAL			       NOT NULL NUMBER(38)

     N.B.: Here we should (MUST) get a single row referring to a particula module for a particula version.
  

  colNames.push_back("CONFIG_KEY" 	);
  colNames.push_back("KEY_TYPE"   	);
  colNames.push_back("KEY_ALIAS"  	);
  colNames.push_back("VERSION"    	);
  colNames.push_back("KIND_OF_COND"	);
  colNames.push_back("TBM_NAME"   	);
  colNames.push_back("MODULE_NAME"      );
  colNames.push_back("HUB_ADDRS"  	);
  colNames.push_back("TBM_MODE"   	);
  colNames.push_back("ANLG_INBIAS_ADDR" );
  colNames.push_back("ANLG_INBIAS_VAL"  );
  colNames.push_back("ANLG_OUTBIAS_ADDR");
  colNames.push_back("ANLG_OUTBIAS_VAL" );
  colNames.push_back("ANLG_OUTGAIN_ADDR");
  colNames.push_back("ANLG_OUTGAIN_VAL" );

  for(unsigned int c = 0 ; c < ins.size() ; c++){
    for(unsigned int n=0; n<colNames.size(); n++){
      if(tableMat[0][c] == colNames[n]){
        colM[colNames[n]] = c;
        break;
      }
    }
  }//end for
  for(unsigned int n=0; n<colNames.size(); n++){
    if(colM.find(colNames[n]) == colM.end()){
      std::cerr << __LINE__ << mthn << "Couldn't find in the database the column with name " << colNames[n] << std::endl;
      assert(0);
    }
  }
 
  if(tableMat.size() >1)
    {
      //std::cout << __LINE__ << mthn << "Module from DB: " << tableMat[1][colM["MODULE_NAME"]]<< std::endl ;
      PixelROCName tmp(tableMat[1][colM["MODULE_NAME"]]);
      rocid_ = tmp ;
      //std::cout << __LINE__ << mthn << "Built ROCNAME: " << rocid_.rocname()<< std::endl ;

#if 0      
      analogInputBias_  = atoi(tableMat[1][colM["ANLG_INBIAS_VAL"]].c_str());
      analogOutputBias_ = atoi(tableMat[1][colM["ANLG_OUTBIAS_VAL"]].c_str());
      analogOutputGain_ = atoi(tableMat[1][colM["ANLG_OUTGAIN_VAL"]].c_str());

      if( tableMat[1][colM["TBM_MODE"]] == "SingleMode"){
	singlemode_=true;
      }
      else{
	singlemode_=false;
      }
     #endif
    }*/
}//end contructor

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

PixelP1TBMSettings::PixelP1TBMSettings(std::ifstream& in, std::string& tag){
  
	PixelROCName tmp(tag);
	rocid_=tmp;
	std::cout << "Successfuly make the rocid: " << rocid_ << std::endl;
        unsigned int tmpint;	

	in >> tag;
	//std::cout << "Tag="<<tag<<std::endl;
	assert(tag=="TBMAAutoReset:");
	in >> tmpint;
	TBMAAutoReset_=tmpint;

	in >> tag;
	//std::cout << "Tag="<<tag<<std::endl;
	assert(tag=="TBMBAutoReset:");
	in >> tmpint;
	TBMBAutoReset_=tmpint;

	in >> tag;
	//std::cout << "Tag="<<tag<<std::endl;
	assert(tag=="TBMAPKAMCount:");
	in >> tmpint;
	TBMAPKAMCount_=tmpint;

	in >> tag;
	//std::cout << "Tag="<<tag<<std::endl;
	assert(tag=="TBMBPKAMCount:");
	in >> tmpint;
	TBMBPKAMCount_=tmpint;
	
	in >> tag;
	//std::cout << "Tag="<<tag<<std::endl;
	assert(tag=="TBMPLLDelay:");
	in >> tmpint;
	TBMPLLDelay_=tmpint;
	
	in >> tag;
	//std::cout << "Tag="<<tag<<std::endl;
	assert(tag=="TBMADelay:");
	in >> tmpint;
	TBMADelay_=tmpint;

	in >> tag;
	//std::cout << "Tag="<<tag<<std::endl;
	assert(tag=="TBMBDelay:");
	in >> tmpint;
	TBMBDelay_=tmpint;
	
	in.close();

  
}

void PixelP1TBMSettings::setTBMGenericValue(std::string what, int value) 
{
 if     ( what == "TBMAAutoReset" ) {TBMAAutoReset_ = (bool)value;}
 else if( what == "TBMBAutoReset" ) {TBMBAutoReset_ = (bool)value;}
 else if( what == "TBMAPKAMCount" ) {TBMAPKAMCount_ = (unsigned char)value;}
 else if( what == "TBMBPKAMCount" ) {TBMBPKAMCount_ = (unsigned char)value;}
 else if( what == "TBMPLLDelay" ) {TBMPLLDelay_ = (unsigned char)value;}
 else if( what == "TBMADelay" ) {TBMADelay_ = (unsigned char)value;}
 else if( what == "TBMBDelay" ) {TBMBDelay_ = (unsigned char)value;}
 else 
 {
   std::cout << __LINE__ << "]\t[PixelP1TBMSettings::setTBMGenericValue()]\t\tFATAL: invalid key/value pair: " << what << "/" << value << std::endl ; 
   assert(0);
 }
}
 
void PixelP1TBMSettings::writeBinary(std::ofstream& out) const {

    out << (char)rocid_.rocname().size();
    out.write(rocid_.rocname().c_str(),rocid_.rocname().size());

    out <<TBMAAutoReset_;
    out <<TBMBAutoReset_;
    out <<TBMAPKAMCount_;
    out <<TBMBPKAMCount_;
    out <<TBMPLLDelay_;
    out <<TBMADelay_;
    out <<TBMBDelay_;

}

void PixelP1TBMSettings::writeASCII(std::string& dir) const {

 PixelModuleName module(rocid_.rocname());

  if (dir!="") dir+="/";
  std::string filename=dir+"TBM_module_"+module.modulename()+".dat";

    std::ofstream out(filename.c_str());

    out << rocid_.rocname() << std::endl;

    out << "TBMAAutoReset: "<<(int)TBMAAutoReset_<<std::endl;
    out << "TBMBAutoReset: "<<(int)TBMBAutoReset_<<std::endl;
    out << "TBMAPKAMCount: "<<(int)TBMAPKAMCount_<<std::endl;
    out << "TBMBPKAMCount: "<<(int)TBMBPKAMCount_<<std::endl;
    out << "TBMPLLDelay: "<<(int)TBMPLLDelay_<<std::endl;
    out << "TBMADelay: "<<(int)TBMADelay_<<std::endl;
    out << "TBMBDelay: "<<(int)TBMBDelay_<<std::endl;
}


void PixelP1TBMSettings::generateConfiguration(PixelFECConfigInterface* pixelFEC,
					     PixelNameTranslation* trans,
					     bool physics, bool doResets) const{
    assert(trans != NULL);

    std::cout << "Begin PixelP1TBMSettings::generateConfiguration, with: " << std::endl;
    PixelHdwAddress theROC=*(trans->getHdwAddress(rocid_));


    int mfec=theROC.mfec();
    int mfecchannel=theROC.mfecchannel();
    int tbmchannel=14; 
    int tbmchannelB=15; 
    int hubaddress=theROC.hubaddress();

    if (doResets) {
      pixelFEC->injectrsttbm(mfec, 1);
      pixelFEC->injectrstroc(mfec,1);
    }
    pixelFEC->enablecallatency(mfec,0);
    pixelFEC->disableexttrigger(mfec,0);
    pixelFEC->injecttrigger(mfec,0);
    pixelFEC->callatencycount(mfec,79);

    //pixelFEC->synccontrolregister(mfec);

    if (doResets) pixelFEC->tbmcmd(mfec, mfecchannel, tbmchannel, hubaddress, 4, 2, 0x14, 0);
    if (!TBMAAutoReset_) pixelFEC->tbmcmd(mfec, mfecchannel, tbmchannel,  hubaddress, 4, 0, 0x80, 0);
    pixelFEC->tbmcmd(mfec, mfecchannel, tbmchannel, hubaddress, 4, 4, TBMAPKAMCount_, 0);
    pixelFEC->tbmcmd(mfec, mfecchannel, tbmchannel, hubaddress, 4, 1, 0xC0, 0); // setting the mode, we should always stay in the CAL = 0xC0 mode since the EventNumberClear Mode = 0x80 does not work correctly
    pixelFEC->tbmcmd(mfec, mfecchannel, tbmchannel, hubaddress, 4, 5, TBMADelay_, 0);
    pixelFEC->tbmcmd(mfec, mfecchannel, tbmchannel, hubaddress, 4, 7, TBMPLLDelay_, 0);

    if (doResets) pixelFEC->tbmcmd(mfec, mfecchannel, tbmchannelB, hubaddress, 4, 2, 0x14, 0);
    if (!TBMBAutoReset_) pixelFEC->tbmcmd(mfec, mfecchannel, tbmchannelB,  hubaddress, 4, 0, 0x80, 0);
    pixelFEC->tbmcmd(mfec, mfecchannel, tbmchannelB, hubaddress, 4, 4, TBMBPKAMCount_, 0);
    pixelFEC->tbmcmd(mfec, mfecchannel, tbmchannelB, hubaddress, 4, 1, 0xC0, 0); // setting the mode, we should always stay in the CAL = 0xC0 mode since the EventNumberClear Mode = 0x80 does not work correctly
    pixelFEC->tbmcmd(mfec, mfecchannel, tbmchannelB, hubaddress, 4, 5, TBMBDelay_, 0);

    std::cout << "End PixelP1TBMSettings::generateConfiguration" << std::endl;
} 


std::ostream& pos::operator<<(std::ostream& s, const PixelP1TBMSettings& tbm){

    s << "Module: "<<tbm.rocid_.rocname() <<std::endl; 
    s << "TBMAAutoReset: "<<int(tbm.TBMAAutoReset_)<<std::endl;
    s << "TBMBAutoReset: "<<int(tbm.TBMBAutoReset_)<<std::endl;
    s << "TBMAPKAMCount: "<<tbm.TBMAPKAMCount_<<std::endl;
    s << "TBMBPKAMCount: "<<tbm.TBMBPKAMCount_<<std::endl;
    s << "TBMPLLDelay: "<<tbm.TBMPLLDelay_<<std::endl;
    s << "TBMADelay: "<<tbm.TBMADelay_<<std::endl;
    s << "TBMBDelay: "<<tbm.TBMBDelay_<<std::endl;
    return s;

}
//=============================================================================================
void PixelP1TBMSettings::writeXML(std::ofstream *outstream,
                                std::ofstream *out1stream,
                                std::ofstream *out2stream) const 
{
  std::string mthn = "]\t[PixelP1TBMSettings::writeXML()]\t\t\t    " ;

  PixelModuleName module(rocid_.rocname());
  													     
  *outstream << "  <DATA>"										     << std::endl ;
  *outstream << "   <MODULE_NAME>"	<< rocid_.rocname()	 << "</MODULE_NAME>"			     << std::endl ;

  assert(0);
#if 0
  *outstream << "   <ANLG_INBIAS_VAL>"  <<(int)analogInputBias_  << "</ANLG_INBIAS_VAL>"		     << std::endl ;
  *outstream << "   <ANLG_OUTBIAS_VAL>" <<(int)analogOutputBias_ << "</ANLG_OUTBIAS_VAL>"		     << std::endl ;
  *outstream << "   <ANLG_OUTGAIN_VAL>" <<(int)analogOutputGain_ << "</ANLG_OUTGAIN_VAL>"		     << std::endl ;
  if (singlemode_) {											     	
    *outstream << "  <TBM_MODE>SingleMode</TBM_MODE>" 					 		     << std::endl ;
  }
  else{ 												     
    *outstream << "  <TBM_MODE>DualMode</TBM_MODE>"   					 		     << std::endl ;
  }													     
#endif
  *outstream << "  </DATA>"                                                               		     << std::endl ;
}

//=============================================================================================
void PixelP1TBMSettings::getDACs(std::map<std::string, unsigned int>& dacs) const {
  dacs.clear();
  
  dacs[k_DACName_TBMADelay] = TBMADelay_;
  dacs[k_DACName_TBMBDelay] = TBMBDelay_;
  dacs[k_DACName_TBMPLL] = TBMPLLDelay_;
}
