#ifndef PixelDACSettings_h
#define PixelDACSettings_h
/**
* \file CalibFormats/SiPixelObjects/interface/PixelDACSettings.h
*   \brief This class provide a base class for the pixel ROC dac data for the pixel FEC configuration
*
*   This is a pure interface (abstract class) that needs to have an implementation.
*/

//
// This class provide a base class for the
// pixel ROC dac data for the pixel FEC configuration
// This is a pure interface (abstract class) that
// needs to have an implementation.
//
//
//

#include <memory>
#include <vector>
#include <string>
#include "CalibFormats/SiPixelObjects/interface/PixelConfigBase.h"
#include "CalibFormats/SiPixelObjects/interface/PixelROCDACSettings.h"
#include "CalibFormats/SiPixelObjects/interface/PixelFECConfigInterface.h"
#include "CalibFormats/SiPixelObjects/interface/PixelROCName.h"
#include "CalibFormats/SiPixelObjects/interface/PixelNameTranslation.h"
#include "CalibFormats/SiPixelObjects/interface/PixelDetectorConfig.h"
#include "CalibFormats/SiPixelObjects/interface/PixelP1ROCDACSettings.h"
#include "CalibFormats/SiPixelObjects/interface/PixelP0ROCDACSettings.h"

namespace pos{
/*!  \defgroup ConfigurationObjects "Configuration Objects"
*   \brief This is the base class of all configuration objects
*    
*   A longer explanation of what a 'configuration object' actually is will be 
*   posted here once we find the time to write it....
*
*  @{
*
*  \class PixelDACSettings PixelDACSettings.h
*  \brief This class is responsible for manipulating the DACsettings of a ROC.
*
*  This is a placeholder for a lengthy description of the class, it's methods
*  behavior and additional stuff like images. This description can be arbitrary
*  long and complex, see for eg. \ref page3Sect3. <P>
*  Ut perspiciatis, unde omnis iste natus error sit voluptatem 
*  accusantium doloremque laudantium, totam rem aperiam eaque ipsa, quae ab 
*  illo inventore veritatis et quasi architecto beatae vitae dicta sunt, explicabo. 
*
*  \image html temp.png
*
*  Nemo enim ipsam voluptatem, quia voluptas sit, aspernatur aut odit aut fugit, 
*  sed quia consequuntur magni dolores eos, qui ratione voluptatem sequi nesciunt, 
*  neque porro quisquam est, qui dolorem ipsum, quia dolor sit, amet, consectetur, 
*  adipisci velit, sed quia non numquam eius modi tempora incidunt, ut labore et 
*  dolore magnam aliquam quaerat voluptatem. Ut enim ad minima veniam, quis nostrum 
*  exercitationem ullam corporis suscipit laboriosam, nisi ut aliquid ex ea commodi 
*  consequatur? Quis autem vel eum iure reprehenderit, qui in ea voluptate velit esse, 
*  quam nihil molestiae consequatur, vel illum, qui dolorem eum fugiat, quo 
*  voluptas nulla pariatur? 
*/

  class PixelDACSettings: public PixelConfigBase {

  public:
    //Reads from the filename and determines if ROCs are Phase0 or Phase1
    //by looking for the string "digital" at the top line of the file
    //	Note: if there is no string found, constructor will default to 
    //	constructing Phase0 ROCs
    //TODO: Binary files are currently not supported in this constructor
    PixelDACSettings(std::string filename);

    //Added by Umesh
    //TODO: Add support for phase1 ROCs
    PixelDACSettings(std::vector<std::vector<std::string> >& tableMat);   

    // modified by MR on 10-01-2008 14:47:47
    //Constructs a PixelDACSettings object from a rocname pointer.
    //The cliend should provide a valid Phase0 ROC
    //TODO: Add support for Phase1 ROCs
    PixelDACSettings(std::shared_ptr<PixelROCDACSettings> rocname);

    // modified by MR on 24-01-2008 14:28:14
    ~PixelDACSettings();

    //Adds the current ROC to the dacsettings_ vector
    //It is the responsability of the client to provide a valid rocname
    void addROC(std::shared_ptr<PixelROCDACSettings> rocname);

    //returns a PixelROCDACSettings shared pointer to the correspoding ROC
    //It is the responsabilty of the client to provide a valid ROCId/PixelROCName    
    std::shared_ptr<PixelROCDACSettings> getDACSettings(int ROCId) const;
    std::shared_ptr<PixelROCDACSettings> getDACSettings(PixelROCName);

    unsigned int numROCs() {return dacsettings_.size();}

    //Programs all of the DACs in a current ROC in the following order:
    //		ChipContReg -> All DACs except WBC -> WBC 
    //It is the responsability of the user to provide the correct HdwAddress 
    //for the ROC
    void setAllDAC(PixelFECConfigInterface *& pixelFEC, const PixelHdwAddress& theROC, 
		   std::map<std::string,std::vector<unsigned int> >& dacs,
		   const bool buffermode, const bool ROCType) const;

    //TODO: Write proper description of this file
    void generateConfiguration(PixelFECConfigInterface* pixelFEC,
	                       PixelNameTranslation* trans, PixelDetectorConfig* detconfig,
			       bool HVon=true) const;

    //Loops through all of the module's ROCs,and for each: 
    //	Set VCThr to zero 
    //	Disable the ROC
    //It is up to the user to provide non-null pointers
    void setVcthrDisable(PixelFECConfigInterface* pixelFEC, PixelNameTranslation* trans) const;
    
    //Loops through all of the module's ROCs, and for each:
    //	Set Vcthr to its nominal value
    //	Enable to the ROC
    //It is the responsability of the user to provide non-null pointers 
    void setVcthrEnable(PixelFECConfigInterface* pixelFEC, PixelNameTranslation* trans, PixelDetectorConfig* detconfig) const;

    void writeBinary(std::string filename) const;
    void         writeASCII(std::string dir) const;
    void 	 writeXML(        pos::PixelConfigKey key, int version, 
				  std::string path) const  {;}

    virtual void writeXMLHeader(  pos::PixelConfigKey key, 
				  int version, 
				  std::string path, 
				  std::ofstream *out,
				  std::ofstream *out1 = NULL,
				  std::ofstream *out2 = NULL
				  ) const ;

    virtual void writeXML( 	  std::ofstream *out,		        		
			   	  std::ofstream *out1 = NULL ,	       
			   	  std::ofstream *out2 = NULL ) const ; 

    virtual void writeXMLTrailer( std::ofstream *out, 
				  std::ofstream *out1 = NULL,
				  std::ofstream *out2 = NULL
				  ) const ;

    friend std::ostream& operator<<(std::ostream& s, const PixelDACSettings& mask);

  private:
    //List of all the pixelROCDACSettings Objects contained within one module 
    std::vector<std::shared_ptr<PixelROCDACSettings>> dacsettings_;
    
    //value that determines which type of ROC we are working with.  
    //If RocType_ == true, then we are using Phase1 ROCs
    bool  ROCType_;

    //determines the status of the specified ROC
    //returns true if the specified ROC is disabled
    bool rocIsDisabled(const PixelDetectorConfig* detconfig, const PixelROCName rocname) const;

  };
}

/* @} */
#endif
