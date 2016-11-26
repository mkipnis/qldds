

/*
   Copyright (C) 2016 Mike Kipnis

   This file is part of QLDDS, a free-software/open-source library
   for utilization of QuantLib in the distributed envrionment via DDS.

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
*/


#include <ql/quantlib.hpp>
#include <Addins/Cpp/addincpp.hpp>
#include <oh/ohdefines.hpp>

#include <CurveBuilderC.h>
#include <CurveBuilderTypeSupportC.h>
#include <CurveBuilderTypeSupportImpl.h>

#include "CurveBuilderRequestDataReaderListenerImpl.h"

#include <BasicDomainParticipant.h>

int ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
  DDS::DomainParticipantFactory_var dpf = DDS::DomainParticipantFactory::_nil();
  DDS::DomainParticipant_var participant = DDS::DomainParticipant::_nil();

  try
  {
     QuantLibAddinCpp::initializeAddin();

     QuantLib::Calendar calendar = QuantLib::TARGET();

     dpf = TheParticipantFactoryWithArgs(argc, argv);

     qldds_utils::BasicDomainParticipant participant( dpf, 4 );
     participant.createPublisher();
     participant.createSubscriber();

    // QuantLibAddinCpp::qlLibor("USDLibor3M", "USD", "3M", "", false, false, true);

     DDS::Topic_var curve_price_request_topic =
         participant.createTopicAndRegisterType
         < CurveBuilder::CurveBuilderRequestTypeSupport_var, CurveBuilder::CurveBuilderRequestTypeSupportImpl >
         ( "CURVE_BUILDER_REQUEST_TOPIC" );


     DDS::Topic_var curve_price_reply_topic =
         participant.createTopicAndRegisterType
         < CurveBuilder::CurveBuilderReplyTypeSupport_var, CurveBuilder::CurveBuilderReplyTypeSupportImpl >
         ( "CURVE_BUILDER_REPLY_TOPIC" );

     CurveBuilder::CurveBuilderReplyDataWriter_var curve_builder_reply_dw = participant.createDataWriter
      < CurveBuilder::CurveBuilderReplyDataWriter_var, CurveBuilder::CurveBuilderReplyDataWriter >
       ( curve_price_reply_topic );


     DDS::DataReaderListener_var listener (new CurveBuilderRequestDataReaderListenerImpl( curve_builder_reply_dw ) );

     participant.createDataReaderListener ( curve_price_request_topic, listener );
  
     for ( int times=0; times<100; times++)
        ACE_OS::sleep(1);

  }catch (CORBA::Exception& e)
  {
    cerr << "Exception caught in main.cpp:" << endl << e << endl;
    ACE_OS::exit(1);
  }

  TheServiceParticipant->shutdown();

  return 0;
}
