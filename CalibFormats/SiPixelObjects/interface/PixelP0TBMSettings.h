#ifndef PixelP0TBMSettings_h
#define PixelP0TBMSettings_h
/**
* \file CalibFormats/SiPixelObjects/interface/PixelP0TBMSettings.h
* \brief This class implements..
*
*/
//This class holds the settings used by the Phase0 TBM. The file contains the module name
//and gain settings as well as if the TBM should be configured in "SingleMode or
//"DualMode."
//  The format used for this information is given by: 
//  FPix_BpI_D1_BLD1_PNL1_PLQ2_ROC1
//  AnalogInputBias: 160
//  AnalogOutputBias: 110
//  AnalogOutputGain: 207
//  Mode: SingleMode

#include <vector>
#include "CalibFormats/SiPixelObjects/interface/PixelConfigBase.h"
#include "CalibFormats/SiPixelObjects/interface/PixelFECConfigInterface.h"
#include "CalibFormats/SiPixelObjects/interface/PixelNameTranslation.h"

namespace pos{
/*!  \ingroup ConfigurationObjects "Configuration Objects"
*    
*  @{
*
*  \class PixelP0TBMSettings PixelP0TBMSettings.h
*  \brief This is the documentation about PixelP0TBMSettings...
*
*   A longer explanation will be placed here later
*
*/
  class PixelP0TBMSettings{

  public:

    PixelP0TBMSettings(std::vector < std::vector< std::string> > &tableMat);
    PixelP0TBMSettings(std::ifstream& in, std::string& tag);
    // modified by MR on 29-04-2008 16:43:30

    virtual ~PixelP0TBMSettings(){}

    //Generate the DAC settings
    void generateConfiguration(PixelFECConfigInterface* pixelFEC,
	                       PixelNameTranslation* trans,
			       bool physics=false, bool doResets=true) const; 

    void writeBinary(std::ofstream& out) const;

    void 	 writeASCII(std::string& dir) const;
   virtual void writeXML(        std::ofstream *out,			                                    
			   	  std::ofstream *out1 = NULL ,
			   	  std::ofstream *out2 = NULL ) const ;
    friend std::ostream& operator<<(std::ostream& s, const PixelP0TBMSettings& mask);

    unsigned char getAnalogInputBias() {return analogInputBias_;}
    void setAnalogInputBias(unsigned char analogInputBias) {analogInputBias_=analogInputBias;}
    
    unsigned char getAnalogOutputBias() {return analogOutputBias_;}
    void setAnalogOutputBias(unsigned char analogOutputBias) {analogOutputBias_=analogOutputBias;}
    
    unsigned char getAnalogOutputGain() {return analogOutputGain_;}
    void setAnalogOutputGain(unsigned char analogOutputGain) {analogOutputGain_=analogOutputGain;}
    
    // Added by Dario (Apr 2008)
    bool getMode(void)      {return singlemode_;}
    void setMode(bool mode) {singlemode_ = mode;}
    void setTBMGenericValue(std::string, int) ;
    
    void setROCName(PixelROCName& tmp){
	rocid_=tmp;
    }    
  private:
    PixelROCName rocid_;
    PixelModuleName moduleId_;

    //Phase0 TBM values
    unsigned char analogInputBias_;
    unsigned char analogOutputBias_;
    unsigned char analogOutputGain_;
    bool singlemode_;

  };
}
/* @} */
#endif
