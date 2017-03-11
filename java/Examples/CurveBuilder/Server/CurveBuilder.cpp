/*
    Copyright (C) 2013 Mike Kipnis

   This file is part of QLDDS, a free-software/open-source library
   for utilization of QuantLib in the distributed envrionment via DDS.

   QLDDS is free software: you can redistribute it and/or modify it
   under the terms of the QLDDS license.  You should have received a
   copy of the license along with this program; if not, please email
   <dev@qldds.org>. The license is also available online at
   <http://qldds.org/qldds-license/>.

   This program is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
   FOR A PARTICULAR PURPOSE.  See the license for more details.
*/


#include <ql/quantlib.hpp>
#include <Addins/Cpp/addincpp.hpp>
#include <oh/ohdefines.hpp>

#include <CurveBuilderC.h>
#include <CurveBuilderTypeSupportC.h>
#include <CurveBuilderTypeSupportImpl.h>

#include "CurveBuilderRequestDataReaderListenerImpl.h"

#include <BasicDomainParticipant.h>

ObjectHandler::property_t OH_NULL;

int ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
  DDS::DomainParticipantFactory_var dpf = DDS::DomainParticipantFactory::_nil();
  DDS::DomainParticipant_var participant = DDS::DomainParticipant::_nil();

  try
  {
     QuantLibAddinCpp::initializeAddin();

     QuantLib::Calendar calendar = QuantLib::TARGET();

     QuantLib::Date settlementDate(19, QuantLib::September, 2016);

     settlementDate = calendar.adjust(settlementDate);

     QuantLib::Integer fixingDays = 2;

     QuantLib::Date todaysDate = calendar.advance(settlementDate, -fixingDays, QuantLib::Days);

     QuantLibAddinCpp::qlSettingsSetEvaluationDate( todaysDate.serialNumber(), OH_NULL );

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
