//
// This class provide the data structure for the
// ROC DAC parameters
//
// At this point I do not see a reason to make an
// abstract layer for this code.
//

#include "CalibFormats/SiPixelObjects/interface/PixelROCDACSettings.h"
#include "CalibFormats/SiPixelObjects/interface/PixelP1ROCDACSettings.h"
#include "CalibFormats/SiPixelObjects/interface/PixelDACNames.h"
#include "CalibFormats/SiPixelObjects/interface/PixelP1DACNames.h"
#include <fstream>
#include <iostream>

using namespace pos;
using namespace std;

PixelP1ROCDACSettings::PixelP1ROCDACSettings(){}


// Added by Dario
void PixelP1ROCDACSettings::getDACs(std::map<std::string,std::vector<unsigned int>>& dacs) const
{
    dacs.clear();
    dacs.insert(pair<string, vector<unsigned int> > (k_DACName_Vdd, 	   make_vector(Vdd_, k_DACAddress_Vdd)));
    dacs.insert(pair<string, vector<unsigned int> > (k_DACName_Vana, 	   make_vector(Vana_, k_DACAddress_Vana)));
    dacs.insert(pair<string, vector<unsigned int> > (k_DACName_Vsh, 	   make_vector(Vsh_, k_DACAddress_Vsh)));
    dacs.insert(pair<string, vector<unsigned int> > (k_DACName_Vcomp, 	   make_vector(Vcomp_, k_DACAddress_Vcomp)));
    dacs.insert(pair<string, vector<unsigned int> > (k_DACName_VwllPr, 	   make_vector(VwllPr_, k_DACAddress_VwllPr)));
    dacs.insert(pair<string, vector<unsigned int> > (k_DACName_VwllSh, 	   make_vector(VwllSh_, k_DACAddress_VwllSh)));
    dacs.insert(pair<string, vector<unsigned int> > (k_DACName_VHldDel,    make_vector(VHldDel_, k_DACAddress_VHldDel)));
    dacs.insert(pair<string, vector<unsigned int> > (k_DACName_Vtrim, 	   make_vector(Vtrim_, k_DACAddress_Vtrim)));
    dacs.insert(pair<string, vector<unsigned int> > (k_DACName_VcThr, 	   make_vector(VcThr_, k_DACAddress_VcThr)));
    dacs.insert(pair<string, vector<unsigned int> > (k_DACName_VIbias_bus, make_vector(VIbias_bus_, k_DACAddress_VIbias_bus)));
    dacs.insert(pair<string, vector<unsigned int> > (k_DACName_PHOffset,   make_vector(PHOffset_, k_DACAddress_PHOffset)));
    dacs.insert(pair<string, vector<unsigned int> > (k_DACName_Vcomp_ADC,  make_vector(Vcomp_, k_DACAddress_Vcomp)));
    dacs.insert(pair<string, vector<unsigned int> > (k_DACName_PHScale,    make_vector(PHScale_, k_DACAddress_PHScale)));
    dacs.insert(pair<string, vector<unsigned int> > (k_DACName_VIColOr,    make_vector(VIColOr_, k_DACAddress_VIColOr)));
    dacs.insert(pair<string, vector<unsigned int> > (k_DACName_Vcal,       make_vector(Vcal_, k_DACAddress_Vcal)));
    dacs.insert(pair<string, vector<unsigned int> > (k_DACName_CalDel,     make_vector(CalDel_, k_DACAddress_CalDel)));
    dacs.insert(pair<string, vector<unsigned int> > (k_DACName_TempRange,  make_vector(TempRange_, k_DACAddress_TempRange)));
    dacs.insert(pair<string, vector<unsigned int> > (k_DACName_WBC,        make_vector(WBC_, k_DACAddress_WBC)));
    dacs.insert(pair<string, vector<unsigned int> > (k_DACName_ChipContReg,make_vector(ChipContReg_, k_DACAddress_ChipContReg)));
    dacs.insert(pair<string, vector<unsigned int> > (k_DACName_Readback,   make_vector(Readback_, k_DACAddress_Readback)));
}

