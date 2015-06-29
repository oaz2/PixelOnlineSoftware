// $Id: PixelSupervisorGUI.cc,v 1.20 2007/08/06 16:32:00 jvaughan Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2004, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#include "PixelSupervisorGUI/include/PixelSupervisorGUI.h"
#include "PixelUtilities/PixelGUIUtilities/include/HTML2XGI.h"
#include "PixelConfigDataFormats/include/PixelConfigDB.h"

//
// provides factory method for instantion of HellWorld application
//

XDAQ_INSTANTIATOR_IMPL(PixelSupervisorGUI)

PixelSupervisorGUI::PixelSupervisorGUI(xdaq::ApplicationStub * s) throw (xdaq::exception::Exception) : xdaq::Application(s), SOAPCommander(this)
{
	xgi::bind(this, &PixelSupervisorGUI::Default, "Default");
	xgi::bind(this, &PixelSupervisorGUI::XgiHandler, "XgiHandler");
	xgi::bind(this, &PixelSupervisorGUI::LowLevelHandler, "LowLevelHandler");

	xoap::bind(this, &PixelSupervisorGUI::fireEvent, "InitialisingDone", XDAQ_NS_URI);
	xoap::bind(this, &PixelSupervisorGUI::fireEvent, "ConfiguringDone", XDAQ_NS_URI);
	xoap::bind(this, &PixelSupervisorGUI::fireEvent, "StartingDone", XDAQ_NS_URI);
	xoap::bind(this, &PixelSupervisorGUI::fireEvent, "PausingDone", XDAQ_NS_URI);
	xoap::bind(this, &PixelSupervisorGUI::fireEvent, "ResumingDone", XDAQ_NS_URI);
	xoap::bind(this, &PixelSupervisorGUI::fireEvent, "HaltingDone", XDAQ_NS_URI);

	fsm_.addState('i', "Initialising");
	fsm_.addState('I', "Initial");
	fsm_.addState('a', "Resetting");
	fsm_.addState('b', "Recovering");
	fsm_.addState('p', "Pausing");
	fsm_.addState('P', "Paused");
	fsm_.addState('r', "Resuming");
	fsm_.addState('R', "Running");
	fsm_.addState('h', "Halting");
	fsm_.addState('H', "Halted");
	fsm_.addState('c', "Configuring");
	fsm_.addState('C', "Configured");
	fsm_.addState('s', "Starting");
	fsm_.setStateName('F',"Error");
	fsm_.setFailedStateTransitionAction(this, &PixelSupervisorGUI::failurePage);

	fsm_.addStateTransition('I', 'i', "Initialise");
	fsm_.addStateTransition('i', 'H', "InitialisingDone");
	fsm_.addStateTransition('H', 'c', "Configure");
	fsm_.addStateTransition('c', 'C', "ConfiguringDone");
	fsm_.addStateTransition('C', 's', "Start");
	fsm_.addStateTransition('s', 'R', "StartingDone");
	fsm_.addStateTransition('R', 'p', "Pause");
	fsm_.addStateTransition('p', 'P', "PausingDone");
	fsm_.addStateTransition('P', 'r', "Resume");
	fsm_.addStateTransition('r', 'R', "ResumingDone");
	fsm_.addStateTransition('R', 'h', "Halt");
	fsm_.addStateTransition('h', 'H', "HaltingDone");
	fsm_.addStateTransition('P', 'h', "Halt");
	fsm_.addStateTransition('C', 'h', "Halt");

	fsm_.setInitialState('I');
	fsm_.reset();

	XDAQ_ROOT=getenv("XDAQ_ROOT");
	PixelSupervisor_ = getApplicationContext()->getApplicationGroup()->getApplicationDescriptor("PixelSupervisor", 0);
	PixelTTCSupervisor_ = getApplicationContext()->getApplicationGroup()->getApplicationDescriptor("PixelTTCSupervisor", 0);
	TTCRunning_=false;
	this->getApplicationDescriptor()->setAttribute("icon","pixel/PixelSupervisorGUI/html/pixelsupervisor.gif");
}

