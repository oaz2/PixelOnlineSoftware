#ifndef PixelModuleName_h
#define PixelModuleName_h
//
// This class stores the name and related
// hardware mapings for a ROC
//
//

#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>

class PixelModuleName {

 public:

    PixelModuleName();

    explicit PixelModuleName(std::string rocname);


    explicit PixelModuleName(std::ifstream& s);
    
    std::string modulename() const; 

    char detsub() const {return (id_&0x80000000)?'B':'F';}    
    char mp() const {return id_&0x40000000?'p':'m';}    
    char IO() const {return id_&0x20000000?'I':'O';}    

    //These methods only for FPix
    int disk() const {assert((id_&0x80000000)==0); return (id_>>8)&0x3;}    
    int blade() const {assert((id_&0x80000000)==0); return (id_>>3)&0x1f;}    
    int panel() const {assert((id_&0x80000000)==0); return ((id_>>2)&0x1)+1;} 

    //These methods only for BPix
    int sec() const {assert((id_&0x80000000)!=0); return ((id_>>10)&0x7)+1;} 
    int layer() const {assert((id_&0x80000000)!=0); return (id_>>8)&0x3;}    
    int ladder() const {assert((id_&0x80000000)!=0); return (id_>>2)&0x1f;}    
    char HF() const {assert((id_&0x80000000)!=0); return id_&0x00000080?'F':'H';}
    int module() const {assert((id_&0x80000000)!=0); return ((id_)&0x3)+1;}    
  


    friend std::ostream& operator<<(std::ostream& s, const PixelModuleName& pixelroc);


    const PixelModuleName& operator=(const PixelModuleName& aROC);

    const bool operator<(const PixelModuleName& aROC) const{
	return id_<aROC.id_;
    }

 private:

    void parsename(std::string name);

    void setIdFPix(char np, char LR,int disk,
		   int blade, int panel);

    void setIdBPix(char np, char LR,int sec,
		   int layer, int ladder, char HF, 
		   int module);

    

    //BPix_BpI_SEC1_LYR1_LDR3F_MOD1


    //The id_ holds the following values for BPi
    //bit [0,1] the module#
    //bit [2,3,4,5,6] the ladder#
    //bit [7] H or F (0 or 1)#
    //bit [8,9] the layer#
    //bit [10,11,12] the section#
    //bit [29] I or 0 (0 or 1)
    //bit [30] m or p (0 or 1)
    //bit [31] = 1


    //FPix_BpI_D1_BLD1_PNL1

    //The id_ holds the following values for FPix
    //bit [0] the panel#
    //bit [1,2,3,4,5] the blade#
    //bit [6,7] the disk#
    //bit [29] I or O (0 or 1)
    //bit [30] m or p (0 or 1)
    //bit [31] = 0

    unsigned int id_;
    
};

#endif