// Added by Dario
// updated
void PixelP1ROCDACSettings::setDACs(std::map<std::string, unsigned int>& dacs) 
{
    Vdd_         = dacs[k_DACName_Vdd         ];
    Vana_        = dacs[k_DACName_Vana        ];
    Vsh_         = dacs[k_DACName_Vsh         ];
    Vcomp_       = dacs[k_DACName_Vcomp       ];
    VwllPr_      = dacs[k_DACName_VwllPr      ];
    VwllSh_      = dacs[k_DACName_VwllSh      ];
    VHldDel_     = dacs[k_DACName_VHldDel     ];
    Vtrim_       = dacs[k_DACName_Vtrim       ];
    VcThr_       = dacs[k_DACName_VcThr       ];
    VIbias_bus_  = dacs[k_DACName_VIbias_bus  ];
    PHOffset_    = dacs[k_DACName_PHOffset    ];
    Vcomp_ADC_   = dacs[k_DACName_Vcomp_ADC   ];
    PHScale_     = dacs[k_DACName_PHScale     ];
    VIColOr_     = dacs[k_DACName_VIColOr     ];
    Vcal_        = dacs[k_DACName_Vcal        ];
    CalDel_      = dacs[k_DACName_CalDel      ];
    TempRange_   = dacs[k_DACName_TempRange   ];
    WBC_         = dacs[k_DACName_WBC         ];
    ChipContReg_ = dacs[k_DACName_ChipContReg ];
    Readback_    = dacs[k_DACName_Readback    ];
}

