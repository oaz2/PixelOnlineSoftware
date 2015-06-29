// $Id: PixelSupervisorGUI.h,v 1.7 2007/08/06 16:16:20 jvaughan Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2004, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _PixelSupervisorGUI_h_
#define _PixelSupervisorGUI_h_

#include "xdaq/Application.h"
#include "xdaq/ApplicationGroup.h"
#include "xdaq/ApplicationContext.h"
#include "xdaq/ApplicationStub.h"
#include "xdaq/exception/Exception.h"

#include "xdaq/NamespaceURI.h"

#include "xoap/MessageReference.h"
#include "xoap/MessageFactory.h"
#include "xoap/SOAPEnvelope.h"
#include "xoap/SOAPBody.h"
#include "xoap/Method.h"


#include "xdata/String.h"
#include "xdata/UnsignedLong.h"

#include "xgi/Utils.h"
#include "xgi/Method.h"

#include "cgicc/CgiDefs.h"
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"

#include "toolbox/fsm/FiniteStateMachine.h"
#include "toolbox/fsm/FailedEvent.h"
#include "toolbox/exception/Handler.h"
#include "toolbox/Event.h"
#include "PixelUtilities/PixelSOAPUtilities/include/SOAPCommander.h"

class PixelSupervisorGUI: public xdaq::Application, public SOAPCommander
{
	
	public:
		XDAQ_INSTANTIATOR();

		/// Constructor for PixelSupervisorGUI (to be replaced by the Function Manager).
		/// Bindings made to SOAP and xgi messages and the states and transitions of the Web State Machine defined.
		PixelSupervisorGUI(xdaq::ApplicationStub * s) throw (xdaq::exception::Exception);

		/// Default function to be called whenever XDAQ invokes PixelSupervisorGUI
		/// Renders HTML output
		void Default(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);

		/// Dispatches SOAP messages to PixelSupervisor.
		void XgiHandler (xgi::Input *in, xgi::Output *out) throw (xgi::exception::Exception);

		void LowLevelHandler (xgi::Input *in, xgi::Output *out) throw (xgi::exception::Exception);

		/// fireEvent parses incoming SOAP messages to find incoming commands.
		/// Updates PixelSupervisorGUI state accordingly.
		xoap::MessageReference fireEvent (xoap::MessageReference msg) throw (xoap::exception::Exception);

		/// failurePage is where you go to when the failed state of PixelSupervisorGUI is entered.
		/// Allows the user to retry.
		void failurePage (toolbox::Event::Reference e) throw (toolbox::fsm::exception::Exception);

	protected:

	/// wsm_ is the core state machine.
	/// It is defined as an object of class WSM
	//xgi::WSM wsm_;
	toolbox::fsm::FiniteStateMachine fsm_;

	std::string XDAQ_ROOT;
	xdaq::ApplicationDescriptor *PixelSupervisor_;
	xdaq::ApplicationDescriptor *PixelTTCSupervisor_;
	bool TTCRunning_;

};

#endif
