#ifndef PixelP1DACNames_h
#define PixelP1DACNames_h
/*! \file CalibFormats/SiPixelObjects/interface/PixelDACNames.h
*   \brief A dummy class with ALL public variables 
*
*   A longer explanation will be placed here later
*/

#include <string>

namespace pos{

  const std::string k_DACName_Vsh="Vsh";
  const std::string k_DACName_Vsf="Vsh"; // JMTBAD
  const std::string k_DACName_PHOffset="PHOffset";
  const std::string k_DACName_Vcomp_ADC="Vcomp_ADC";
  const std::string k_DACName_PHScale="PHScale";
  const std::string k_DACName_Readback="Readback";

  const unsigned int k_DACAddress_Vsh=3;
  const unsigned int k_DACAddress_Vsf=3; // JMTBAD
  const unsigned int k_DACAddress_PHOffset=17;
  const unsigned int k_DACAddress_Vcomp_ADC=19;
  const unsigned int k_DACAddress_PHScale=20;
  const unsigned int k_DACAddress_Readback=255;

  const std::string k_DACName_TBMADelay="TBMADelay";
  const std::string k_DACName_TBMBDelay="TBMBDelay";
  const std::string k_DACName_TBMPLL="TBMPLL";
  
  const unsigned int k_DACAddress_TBMADelay=5;
  const unsigned int k_DACAddress_TBMBDelay=5;
  const unsigned int k_DACAddress_TBMPLL=7;
  
}


#endif