// Added by Dario
void PixelP1ROCDACSettings::compareDACs(std::map<std::string, unsigned int>& dacs, 
                                      std::map<std::string, bool>& changes, 
				      std::map<std::string, unsigned int>& previous) 
{
    changes[k_DACName_Vdd        ] = false;
    changes[k_DACName_Vana       ] = false;
    changes[k_DACName_Vsh        ] = false;
    changes[k_DACName_Vcomp      ] = false;
    changes[k_DACName_VwllPr     ] = false;
    changes[k_DACName_VwllSh     ] = false;
    changes[k_DACName_VHldDel    ] = false;
    changes[k_DACName_Vtrim      ] = false;
    changes[k_DACName_VcThr      ] = false;
    changes[k_DACName_VIbias_bus ] = false;
    changes[k_DACName_PHOffset   ] = false;
    changes[k_DACName_Vcomp_ADC  ] = false;
    changes[k_DACName_PHScale    ] = false;
    changes[k_DACName_VIColOr    ] = false;
    changes[k_DACName_Vcal       ] = false;
    changes[k_DACName_CalDel     ] = false;
    changes[k_DACName_TempRange  ] = false;
    changes[k_DACName_WBC        ] = false;
    changes[k_DACName_ChipContReg] = false;
    changes[k_DACName_Readback   ] = false;

    if( Vdd_         != dacs[k_DACName_Vdd         ] ) {changes[k_DACName_Vdd         ] = true; previous[k_DACName_Vdd         ] = Vdd_        ;}
    if( Vana_        != dacs[k_DACName_Vana        ] ) {changes[k_DACName_Vana        ] = true; previous[k_DACName_Vana        ] = Vana_       ;}
    if( Vsh_         != dacs[k_DACName_Vsh         ] ) {changes[k_DACName_Vsh         ] = true; previous[k_DACName_Vsh         ] = Vsh_        ;}
    if( Vcomp_       != dacs[k_DACName_Vcomp       ] ) {changes[k_DACName_Vcomp       ] = true; previous[k_DACName_Vcomp       ] = Vcomp_      ;}
    if( VwllPr_      != dacs[k_DACName_VwllPr      ] ) {changes[k_DACName_VwllPr      ] = true; previous[k_DACName_VwllPr      ] = VwllPr_     ;}
    if( VwllSh_      != dacs[k_DACName_VwllSh      ] ) {changes[k_DACName_VwllSh      ] = true; previous[k_DACName_VwllSh      ] = VwllSh_     ;}
    if( VHldDel_     != dacs[k_DACName_VHldDel     ] ) {changes[k_DACName_VHldDel     ] = true; previous[k_DACName_VHldDel     ] = VHldDel_    ;}
    if( Vtrim_       != dacs[k_DACName_Vtrim       ] ) {changes[k_DACName_Vtrim       ] = true; previous[k_DACName_Vtrim       ] = Vtrim_      ;}
    if( VcThr_       != dacs[k_DACName_VcThr       ] ) {changes[k_DACName_VcThr       ] = true; previous[k_DACName_VcThr       ] = VcThr_      ;}
    if( VIbias_bus_  != dacs[k_DACName_VIbias_bus  ] ) {changes[k_DACName_VIbias_bus  ] = true; previous[k_DACName_VIbias_bus  ] = VIbias_bus_ ;}
    if( PHOffset_    != dacs[k_DACName_PHOffset    ] ) {changes[k_DACName_PHOffset    ] = true; previous[k_DACName_PHOffset    ] = PHOffset_   ;}
    if( Vcomp_ADC_   != dacs[k_DACName_Vcomp_ADC   ] ) {changes[k_DACName_Vcomp_ADC   ] = true; previous[k_DACName_Vcomp_ADC   ] = Vcomp_ADC_  ;}
    if( PHScale_     != dacs[k_DACName_PHScale     ] ) {changes[k_DACName_PHScale     ] = true; previous[k_DACName_PHScale     ] = PHScale_    ;}
    if( VIColOr_     != dacs[k_DACName_VIColOr     ] ) {changes[k_DACName_VIColOr     ] = true; previous[k_DACName_VIColOr     ] = VIColOr_    ;}
    if( Vcal_        != dacs[k_DACName_Vcal        ] ) {changes[k_DACName_Vcal        ] = true; previous[k_DACName_Vcal        ] = Vcal_       ;}
    if( CalDel_      != dacs[k_DACName_CalDel      ] ) {changes[k_DACName_CalDel      ] = true; previous[k_DACName_CalDel      ] = CalDel_     ;}
    if( TempRange_   != dacs[k_DACName_TempRange   ] ) {changes[k_DACName_TempRange   ] = true; previous[k_DACName_TempRange   ] = TempRange_  ;}
    if( WBC_         != dacs[k_DACName_WBC         ] ) {changes[k_DACName_WBC         ] = true; previous[k_DACName_WBC         ] = WBC_        ;}
    if( ChipContReg_ != dacs[k_DACName_ChipContReg ] ) {changes[k_DACName_ChipContReg ] = true; previous[k_DACName_ChipContReg ] = ChipContReg_;}
    if( Readback_    != dacs[k_DACName_Readback    ] ) {changes[k_DACName_Readback    ] = true; previous[k_DACName_Readback    ] = Readback_   ;}
}		   								            
//updated										       
void PixelP1ROCDACSettings::setDAC(unsigned int dacaddress, unsigned int dacvalue)       
{
        std::string mthn = "[PixelROCDACSettings::setDAC()]\t\t\t\t    " ;
	switch (dacaddress) {
		case   1: Vdd_         = dacvalue;  break;
		case   2: Vana_        = dacvalue;  break;
		case   3: Vsh_         = dacvalue;  break;
		case   4: Vcomp_       = dacvalue;  break;
		case   7: VwllPr_      = dacvalue;  break;
		case   9: VwllSh_      = dacvalue;  break;
		case  10: VHldDel_     = dacvalue;  break;
		case  11: Vtrim_       = dacvalue;  break;
		case  12: VcThr_       = dacvalue;  break;
		case  13: VIbias_bus_  = dacvalue;  break;
		case  17: PHOffset_    = dacvalue;  break;
		case  19: Vcomp_ADC_   = dacvalue;  break;
		case  20: PHScale_     = dacvalue;  break;
		case  22: VIColOr_     = dacvalue;  break;
		case  25: Vcal_        = dacvalue;  break;
		case  26: CalDel_      = dacvalue;  break;
		case  27: TempRange_   = dacvalue;  break;
		case 254: WBC_         = dacvalue;  break;
		case 253: ChipContReg_ = dacvalue;  break;
		case 255: Readback_    = dacvalue;  break;
		default: cout << __LINE__ << "]\t" << mthn 
		              << "DAC Address " << dacaddress << " does not exist!" << endl;
	}

}


