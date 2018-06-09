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
//      qldds/gensrc/stubs/stub.opendds.body

#include "defaulttermstructuresDataReaderListenerImpl.hpp"

#include <qldds_convert_utils.h>
#include <ace/Mutex.h>

namespace defaulttermstructures {

void qlFlatHazardRateDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   defaulttermstructures::qlFlatHazardRateDataReader_var obj_dr
     = defaulttermstructures::qlFlatHazardRateDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlFlatHazardRateDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    defaulttermstructures::qlFlatHazardRate obj;
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

              returnObject = QuantLibAddinCpp::qlFlatHazardRate ( 
              obj.ObjectId.in(),
              static_cast<long>(obj.NDays),
              obj.Calendar.in(),
              obj.Rate ,
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
       std::string err = "ERROR: read qlFlatHazardRate: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlFlatHazardRateDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFlatHazardRateDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlFlatHazardRateDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFlatHazardRateDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlFlatHazardRateDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFlatHazardRateDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlFlatHazardRateDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFlatHazardRateDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlFlatHazardRateDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFlatHazardRateDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlFlatHazardRateDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFlatHazardRateDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlFlatHazardRateDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlFlatHazardRateDataReaderListenerImpl::on_reading_start\n")));
}

void qlFlatHazardRateDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlFlatHazardRateDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlFlatHazardRateDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, defaulttermstructures::qlFlatHazardRate& )
{
  return true;
}

bool qlFlatHazardRateDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, defaulttermstructures::qlFlatHazardRate&, std::string& )
{
  return true;
}

void qlFlatHazardRateDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, defaulttermstructures::qlFlatHazardRate&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFlatHazardRateDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlFlatHazardRateDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFlatHazardRateDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlFlatHazardRateDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFlatHazardRateDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlRelinkableHandleDefaultProbabilityTermStructureDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   defaulttermstructures::qlRelinkableHandleDefaultProbabilityTermStructureDataReader_var obj_dr
     = defaulttermstructures::qlRelinkableHandleDefaultProbabilityTermStructureDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlRelinkableHandleDefaultProbabilityTermStructureDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    defaulttermstructures::qlRelinkableHandleDefaultProbabilityTermStructure obj;
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

              returnObject = QuantLibAddinCpp::qlRelinkableHandleDefaultProbabilityTermStructure ( 
              obj.ObjectId.in(),
              obj.CurrentLink.in(),
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
       std::string err = "ERROR: read qlRelinkableHandleDefaultProbabilityTermStructure: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlRelinkableHandleDefaultProbabilityTermStructureDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRelinkableHandleDefaultProbabilityTermStructureDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlRelinkableHandleDefaultProbabilityTermStructureDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRelinkableHandleDefaultProbabilityTermStructureDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlRelinkableHandleDefaultProbabilityTermStructureDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRelinkableHandleDefaultProbabilityTermStructureDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlRelinkableHandleDefaultProbabilityTermStructureDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRelinkableHandleDefaultProbabilityTermStructureDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlRelinkableHandleDefaultProbabilityTermStructureDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRelinkableHandleDefaultProbabilityTermStructureDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlRelinkableHandleDefaultProbabilityTermStructureDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRelinkableHandleDefaultProbabilityTermStructureDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlRelinkableHandleDefaultProbabilityTermStructureDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlRelinkableHandleDefaultProbabilityTermStructureDataReaderListenerImpl::on_reading_start\n")));
}

void qlRelinkableHandleDefaultProbabilityTermStructureDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlRelinkableHandleDefaultProbabilityTermStructureDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlRelinkableHandleDefaultProbabilityTermStructureDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, defaulttermstructures::qlRelinkableHandleDefaultProbabilityTermStructure& )
{
  return true;
}

bool qlRelinkableHandleDefaultProbabilityTermStructureDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, defaulttermstructures::qlRelinkableHandleDefaultProbabilityTermStructure&, std::string& )
{
  return true;
}

void qlRelinkableHandleDefaultProbabilityTermStructureDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, defaulttermstructures::qlRelinkableHandleDefaultProbabilityTermStructure&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRelinkableHandleDefaultProbabilityTermStructureDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlRelinkableHandleDefaultProbabilityTermStructureDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRelinkableHandleDefaultProbabilityTermStructureDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlRelinkableHandleDefaultProbabilityTermStructureDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRelinkableHandleDefaultProbabilityTermStructureDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}
}