void PixelSupervisorGUI::Default(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception)
{
	*out << cgicc::HTMLDoctype(cgicc::HTMLDoctype::eStrict) << std::endl;
	*out << cgicc::html().set("lang", "en").set("dir","ltr") << std::endl;
	//*out << "<meta HTTP-EQUIV=\"Refresh\" CONTENT=\"5; URL=Default\">" <<endl;
	xgi::Utils::getPageHeader(*out, "PixelSupervisorGUI", fsm_.getStateName(fsm_.getCurrentState()));

	std::set<std::string> allInputs;
	allInputs.insert("Initialise");
	allInputs.insert("Configure");
	allInputs.insert("Start");
	allInputs.insert("Pause");
	allInputs.insert("Resume");
	allInputs.insert("Halt");

	std::set<std::string> clickableInputs=fsm_.getInputs(fsm_.getCurrentState());
	std::set<std::string>::iterator i;

	std::string url="/"+getApplicationDescriptor()->getURN();

	std::string currentState=fsm_.getStateName(fsm_.getCurrentState());

	*out<<"<body>"<<std::endl;
        *out<<"<form name=\"input\" method=\"get\" action=\""<<url<<"/XgiHandler"<<"\" enctype=\"multipart/form-data\">";
	*out<<" <table border=1 cellpadding=10 cellspacing=0>";
	*out<<"  <tr>";
	*out<<"   <td> <b>Current State</b> <br/>"<<currentState<<"</td>";
	*out<<"   <td colspan=5>";
	/*
	for (i=allInputs.begin();i!=allInputs.end();i++) {
		if (clickableInputs.find(*i)!=clickableInputs.end()) {
			std::string GUI_file=XDAQ_ROOT+"/pixel/PixelSupervisorGUI/html/"+(*i)+".htm";
			HTML2XGI(out, GUI_file);
		}
	}*/

	std::vector <std::pair<std::string, unsigned int> > aliasesAndKeys=PixelConfigDB::getAliases();
	std::vector <std::pair<std::string, unsigned int> >::iterator i_aliasesAndKeys=aliasesAndKeys.begin();

	if (currentState=="Halted") {

		for (;i_aliasesAndKeys!=aliasesAndKeys.end();++i_aliasesAndKeys) {
			std::string alias=i_aliasesAndKeys->first;
			if(alias[0]!='T' || alias[1]!='T' || alias[2]!='C') {
			  *out<<"       <input type=\"radio\" name=\"Alias\" value=\""<<alias<<"\">"<<alias<<"<br/>"<<std::endl;
			}
		}

	}

	*out<<"</td>"<<endl;
	*out<<"</tr>"<<endl;
	*out<<"<tr>"<<endl;

	for (i=allInputs.begin();i!=allInputs.end();i++)
	{
		*out<<"<td>";
		if (clickableInputs.find(*i)!=clickableInputs.end())
			*out<<"<input type=\"submit\" name=\"StateInput\" value=\""<<(*i)<<"\"/>";
		else
			*out<<"<input type=\"submit\" disabled=\"true\" name=\"StateInput\" value=\""<<(*i)<<"\"/>";
		*out<<"</td>"<<endl;
	}

	*out<<"</tr>";
	*out<<"</table>";
	*out<<"</form>"<<endl;

	std::set<std::string> allLowLevelInputs;
	std::set<std::string> clickableLowLevelInputs;
	
	for(i_aliasesAndKeys=aliasesAndKeys.begin();i_aliasesAndKeys!=aliasesAndKeys.end();++i_aliasesAndKeys) {
	  std::string alias=i_aliasesAndKeys->first;
	  if(alias[0]=='T' && alias[1]=='T' && alias[2]=='C') {
	    std::string ttcalias = alias.substr(3);
	    allLowLevelInputs.insert(ttcalias);
	    if(!TTCRunning_) {
	      clickableLowLevelInputs.insert(ttcalias);
	    }
	  }
	}
	if(!allLowLevelInputs.empty()) {
	  allLowLevelInputs.insert("StopPeriodic");
	}
	if(TTCRunning_) {
	  clickableLowLevelInputs.insert("StopPeriodic");
	}

	std::set<std::string>::iterator lli;

        *out<<"<form name=\"input\" method=\"get\" action=\""<<url<<"/LowLevelHandler"<<"\" enctype=\"multipart/form-data\">";

	if (currentState=="Paused" || currentState=="Configured" || currentState=="Halted") {
	  for (lli=allLowLevelInputs.begin();lli!=allLowLevelInputs.end();lli++)
	    {
	      *out<<"<td>";
	      if (clickableLowLevelInputs.find(*lli)!=clickableLowLevelInputs.end()) {
		*out<<"<input type=\"submit\" name=\"LowLevelCommand\" value=\""<<(*lli)<<"\"/>";
	      } else {
		*out<<"<input type=\"submit\" disabled=\"true\" name=\"LowLevelCommand\" value=\""<<(*lli)<<"\"/>";
	      }
	      *out<<"</td>"<<endl;
	    }
	  //*out<<"       <input type=\"submit\" name=\"LowLevelCommand\" value=\"PeriodicL1A\"/><br/>"<<std::endl;
	}
	*out<<"</form>"<<endl;
	*out<<"</body>"<<endl;
	*out<<"</html>";
}

