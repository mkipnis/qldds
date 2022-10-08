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
//      git/qldds/gensrc/stubs/stub.opendds.body

#include "scheduleDataReaderListenerImpl.hpp"

#include <qldds_convert_utils.h>
#include <ace/Mutex.h>

namespace schedule {

void qlScheduleDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   schedule::qlScheduleDataReader_var obj_dr
     = schedule::qlScheduleDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlScheduleDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    schedule::qlSchedule obj;
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

              returnObject = QuantLibAddinCpp::qlSchedule ( 
              obj.ObjectId.in(),
              qldds_utils::from_iso_string_to_oh_property(obj.EffectiveDate.in()),
              qldds_utils::from_iso_string(obj.TerminationDate.in() ),
              obj.Tenor.in(),
              obj.Calendar.in(),
              obj.Convention.in(),
              obj.TermDateConv.in(),
              obj.GenRule.in(),
              static_cast<bool>(obj.EndOfMonth),
              qldds_utils::from_iso_string_to_oh_property(obj.FirstDate.in()),
              qldds_utils::from_iso_string_to_oh_property(obj.NextToLastDate.in()),
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
       std::string err = "ERROR: read qlSchedule: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlScheduleDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlScheduleDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlScheduleDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlScheduleDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlScheduleDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlScheduleDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlScheduleDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlScheduleDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlScheduleDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlScheduleDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlScheduleDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlScheduleDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlScheduleDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlScheduleDataReaderListenerImpl::on_reading_start\n")));
}

void qlScheduleDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlScheduleDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlScheduleDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, schedule::qlSchedule& )
{
  return true;
}

bool qlScheduleDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, schedule::qlSchedule&, std::string& )
{
  return true;
}

void qlScheduleDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, schedule::qlSchedule&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlScheduleDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlScheduleDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlScheduleDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlScheduleDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlScheduleDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlScheduleFromDateVectorDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   schedule::qlScheduleFromDateVectorDataReader_var obj_dr
     = schedule::qlScheduleFromDateVectorDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlScheduleFromDateVectorDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    schedule::qlScheduleFromDateVector obj;
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

              returnObject = QuantLibAddinCpp::qlScheduleFromDateVector ( 
              obj.ObjectId.in(),
             qldds_utils::vector_cast<ObjectHandler::property_t,qldds_utils::StringSeq>(obj.EffectiveDate),
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
       std::string err = "ERROR: read qlScheduleFromDateVector: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlScheduleFromDateVectorDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlScheduleFromDateVectorDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlScheduleFromDateVectorDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlScheduleFromDateVectorDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlScheduleFromDateVectorDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlScheduleFromDateVectorDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlScheduleFromDateVectorDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlScheduleFromDateVectorDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlScheduleFromDateVectorDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlScheduleFromDateVectorDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlScheduleFromDateVectorDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlScheduleFromDateVectorDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlScheduleFromDateVectorDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlScheduleFromDateVectorDataReaderListenerImpl::on_reading_start\n")));
}

void qlScheduleFromDateVectorDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlScheduleFromDateVectorDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlScheduleFromDateVectorDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, schedule::qlScheduleFromDateVector& )
{
  return true;
}

bool qlScheduleFromDateVectorDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, schedule::qlScheduleFromDateVector&, std::string& )
{
  return true;
}

void qlScheduleFromDateVectorDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, schedule::qlScheduleFromDateVector&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlScheduleFromDateVectorDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlScheduleFromDateVectorDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlScheduleFromDateVectorDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlScheduleFromDateVectorDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlScheduleFromDateVectorDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlScheduleFullInterfaceFromDateVectorDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   schedule::qlScheduleFullInterfaceFromDateVectorDataReader_var obj_dr
     = schedule::qlScheduleFullInterfaceFromDateVectorDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlScheduleFullInterfaceFromDateVectorDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    schedule::qlScheduleFullInterfaceFromDateVector obj;
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

              returnObject = QuantLibAddinCpp::qlScheduleFullInterfaceFromDateVector ( 
              obj.ObjectId.in(),
             qldds_utils::vector_cast<ObjectHandler::property_t,qldds_utils::StringSeq>(obj.Dates),
              qldds_utils::vector_cast<bool,qldds_utils::BooleanSeq>(obj.IsRegular),
              obj.Tenor.in(),
              obj.Calendar.in(),
              obj.Convention.in(),
              obj.TermDateConv.in(),
              obj.GenRule.in(),
              static_cast<bool>(obj.EndOfMonth),
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
       std::string err = "ERROR: read qlScheduleFullInterfaceFromDateVector: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlScheduleFullInterfaceFromDateVectorDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlScheduleFullInterfaceFromDateVectorDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlScheduleFullInterfaceFromDateVectorDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlScheduleFullInterfaceFromDateVectorDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlScheduleFullInterfaceFromDateVectorDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlScheduleFullInterfaceFromDateVectorDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlScheduleFullInterfaceFromDateVectorDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlScheduleFullInterfaceFromDateVectorDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlScheduleFullInterfaceFromDateVectorDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlScheduleFullInterfaceFromDateVectorDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlScheduleFullInterfaceFromDateVectorDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlScheduleFullInterfaceFromDateVectorDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlScheduleFullInterfaceFromDateVectorDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlScheduleFullInterfaceFromDateVectorDataReaderListenerImpl::on_reading_start\n")));
}

void qlScheduleFullInterfaceFromDateVectorDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlScheduleFullInterfaceFromDateVectorDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlScheduleFullInterfaceFromDateVectorDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, schedule::qlScheduleFullInterfaceFromDateVector& )
{
  return true;
}

bool qlScheduleFullInterfaceFromDateVectorDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, schedule::qlScheduleFullInterfaceFromDateVector&, std::string& )
{
  return true;
}

void qlScheduleFullInterfaceFromDateVectorDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, schedule::qlScheduleFullInterfaceFromDateVector&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlScheduleFullInterfaceFromDateVectorDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlScheduleFullInterfaceFromDateVectorDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlScheduleFullInterfaceFromDateVectorDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlScheduleFullInterfaceFromDateVectorDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlScheduleFullInterfaceFromDateVectorDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlScheduleTruncatedDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   schedule::qlScheduleTruncatedDataReader_var obj_dr
     = schedule::qlScheduleTruncatedDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlScheduleTruncatedDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    schedule::qlScheduleTruncated obj;
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

              returnObject = QuantLibAddinCpp::qlScheduleTruncated ( 
              obj.ObjectId.in(),
              obj.OriginalSchedule.in(),
              qldds_utils::from_iso_string(obj.TruncationDate.in() ),
              static_cast<bool>(obj.ReturnDatesBefore),
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
       std::string err = "ERROR: read qlScheduleTruncated: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlScheduleTruncatedDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlScheduleTruncatedDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlScheduleTruncatedDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlScheduleTruncatedDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlScheduleTruncatedDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlScheduleTruncatedDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlScheduleTruncatedDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlScheduleTruncatedDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlScheduleTruncatedDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlScheduleTruncatedDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlScheduleTruncatedDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlScheduleTruncatedDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlScheduleTruncatedDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlScheduleTruncatedDataReaderListenerImpl::on_reading_start\n")));
}

void qlScheduleTruncatedDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlScheduleTruncatedDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlScheduleTruncatedDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, schedule::qlScheduleTruncated& )
{
  return true;
}

bool qlScheduleTruncatedDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, schedule::qlScheduleTruncated&, std::string& )
{
  return true;
}

void qlScheduleTruncatedDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, schedule::qlScheduleTruncated&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlScheduleTruncatedDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlScheduleTruncatedDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlScheduleTruncatedDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlScheduleTruncatedDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlScheduleTruncatedDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}
}
