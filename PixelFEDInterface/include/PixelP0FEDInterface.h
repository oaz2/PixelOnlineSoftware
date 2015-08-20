#ifndef TP_PIXELP0FEDINTERFACE_H
#define TP_PIXELP0FEDINTERFACE_H

/* Experimental class used to test inheretance the FED Interface class
 * Designed to allow for version specific hardware (Phase0/Phase1)
 */

#include "PixelFEDInterface/include/PixelFEDInterface.h"
#define USE_HAL
using namespace pos;
using namespace std;

class PixelP0FEDInterface : public PixelFEDInterface {

  public:

#ifdef USE_HAL 
    PixelP0FEDInterface(const HAL::VMEDevice * const);
    ~PixelP0FEDInterface();

#else
    PixelP0FEDInterface(const uint32_t, long );
    ~PixelP0FEDInterface();
#endif


    //other public/private P0 specific variables go here
 
};
#endif