void PixelSupervisorGUI::XgiHandler (xgi::Input *in, xgi::Output *out) throw (xgi::exception::Exception)
{
	cgicc::Cgicc cgi(in);
	std::string stateInput = cgi.getElement("StateInput")->getValue();

	Attribute_Vector parameters(10);
	if (stateInput=="Configure") {
		parameters.at(0).name_="Alias";	parameters.at(0).value_=cgi.getElement("Alias")->getValue();
		parameters.resize(1);
	} else {
		parameters.resize(0);
	}

	try
	{
		toolbox::Event::Reference e(new toolbox::Event(stateInput, this));
		fsm_.fireEvent(e);
	}
	catch (toolbox::fsm::exception::Exception & e)
        {
                XCEPT_RETHROW(xoap::exception::Exception, "Invalid State Machine Input.", e);
        }

	Send(PixelSupervisor_, stateInput , parameters);
	this->Default(in, out);

}


void PixelSupervisorGUI::LowLevelHandler (xgi::Input *in, xgi::Output *out) throw (xgi::exception::Exception)
{
  cgicc::Cgicc cgi(in);
  std::string input = cgi.getElement("LowLevelCommand")->getValue();
  
  Send(PixelTTCSupervisor_, input);
  if(input=="StopPeriodic") {
    TTCRunning_=false;
  } else {
    TTCRunning_=true;
  }
  
  this->Default(in, out);
  
}

xoap::MessageReference PixelSupervisorGUI::fireEvent (xoap::MessageReference msg) throw (xoap::exception::Exception)
{
	std::string commandName=Receive(msg);
	try
	{
		toolbox::Event::Reference e(new toolbox::Event(commandName, this));
		fsm_.fireEvent(e);
	}
	catch (toolbox::fsm::exception::Exception & e)
	{
		XCEPT_RETHROW(xoap::exception::Exception, "invalid command", e);
	}

	xoap::MessageReference reply = MakeSOAPMessageReference(commandName+"Response");
	return reply;
}

void PixelSupervisorGUI::failurePage (toolbox::Event::Reference e) throw (toolbox::fsm::exception::Exception)
{
	cout<<"HELLO!"<<endl;
  toolbox::fsm::FailedEvent & fe = dynamic_cast<toolbox::fsm::FailedEvent&>(*e);
  LOG4CPLUS_INFO (getApplicationLogger(), "Failure occurred when performing transition from: "  <<
		  fe.getFromState() <<  " to: " << fe.getToState() << " exception: " << fe.getException().what() );
}

