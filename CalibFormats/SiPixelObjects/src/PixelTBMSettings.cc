//
// This class provide a base class for the
// pixel ROC DAC data for the pixel FEC configuration
//
//
//
//

#include "CalibFormats/SiPixelObjects/interface/PixelTBMSettings.h"
#include "CalibFormats/SiPixelObjects/interface/PixelTimeFormatter.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <ios>
#include <assert.h>
#include <stdexcept>


using namespace pos;


PixelTBMSettings::PixelTBMSettings(std::vector < std::vector< std::string> > &tableMat):PixelConfigBase("","",""){
  std::cout << "This constructor is not supported" << std::endl;
  assert(0);
  /*std::string mthn = "]\t[PixelTBMSettings::PixelTBMSettings()]\t\t\t    " ;
  std::vector< std::string > ins = tableMat[0];
  std::map<std::string , int > colM;
  std::vector<std::string > colNames;

  

     EXTENSION_TABLE_NAME:     (VIEW:)

     CONFIG_KEY 			       NOT NULL VARCHAR2(80)
     KEY_TYPE				       NOT NULL VARCHAR2(80)
     KEY_ALIAS  			       NOT NULL VARCHAR2(80)
     VERSION						VARCHAR2(40)
     KIND_OF_COND			       NOT NULL VARCHAR2(40)
     TBM_NAME						VARCHAR2(200)
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
      
      analogInputBias_  = atoi(tableMat[1][colM["ANLG_INBIAS_VAL"]].c_str());
      analogOutputBias_ = atoi(tableMat[1][colM["ANLG_OUTBIAS_VAL"]].c_str());
      analogOutputGain_ = atoi(tableMat[1][colM["ANLG_OUTGAIN_VAL"]].c_str());
      
      if( tableMat[1][colM["TBM_MODE"]] == "SingleMode"){
	singlemode_=true;
      }
      else{
	singlemode_=false;
      }
    }*/
}//end contructor

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

PixelTBMSettings::PixelTBMSettings(std::string filename):
  PixelConfigBase("","",""){

    std::string mthn = "]\t[PixelTBMSettings::PixelTBMSettings()]\t\t\t    " ;
    if (filename[filename.size()-1]=='t'){

	std::ifstream in(filename.c_str());

	if (!in.good()){
	    std::cout << __LINE__ << mthn << "Could not open:"<<filename<<std::endl;
	    throw std::runtime_error("Failed to open file "+filename);
	}
	else {
	  // std::cout << "Opened:"<<filename<<std::endl;
	}
	
       	std::string tag;
	in >> tag;
	if(tag.compare("digital")==0){//digital
		tbmType_= true; 
		std::cout << "digital TBM" << std::endl;
		in >> tag;
		tbmP1 = new PixelP1TBMSettings(in,tag);
	}
	else{//analog
		tbmType_ = false;
		std::cout<< "analog TBM, tag: " << tag  << std::endl;
		if(tag.compare("analog")==0){
			in >> tag;
		}
		std::cout<< "tag is now: " << tag << std::endl;
		tbmP0 = new PixelP0TBMSettings(in,tag);
	}
    }
    else{
	std::cout << "ERROR: Binary not supported" << std::endl;
	assert(0);
    }


}

void PixelTBMSettings::setTBMGenericValue(std::string what, int value) 
{
 if(tbmType_ == true ){
	tbmP1->setTBMGenericValue(what, value);
 }
 else{
	tbmP0->setTBMGenericValue(what, value);
 }
}
 
void PixelTBMSettings::writeBinary(std::string filename) const {

    std::ofstream out(filename.c_str(),std::ios::binary);

    if(tbmType_ == true){
	tbmP1->writeBinary(out);
    }
    else{
	tbmP0->writeBinary(out);
    }

}

void PixelTBMSettings::writeASCII(std::string dir) const {
  
    if(tbmType_ == true){
	tbmP1->writeASCII(dir);
    }
    else{
	tbmP0->writeASCII(dir);
    }
}