void PixelP1ROCDACSettings::writeBinary(ofstream& out) const
{
    out << (char)rocid_.rocname().size();
    out.write(rocid_.rocname().c_str(),rocid_.rocname().size());

    out << Vdd_;
    out << Vana_;
    out << Vsh_;
    out << Vcomp_;
    out << VwllPr_;
    out << VwllSh_;
    out << VHldDel_;
    out << Vtrim_;
    out << VcThr_;
    out << VIbias_bus_;
    out << PHOffset_;
    out << Vcomp_ADC_;
    out << PHScale_;
    out << VIColOr_;
    out << Vcal_;
    out << CalDel_;
    out << TempRange_;
    out << WBC_;
    out << ChipContReg_;
    out << Readback_;
}


int PixelP1ROCDACSettings::readBinary(ifstream& in, const PixelROCName& rocid){
    
    rocid_=rocid;

    in.read((char*)&Vdd_,1);
    in.read((char*)&Vana_,1);
    in.read((char*)&Vsh_,1);
    in.read((char*)&Vcomp_,1);
    in.read((char*)&VwllPr_,1);
    in.read((char*)&VwllSh_,1);
    in.read((char*)&VHldDel_,1);
    in.read((char*)&Vtrim_,1);
    in.read((char*)&VcThr_,1);
    in.read((char*)&VIbias_bus_,1);
    in.read((char*)&PHOffset_,1);
    in.read((char*)&Vcomp_ADC_,1);
    in.read((char*)&PHScale_,1);
    in.read((char*)&VIColOr_,1);
    in.read((char*)&Vcal_,1);
    in.read((char*)&CalDel_,1);
    in.read((char*)&TempRange_,1);
    in.read((char*)&WBC_,1);
    in.read((char*)&ChipContReg_,1);
    in.read((char*)&Readback_,1);
    
    return 1;

}

void PixelP1ROCDACSettings::writeASCII(ostream& out) const{

    out << "ROC:           " << rocid_.rocname()   <<endl;

    out << k_DACName_Vdd << ":           " << (int)Vdd_          <<endl;
    out << k_DACName_Vana << ":          " << (int)Vana_         <<endl;
    out << k_DACName_Vsh << ":           " << (int)Vsh_          <<endl;
    out << k_DACName_Vcomp << ":         " << (int)Vcomp_        <<endl;
    out << k_DACName_VwllPr << ":        " << (int)VwllPr_       <<endl;
    out << k_DACName_VwllSh << ":        " << (int)VwllSh_       <<endl;
    out << k_DACName_VHldDel << ":       " << (int)VHldDel_      <<endl;
    out << k_DACName_Vtrim << ":         " << (int)Vtrim_        <<endl;
    out << k_DACName_VcThr << ":         " << (int)VcThr_        <<endl;
    out << k_DACName_VIbias_bus << ":    " << (int)VIbias_bus_   <<endl;
    out << k_DACName_PHOffset << ":      " << (int)PHOffset_     <<endl;
    out << k_DACName_Vcomp_ADC << ":     " << (int)Vcomp_ADC_    <<endl;
    out << k_DACName_PHScale << ":       " << (int)PHScale_      <<endl;
    out << k_DACName_VIColOr << ":       " << (int)VIColOr_      <<endl;
    out << k_DACName_Vcal << ":          " << (int)Vcal_         <<endl;
    out << k_DACName_CalDel << ":        " << (int)CalDel_       <<endl;
    out << k_DACName_TempRange << ":     " << (int)TempRange_    <<endl;
    out << k_DACName_WBC << ":           " << (int)WBC_          <<endl;
    out << k_DACName_ChipContReg << ":   " << (int)ChipContReg_  <<endl;
    out << k_DACName_Readback << ":      " << (int)Readback_     <<endl;
}

