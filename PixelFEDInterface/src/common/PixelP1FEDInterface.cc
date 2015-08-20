#include "PixelFEDInterface/include/PixelP1FEDInterface.h"

#ifdef USE_HAL
PixelP1FEDInterface::PixelP1FEDInterface(const HAL::VMEDevice * const vmeDeviceP ) :
  PixelFEDInterface(vmeDeviceP) {
  std::cout << "Greeting from the PixelP1FEDInterface constructor" << std::endl;
}

PixelP1FEDInterface::~PixelP1FEDInterface(void){
  std::cout << "PixelP1FEDInterface destructor" << std::endl;
}

#else
PixelP1FEDInterface::PixelP1FEDInterface(const uint32_t fedBase, long BHandle) :
  PixelFEDInterface(fedBase, BHandle) {
  std::cout << "Greetings from the PixelP1FEDInterface constructor" << std:endl;
} 

PixelP1FEDInterface::~PixelP1FEDInterface(void){
  std::cout << "PixelP1FEDInterface destructor" << std::endl;
}

#endif 
/* P1 specific functions go below
 */

