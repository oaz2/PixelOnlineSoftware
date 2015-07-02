#ifndef PixelP1ROCDACSettings_h
#define PixelP1ROCDACSettings_h
/*! \file CalibFormats/SiPixelObjects/interface/PixelROCDACSettings.h
*   \brief This class provide the data structure for the ROC DAC parameters
*
*   At this point I do not see a reason to make an abstract layer for this code.
*/

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include "CalibFormats/SiPixelObjects/interface/PixelROCDACSettings.h"
#include "CalibFormats/SiPixelObjects/interface/PixelConfigKey.h"
#include "CalibFormats/SiPixelObjects/interface/PixelROCName.h"

namespace pos{
  typedef unsigned char bits8;
  typedef unsigned char bits4;

/*! \class PixelROCDACSettings PixelROCDACSettings.h "interface/PixelROCDACSettings.h"
*   \brief This class implements..
*
*   A longer explanation will be placed here later
*/
  class PixelP1ROCDACSettings: public PixelROCDACSettings{

  public:

    PixelP1ROCDACSettings();
    virtual ~PixelP1ROCDACSettings(){};

    PixelP1ROCDACSettings(const PixelROCName& rocid){rocid_= rocid;}

    int read(std::ifstream& in, const PixelROCName& rocid);
    int read(std::istringstream& in, const PixelROCName& rocid);

    int readBinary(std::ifstream& in, const PixelROCName& rocid);

    void writeBinary(std::ofstream& out) const;
    void writeASCII(std::ostream& out) const;

    void writeXML(pos::PixelConfigKey key, int version, std::string path) const {;}
    void writeXMLHeader(pos::PixelConfigKey key, int version, std::string path, std::ofstream *out) const {;}
    void writeXML(std::ofstream *out) const;
    void writeXMLTrailer(std::ofstream *out) const {;}

    //void getDACs(std::vector<unsigned int>& dacs) const;
    void getDACs(std::map<std::string,std::vector<unsigned int>>& dacs) const;
    //static unsigned int getDACAddress(const std::string DACName);

    void setDAC(unsigned int dacaddress, unsigned int dacvalue);
    void setDACs(std::map<std::string, unsigned int>& dacs) ;

    void compareDACs(std::map<std::string, unsigned int> & dacs, 
                     std::map<std::string, bool>         & changes,
		     std::map<std::string, unsigned int> & previous) ;

    //void checkTag(std::string tag, 
	//	  std::string dacName,
	//	  const PixelROCName& rocid);
    //made it virtual  
    void setDac(std::string dacName, int value);

    unsigned int getDac(std::string dacName) const;
	//Phase1 getter and setter functions
    bits8 getPHOffset() {return PHOffset_;}
    void setPHOffset(bits8 PHOffset) {PHOffset_=PHOffset;}

    bits8 getVcomp_ADC() {return Vcomp_ADC_;}
    void setVcomp_ADC(bits8 Vcomp_ADC) {Vcomp_ADC_=Vcomp_ADC;}

    bits8 getPHScale() {return PHScale_;}
    void setPHScale(bits8 PHScale) {PHScale_=PHScale;}

    bits8 getReadback() {return Readback_;}
    void setReadback(bits8 Readback) {Readback_=Readback;} 

    bits8 getVsf() {return Vsh_;} // JMTBAD
    bits8 getVsh() {return Vsh_;}
    void setVsf(bits8 vsh) {Vsh_=vsh;} // JMTBAD
    void setVsh(bits8 vsh) {Vsh_=vsh;}

    friend std::ostream& operator<<(std::ostream& s, const PixelP1ROCDACSettings& dacs);

  private:

    //The dac settings used by the ROC

    bits8 PHOffset_;         //addr 17
    bits8 Vcomp_ADC_;        //addr 19
    bits8 PHScale_;          //addr 20
    bits8 Readback_;         //addr 255
    bits8 Vsh_;		     //addr 3    
  };
}
#endif
