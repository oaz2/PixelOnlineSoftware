#ifndef PixelROCDACSettings_h
#define PixelROCDACSettings_h
/*! \file CalibFormats/SiPixelObjects/interface/PixelROCDACSettings.h
*   \brief This class provide the data structure for the ROC DAC parameters
*
*   This class is abstract base class to be used in PixelDACSettings.  this 
*   class has function declarations that are defined in its derived classes
*   PixelP0ROCDACSettigns and PixelP1ROCDACSettings.  Additionally, shared 
*   member variables are defined in this class as well.  
*   Since this class is abstract, any call to it must be through the use of 
*   pointers.
*
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

    //TODO: function currently return a null string
    std::string getConfigCommand();

    //Both functions read from a stream, then set each dac variable to its
    //corresponding value.
    //It is the client's responsiblilty to correctly utilize the function as it
    //is defined, such that each variable is matched with a unique value.
    virtual int read(std::ifstream& in, const PixelROCName& rocid) = 0 ;
    virtual int read(std::istringstream& in, const PixelROCName& rocid) = 0;
    
    virtual int readBinary(std::ifstream& in, const PixelROCName& rocid) = 0;
    
    //Writes to a binary file 
    virtual void writeBinary(std::ofstream& out) const = 0;
    
    //Writes data to ASCII file
    virtual void writeASCII(std::ostream& out) const = 0;

    //Each function writes data to its specific XML file
    virtual void writeXML(pos::PixelConfigKey key, int version, std::string path) const = 0 ;  
    virtual void writeXMLHeader(pos::PixelConfigKey key, int version, std::string path, std::ofstream *out) const = 0 ;
    virtual void writeXML(std::ofstream *out) const = 0 ;
    virtual void writeXMLTrailer(std::ofstream *out) const = 0 ;
   
    //Assigns every DACNAme as a key in dacs and maps it to a corresponding 
    //vector.  Inside the vector is the address(index at 1) and the value
    //(index at 0) of the dacs.  Sample usage:
    //  map<string, vector<unsigned int>> dacs; 
    //  ROCDACSettingObject->getDacs(dacs);
    //Note: if dacs contains a value, they will be overwritt
    virtual void getDACs(std::map<std::string,std::vector<unsigned int>>& dacs) const = 0;

    //sets the value of a specific DAC to davvalue given its DACAddress.
    //It is the responsability of the client to provide a valid DACAdress
    virtual void setDAC(unsigned int dacaddress, unsigned int dacvalue) = 0;
    
    //This function matches the dacs address with its value by using a map.
    //It is the responsability of the user to provide a map containing a 
    //valid mapping for each DACName
    virtual void setDACs(std::map<std::string, unsigned int>& dacs) = 0;

    //Determines the differences between this and dacs.  records the 
    //differences in changes and stores the value in previous
    //It is the responsability of the user to provide a map 
    //containing a valid mapping for each DACName
    virtual void compareDACs(std::map<std::string, unsigned int> & dacs, 
                     std::map<std::string, bool>         & changes,
		     std::map<std::string, unsigned int> & previous) = 0;

    void checkTag(std::string tag, 
		  std::string dacName,
		  const PixelROCName& rocid);

    //This function sets dacs to their corresponding value.
    //The client is responsible for inputing valid dacnames.
    virtual void setDac(std::string dacName, int value) = 0;
    
    //This function returns a value that corresponds to a given dacname,
    //given that the client inputs a valid dacname.
    virtual unsigned int getDac(std::string dacName) const = 0;

    //Getter and Setter functions for common DACs
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


  protected:
    //helper function used in getDACs
    std::vector<unsigned int> make_vector(unsigned int DACValue, unsigned int DACAddress) const ;
    
    //The name of the ROC, follows the stanard Naming convection	
    PixelROCName rocid_;

    //The dac settings used by the ROC which are common in Phase 0 and Phase 1
    //ROCs, members unique to them are declared in the corresponding derived
    //class
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

    //Return the lowercase version of the given string
    //(e.g PIxeL -> pixel)
    std::string ToLower(std::string) ;
    
  };
}
#endif
