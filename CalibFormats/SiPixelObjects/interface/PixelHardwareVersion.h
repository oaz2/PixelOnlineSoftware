#ifndef PixelHardwareVersion_h
#define PixelHardwareVersion_h
/*! \file CalibFormats/SiPixelObjects/interface/PixelHardwareVersion.h
 *  \brief class containi an enum that specifies the version of the 
 *  hardware.  Currently just Phase0 or Phase1
 */
namespace pos {
  enum HdwType { 
    phase0,
    phase1,
    unknown
  };
};
#endif 

