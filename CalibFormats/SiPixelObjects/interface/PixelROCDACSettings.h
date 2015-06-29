#ifndef PixelROCDACSettings_h
#define PixelROCDACSettings_h
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
  class PixelROCDACSettings{

  public:

    PixelROCDACSettings();
    virtual ~PixelROCDACSettings() {};

    PixelROCDACSettings(const PixelROCName& rocid){rocid_= rocid;}

    //Build the commands needed to configure ROC
    //Need to use the mask bits also for this
    std::string getConfigCommand();

    //made both function virtual, wil be declared in the base classes	
    virtual int read(std::ifstream& in, const PixelROCName& rocid) = 0 ;
    virtual int read(std::istringstream& in, const PixelROCName& rocid) = 0;
    
    virtual int readBinary(std::ifstream& in, const PixelROCName& rocid) = 0;
    virtual void writeBinary(std::ofstream& out) const = 0;
    virtual void writeASCII(std::ostream& out) const = 0;
    
    virtual void writeXML(pos::PixelConfigKey key, int version, std::string path) const = 0 ;  
    virtual void writeXMLHeader(pos::PixelConfigKey key, int version, std::string path, std::ofstream *out) const = 0 ;
    virtual void writeXML(std::ofstream *out) const = 0 ;
    virtual void writeXMLTrailer(std::ofstream *out) const = 0 ;
    
    //made both of these pure virtual 
    virtual void getDACs(std::vector<unsigned int>& dacs) const = 0;
    virtual void getDACs(std::map<std::string, unsigned int>& dacs) const = 0;

    //made setDAC into a pure vortual function
    virtual void setDAC(unsigned int dacaddress, unsigned int dacvalue) = 0;
    
    virtual void setDACs(std::map<std::string, unsigned int>& dacs) = 0;

    virtual void compareDACs(std::map<std::string, unsigned int> & dacs, 
                     std::map<std::string, bool>         & changes,
		     std::map<std::string, unsigned int> & previous) = 0;

    void checkTag(std::string tag, 
		  std::string dacName,
		  const PixelROCName& rocid);
    //should make it virtual, only derived class should be able to 
    //call it  
    virtual void setDac(std::string dacName, int value) = 0;

    //also made it virtuall so that derived classes can call it
    virtual unsigned int getDac(std::string dacName) const = 0;

    bits4 getVdd() {return Vdd_;}
    void setVdd(bits4 vdd) {Vdd_=vdd;}

    bits8 getVana() {return Vana_;}
    void setVana(bits8 vana) {Vana_=vana;}

    virtual bits8 getVsf() = 0; 
    virtual void setVsf(bits8 vsh) = 0;

    bits4 getVcomp() {return Vcomp_;}
    void setVcomp(bits4 vcomp) {Vcomp_=vcomp;}

    bits8 getVwllPr() {return VwllPr_;}
    void setVwllPr_(bits8 vwllPr) {VwllPr_=vwllPr;}

    bits8 getVwllSh() {return VwllSh_;}
    void setVwllSh(bits8 vwllSh) {VwllSh_=vwllSh;}

    bits8 getVHldDel() {return VHldDel_;}
    void setVHldDel(bits8 vHldDel) {VHldDel_=vHldDel;}

    bits8 getVtrim() {return Vtrim_;}
    void setVtrim(bits8 vtrim) {Vtrim_=vtrim;}

    bits8 getVcThr() {return VcThr_;}
    void setVcThr(bits8 vcThr) {VcThr_=vcThr;}

    bits8 getVIbias_bus() {return VIbias_bus_;}
    void setVIbias_bus(bits8 vIbias_bus) {VIbias_bus_=vIbias_bus;} 

    bits8 getVIColOr() {return VIColOr_;}
    void setVIColOr(bits8 vIColOr) {VIColOr_=vIColOr;}

    bits8 getVcal() {return Vcal_;}
    void setVcal(bits8 vcal) {Vcal_=vcal;}

    bits8 getCalDel() {return CalDel_;}
    void setCalDel(bits8 calDel) {CalDel_=calDel;}

    bits8 getTempRange() {return TempRange_;}
    void setTempRange(bits8 tempRange) {TempRange_=tempRange;}

    bits8 getWBC() {return WBC_;}
    void setWBC(bits8 wbc) {WBC_=wbc;}

    bits8 getControlRegister() const {return ChipContReg_;}
    void setControlRegister(bits8 controlregister) {ChipContReg_=controlregister;}

    PixelROCName getROCName() const {return rocid_;} 

    //friend std::ostream& operator<<(std::ostream& s, const PixelROCDACSettings& dacs);

  protected:

    PixelROCName rocid_;

    //The dac settings used by the ROC

    bits4 Vdd_;              //addr 1
    bits8 Vana_;             //addr 2
    bits4 Vcomp_;            //addr 4
    bits8 VwllPr_;           //addr 7
    bits8 VwllSh_;           //addr 9
    bits8 VHldDel_;          //addr 10
    bits8 Vtrim_;            //addr 11
    bits8 VcThr_;            //addr 12
    bits8 VIbias_bus_;       //addr 13
    bits8 VIColOr_;          //addr 22
    bits8 Vcal_;             //addr 25
    bits8 CalDel_;           //addr 26
    bits8 TempRange_;        //addr 27
    bits8 WBC_;              //addr 254
    bits8 ChipContReg_;      //add   
    
    std::string ToLower(std::string) ;
    
  };
}
#endif
