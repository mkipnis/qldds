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

#include "overnightindexedswapDataReaderListenerImpl.hpp"

#include <qldds_convert_utils.h>
#include <ace/Mutex.h>

namespace overnightindexedswap {

void qlMakeDatedOISDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   overnightindexedswap::qlMakeDatedOISDataReader_var obj_dr
     = overnightindexedswap::qlMakeDatedOISDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlMakeDatedOISDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    overnightindexedswap::qlMakeDatedOIS obj;
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

              returnObject = QuantLibAddinCpp::qlMakeDatedOIS ( 
              obj.ObjectId.in(),
              qldds_utils::from_iso_string_to_oh_property(obj.StartDate.in()),
              qldds_utils::from_iso_string_to_oh_property(obj.EndDate.in()),
              obj.OvernightIndex.in(),
              static_cast<double>(obj.FixedRate),
              obj.FixDayCounter.in(),
              static_cast<double>(obj.Spread),
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
       std::string err = "ERROR: read qlMakeDatedOIS: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlMakeDatedOISDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMakeDatedOISDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlMakeDatedOISDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMakeDatedOISDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlMakeDatedOISDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMakeDatedOISDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlMakeDatedOISDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMakeDatedOISDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlMakeDatedOISDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMakeDatedOISDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlMakeDatedOISDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMakeDatedOISDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlMakeDatedOISDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlMakeDatedOISDataReaderListenerImpl::on_reading_start\n")));
}

void qlMakeDatedOISDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlMakeDatedOISDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlMakeDatedOISDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, overnightindexedswap::qlMakeDatedOIS& )
{
  return true;
}

bool qlMakeDatedOISDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, overnightindexedswap::qlMakeDatedOIS&, std::string& )
{
  return true;
}

void qlMakeDatedOISDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, overnightindexedswap::qlMakeDatedOIS&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMakeDatedOISDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlMakeDatedOISDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMakeDatedOISDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlMakeDatedOISDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMakeDatedOISDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlMakeOISDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   overnightindexedswap::qlMakeOISDataReader_var obj_dr
     = overnightindexedswap::qlMakeOISDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlMakeOISDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    overnightindexedswap::qlMakeOIS obj;
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

              returnObject = QuantLibAddinCpp::qlMakeOIS ( 
              obj.ObjectId.in(),
              static_cast<long>(obj.SettlDays),
              obj.SwapTenor.in(),
              obj.OvernightIndex.in(),
              static_cast<double>(obj.FixedRate),
              obj.ForwardStart.in(),
              obj.FixDayCounter.in(),
              static_cast<double>(obj.Spread),
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
       std::string err = "ERROR: read qlMakeOIS: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlMakeOISDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMakeOISDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlMakeOISDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMakeOISDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlMakeOISDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMakeOISDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlMakeOISDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMakeOISDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlMakeOISDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMakeOISDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlMakeOISDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMakeOISDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlMakeOISDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlMakeOISDataReaderListenerImpl::on_reading_start\n")));
}

void qlMakeOISDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlMakeOISDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlMakeOISDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, overnightindexedswap::qlMakeOIS& )
{
  return true;
}

bool qlMakeOISDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, overnightindexedswap::qlMakeOIS&, std::string& )
{
  return true;
}

void qlMakeOISDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, overnightindexedswap::qlMakeOIS&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMakeOISDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlMakeOISDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMakeOISDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlMakeOISDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMakeOISDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlOvernightIndexedSwapDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   overnightindexedswap::qlOvernightIndexedSwapDataReader_var obj_dr
     = overnightindexedswap::qlOvernightIndexedSwapDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlOvernightIndexedSwapDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    overnightindexedswap::qlOvernightIndexedSwap obj;
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

              returnObject = QuantLibAddinCpp::qlOvernightIndexedSwap ( 
              obj.ObjectId.in(),
              obj.PayerReceiver.in(),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.Nominal),
              obj.Schedule.in(),
              static_cast<double>(obj.FixedRate),
              obj.FixDayCounter.in(),
              obj.OvernightIndex.in(),
              static_cast<double>(obj.Spread),
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
       std::string err = "ERROR: read qlOvernightIndexedSwap: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlOvernightIndexedSwapDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlOvernightIndexedSwapDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlOvernightIndexedSwapDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlOvernightIndexedSwapDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlOvernightIndexedSwapDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlOvernightIndexedSwapDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlOvernightIndexedSwapDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlOvernightIndexedSwapDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlOvernightIndexedSwapDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlOvernightIndexedSwapDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlOvernightIndexedSwapDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlOvernightIndexedSwapDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlOvernightIndexedSwapDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlOvernightIndexedSwapDataReaderListenerImpl::on_reading_start\n")));
}

void qlOvernightIndexedSwapDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlOvernightIndexedSwapDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlOvernightIndexedSwapDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, overnightindexedswap::qlOvernightIndexedSwap& )
{
  return true;
}

bool qlOvernightIndexedSwapDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, overnightindexedswap::qlOvernightIndexedSwap&, std::string& )
{
  return true;
}

void qlOvernightIndexedSwapDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, overnightindexedswap::qlOvernightIndexedSwap&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlOvernightIndexedSwapDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlOvernightIndexedSwapDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlOvernightIndexedSwapDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlOvernightIndexedSwapDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlOvernightIndexedSwapDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlOvernightIndexedSwapFromOISRateHelperDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   overnightindexedswap::qlOvernightIndexedSwapFromOISRateHelperDataReader_var obj_dr
     = overnightindexedswap::qlOvernightIndexedSwapFromOISRateHelperDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlOvernightIndexedSwapFromOISRateHelperDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    overnightindexedswap::qlOvernightIndexedSwapFromOISRateHelper obj;
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

              returnObject = QuantLibAddinCpp::qlOvernightIndexedSwapFromOISRateHelper ( 
              obj.ObjectId.in(),
              obj.OISRateHelper.in(),
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
       std::string err = "ERROR: read qlOvernightIndexedSwapFromOISRateHelper: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlOvernightIndexedSwapFromOISRateHelperDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlOvernightIndexedSwapFromOISRateHelperDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlOvernightIndexedSwapFromOISRateHelperDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlOvernightIndexedSwapFromOISRateHelperDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlOvernightIndexedSwapFromOISRateHelperDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlOvernightIndexedSwapFromOISRateHelperDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlOvernightIndexedSwapFromOISRateHelperDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlOvernightIndexedSwapFromOISRateHelperDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlOvernightIndexedSwapFromOISRateHelperDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlOvernightIndexedSwapFromOISRateHelperDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlOvernightIndexedSwapFromOISRateHelperDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlOvernightIndexedSwapFromOISRateHelperDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlOvernightIndexedSwapFromOISRateHelperDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlOvernightIndexedSwapFromOISRateHelperDataReaderListenerImpl::on_reading_start\n")));
}

void qlOvernightIndexedSwapFromOISRateHelperDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlOvernightIndexedSwapFromOISRateHelperDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlOvernightIndexedSwapFromOISRateHelperDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, overnightindexedswap::qlOvernightIndexedSwapFromOISRateHelper& )
{
  return true;
}

bool qlOvernightIndexedSwapFromOISRateHelperDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, overnightindexedswap::qlOvernightIndexedSwapFromOISRateHelper&, std::string& )
{
  return true;
}

void qlOvernightIndexedSwapFromOISRateHelperDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, overnightindexedswap::qlOvernightIndexedSwapFromOISRateHelper&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlOvernightIndexedSwapFromOISRateHelperDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlOvernightIndexedSwapFromOISRateHelperDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlOvernightIndexedSwapFromOISRateHelperDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlOvernightIndexedSwapFromOISRateHelperDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlOvernightIndexedSwapFromOISRateHelperDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}
}
