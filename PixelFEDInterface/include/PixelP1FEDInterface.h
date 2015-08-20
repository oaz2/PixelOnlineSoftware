#ifndef TP_PIXELP1FEDINTERFACE_H
#define TP_PIXELP1FEDINTERFACE_H

// Experimental class used to test inheretance

#include "PixelFEDInterface/include/PixelFEDInterface.h"
#define USE_HAL
using namespace pos;
using namespace std;

class PixelP1FEDInterface : public PixelFEDInterface {

  public:

#ifdef USE_HAL 
    PixelP1FEDInterface(const HAL::VMEDevice * const);
    ~PixelP1FEDInterface();

#else
    PixelP1FEDInterface(const uint32_t, long );
    ~PixelP1FEDInterface();
#endif


    //other public/private P0 specific variables go here
 
};
#endif
