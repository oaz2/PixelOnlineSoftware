#ifndef PixelP0DACNames_h
#define PixelP0DACNames_h
/*! \file CalibFormats/SiPixelObjects/interface/PixelDACNames.h
*   \brief A dummy class with ALL public variables 
*
*   A longer explanation will be placed here later
*/

#include <string>

namespace pos{

 const std::string k_DACName_Vsf="Vsf";
 const std::string k_DACName_Vleak="Vleak";
  const std::string k_DACName_VrgPr="VrgPr";

  const std::string k_DACName_VrgSh="VrgSh";
  const std::string k_DACName_VIbias_sf="VIbias_sf";
  const std::string k_DACName_VOffsetOp="VOffsetOp";
  const std::string k_DACName_VbiasOp="VbiasOp";
  const std::string k_DACName_VOffsetRO="VOffsetRO";
  const std::string k_DACName_VIon="VIon";
  const std::string k_DACName_VIbias_PH="VIbias_PH";
  const std::string k_DACName_VIbias_DAC="VIbias_DAC";
  const std::string k_DACName_VIbias_roc="VIbias_roc";
  const std::string k_DACName_Vnpix="Vnpix";
  const std::string k_DACName_VsumCol="VsumCol";

  const unsigned int k_DACAddress_Vsf=3;
  const unsigned int k_DACAddress_Vleak=5;
  const unsigned int k_DACAddress_VrgPr=6;
  const unsigned int k_DACAddress_VrgSh=8;
  const unsigned int k_DACAddress_VIbias_sf=14;
  const unsigned int k_DACAddress_VOffsetOp=15;
  const unsigned int k_DACAddress_VbiasOp=16;
  const unsigned int k_DACAddress_VOffsetRO=17;
  const unsigned int k_DACAddress_VIon=18;
  const unsigned int k_DACAddress_VIbias_PH=19;
  const unsigned int k_DACAddress_VIbias_DAC=20;
  const unsigned int k_DACAddress_VIbias_roc=21;
  const unsigned int k_DACAddress_Vnpix=23;
  const unsigned int k_DACAddress_VsumCol=24;
}


#endif