void PixelTBMSettings::generateConfiguration(PixelFECConfigInterface* pixelFEC,
					     PixelNameTranslation* trans,
    					     bool physics, bool doResets) const{
    if (tbmType_== true){//have a digital one
	//do digital stuff
	tbmP1->generateConfiguration(pixelFEC, trans, physics, doResets);
    }
    else{//analog
	tbmP0->generateConfiguration(pixelFEC, trans, physics, doResets);
    }
}
//=============================================================================================
void PixelTBMSettings::writeXMLHeader(pos::PixelConfigKey key, 
                                      int version, 
                                      std::string path, 
                                      std::ofstream *outstream,
                                      std::ofstream *out1stream,
                                      std::ofstream *out2stream) const
{
  std::string mthn = "]\t[PixelTBMSettings::writeXMLHeader()]\t\t\t    " ;
  std::stringstream fullPath ;
  fullPath << path << "/Pixel_TbmParameters_" << PixelTimeFormatter::getmSecTime() << ".xml" ;
  std::cout << __LINE__ << mthn << "Writing to: " << fullPath.str() << std::endl ;
  
  outstream->open(fullPath.str().c_str()) ;
  
  *outstream << "<?xml version='1.0' encoding='UTF-8' standalone='yes'?>"			 	     << std::endl ;
  *outstream << "<ROOT xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance'>" 		 	             << std::endl ;
  *outstream << " <HEADER>"								         	     << std::endl ;
  *outstream << "  <TYPE>"								         	     << std::endl ;
  *outstream << "   <EXTENSION_TABLE_NAME>PIXEL_TBM_PARAMETERS</EXTENSION_TABLE_NAME>"          	     << std::endl ;
  *outstream << "   <NAME>Pixel TBM Parameters</NAME>"				         	             << std::endl ;
  *outstream << "  </TYPE>"								         	     << std::endl ;
  *outstream << "  <RUN>"								         	     << std::endl ;
  *outstream << "   <RUN_TYPE>Pixel TBM Parameters</RUN_TYPE>" 		                                     << std::endl ;
  *outstream << "   <RUN_NUMBER>1</RUN_NUMBER>"					         	             << std::endl ;
  *outstream << "   <RUN_BEGIN_TIMESTAMP>" << pos::PixelTimeFormatter::getTime() << "</RUN_BEGIN_TIMESTAMP>" << std::endl ;
  *outstream << "   <LOCATION>CERN P5</LOCATION>"                                                            << std::endl ; 
  *outstream << "  </RUN>"								         	     << std::endl ;
  *outstream << " </HEADER>"								         	     << std::endl ;
  *outstream << ""										 	     << std::endl ;
  *outstream << " <DATA_SET>"								         	     << std::endl ;
  *outstream << "  <PART>"                                                                                   << std::endl ;
  *outstream << "   <NAME_LABEL>CMS-PIXEL-ROOT</NAME_LABEL>"                                                 << std::endl ;
  *outstream << "   <KIND_OF_PART>Detector ROOT</KIND_OF_PART>"                                              << std::endl ;
  *outstream << "  </PART>"                                                                                  << std::endl ;
  *outstream << "  <VERSION>"             << version      << "</VERSION>"				     << std::endl ;
  *outstream << "  <COMMENT_DESCRIPTION>" << getComment() << "</COMMENT_DESCRIPTION>"			     << std::endl ;
  *outstream << "  <CREATED_BY_USER>"     << getAuthor()  << "</CREATED_BY_USER>"  			     << std::endl ;
  *outstream << " "				         	                                             << std::endl ;
}

//=============================================================================================
void PixelTBMSettings::writeXML(std::ofstream *outstream,
                                std::ofstream *out1stream,
                                std::ofstream *out2stream) const 
{
  if(tbmType_ == true ){
	tbmP1->writeXML(outstream, out1stream, out2stream);
  }
  else{
	tbmP0->writeXML(outstream, out1stream, out2stream);
  }
}
//=============================================================================================
void PixelTBMSettings::writeXMLTrailer(std::ofstream *outstream,
                                       std::ofstream *out1stream,
                                       std::ofstream *out2stream) const 
{
  std::string mthn = "]\t[PixelTBMSettings::writeXMLTrailer()]\t\t\t    " ;
  
  *outstream << " " 						    	 	              	             << std::endl ;
  *outstream << " </DATA_SET>" 						    	 	              	     << std::endl ;
  *outstream << "</ROOT> "								              	     << std::endl ;

  outstream->close() ;
}