//=============================================================================================
void PixelP1ROCDACSettings::writeXML(ofstream *out) const {
  std::string mthn = "[PixelROCDACSettings::writeXML()]\t\t\t    " ;

  *out << "  <DATA>"                                                  << endl ;
  *out << "   <VDD>"            << (int)Vdd_         << "</VDD>"            << endl ;
  *out << "   <VANA>"           << (int)Vana_        << "</VANA>"           << endl ;
  *out << "   <VSH>"            << (int)Vsh_         << "</VSH>"            << endl ;
  *out << "   <VCOMP>"          << (int)Vcomp_       << "</VCOMP>"          << endl ;
  *out << "   <VWLLPR>"         << (int)VwllPr_      << "</VWLLPR>"         << endl ;
  *out << "   <VWLLSH>"         << (int)VwllSh_      << "</VWLLSH>"         << endl ;
  *out << "   <VHLDDEL>"        << (int)VHldDel_     << "</VHLDDEL>"        << endl ;
  *out << "   <VTRIM>"          << (int)Vtrim_       << "</VTRIM>"          << endl ;
  *out << "   <VCTHR>"          << (int)VcThr_       << "</VCTHR>"          << endl ;
  *out << "   <VIBIAS_BUS>"     << (int)VIbias_bus_  << "</VIBIAS_BUS>"     << endl ;
  *out << "   <PHOFFSET>"       << (int)PHOffset_    << "</PHOFFSET>"       << endl ;
  *out << "   <VCOMP_ADC>"      << (int)Vcomp_ADC_   << "</VCOMP_ADC>"      << endl ;
  *out << "   <PHSCALE>"        << (int)PHScale_     << "</PHSCALE>"        << endl ;
  *out << "   <VICOLOR>"        << (int)VIColOr_     << "</VICOLOR>"        << endl ;
  *out << "   <VCAL>"           << (int)Vcal_        << "</VCAL>"           << endl ;
  *out << "   <CALDEL>"         << (int)CalDel_      << "</CALDEL>"         << endl ;
  *out << "   <TEMPRANGE>"      << (int)TempRange_   << "</TEMPRANGE>"      << endl ;
  *out << "   <WBC>"            << (int)WBC_         << "</WBC>"            << endl ;
  *out << "   <CHIPCONTREG>"    << (int)ChipContReg_ << "</CHIPCONTREG>"    << endl ;
  *out << "   <READBACK>"       << (int)Readback_    << "</READBACK>"       << endl ;
  *out << "  </DATA>"						      << endl ;
  *out << " "							      << endl ;

}

//=============================================================================================
int PixelP1ROCDACSettings::read(std::istringstream& in, const PixelROCName& rocid)
{
    std::string mthn = "[PixelROCDACSettings::read()]\t\t\t\t    " ;

    rocid_=rocid;

    unsigned int tmp;
    string tag;

    //    cout << "[PixelROCDACSettings::read()] |" << in.str() << "|" << endl ;

    in >> tag; 
    checkTag(tag,k_DACName_Vdd,rocid);
    in >> tmp; Vdd_=tmp;
    in >> tag; 
    checkTag(tag,k_DACName_Vana,rocid);
    in >> tmp; Vana_=tmp;
    in >> tag; 
    checkTag(tag,k_DACName_Vsh,rocid);
    in >> tmp; Vsh_=tmp;
    in >> tag; 
    checkTag(tag,k_DACName_Vcomp,rocid);
    in >> tmp; Vcomp_=tmp;
    in >> tag; 
    checkTag(tag,k_DACName_VwllPr,rocid);
    in >> tmp; VwllPr_=tmp;
    in >> tag; 
    checkTag(tag,k_DACName_VwllSh,rocid);
    in >> tmp; VwllSh_=tmp;
    in >> tag; 
    checkTag(tag,k_DACName_VHldDel,rocid);
    in >> tmp; VHldDel_=tmp;
    in >> tag; 
    checkTag(tag,k_DACName_Vtrim,rocid);
    in >> tmp; Vtrim_=tmp;
    in >> tag; 
    checkTag(tag,k_DACName_VcThr,rocid);
    in >> tmp; VcThr_=tmp;
    in >> tag; 
    checkTag(tag,k_DACName_VIbias_bus,rocid);
    in >> tmp; VIbias_bus_=tmp;
    in >> tag; 
    checkTag(tag,k_DACName_PHOffset,rocid);
    in >> tmp; PHOffset_=tmp;
    in >> tag; 
    checkTag(tag,k_DACName_Vcomp_ADC,rocid);
    in >> tmp; Vcomp_ADC_=tmp;
    in >> tag; 
    checkTag(tag,k_DACName_PHScale,rocid);
    in >> tmp; PHScale_=tmp;
    in >> tag; 
    checkTag(tag,k_DACName_VIColOr,rocid);
    in >> tmp; VIColOr_=tmp;
    in >> tag; 
    checkTag(tag,k_DACName_Vcal,rocid);
    in >> tmp; Vcal_=tmp;
    in >> tag; 
    checkTag(tag,k_DACName_CalDel,rocid);
    in >> tmp; CalDel_=tmp;
    in >> tag; 
    if (tag==k_DACName_WBC+":"){
      static bool first=true;
      if (first){
	cout << __LINE__ << "]\t" << mthn << "**********************************************" << endl;
	cout << __LINE__ << "]\t" << mthn << "Did not find TempRange setting in DAC settings" << endl;
	cout << __LINE__ << "]\t" << mthn << "Will use a default value of 4."                 << endl;
	cout << __LINE__ << "]\t" << mthn << "This message will only be printed out once"     << endl;
	cout << __LINE__ << "]\t" << mthn << "**********************************************" << endl;
	TempRange_=4;
	first=false;
      }
      in >> tmp; WBC_=tmp;
    } else {	
      checkTag(tag,k_DACName_TempRange,rocid);
      in >> tmp; TempRange_=tmp;
      in >> tag; 
      checkTag(tag,k_DACName_WBC,rocid);
      in >> tmp; WBC_=tmp;
    }
    in >> tag; 
    checkTag(tag,k_DACName_ChipContReg,rocid);
    in >> tmp; ChipContReg_=tmp;
    in >> tag; 
    checkTag(tag,k_DACName_Readback,rocid);
    in >> tmp; Readback_=tmp;

    return 0;
}

