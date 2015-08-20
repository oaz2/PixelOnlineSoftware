#ifndef PixelTBMSettings_h
#define PixelTBMSettings_h
/**
* \file CalibFormats/SiPixelObjects/interface/PixelTBMSettings.h
* \brief This class implements..
*
*   This class contains all the functions that a Phase0 and Phase1 
*   PixelTBMSettings has.  This class will act as a guide in the sense
*   that it will direct every function call to the correct PixelTBMSetting 
*   object (PixelP0TBMSettings or PixelP1TBMSettings).  
*   In addition, this function is responsible for calling the correct object
*   based on the TBM being used (Phase0 or Phase1)
*
*/

#include "CalibFormats/SiPixelObjects/interface/PixelP1TBMSettings.h"
#include "CalibFormats/SiPixelObjects/interface/PixelP0TBMSettings.h"
#include <vector>
#include "CalibFormats/SiPixelObjects/interface/PixelConfigBase.h"
#include "CalibFormats/SiPixelObjects/interface/PixelFECConfigInterface.h"
#include "CalibFormats/SiPixelObjects/interface/PixelNameTranslation.h"

namespace pos{
/*!  \ingroup ConfigurationObjects "Configuration Objects"
*    
*  @{
*
*  \class PixelTBMSettings PixelTBMSettings.h
*  \brief This is the documentation about PixelTBMSettings...
*
*   A longer explanation will be placed here later
*
*/
  class PixelTBMSettings: public PixelConfigBase {

  public:
    //TODO: Add support for Phase1 TBM
    PixelTBMSettings(std::vector < std::vector< std::string> > &tableMat);
    
    //Reads from file determines if the TBM are Phase0 or Phase1
    //by looking for a string "digital" or "analog" at the top line of the file
    //Depending on this, it will construct either a PixelP0TBMSettings or a 
    //PixelP1TBMSettings object. 
    //	Note: if no string string is found, the constructor defaults to 
    //	a Phase0 TBM
    //TODO: Add support for Binary files
    PixelTBMSettings(std::string filename);

    // modified by MR on 29-04-2008 16:43:30
    PixelTBMSettings():PixelConfigBase("", "", "") { std::cout << "default TBM" << std::endl;;}

    virtual ~PixelTBMSettings(){}

    //This function generates the DAC settings
    void generateConfiguration(PixelFECConfigInterface* pixelFEC,
	                       PixelNameTranslation* trans,
			       bool physics=false, bool doResets=true) const; 
    
    //Writes data into binary file
    void writeBinary(std::string filename) const;

    //Each of these functions writes data into their respective files 
    void 	 writeASCII(std::string dir) const;
    void 	 writeXML(         pos::PixelConfigKey key, int version, std::string path) const {;}
    virtual void writeXMLHeader(   pos::PixelConfigKey key, 
				   int version, 
				   std::string path, 
				   std::ofstream *out,
				   std::ofstream *out1 = NULL,
				   std::ofstream *out2 = NULL
				   ) const ;
    virtual void writeXML(        std::ofstream *out,			                                    
			   	  std::ofstream *out1 = NULL ,
			   	  std::ofstream *out2 = NULL ) const ;
    virtual void writeXMLTrailer( std::ofstream *out, 
				  std::ofstream *out1 = NULL,
				  std::ofstream *out2 = NULL
				  ) const ;

   //  friend std::ostream& operator<<(std::ostream& s, const PixelTBMSettings& mask);
   
//====================================================================================
//============================== Phase1 Specific Functions============================
//====================================================================================
    unsigned char getTBMADelay() {
	assert(tbmType_ == true && "ERROR calling digital function with analog TBM");
	return tbmP1->getTBMADelay();
	}

    void setTBMDelay(unsigned char x) {
	assert(tbmType_ == true && "ERROR calling digital function with analog TBM");
	 tbmP1->setTBMADelay(x);
	}

    unsigned char getTBMBDelay() {
	assert(tbmType_ == true && "ERROR calling digital function with analog TBM");
	return  tbmP1->getTBMBDelay();
	}
    void setTBMBDelay(unsigned char x) {
	assert(tbmType_ == true && "ERROR calling digital function with analog TBM");
	tbmP1->setTBMBDelay(x);}

    unsigned char getTBMPLLDelay() {
	assert (tbmType_ == true && "ERROR calling digital function with analog TBM");
	return tbmP1->getTBMPLLDelay();}
    void setTBMPLLDelay(unsigned char x) {
	assert (tbmType_ == true && "ERROR calling digital function with analog TBM");
	tbmP1->setTBMPLLDelay(x);}

    void getDACs(std::map<std::string, unsigned int>& dacs) const;
//========================================================================================
//======================= Phase0 specific functions=======================================
//========================================================================================
    unsigned char getAnalogInputBias() {
	assert (tbmType_ == false && "ERROR calling analog function with digital TBM");
	return tbmP0->getAnalogInputBias();}
    void setAnalogInputBias(unsigned char analogInputBias) {
	assert (tbmType_ == false && "ERROR calling analog function with digital TBM"); 
	tbmP0->setAnalogInputBias(analogInputBias);}
    
    unsigned char getAnalogOutputBias() {
	assert (tbmType_ == false && "ERROR calling analog function with digital TBM");
	return tbmP0->getAnalogOutputBias();}
    void setAnalogOutputBias(unsigned char analogOutputBias) {
	assert (tbmType_ == false && "ERROR calling analog function with digital TBM"); 
	tbmP0->setAnalogOutputBias(analogOutputBias);}
    
    unsigned char getAnalogOutputGain() { 
	assert (tbmType_ == false && "ERROR calling analog function with digital TBM");
	return tbmP0->getAnalogOutputGain();}
    void setAnalogOutputGain(unsigned char analogOutputGain) {
	assert (tbmType_ == false && "ERROR calling analog function with digital TBM");
	tbmP0->setAnalogOutputGain(analogOutputGain);}
    
    // Added by Dario (Apr 2008)
    bool getMode(void)      {
	assert (tbmType_ == false && "ERROR: Calling analog function with digital TBM"); 
	return tbmP0->getMode();}
    void setMode(bool mode) {
	assert (tbmType_ == false && "ERROR: Calling analog function with digital TBM");
	tbmP0->setMode(mode);}
//========================================================================================
//=======================================================================================
    
    //This function differentiates between rocnames that are of type analog and  type digital
    //,and sets them according to their type.  
    void setROCName(std::string rocname){
      	PixelROCName tmp(rocname);
        if(tbmType_ == true ){
		tbmP1->setROCName(tmp);
	} 
	else{
		tbmP0->setROCName(tmp);
	}
    }

    //This function sets TBM to a generic value. It is the client's 
    //responsibility to use valid notation to achieve desired result. 
    void setTBMGenericValue(std::string, int) ;
    
  private:
  
  bool tbmType_;
  pos::PixelP0TBMSettings* tbmP0;
  pos::PixelP1TBMSettings* tbmP1;

  };
}
/* @} */
#endif
