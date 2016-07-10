/*
   Copyright (C) 2015 Mike Kipnis

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
// This file was generated automatically by qldds_gensrc.py.  If you edit this file
// manually then your changes will be lost the next time gensrc runs.

// This source code file was generated from the following stub:
//      ocm/qldds/gensrc/stubs/stub.opendds.body

#include "instrumentsDataReaderListenerImpl.hpp"

#include <qldds_convert_utils.h>

namespace instruments {

void qlInstrumentNPVDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   instruments::qlInstrumentNPVDataReader_var obj_dr
     = instruments::qlInstrumentNPVDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlInstrumentNPVDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    instruments::qlInstrumentNPV obj;
    DDS::SampleInfo si ;
    DDS::ReturnCode_t status = obj_dr->take_next_sample(obj, si) ;

    if ( status == DDS::RETCODE_OK )
    {
      if ( si.valid_data == true )
      {
         ++count;

         if ( pre_quantlib_addin_call( reader, si, obj ) )
         {
            double returnObject;;

            try {

              ACE_Guard<ACE_Mutex> guard( get_ACE_Mutex() );

              returnObject = QuantLibAddinCpp::qlInstrumentNPV ( 
              obj.ObjectId.in(),
              obj.Trigger );
              ;
          
            } catch ( std::exception& e )
            {
              on_std_exception( reader, obj, e );
              continue;
            }

            if ( !post_quantlib_addin_call( reader, obj, returnObject ) )
             break; 
         }
      }

    } else if (status == DDS::RETCODE_NO_DATA) {

       on_reading_end( reader, count );

       break;

    }  else {
       std::string err = "ERROR: read qlInstrumentNPV: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlInstrumentNPVDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInstrumentNPVDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlInstrumentNPVDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInstrumentNPVDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlInstrumentNPVDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInstrumentNPVDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlInstrumentNPVDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInstrumentNPVDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlInstrumentNPVDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInstrumentNPVDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlInstrumentNPVDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInstrumentNPVDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlInstrumentNPVDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlInstrumentNPVDataReaderListenerImpl::on_reading_start\n")));
}

void qlInstrumentNPVDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlInstrumentNPVDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlInstrumentNPVDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, instruments::qlInstrumentNPV& )
{
  return true;
}

bool qlInstrumentNPVDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, instruments::qlInstrumentNPV&, double& )
{
  return true;
}

void qlInstrumentNPVDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, instruments::qlInstrumentNPV&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInstrumentNPVDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlInstrumentNPVDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInstrumentNPVDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlInstrumentNPVDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInstrumentNPVDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlInstrumentSetPricingEngineDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   instruments::qlInstrumentSetPricingEngineDataReader_var obj_dr
     = instruments::qlInstrumentSetPricingEngineDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlInstrumentSetPricingEngineDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    instruments::qlInstrumentSetPricingEngine obj;
    DDS::SampleInfo si ;
    DDS::ReturnCode_t status = obj_dr->take_next_sample(obj, si) ;

    if ( status == DDS::RETCODE_OK )
    {
      if ( si.valid_data == true )
      {
         ++count;

         if ( pre_quantlib_addin_call( reader, si, obj ) )
         {
            bool returnObject;;

            try {

              ACE_Guard<ACE_Mutex> guard( get_ACE_Mutex() );

              returnObject = QuantLibAddinCpp::qlInstrumentSetPricingEngine ( 
              obj.ObjectId.in(),
              obj.PricingEngine.in(),
              obj.Trigger );
              ;
          
            } catch ( std::exception& e )
            {
              on_std_exception( reader, obj, e );
              continue;
            }

            if ( !post_quantlib_addin_call( reader, obj, returnObject ) )
             break; 
         }
      }

    } else if (status == DDS::RETCODE_NO_DATA) {

       on_reading_end( reader, count );

       break;

    }  else {
       std::string err = "ERROR: read qlInstrumentSetPricingEngine: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlInstrumentSetPricingEngineDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInstrumentSetPricingEngineDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlInstrumentSetPricingEngineDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInstrumentSetPricingEngineDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlInstrumentSetPricingEngineDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInstrumentSetPricingEngineDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlInstrumentSetPricingEngineDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInstrumentSetPricingEngineDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlInstrumentSetPricingEngineDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInstrumentSetPricingEngineDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlInstrumentSetPricingEngineDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInstrumentSetPricingEngineDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlInstrumentSetPricingEngineDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlInstrumentSetPricingEngineDataReaderListenerImpl::on_reading_start\n")));
}

void qlInstrumentSetPricingEngineDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlInstrumentSetPricingEngineDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlInstrumentSetPricingEngineDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, instruments::qlInstrumentSetPricingEngine& )
{
  return true;
}

bool qlInstrumentSetPricingEngineDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, instruments::qlInstrumentSetPricingEngine&, bool& )
{
  return true;
}

void qlInstrumentSetPricingEngineDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, instruments::qlInstrumentSetPricingEngine&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInstrumentSetPricingEngineDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlInstrumentSetPricingEngineDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInstrumentSetPricingEngineDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlInstrumentSetPricingEngineDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInstrumentSetPricingEngineDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlInstrumentValuationDateDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   instruments::qlInstrumentValuationDateDataReader_var obj_dr
     = instruments::qlInstrumentValuationDateDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlInstrumentValuationDateDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    instruments::qlInstrumentValuationDate obj;
    DDS::SampleInfo si ;
    DDS::ReturnCode_t status = obj_dr->take_next_sample(obj, si) ;

    if ( status == DDS::RETCODE_OK )
    {
      if ( si.valid_data == true )
      {
         ++count;

         if ( pre_quantlib_addin_call( reader, si, obj ) )
         {
            long returnObject;;

            try {

              ACE_Guard<ACE_Mutex> guard( get_ACE_Mutex() );

              returnObject = QuantLibAddinCpp::qlInstrumentValuationDate ( 
              obj.ObjectId.in(),
              obj.Trigger );
              ;
          
            } catch ( std::exception& e )
            {
              on_std_exception( reader, obj, e );
              continue;
            }

            if ( !post_quantlib_addin_call( reader, obj, returnObject ) )
             break; 
         }
      }

    } else if (status == DDS::RETCODE_NO_DATA) {

       on_reading_end( reader, count );

       break;

    }  else {
       std::string err = "ERROR: read qlInstrumentValuationDate: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlInstrumentValuationDateDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInstrumentValuationDateDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlInstrumentValuationDateDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInstrumentValuationDateDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlInstrumentValuationDateDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInstrumentValuationDateDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlInstrumentValuationDateDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInstrumentValuationDateDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlInstrumentValuationDateDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInstrumentValuationDateDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlInstrumentValuationDateDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInstrumentValuationDateDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlInstrumentValuationDateDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlInstrumentValuationDateDataReaderListenerImpl::on_reading_start\n")));
}

void qlInstrumentValuationDateDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlInstrumentValuationDateDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlInstrumentValuationDateDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, instruments::qlInstrumentValuationDate& )
{
  return true;
}

bool qlInstrumentValuationDateDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, instruments::qlInstrumentValuationDate&, long& )
{
  return true;
}

void qlInstrumentValuationDateDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, instruments::qlInstrumentValuationDate&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInstrumentValuationDateDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlInstrumentValuationDateDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInstrumentValuationDateDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlInstrumentValuationDateDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInstrumentValuationDateDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}
}