int PixelP1ROCDACSettings::read(ifstream& in, const PixelROCName& rocid){
    
    std::string mthn = "[PixelROCDACSettings::read()]\t\t\t\t    " ;
    rocid_=rocid;

    unsigned int tmp;
    string tag;

    in >> tag; 
    checkTag(tag,k_DACName_Vdd,rocid);
    in >> tmp; Vdd_=tmp;
    in >> tag; 
    checkTag(tag,k_DACName_Vana,rocid);
    in >> tmp; Vana_=tmp;
    in >> tag; 
    checkTag(tag,k_DACName_Vsh,rocid);
    in >> tmp; Vsh_=tmp;
    in >> tag; 
    checkTag(tag,k_DACName_Vcomp,rocid);
    in >> tmp; Vcomp_=tmp;
    in >> tag; 
    checkTag(tag,k_DACName_VwllPr,rocid);
    in >> tmp; VwllPr_=tmp;
    in >> tag; 
    checkTag(tag,k_DACName_VwllSh,rocid);
    in >> tmp; VwllSh_=tmp;
    in >> tag; 
    checkTag(tag,k_DACName_VHldDel,rocid);
    in >> tmp; VHldDel_=tmp;
    in >> tag; 
    checkTag(tag,k_DACName_Vtrim,rocid);
    in >> tmp; Vtrim_=tmp;
    in >> tag; 
    checkTag(tag,k_DACName_VcThr,rocid);
    in >> tmp; VcThr_=tmp;
    in >> tag; 
    checkTag(tag,k_DACName_VIbias_bus,rocid);
    in >> tmp; VIbias_bus_=tmp;
    in >> tag; 
    checkTag(tag,k_DACName_PHOffset,rocid);
    in >> tmp; PHOffset_=tmp;
    in >> tag; 
    checkTag(tag,k_DACName_Vcomp_ADC,rocid);
    in >> tmp; Vcomp_ADC_=tmp;
    in >> tag; 
    checkTag(tag,k_DACName_PHScale,rocid);
    in >> tmp; PHScale_=tmp;
    in >> tag; 
    checkTag(tag,k_DACName_VIColOr,rocid);
    in >> tmp; VIColOr_=tmp;
    in >> tag; 
    checkTag(tag,k_DACName_Vcal,rocid);
    in >> tmp; Vcal_=tmp;
    in >> tag; 
    checkTag(tag,k_DACName_CalDel,rocid);
    in >> tmp; CalDel_=tmp;
    in >> tag; 
    if (tag==k_DACName_WBC+":"){
      static bool first=true;
      if (first){
	cout << __LINE__ << "]\t" << mthn << "**********************************************" << endl;
	cout << __LINE__ << "]\t" << mthn << "Did not find TempRange setting in DAC settings" << endl;
	cout << __LINE__ << "]\t" << mthn << "Will use a default value of 4."                 << endl;
	cout << __LINE__ << "]\t" << mthn << "This message will only be printed out once"     << endl;
	cout << __LINE__ << "]\t" << mthn << "**********************************************" << endl;
	TempRange_=4;
	first=false;
      }
      in >> tmp; WBC_=tmp;
    } else {	
      checkTag(tag,k_DACName_TempRange,rocid);
      in >> tmp; TempRange_=tmp;
      in >> tag; 
      checkTag(tag,k_DACName_WBC,rocid);
      in >> tmp; WBC_=tmp;
    }
    in >> tag; 
    checkTag(tag,k_DACName_ChipContReg,rocid);
    in >> tmp; ChipContReg_=tmp;
    in >> tag; 
    checkTag(tag,k_DACName_Readback,rocid);
    in >> tmp; Readback_=tmp;

    return 0;
}

