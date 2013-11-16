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
// This file was generated automatically by qldds_gensrc.py.  If you edit this file
// manually then your changes will be lost the next time gensrc runs.

// This source code file was generated from the following stub:
//      Users/mkipnis/Dev/qldds/gensrc/stubs/stub.opendds.body

#include "creditDataReaderListenerImpl.hpp"

#include <qldds_convert_utils.h>

namespace credit {

void qlHazardRateCurveDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   credit::qlHazardRateCurveDataReader_var obj_dr
     = credit::qlHazardRateCurveDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlHazardRateCurveDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    credit::qlHazardRateCurve obj;
    DDS::SampleInfo si ;
    DDS::ReturnCode_t status = obj_dr->take_next_sample(obj, si) ;

    if ( status == DDS::RETCODE_OK )
    {
      if ( si.valid_data == true )
      {
         ++count;

         if ( pre_quantlib_addin_call( reader, si, obj ) )
         {
            std::string returnObject;;

            try {

              ACE_Guard<ACE_Mutex> guard( get_ACE_Mutex() );

              returnObject = QuantLibAddinCpp::qlHazardRateCurve ( 
              obj.ObjectId.in(),
             qldds_utils::vector_cast<ObjectHandler::property_t,CORBA::StringSeq>(obj.CurveDates),
             qldds_utils::vector_cast<double,CORBA::DoubleSeq>(obj.CurveRates),
              obj.DayCounter.in(),
              static_cast<bool>(obj.Permanent),
              obj.Trigger,
              static_cast<bool>(obj.Overwrite) );
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
       std::string err = "ERROR: read qlHazardRateCurve: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlHazardRateCurveDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlHazardRateCurveDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlHazardRateCurveDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlHazardRateCurveDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlHazardRateCurveDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlHazardRateCurveDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlHazardRateCurveDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlHazardRateCurveDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlHazardRateCurveDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlHazardRateCurveDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlHazardRateCurveDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlHazardRateCurveDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlHazardRateCurveDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlHazardRateCurveDataReaderListenerImpl::on_reading_start\n")));
}

void qlHazardRateCurveDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlHazardRateCurveDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlHazardRateCurveDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, credit::qlHazardRateCurve& )
{
  return true;
}

bool qlHazardRateCurveDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, credit::qlHazardRateCurve&, std::string& )
{
  return true;
}

void qlHazardRateCurveDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, credit::qlHazardRateCurve&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlHazardRateCurveDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlHazardRateCurveDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlHazardRateCurveDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlHazardRateCurveDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlHazardRateCurveDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlMidPointCdsEngineDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   credit::qlMidPointCdsEngineDataReader_var obj_dr
     = credit::qlMidPointCdsEngineDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlMidPointCdsEngineDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    credit::qlMidPointCdsEngine obj;
    DDS::SampleInfo si ;
    DDS::ReturnCode_t status = obj_dr->take_next_sample(obj, si) ;

    if ( status == DDS::RETCODE_OK )
    {
      if ( si.valid_data == true )
      {
         ++count;

         if ( pre_quantlib_addin_call( reader, si, obj ) )
         {
            std::string returnObject;;

            try {

              ACE_Guard<ACE_Mutex> guard( get_ACE_Mutex() );

              returnObject = QuantLibAddinCpp::qlMidPointCdsEngine ( 
              obj.ObjectId.in(),
              obj.DefaultCurve.in(),
              static_cast<double>(obj.RecoveryRate),
              obj.YieldCurve.in(),
              static_cast<bool>(obj.Permanent),
              obj.Trigger,
              static_cast<bool>(obj.Overwrite) );
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
       std::string err = "ERROR: read qlMidPointCdsEngine: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlMidPointCdsEngineDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMidPointCdsEngineDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlMidPointCdsEngineDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMidPointCdsEngineDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlMidPointCdsEngineDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMidPointCdsEngineDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlMidPointCdsEngineDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMidPointCdsEngineDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlMidPointCdsEngineDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMidPointCdsEngineDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlMidPointCdsEngineDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMidPointCdsEngineDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlMidPointCdsEngineDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlMidPointCdsEngineDataReaderListenerImpl::on_reading_start\n")));
}

void qlMidPointCdsEngineDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlMidPointCdsEngineDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlMidPointCdsEngineDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, credit::qlMidPointCdsEngine& )
{
  return true;
}

bool qlMidPointCdsEngineDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, credit::qlMidPointCdsEngine&, std::string& )
{
  return true;
}

void qlMidPointCdsEngineDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, credit::qlMidPointCdsEngine&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMidPointCdsEngineDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlMidPointCdsEngineDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMidPointCdsEngineDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlMidPointCdsEngineDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMidPointCdsEngineDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlPiecewiseFlatForwardCurveDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   credit::qlPiecewiseFlatForwardCurveDataReader_var obj_dr
     = credit::qlPiecewiseFlatForwardCurveDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlPiecewiseFlatForwardCurveDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    credit::qlPiecewiseFlatForwardCurve obj;
    DDS::SampleInfo si ;
    DDS::ReturnCode_t status = obj_dr->take_next_sample(obj, si) ;

    if ( status == DDS::RETCODE_OK )
    {
      if ( si.valid_data == true )
      {
         ++count;

         if ( pre_quantlib_addin_call( reader, si, obj ) )
         {
            std::string returnObject;;

            try {

              ACE_Guard<ACE_Mutex> guard( get_ACE_Mutex() );

              returnObject = QuantLibAddinCpp::qlPiecewiseFlatForwardCurve ( 
              obj.ObjectId.in(),
              qldds_utils::from_iso_string_to_oh_property(obj.ReferenceDate.in()),
             qldds_utils::vector_cast<std::string,CORBA::StringSeq>(obj.RateHelpers),
              obj.DayCounter.in(),
              static_cast<double>(obj.Accuracy),
              static_cast<bool>(obj.Permanent),
              obj.Trigger,
              static_cast<bool>(obj.Overwrite) );
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
       std::string err = "ERROR: read qlPiecewiseFlatForwardCurve: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlPiecewiseFlatForwardCurveDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlPiecewiseFlatForwardCurveDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlPiecewiseFlatForwardCurveDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlPiecewiseFlatForwardCurveDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlPiecewiseFlatForwardCurveDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlPiecewiseFlatForwardCurveDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlPiecewiseFlatForwardCurveDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlPiecewiseFlatForwardCurveDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlPiecewiseFlatForwardCurveDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlPiecewiseFlatForwardCurveDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlPiecewiseFlatForwardCurveDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlPiecewiseFlatForwardCurveDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlPiecewiseFlatForwardCurveDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlPiecewiseFlatForwardCurveDataReaderListenerImpl::on_reading_start\n")));
}

void qlPiecewiseFlatForwardCurveDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlPiecewiseFlatForwardCurveDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlPiecewiseFlatForwardCurveDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, credit::qlPiecewiseFlatForwardCurve& )
{
  return true;
}

bool qlPiecewiseFlatForwardCurveDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, credit::qlPiecewiseFlatForwardCurve&, std::string& )
{
  return true;
}

void qlPiecewiseFlatForwardCurveDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, credit::qlPiecewiseFlatForwardCurve&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlPiecewiseFlatForwardCurveDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlPiecewiseFlatForwardCurveDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlPiecewiseFlatForwardCurveDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlPiecewiseFlatForwardCurveDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlPiecewiseFlatForwardCurveDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlPiecewiseFlatHazardRateCurveDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   credit::qlPiecewiseFlatHazardRateCurveDataReader_var obj_dr
     = credit::qlPiecewiseFlatHazardRateCurveDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlPiecewiseFlatHazardRateCurveDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    credit::qlPiecewiseFlatHazardRateCurve obj;
    DDS::SampleInfo si ;
    DDS::ReturnCode_t status = obj_dr->take_next_sample(obj, si) ;

    if ( status == DDS::RETCODE_OK )
    {
      if ( si.valid_data == true )
      {
         ++count;

         if ( pre_quantlib_addin_call( reader, si, obj ) )
         {
            std::string returnObject;;

            try {

              ACE_Guard<ACE_Mutex> guard( get_ACE_Mutex() );

              returnObject = QuantLibAddinCpp::qlPiecewiseFlatHazardRateCurve ( 
              obj.ObjectId.in(),
              qldds_utils::from_iso_string_to_oh_property(obj.ReferenceDate.in()),
             qldds_utils::vector_cast<std::string,CORBA::StringSeq>(obj.Helpers),
              obj.DayCounter.in(),
              static_cast<double>(obj.Accuracy),
              static_cast<bool>(obj.Permanent),
              obj.Trigger,
              static_cast<bool>(obj.Overwrite) );
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
       std::string err = "ERROR: read qlPiecewiseFlatHazardRateCurve: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlPiecewiseFlatHazardRateCurveDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlPiecewiseFlatHazardRateCurveDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlPiecewiseFlatHazardRateCurveDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlPiecewiseFlatHazardRateCurveDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlPiecewiseFlatHazardRateCurveDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlPiecewiseFlatHazardRateCurveDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlPiecewiseFlatHazardRateCurveDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlPiecewiseFlatHazardRateCurveDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlPiecewiseFlatHazardRateCurveDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlPiecewiseFlatHazardRateCurveDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlPiecewiseFlatHazardRateCurveDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlPiecewiseFlatHazardRateCurveDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlPiecewiseFlatHazardRateCurveDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlPiecewiseFlatHazardRateCurveDataReaderListenerImpl::on_reading_start\n")));
}

void qlPiecewiseFlatHazardRateCurveDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlPiecewiseFlatHazardRateCurveDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlPiecewiseFlatHazardRateCurveDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, credit::qlPiecewiseFlatHazardRateCurve& )
{
  return true;
}

bool qlPiecewiseFlatHazardRateCurveDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, credit::qlPiecewiseFlatHazardRateCurve&, std::string& )
{
  return true;
}

void qlPiecewiseFlatHazardRateCurveDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, credit::qlPiecewiseFlatHazardRateCurve&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlPiecewiseFlatHazardRateCurveDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlPiecewiseFlatHazardRateCurveDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlPiecewiseFlatHazardRateCurveDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlPiecewiseFlatHazardRateCurveDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlPiecewiseFlatHazardRateCurveDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlSpreadCdsHelperDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   credit::qlSpreadCdsHelperDataReader_var obj_dr
     = credit::qlSpreadCdsHelperDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlSpreadCdsHelperDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    credit::qlSpreadCdsHelper obj;
    DDS::SampleInfo si ;
    DDS::ReturnCode_t status = obj_dr->take_next_sample(obj, si) ;

    if ( status == DDS::RETCODE_OK )
    {
      if ( si.valid_data == true )
      {
         ++count;

         if ( pre_quantlib_addin_call( reader, si, obj ) )
         {
            std::string returnObject;;

            try {

              ACE_Guard<ACE_Mutex> guard( get_ACE_Mutex() );

              returnObject = QuantLibAddinCpp::qlSpreadCdsHelper ( 
              obj.ObjectId.in(),
              obj.RunningSpread ,
              obj.Tenor.in(),
              static_cast<long>(obj.SettlementDays),
              obj.Calendar.in(),
              obj.Frequency.in(),
              obj.PaymentConvention.in(),
              obj.GenRule.in(),
              obj.DayCounter.in(),
              static_cast<double>(obj.RecoveryRate),
              obj.DiscountingCurve.in(),
              static_cast<bool>(obj.SettleAccrual),
              static_cast<bool>(obj.PayAtDefault),
              static_cast<bool>(obj.Permanent),
              obj.Trigger,
              static_cast<bool>(obj.Overwrite) );
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
       std::string err = "ERROR: read qlSpreadCdsHelper: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlSpreadCdsHelperDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSpreadCdsHelperDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlSpreadCdsHelperDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSpreadCdsHelperDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlSpreadCdsHelperDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSpreadCdsHelperDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlSpreadCdsHelperDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSpreadCdsHelperDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlSpreadCdsHelperDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSpreadCdsHelperDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlSpreadCdsHelperDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSpreadCdsHelperDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlSpreadCdsHelperDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlSpreadCdsHelperDataReaderListenerImpl::on_reading_start\n")));
}

void qlSpreadCdsHelperDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlSpreadCdsHelperDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlSpreadCdsHelperDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, credit::qlSpreadCdsHelper& )
{
  return true;
}

bool qlSpreadCdsHelperDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, credit::qlSpreadCdsHelper&, std::string& )
{
  return true;
}

void qlSpreadCdsHelperDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, credit::qlSpreadCdsHelper&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSpreadCdsHelperDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlSpreadCdsHelperDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSpreadCdsHelperDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlSpreadCdsHelperDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSpreadCdsHelperDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}
}
