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
// This file was generated automatically by qldds_gensrc.py.  If you edit this file
// manually then your changes will be lost the next time gensrc runs.

// This source code file was generated from the following stub:
//      dds.no_nt/gensrc/stubs/stub.opendds.body

#include "creditDataReaderListenerImpl.hpp"

#include <qldds_convert_utils.h>
#include <ace/Mutex.h>

namespace credit {

void qlBaseCorrelationTermStructureDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   credit::qlBaseCorrelationTermStructureDataReader_var obj_dr
     = credit::qlBaseCorrelationTermStructureDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlBaseCorrelationTermStructureDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    credit::qlBaseCorrelationTermStructure obj;
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

              returnObject = QuantLibAddinCpp::qlBaseCorrelationTermStructure ( 
              obj.ObjectId.in(),
              obj.InterpolatorType.in(),
              static_cast<long>(obj.SettlementDays),
              obj.Calendar.in(),
              obj.Convention.in(),
             qldds_utils::vector_cast_str<ObjectHandler::property_t,qldds_utils::StringSeq>(obj.Tenors),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.LossLevel),
             qldds_utils::matrix_cast<ObjectHandler::property_t,qldds_utils::Matrix>(obj.Correlations),
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
       std::string err = "ERROR: read qlBaseCorrelationTermStructure: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlBaseCorrelationTermStructureDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBaseCorrelationTermStructureDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlBaseCorrelationTermStructureDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBaseCorrelationTermStructureDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlBaseCorrelationTermStructureDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBaseCorrelationTermStructureDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlBaseCorrelationTermStructureDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBaseCorrelationTermStructureDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlBaseCorrelationTermStructureDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBaseCorrelationTermStructureDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlBaseCorrelationTermStructureDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBaseCorrelationTermStructureDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlBaseCorrelationTermStructureDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlBaseCorrelationTermStructureDataReaderListenerImpl::on_reading_start\n")));
}

void qlBaseCorrelationTermStructureDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlBaseCorrelationTermStructureDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlBaseCorrelationTermStructureDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, credit::qlBaseCorrelationTermStructure& )
{
  return true;
}

bool qlBaseCorrelationTermStructureDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, credit::qlBaseCorrelationTermStructure&, std::string& )
{
  return true;
}

void qlBaseCorrelationTermStructureDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, credit::qlBaseCorrelationTermStructure&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBaseCorrelationTermStructureDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlBaseCorrelationTermStructureDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBaseCorrelationTermStructureDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlBaseCorrelationTermStructureDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBaseCorrelationTermStructureDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlBlackCdsOptionEngineDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   credit::qlBlackCdsOptionEngineDataReader_var obj_dr
     = credit::qlBlackCdsOptionEngineDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlBlackCdsOptionEngineDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    credit::qlBlackCdsOptionEngine obj;
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

              returnObject = QuantLibAddinCpp::qlBlackCdsOptionEngine ( 
              obj.ObjectId.in(),
              obj.DefaultCurve.in(),
              static_cast<double>(obj.RecoveryRate),
              obj.YieldCurve.in(),
              obj.BlackVol ,
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
       std::string err = "ERROR: read qlBlackCdsOptionEngine: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlBlackCdsOptionEngineDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBlackCdsOptionEngineDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlBlackCdsOptionEngineDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBlackCdsOptionEngineDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlBlackCdsOptionEngineDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBlackCdsOptionEngineDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlBlackCdsOptionEngineDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBlackCdsOptionEngineDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlBlackCdsOptionEngineDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBlackCdsOptionEngineDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlBlackCdsOptionEngineDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBlackCdsOptionEngineDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlBlackCdsOptionEngineDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlBlackCdsOptionEngineDataReaderListenerImpl::on_reading_start\n")));
}

void qlBlackCdsOptionEngineDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlBlackCdsOptionEngineDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlBlackCdsOptionEngineDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, credit::qlBlackCdsOptionEngine& )
{
  return true;
}

bool qlBlackCdsOptionEngineDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, credit::qlBlackCdsOptionEngine&, std::string& )
{
  return true;
}

void qlBlackCdsOptionEngineDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, credit::qlBlackCdsOptionEngine&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBlackCdsOptionEngineDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlBlackCdsOptionEngineDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBlackCdsOptionEngineDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlBlackCdsOptionEngineDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBlackCdsOptionEngineDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlDefaultEventDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   credit::qlDefaultEventDataReader_var obj_dr
     = credit::qlDefaultEventDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlDefaultEventDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    credit::qlDefaultEvent obj;
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

              returnObject = QuantLibAddinCpp::qlDefaultEvent ( 
              obj.ObjectId.in(),
              obj.QLEventType.in(),
              qldds_utils::from_iso_string_to_oh_property(obj.EventDate.in()),
              obj.Currency.in(),
              obj.Seniority.in(),
              qldds_utils::from_iso_string_to_oh_property(obj.SettlementDate.in()),
              static_cast<double>(obj.SettledRecovery),
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
       std::string err = "ERROR: read qlDefaultEvent: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlDefaultEventDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDefaultEventDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlDefaultEventDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDefaultEventDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlDefaultEventDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDefaultEventDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlDefaultEventDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDefaultEventDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlDefaultEventDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDefaultEventDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlDefaultEventDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDefaultEventDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlDefaultEventDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlDefaultEventDataReaderListenerImpl::on_reading_start\n")));
}

void qlDefaultEventDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlDefaultEventDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlDefaultEventDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, credit::qlDefaultEvent& )
{
  return true;
}

bool qlDefaultEventDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, credit::qlDefaultEvent&, std::string& )
{
  return true;
}

void qlDefaultEventDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, credit::qlDefaultEvent&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDefaultEventDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlDefaultEventDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDefaultEventDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlDefaultEventDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDefaultEventDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

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
             qldds_utils::vector_cast<ObjectHandler::property_t,qldds_utils::StringSeq>(obj.CurveDates),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.CurveRates),
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

void qlIntegralNtdEngineDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   credit::qlIntegralNtdEngineDataReader_var obj_dr
     = credit::qlIntegralNtdEngineDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlIntegralNtdEngineDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    credit::qlIntegralNtdEngine obj;
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

              returnObject = QuantLibAddinCpp::qlIntegralNtdEngine ( 
              obj.ObjectId.in(),
              obj.IntegrationStep.in(),
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
       std::string err = "ERROR: read qlIntegralNtdEngine: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlIntegralNtdEngineDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIntegralNtdEngineDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlIntegralNtdEngineDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIntegralNtdEngineDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlIntegralNtdEngineDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIntegralNtdEngineDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlIntegralNtdEngineDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIntegralNtdEngineDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlIntegralNtdEngineDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIntegralNtdEngineDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlIntegralNtdEngineDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIntegralNtdEngineDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlIntegralNtdEngineDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlIntegralNtdEngineDataReaderListenerImpl::on_reading_start\n")));
}

void qlIntegralNtdEngineDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlIntegralNtdEngineDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlIntegralNtdEngineDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, credit::qlIntegralNtdEngine& )
{
  return true;
}

bool qlIntegralNtdEngineDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, credit::qlIntegralNtdEngine&, std::string& )
{
  return true;
}

void qlIntegralNtdEngineDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, credit::qlIntegralNtdEngine&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIntegralNtdEngineDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlIntegralNtdEngineDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIntegralNtdEngineDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlIntegralNtdEngineDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIntegralNtdEngineDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlIssuerDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   credit::qlIssuerDataReader_var obj_dr
     = credit::qlIssuerDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlIssuerDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    credit::qlIssuer obj;
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

              returnObject = QuantLibAddinCpp::qlIssuer ( 
              obj.ObjectId.in(),
              obj.DefaultCurves.in(),
              obj.DefaultEvents.in(),
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
       std::string err = "ERROR: read qlIssuer: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlIssuerDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIssuerDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlIssuerDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIssuerDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlIssuerDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIssuerDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlIssuerDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIssuerDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlIssuerDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIssuerDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlIssuerDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIssuerDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlIssuerDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlIssuerDataReaderListenerImpl::on_reading_start\n")));
}

void qlIssuerDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlIssuerDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlIssuerDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, credit::qlIssuer& )
{
  return true;
}

bool qlIssuerDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, credit::qlIssuer&, std::string& )
{
  return true;
}

void qlIssuerDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, credit::qlIssuer&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIssuerDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlIssuerDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIssuerDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlIssuerDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIssuerDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlMidPointCDOEngineDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   credit::qlMidPointCDOEngineDataReader_var obj_dr
     = credit::qlMidPointCDOEngineDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlMidPointCDOEngineDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    credit::qlMidPointCDOEngine obj;
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

              returnObject = QuantLibAddinCpp::qlMidPointCDOEngine ( 
              obj.ObjectId.in(),
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
       std::string err = "ERROR: read qlMidPointCDOEngine: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlMidPointCDOEngineDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMidPointCDOEngineDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlMidPointCDOEngineDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMidPointCDOEngineDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlMidPointCDOEngineDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMidPointCDOEngineDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlMidPointCDOEngineDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMidPointCDOEngineDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlMidPointCDOEngineDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMidPointCDOEngineDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlMidPointCDOEngineDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMidPointCDOEngineDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlMidPointCDOEngineDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlMidPointCDOEngineDataReaderListenerImpl::on_reading_start\n")));
}

void qlMidPointCDOEngineDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlMidPointCDOEngineDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlMidPointCDOEngineDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, credit::qlMidPointCDOEngine& )
{
  return true;
}

bool qlMidPointCDOEngineDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, credit::qlMidPointCDOEngine&, std::string& )
{
  return true;
}

void qlMidPointCDOEngineDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, credit::qlMidPointCDOEngine&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMidPointCDOEngineDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlMidPointCDOEngineDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMidPointCDOEngineDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlMidPointCDOEngineDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMidPointCDOEngineDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
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

void qlNthToDefaultDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   credit::qlNthToDefaultDataReader_var obj_dr
     = credit::qlNthToDefaultDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlNthToDefaultDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    credit::qlNthToDefault obj;
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

              returnObject = QuantLibAddinCpp::qlNthToDefault ( 
              obj.ObjectId.in(),
              obj.Basket.in(),
              static_cast<long>(obj.Order),
              obj.BuyerSeller.in(),
              obj.PremiumSchedule.in(),
              static_cast<double>(obj.Upfront),
              static_cast<double>(obj.Spread),
              obj.DayCounter.in(),
              static_cast<double>(obj.Notional),
              static_cast<bool>(obj.SettlesAccrual),
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
       std::string err = "ERROR: read qlNthToDefault: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlNthToDefaultDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlNthToDefaultDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlNthToDefaultDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlNthToDefaultDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlNthToDefaultDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlNthToDefaultDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlNthToDefaultDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlNthToDefaultDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlNthToDefaultDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlNthToDefaultDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlNthToDefaultDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlNthToDefaultDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlNthToDefaultDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlNthToDefaultDataReaderListenerImpl::on_reading_start\n")));
}

void qlNthToDefaultDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlNthToDefaultDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlNthToDefaultDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, credit::qlNthToDefault& )
{
  return true;
}

bool qlNthToDefaultDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, credit::qlNthToDefault&, std::string& )
{
  return true;
}

void qlNthToDefaultDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, credit::qlNthToDefault&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlNthToDefaultDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlNthToDefaultDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlNthToDefaultDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlNthToDefaultDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlNthToDefaultDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
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
             qldds_utils::vector_cast<std::string,qldds_utils::StringSeq>(obj.RateHelpers),
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

void qlPiecewiseHazardRateCurveDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   credit::qlPiecewiseHazardRateCurveDataReader_var obj_dr
     = credit::qlPiecewiseHazardRateCurveDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlPiecewiseHazardRateCurveDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    credit::qlPiecewiseHazardRateCurve obj;
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

              returnObject = QuantLibAddinCpp::qlPiecewiseHazardRateCurve ( 
              obj.ObjectId.in(),
             qldds_utils::vector_cast<std::string,qldds_utils::StringSeq>(obj.Helpers),
              obj.DayCounter.in(),
              obj.Calendar.in(),
              obj.Interpolation.in(),
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
       std::string err = "ERROR: read qlPiecewiseHazardRateCurve: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlPiecewiseHazardRateCurveDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlPiecewiseHazardRateCurveDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlPiecewiseHazardRateCurveDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlPiecewiseHazardRateCurveDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlPiecewiseHazardRateCurveDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlPiecewiseHazardRateCurveDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlPiecewiseHazardRateCurveDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlPiecewiseHazardRateCurveDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlPiecewiseHazardRateCurveDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlPiecewiseHazardRateCurveDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlPiecewiseHazardRateCurveDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlPiecewiseHazardRateCurveDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlPiecewiseHazardRateCurveDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlPiecewiseHazardRateCurveDataReaderListenerImpl::on_reading_start\n")));
}

void qlPiecewiseHazardRateCurveDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlPiecewiseHazardRateCurveDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlPiecewiseHazardRateCurveDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, credit::qlPiecewiseHazardRateCurve& )
{
  return true;
}

bool qlPiecewiseHazardRateCurveDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, credit::qlPiecewiseHazardRateCurve&, std::string& )
{
  return true;
}

void qlPiecewiseHazardRateCurveDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, credit::qlPiecewiseHazardRateCurve&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlPiecewiseHazardRateCurveDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlPiecewiseHazardRateCurveDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlPiecewiseHazardRateCurveDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlPiecewiseHazardRateCurveDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlPiecewiseHazardRateCurveDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlRiskyFixedBondDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   credit::qlRiskyFixedBondDataReader_var obj_dr
     = credit::qlRiskyFixedBondDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlRiskyFixedBondDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    credit::qlRiskyFixedBond obj;
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

              returnObject = QuantLibAddinCpp::qlRiskyFixedBond ( 
              obj.ObjectId.in(),
              obj.Bondname.in(),
              obj.Currency.in(),
              static_cast<double>(obj.Recovery),
              obj.DefaultCurve.in(),
              obj.Schedule.in(),
              static_cast<double>(obj.Rate),
              obj.DayCounter.in(),
              obj.PaymentConvention.in(),
              static_cast<double>(obj.Notional),
              obj.DiscountingCurve.in(),
              qldds_utils::from_iso_string(obj.PricingDate.in() ),
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
       std::string err = "ERROR: read qlRiskyFixedBond: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlRiskyFixedBondDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRiskyFixedBondDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlRiskyFixedBondDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRiskyFixedBondDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlRiskyFixedBondDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRiskyFixedBondDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlRiskyFixedBondDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRiskyFixedBondDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlRiskyFixedBondDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRiskyFixedBondDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlRiskyFixedBondDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRiskyFixedBondDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlRiskyFixedBondDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlRiskyFixedBondDataReaderListenerImpl::on_reading_start\n")));
}

void qlRiskyFixedBondDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlRiskyFixedBondDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlRiskyFixedBondDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, credit::qlRiskyFixedBond& )
{
  return true;
}

bool qlRiskyFixedBondDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, credit::qlRiskyFixedBond&, std::string& )
{
  return true;
}

void qlRiskyFixedBondDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, credit::qlRiskyFixedBond&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRiskyFixedBondDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlRiskyFixedBondDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRiskyFixedBondDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlRiskyFixedBondDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRiskyFixedBondDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
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

void qlSyntheticCDODataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   credit::qlSyntheticCDODataReader_var obj_dr
     = credit::qlSyntheticCDODataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlSyntheticCDODataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    credit::qlSyntheticCDO obj;
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

              returnObject = QuantLibAddinCpp::qlSyntheticCDO ( 
              obj.ObjectId.in(),
              obj.Basket.in(),
              obj.BuyerSeller.in(),
              obj.PremiumSchedule.in(),
              static_cast<double>(obj.Upfront),
              static_cast<double>(obj.Spread),
              obj.DayCounter.in(),
              obj.PaymentConvention.in(),
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
       std::string err = "ERROR: read qlSyntheticCDO: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlSyntheticCDODataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSyntheticCDODataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlSyntheticCDODataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSyntheticCDODataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlSyntheticCDODataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSyntheticCDODataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlSyntheticCDODataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSyntheticCDODataReaderListenerImpl::on_subscription_matched\n")));
}

void qlSyntheticCDODataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSyntheticCDODataReaderListenerImpl::on_sample_rejected\n")));
}

void qlSyntheticCDODataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSyntheticCDODataReaderListenerImpl::on_sample_rejected\n")));
}

void qlSyntheticCDODataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlSyntheticCDODataReaderListenerImpl::on_reading_start\n")));
}

void qlSyntheticCDODataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlSyntheticCDODataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlSyntheticCDODataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, credit::qlSyntheticCDO& )
{
  return true;
}

bool qlSyntheticCDODataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, credit::qlSyntheticCDO&, std::string& )
{
  return true;
}

void qlSyntheticCDODataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, credit::qlSyntheticCDO&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSyntheticCDODataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlSyntheticCDODataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSyntheticCDODataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlSyntheticCDODataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSyntheticCDODataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}
}
