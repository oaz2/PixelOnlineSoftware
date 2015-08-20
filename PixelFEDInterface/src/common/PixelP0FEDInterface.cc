#include "PixelFEDInterface/include/PixelP0FEDInterface.h"


#ifdef USE_HAL
PixelP0FEDInterface::PixelP0FEDInterface(const HAL::VMEDevice * const vmeDeviceP ) :
  PixelFEDInterface(vmeDeviceP) {
  std::cout << "Greetings from the PixelP0FEDInterface constructor" << std::endl;
}

PixelP0FEDInterface::~PixelP0FEDInterface(void) {
  std::cout << "PixelP0FEDInterface destructor" << std::endl;
}

#else
PixelP0FEDInterface::PixelP0FEDInterface(const uint32_t fedBase, long BHandle) :
  PixelFEDInterface(fedBase, BHandle) {
  std::cout << "Greetings from the PixelP1FEDInterface constructor" << std::endl;
} 

PixelP0FEDInterface::PixelP0FEDInterface(void) {
  std::cout << "PixelP0FEDInterface destructor" << std::endl;
}

#endif 
/* P0 specific functions go below
 */

