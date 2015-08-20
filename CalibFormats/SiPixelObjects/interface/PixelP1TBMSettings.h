#ifndef PixelP1TBMSettings_h
#define PixelP1TBMSettings_h
/**
* \file CalibFormats/SiPixelObjects/interface/PixelP1TBMSettings.h
* \brief This class implements..
*
*   This class holds settings used by a Phase1 TBM.  The class contains delay
*   and auto reset settings for the TBMA and TBMB.  The format information should be:
*     digital
*     FPix_BpI_D1_BLD1_PNL1_PLQ2_ROC1
*     TBMAAutoReset: 0
*     TBMBAutoReset: 0
*     TBMAPKAMCount: 5
*     TBMBPKAMCount: 5
*     TBMPLLDelay: 4
*     TBMADelay: 0
*     TBMBDelay: 0
*
*/

#include <vector>
#include "CalibFormats/SiPixelObjects/interface/PixelConfigBase.h"
#include "CalibFormats/SiPixelObjects/interface/PixelFECConfigInterface.h"
#include "CalibFormats/SiPixelObjects/interface/PixelNameTranslation.h"

namespace pos{
/*!  \ingroup ConfigurationObjects "Configuration Objects"
*    
*  @{
*
*  \class PixelP1TBMSettings PixelP1TBMSettings.h
*  \brief This is the documentation about PixelP1TBMSettings...
*
*   A longer explanation will be placed here later
*
*/
  class PixelP1TBMSettings{

  public:

    PixelP1TBMSettings(std::vector < std::vector< std::string> > &tableMat);
    PixelP1TBMSettings(std::ifstream& in, std::string& tag);
    // modified by MR on 29-04-2008 16:43:30

    virtual ~PixelP1TBMSettings(){}

    //Generate the DAC settings
    void generateConfiguration(PixelFECConfigInterface* pixelFEC,
	                       PixelNameTranslation* trans,
			       bool physics=false, bool doResets=true) const; 

    void writeBinary(std::ofstream& out) const;

    void 	 writeASCII(std::string& dir) const;
    virtual void writeXML(        std::ofstream *out,			                                    
			   	  std::ofstream *out1 = NULL ,
			   	  std::ofstream *out2 = NULL ) const ;

    friend std::ostream& operator<<(std::ostream& s, const PixelP1TBMSettings& mask);

    unsigned char getTBMADelay() {return TBMADelay_;}
    void setTBMADelay(unsigned char x) {TBMADelay_=x;}
    
    unsigned char getTBMBDelay() {return TBMBDelay_;}
    void setTBMBDelay(unsigned char x) {TBMBDelay_=x;}
    
    unsigned char getTBMPLLDelay() {return TBMPLLDelay_;}
    void setTBMPLLDelay(unsigned char x) {TBMPLLDelay_=x;}

    void getDACs(std::map<std::string, unsigned int>& dacs) const;
    
    // Added by Dario (Apr 2008)
     
    void setTBMGenericValue(std::string, int) ;
    
    void setROCName(PixelROCName& tmp){
	rocid_=tmp;
    }
     
  private:
    
    PixelROCName rocid_;
    PixelModuleName moduleId_;	

    //Phase1 TBM members
    unsigned char TBMAAutoReset_;
    unsigned char TBMBAutoReset_;
    unsigned char TBMAPKAMCount_;
    unsigned char TBMBPKAMCount_;
    unsigned char TBMPLLDelay_;
    unsigned char TBMADelay_;
    unsigned char TBMBDelay_;
  };
}
/* @} */
#endif
