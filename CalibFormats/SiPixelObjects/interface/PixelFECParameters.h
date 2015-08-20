#ifndef PixelFECParameters_h
#define PixelFECParameters_h
/**
*   \file CalibFormats/SiPixelObjects/interface/PixelFECParameters.h
*   \brief This class implements..
*
*   A longer explanation will be placed here later
*/

#include <iosfwd>
#include "CalibFormats/SiPixelObjects/interface/PixelHardwareVersion.h"
namespace pos{
/*! \class PixelFECParameters PixelFECParameters.h "interface/PixelFECParameters.h"
*   \brief This class implements..
*
*   A longer explanation will be placed here later
*/

  class PixelFECParameters;
  std::ostream&  operator <<(std::ostream& s ,const PixelFECParameters &pFECp);
  
  class PixelFECParameters {
  public:

    PixelFECParameters();
    ~PixelFECParameters();

    unsigned int getFECNumber() const;
    unsigned int getCrate() const;
    unsigned int getVMEBaseAddress() const;
    HdwType getFECType() const; 
    
    void setFECParameters( unsigned int fecnumber , unsigned int crate , unsigned int vmebaseaddress, unsigned int fectype = 0);
    void setFECNumber(unsigned int fecnumber);
    void setCrate(unsigned int crate);
    void setVMEBaseAddress(unsigned int vmebaseaddress) ;
    void setFECType(unsigned int fectype);
    friend std::ostream& pos::operator <<(std::ostream& s,const PixelFECParameters &pFECp);
  private :

    unsigned int fecnumber_;   
    unsigned int crate_;   
    unsigned int vmebaseaddress_;   
    HdwType FECType_; 
  };
}
#endif
