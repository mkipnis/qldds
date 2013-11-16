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


#include "DataReaderImplHandler.hpp"

using namespace qldds_utils;

void DataReaderImplHandler::on_reading_start( DDS::DataReader_ptr& reader ) 
{
   ACE_DEBUG( (LM_DEBUG, "(%T|%P|%t) DataReaderImplHandler::on_reading_start : [%s|%s]\n",
         reader->get_topicdescription()->get_type_name(), reader->get_topicdescription()->get_name() ) );
};

void DataReaderImplHandler::on_reading_end( DDS::DataReader_ptr& reader, int count ) 
{
  ACE_DEBUG( (LM_DEBUG, "(%T|%P|%t) DataReaderImplHandler::onReadingEnd : [%s|%s]\n",
        reader->get_topicdescription()->get_type_name(), reader->get_topicdescription()->get_name() ) );
};

bool DataReaderImplHandler::pre_quantlib_addin_call( DDS::DataReader_ptr& reader, const char* qlType, void* qlddsObj ) 
{
  ACE_DEBUG( (LM_DEBUG, "(%T|%P|%t) DataReaderImplHandler::preQuantLibAddinCall : [%s|%s|%s|%08X]\n",
        reader->get_topicdescription()->get_type_name(), reader->get_topicdescription()->get_name(), qlType, qlddsObj ) );

  return true; 
};

bool DataReaderImplHandler::post_quantlib_addin_call( DDS::DataReader_ptr& reader, const char* qlType, void* qlddsObj, const char* returnType, void* returnObject ) 
{
  ACE_DEBUG( (LM_DEBUG, "(%T|%P|%t) DataReaderImplHandler::post_quantlib_addin_call : [%s|%s|%s|%08X|%s|%08X]\n",
        reader->get_topicdescription()->get_type_name(), reader->get_topicdescription()->get_name(),
        qlType, qlddsObj, returnType, returnObject ) );

  return true; 
};

void DataReaderImplHandler::on_std_exception( DDS::DataReader_ptr& reader, void* obj, std::exception& e ) 
{
  ACE_DEBUG( (LM_DEBUG, "(%T|%P|%t) DataReaderImplHandler::on_std_exception : [%s|%s|%s]\n",
        reader->get_topicdescription()->get_type_name(), reader->get_topicdescription()->get_name(), e.what() ) ); 
};

void DataReaderImplHandler::on_dds_reading_error( DDS::DataReader_ptr& reader, std::string& err ) 
{
  ACE_DEBUG( (LM_DEBUG, "(%T|%P|%t) DataReaderImplHandler::on_dds_reading_error : [%s|%s|%s]\n",
        reader->get_topicdescription()->get_type_name(), reader->get_topicdescription()->get_name(), err.c_str() ) ); 
};

void DataReaderImplHandler::on_dds_exception( DDS::DataReader_ptr& reader, CORBA::Exception& exp ) 
{ 
  ACE_DEBUG( (LM_DEBUG, "(%T|%P|%t) DataReaderImplHandler::on_dds_exception : [%s|%s|%s]\n",
        reader->get_topicdescription()->get_type_name(), reader->get_topicdescription()->get_name(), exp._info().c_str() ) ); 
};

void DataReaderImplHandler::on_data_available( DDS::DataReader_ptr reader) 
         throw (CORBA::SystemException)
{
  ACE_DEBUG( (LM_DEBUG, "(%T|%P|%t) DataReaderImplHandler::on_data_available" ) );
}

void DataReaderImplHandler::on_requested_deadline_missed ( DDS::DataReader_ptr reader, const DDS::RequestedDeadlineMissedStatus & status)
        throw (CORBA::SystemException)
{
  ACE_DEBUG( (LM_DEBUG, "(%T|%P|%t) DataReaderImplHandler::on_requested_deadline_missed" ) );
};

void DataReaderImplHandler::on_requested_incompatible_qos ( DDS::DataReader_ptr reader, const DDS::RequestedIncompatibleQosStatus & status)
        throw (CORBA::SystemException)
{
  ACE_DEBUG( (LM_DEBUG, "(%T|%P|%t) DataReaderImplHandler::on_requested_incompatible_qos" ) );
};

void DataReaderImplHandler::on_liveliness_changed ( DDS::DataReader_ptr reader, const DDS::LivelinessChangedStatus & status)
        throw (CORBA::SystemException)
{
  ACE_DEBUG( (LM_DEBUG, "(%T|%P|%t) DataReaderImplHandler::on_liveliness_changed" ) );
};

void DataReaderImplHandler::on_subscription_matched ( DDS::DataReader_ptr reader, const DDS::SubscriptionMatchedStatus & status)
        throw (CORBA::SystemException)
{
  ACE_DEBUG( (LM_DEBUG, "(%T|%P|%t) DataReaderImplHandler::on_subscription_matched" ) );
};

void DataReaderImplHandler::on_sample_rejected( DDS::DataReader_ptr reader, const DDS::SampleRejectedStatus& status)
        throw (CORBA::SystemException)
{
  ACE_DEBUG( (LM_DEBUG, "(%T|%P|%t) DataReaderImplHandler::on_sample_rejected" ) );
};

void DataReaderImplHandler::on_sample_lost( DDS::DataReader_ptr reader, const DDS::SampleLostStatus& status)
        throw (CORBA::SystemException)
{
  ACE_DEBUG( (LM_DEBUG, "(%T|%P|%t) DataReaderImplHandler::on_sample_lost" ) );
};