/*This Function is declared in the base class
string PixelROCDACSettings::getConfigCommand(){

  string s;

  return s;

}
*/
ostream& pos::operator<<(ostream& s, const PixelP1ROCDACSettings& dacs){
  
  s << k_DACName_Vdd << "           :" << (unsigned int)dacs.Vdd_ << endl;
  s << k_DACName_Vana << "          :" << (unsigned int)dacs.Vana_ << endl;
  s << k_DACName_Vsh << "           :" << (unsigned int)dacs.Vsh_ << endl;
  s << k_DACName_Vcomp << "         :" << (unsigned int)dacs.Vcomp_ << endl;
  s << k_DACName_VwllPr << "        :" << (unsigned int)dacs.VwllPr_ << endl;
  s << k_DACName_VwllSh << "        :" << (unsigned int)dacs.VwllSh_ << endl;
  s << k_DACName_VHldDel << "       :" << (unsigned int)dacs.VHldDel_ << endl;
  s << k_DACName_Vtrim << "         :" << (unsigned int)dacs.Vtrim_ << endl;
  s << k_DACName_VcThr << "         :" << (unsigned int)dacs.VcThr_ << endl;
  s << k_DACName_VIbias_bus << "    :" << (unsigned int)dacs.VIbias_bus_ << endl;
  s << k_DACName_PHOffset << "      :" << (unsigned int)dacs.PHOffset_ << endl;
  s << k_DACName_Vcomp_ADC << "     :" << (unsigned int)dacs.Vcomp_ADC_ << endl;
  s << k_DACName_PHScale << "       :" << (unsigned int)dacs.PHScale_ << endl;
  s << k_DACName_VIColOr << "       :" << (unsigned int)dacs.VIColOr_ << endl;
  s << k_DACName_Vcal << "          :" << (unsigned int)dacs.Vcal_ << endl;
  s << k_DACName_CalDel << "        :" << (unsigned int)dacs.CalDel_ << endl;
  s << k_DACName_TempRange << "     :" << (unsigned int)dacs.TempRange_ << endl;
  s << k_DACName_WBC << "           :" << (unsigned int)dacs.WBC_ << endl;
  s << k_DACName_ChipContReg << "   :" << (unsigned int)dacs.ChipContReg_ << endl;
  s << k_DACName_Readback << "      :" << (unsigned int)dacs.Readback_ << endl;
  
  return s;

}

