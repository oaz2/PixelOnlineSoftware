//
// This class provide the data structure for the
// ROC DAC parameters
//
// At this point I do not see a reason to make an
// abstract layer for this code.
//

#include "CalibFormats/SiPixelObjects/interface/PixelROCDACSettings.h"
#include "CalibFormats/SiPixelObjects/interface/PixelDACNames.h"
#include <fstream>
#include <iostream>

using namespace pos;
using namespace std;

PixelROCDACSettings::PixelROCDACSettings(){}


//=============================================================================================
void PixelROCDACSettings::checkTag(string tag, 
				   string dacName,
				   const PixelROCName& rocid){
  
  std::string mthn = "[PixelROCDACSettings::checkTag()]\t\t\t\t    " ;
  dacName+=":";
  if (tag!=dacName) {
    cout << __LINE__ << "]\t" << mthn << "Read ROC name       : "	      << tag     << endl;
    cout << __LINE__ << "]\t" << mthn << "But expected to find: "	      << dacName << endl;
    cout << __LINE__ << "]\t" << mthn << "When reading DAC settings for ROC " << rocid   << endl;
    assert(0);
  }

}

//Doesnt do anythiing!
string PixelROCDACSettings::getConfigCommand(){

  string s;

  return s;

}

string PixelROCDACSettings::ToLower(string generic)
{
  string result ;
  for(unsigned int i = 0; i < generic.length() ; i++)
    {
      result.append(1,(char)tolower(generic[i]) );
    }
  return result ;
}