//Added by Umesh
//modfied- include switch statements
void PixelP1ROCDACSettings::setDac(string dacName, int dacValue){
if(ToLower(dacName) == ToLower(k_DACName_Vdd)){
    Vdd_ = dacValue;
  }
  else if(ToLower(dacName) == ToLower(k_DACName_Vdd)){
    Vdd_ = dacValue;
  }
  else if(ToLower(dacName) == ToLower(k_DACName_Vana)){
    Vana_ = dacValue;
  }
  else if(ToLower(dacName) == ToLower(k_DACName_Vsh)){
    Vsh_ = dacValue;
  }
  else if(ToLower(dacName) == ToLower(k_DACName_Vcomp)){
    Vcomp_ = dacValue;
  }
  else if(ToLower(dacName) == ToLower(k_DACName_VwllPr)){
  VwllPr_ = dacValue;
  }
  else if(ToLower(dacName) == ToLower(k_DACName_VwllSh)){
    VwllSh_ = dacValue;
  }
  else if(ToLower(dacName) == ToLower(k_DACName_VHldDel)){
    VHldDel_ = dacValue;
  }
  else if(ToLower(dacName) == ToLower(k_DACName_Vtrim)){
    Vtrim_ = dacValue;
  }
  else if(ToLower(dacName) == ToLower(k_DACName_VcThr)){
    VcThr_ = dacValue;
  }
  else if(ToLower(dacName) == ToLower(k_DACName_VIbias_bus)){
    VIbias_bus_ = dacValue;
  }
  else if(ToLower(dacName) == ToLower(k_DACName_PHOffset)){
    PHOffset_ = dacValue;
  }
  else if(ToLower(dacName) == ToLower(k_DACName_Vcomp_ADC)){
    Vcomp_ADC_ = dacValue;
  }
  else if(ToLower(dacName) == ToLower(k_DACName_PHScale)){
    PHScale_ = dacValue;
  }
  else if(ToLower(dacName) == ToLower(k_DACName_VIColOr)){
    VIColOr_ = dacValue;
  }
  else if(ToLower(dacName) == ToLower(k_DACName_Vcal)){
    Vcal_ = dacValue;
  }
  else if(ToLower(dacName) == ToLower(k_DACName_CalDel)){
    CalDel_ = dacValue;
  }
  else if(ToLower(dacName) == ToLower(k_DACName_TempRange)){
    TempRange_ = dacValue;
  }
  else if(ToLower(dacName) == ToLower(k_DACName_WBC)){
    WBC_ = dacValue;
  }
  else if(ToLower(dacName) == ToLower(k_DACName_ChipContReg)){
    ChipContReg_ = dacValue;
  }
  else if(ToLower(dacName) == ToLower(k_DACName_Readback)){
    Readback_ = dacValue;
  }
  else
{
    cout << "ERROR in PixelROCDACSettings::setDac: DAC name " << dacName << " does not exist." << endl;
    assert(0);
  }

}
//updated
unsigned int PixelP1ROCDACSettings::getDac(string dacName) const {
	 if(dacName == k_DACName_Vdd){
    return Vdd_;
  }
  else if(dacName == k_DACName_Vdd){
    return Vdd_;
  }
  else if(dacName == k_DACName_Vana){
    return Vana_;
  }
  else if(dacName == k_DACName_Vsh){
    return Vsh_;
  }
  else if(dacName == k_DACName_Vcomp){
    return Vcomp_;
  }
  else if(dacName == k_DACName_VwllPr){
    return VwllPr_;
  }
  else if(dacName == k_DACName_VwllSh){
    return VwllSh_;
  }
  else if(dacName == k_DACName_VHldDel){
    return VHldDel_;
  }
  else if(dacName == k_DACName_Vtrim){
    return Vtrim_;
  }
  else if(dacName == k_DACName_VcThr){
    return VcThr_;
  }
  else if(dacName == k_DACName_VIbias_bus){
    return VIbias_bus_;
  }
  else if(dacName == k_DACName_PHOffset){
    return PHOffset_;
  }
  else if(dacName == k_DACName_Vcomp_ADC){
    return Vcomp_ADC_;
  }
  else if(dacName == k_DACName_PHScale){
    return PHScale_;
  }
  else if(dacName == k_DACName_VIColOr){
    return VIColOr_;
  }
  else if(dacName == k_DACName_Vcal){
    return Vcal_;
  }
  else if(dacName == k_DACName_CalDel){
    return CalDel_;
  }
  else if(dacName == k_DACName_TempRange){
    return TempRange_;
  }
  else if(dacName == k_DACName_WBC){
    return WBC_;
  }
  else if(dacName == k_DACName_ChipContReg){
    return ChipContReg_;
  }
  else if(dacName == k_DACName_Readback){
    return Readback_;
  }
  else {
    cout << "ERROR in PixelROCDACSettings::getDac: DAC name " << dacName << " does not exist." << endl;
    assert(0);
  }
}
