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

#include "ratehelpersDataReaderListenerImpl.hpp"

#include <qldds_convert_utils.h>
#include <ace/Mutex.h>

namespace ratehelpers {

void qlBondHelperDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   ratehelpers::qlBondHelperDataReader_var obj_dr
     = ratehelpers::qlBondHelperDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlBondHelperDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    ratehelpers::qlBondHelper obj;
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

              returnObject = QuantLibAddinCpp::qlBondHelper ( 
              obj.ObjectId.in(),
              obj.Price ,
              obj.Bond.in(),
              static_cast<bool>(obj.UseCleanPrice),
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
       std::string err = "ERROR: read qlBondHelper: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlBondHelperDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBondHelperDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlBondHelperDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBondHelperDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlBondHelperDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBondHelperDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlBondHelperDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBondHelperDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlBondHelperDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBondHelperDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlBondHelperDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBondHelperDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlBondHelperDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlBondHelperDataReaderListenerImpl::on_reading_start\n")));
}

void qlBondHelperDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlBondHelperDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlBondHelperDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, ratehelpers::qlBondHelper& )
{
  return true;
}

bool qlBondHelperDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, ratehelpers::qlBondHelper&, std::string& )
{
  return true;
}

void qlBondHelperDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, ratehelpers::qlBondHelper&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBondHelperDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlBondHelperDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBondHelperDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlBondHelperDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBondHelperDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlDatedOISRateHelperDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   ratehelpers::qlDatedOISRateHelperDataReader_var obj_dr
     = ratehelpers::qlDatedOISRateHelperDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlDatedOISRateHelperDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    ratehelpers::qlDatedOISRateHelper obj;
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

              returnObject = QuantLibAddinCpp::qlDatedOISRateHelper ( 
              obj.ObjectId.in(),
              qldds_utils::from_iso_string(obj.StartDate.in() ),
              qldds_utils::from_iso_string(obj.EndDate.in() ),
              obj.FixedRate ,
              obj.ONIndex.in(),
              obj.DiscountingCurve.in(),
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
       std::string err = "ERROR: read qlDatedOISRateHelper: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlDatedOISRateHelperDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDatedOISRateHelperDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlDatedOISRateHelperDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDatedOISRateHelperDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlDatedOISRateHelperDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDatedOISRateHelperDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlDatedOISRateHelperDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDatedOISRateHelperDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlDatedOISRateHelperDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDatedOISRateHelperDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlDatedOISRateHelperDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDatedOISRateHelperDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlDatedOISRateHelperDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlDatedOISRateHelperDataReaderListenerImpl::on_reading_start\n")));
}

void qlDatedOISRateHelperDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlDatedOISRateHelperDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlDatedOISRateHelperDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, ratehelpers::qlDatedOISRateHelper& )
{
  return true;
}

bool qlDatedOISRateHelperDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, ratehelpers::qlDatedOISRateHelper&, std::string& )
{
  return true;
}

void qlDatedOISRateHelperDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, ratehelpers::qlDatedOISRateHelper&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDatedOISRateHelperDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlDatedOISRateHelperDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDatedOISRateHelperDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlDatedOISRateHelperDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDatedOISRateHelperDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlDepositRateHelperDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   ratehelpers::qlDepositRateHelperDataReader_var obj_dr
     = ratehelpers::qlDepositRateHelperDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlDepositRateHelperDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    ratehelpers::qlDepositRateHelper obj;
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

              returnObject = QuantLibAddinCpp::qlDepositRateHelper ( 
              obj.ObjectId.in(),
              obj.Rate ,
              obj.IborIndex.in(),
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
       std::string err = "ERROR: read qlDepositRateHelper: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlDepositRateHelperDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDepositRateHelperDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlDepositRateHelperDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDepositRateHelperDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlDepositRateHelperDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDepositRateHelperDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlDepositRateHelperDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDepositRateHelperDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlDepositRateHelperDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDepositRateHelperDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlDepositRateHelperDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDepositRateHelperDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlDepositRateHelperDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlDepositRateHelperDataReaderListenerImpl::on_reading_start\n")));
}

void qlDepositRateHelperDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlDepositRateHelperDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlDepositRateHelperDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, ratehelpers::qlDepositRateHelper& )
{
  return true;
}

bool qlDepositRateHelperDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, ratehelpers::qlDepositRateHelper&, std::string& )
{
  return true;
}

void qlDepositRateHelperDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, ratehelpers::qlDepositRateHelper&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDepositRateHelperDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlDepositRateHelperDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDepositRateHelperDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlDepositRateHelperDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDepositRateHelperDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlDepositRateHelper2DataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   ratehelpers::qlDepositRateHelper2DataReader_var obj_dr
     = ratehelpers::qlDepositRateHelper2DataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlDepositRateHelper2DataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    ratehelpers::qlDepositRateHelper2 obj;
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

              returnObject = QuantLibAddinCpp::qlDepositRateHelper2 ( 
              obj.ObjectId.in(),
              obj.Rate ,
              obj.Tenor.in(),
              static_cast<long>(obj.FixingDays),
              obj.Calendar.in(),
              obj.Convention.in(),
              static_cast<bool>(obj.EndOfMonth),
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
       std::string err = "ERROR: read qlDepositRateHelper2: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlDepositRateHelper2DataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDepositRateHelper2DataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlDepositRateHelper2DataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDepositRateHelper2DataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlDepositRateHelper2DataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDepositRateHelper2DataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlDepositRateHelper2DataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDepositRateHelper2DataReaderListenerImpl::on_subscription_matched\n")));
}

void qlDepositRateHelper2DataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDepositRateHelper2DataReaderListenerImpl::on_sample_rejected\n")));
}

void qlDepositRateHelper2DataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDepositRateHelper2DataReaderListenerImpl::on_sample_rejected\n")));
}

void qlDepositRateHelper2DataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlDepositRateHelper2DataReaderListenerImpl::on_reading_start\n")));
}

void qlDepositRateHelper2DataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlDepositRateHelper2DataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlDepositRateHelper2DataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, ratehelpers::qlDepositRateHelper2& )
{
  return true;
}

bool qlDepositRateHelper2DataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, ratehelpers::qlDepositRateHelper2&, std::string& )
{
  return true;
}

void qlDepositRateHelper2DataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, ratehelpers::qlDepositRateHelper2&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDepositRateHelper2DataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlDepositRateHelper2DataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDepositRateHelper2DataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlDepositRateHelper2DataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDepositRateHelper2DataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlFixedRateBondHelperDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   ratehelpers::qlFixedRateBondHelperDataReader_var obj_dr
     = ratehelpers::qlFixedRateBondHelperDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlFixedRateBondHelperDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    ratehelpers::qlFixedRateBondHelper obj;
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

              returnObject = QuantLibAddinCpp::qlFixedRateBondHelper ( 
              obj.ObjectId.in(),
              obj.Price ,
              static_cast<long>(obj.SettlementDays),
              static_cast<double>(obj.FaceAmount),
              obj.ScheduleID.in(),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.Coupons),
              obj.DayCounter.in(),
              obj.PaymentBDC.in(),
              static_cast<double>(obj.Redemption),
              qldds_utils::from_iso_string_to_oh_property(obj.IssueDate.in()),
              obj.PaymentCalendar.in(),
              obj.ExCouponPeriod.in(),
              obj.ExCouponCalendar.in(),
              obj.ExCouponBDC.in(),
              static_cast<bool>(obj.ExCouponEndOfMonth),
              static_cast<bool>(obj.UseCleanPrice),
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
       std::string err = "ERROR: read qlFixedRateBondHelper: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlFixedRateBondHelperDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFixedRateBondHelperDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlFixedRateBondHelperDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFixedRateBondHelperDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlFixedRateBondHelperDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFixedRateBondHelperDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlFixedRateBondHelperDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFixedRateBondHelperDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlFixedRateBondHelperDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFixedRateBondHelperDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlFixedRateBondHelperDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFixedRateBondHelperDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlFixedRateBondHelperDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlFixedRateBondHelperDataReaderListenerImpl::on_reading_start\n")));
}

void qlFixedRateBondHelperDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlFixedRateBondHelperDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlFixedRateBondHelperDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, ratehelpers::qlFixedRateBondHelper& )
{
  return true;
}

bool qlFixedRateBondHelperDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, ratehelpers::qlFixedRateBondHelper&, std::string& )
{
  return true;
}

void qlFixedRateBondHelperDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, ratehelpers::qlFixedRateBondHelper&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFixedRateBondHelperDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlFixedRateBondHelperDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFixedRateBondHelperDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlFixedRateBondHelperDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFixedRateBondHelperDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlFraRateHelperDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   ratehelpers::qlFraRateHelperDataReader_var obj_dr
     = ratehelpers::qlFraRateHelperDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlFraRateHelperDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    ratehelpers::qlFraRateHelper obj;
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

              returnObject = QuantLibAddinCpp::qlFraRateHelper ( 
              obj.ObjectId.in(),
              obj.Rate ,
              obj.PeriodToStart.in(),
              obj.IborIndex.in(),
              obj.PillarDate.in(),
              qldds_utils::from_iso_string_to_oh_property(obj.CustomPillarDate.in()),
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
       std::string err = "ERROR: read qlFraRateHelper: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlFraRateHelperDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFraRateHelperDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlFraRateHelperDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFraRateHelperDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlFraRateHelperDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFraRateHelperDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlFraRateHelperDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFraRateHelperDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlFraRateHelperDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFraRateHelperDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlFraRateHelperDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFraRateHelperDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlFraRateHelperDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlFraRateHelperDataReaderListenerImpl::on_reading_start\n")));
}

void qlFraRateHelperDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlFraRateHelperDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlFraRateHelperDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, ratehelpers::qlFraRateHelper& )
{
  return true;
}

bool qlFraRateHelperDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, ratehelpers::qlFraRateHelper&, std::string& )
{
  return true;
}

void qlFraRateHelperDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, ratehelpers::qlFraRateHelper&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFraRateHelperDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlFraRateHelperDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFraRateHelperDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlFraRateHelperDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFraRateHelperDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlFraRateHelper2DataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   ratehelpers::qlFraRateHelper2DataReader_var obj_dr
     = ratehelpers::qlFraRateHelper2DataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlFraRateHelper2DataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    ratehelpers::qlFraRateHelper2 obj;
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

              returnObject = QuantLibAddinCpp::qlFraRateHelper2 ( 
              obj.ObjectId.in(),
              obj.Rate ,
              obj.PeriodToStart.in(),
              static_cast<long>(obj.LengthInMonths),
              static_cast<long>(obj.FixingDays),
              obj.Calendar.in(),
              obj.Convention.in(),
              static_cast<bool>(obj.EndOfMonth),
              obj.DayCounter.in(),
              obj.PillarDate.in(),
              qldds_utils::from_iso_string_to_oh_property(obj.CustomPillarDate.in()),
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
       std::string err = "ERROR: read qlFraRateHelper2: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlFraRateHelper2DataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFraRateHelper2DataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlFraRateHelper2DataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFraRateHelper2DataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlFraRateHelper2DataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFraRateHelper2DataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlFraRateHelper2DataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFraRateHelper2DataReaderListenerImpl::on_subscription_matched\n")));
}

void qlFraRateHelper2DataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFraRateHelper2DataReaderListenerImpl::on_sample_rejected\n")));
}

void qlFraRateHelper2DataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFraRateHelper2DataReaderListenerImpl::on_sample_rejected\n")));
}

void qlFraRateHelper2DataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlFraRateHelper2DataReaderListenerImpl::on_reading_start\n")));
}

void qlFraRateHelper2DataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlFraRateHelper2DataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlFraRateHelper2DataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, ratehelpers::qlFraRateHelper2& )
{
  return true;
}

bool qlFraRateHelper2DataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, ratehelpers::qlFraRateHelper2&, std::string& )
{
  return true;
}

void qlFraRateHelper2DataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, ratehelpers::qlFraRateHelper2&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFraRateHelper2DataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlFraRateHelper2DataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFraRateHelper2DataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlFraRateHelper2DataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFraRateHelper2DataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlFuturesRateHelperDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   ratehelpers::qlFuturesRateHelperDataReader_var obj_dr
     = ratehelpers::qlFuturesRateHelperDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlFuturesRateHelperDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    ratehelpers::qlFuturesRateHelper obj;
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

              returnObject = QuantLibAddinCpp::qlFuturesRateHelper ( 
              obj.ObjectId.in(),
              obj.Price ,
              obj.FuturesType.in(),
              qldds_utils::from_iso_string(obj.FuturesDate.in() ),
              obj.IborIndex.in(),
              obj.ConvexityAdjQuote ,
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
       std::string err = "ERROR: read qlFuturesRateHelper: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlFuturesRateHelperDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFuturesRateHelperDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlFuturesRateHelperDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFuturesRateHelperDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlFuturesRateHelperDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFuturesRateHelperDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlFuturesRateHelperDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFuturesRateHelperDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlFuturesRateHelperDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFuturesRateHelperDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlFuturesRateHelperDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFuturesRateHelperDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlFuturesRateHelperDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlFuturesRateHelperDataReaderListenerImpl::on_reading_start\n")));
}

void qlFuturesRateHelperDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlFuturesRateHelperDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlFuturesRateHelperDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, ratehelpers::qlFuturesRateHelper& )
{
  return true;
}

bool qlFuturesRateHelperDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, ratehelpers::qlFuturesRateHelper&, std::string& )
{
  return true;
}

void qlFuturesRateHelperDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, ratehelpers::qlFuturesRateHelper&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFuturesRateHelperDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlFuturesRateHelperDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFuturesRateHelperDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlFuturesRateHelperDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFuturesRateHelperDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlFuturesRateHelper2DataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   ratehelpers::qlFuturesRateHelper2DataReader_var obj_dr
     = ratehelpers::qlFuturesRateHelper2DataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlFuturesRateHelper2DataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    ratehelpers::qlFuturesRateHelper2 obj;
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

              returnObject = QuantLibAddinCpp::qlFuturesRateHelper2 ( 
              obj.ObjectId.in(),
              obj.Price ,
              obj.FuturesType.in(),
              qldds_utils::from_iso_string(obj.FuturesDate.in() ),
              static_cast<long>(obj.LengthInMonths),
              obj.Calendar.in(),
              obj.Convention.in(),
              static_cast<bool>(obj.EndOfMonth),
              obj.DayCounter.in(),
              obj.ConvexityAdjQuote ,
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
       std::string err = "ERROR: read qlFuturesRateHelper2: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlFuturesRateHelper2DataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFuturesRateHelper2DataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlFuturesRateHelper2DataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFuturesRateHelper2DataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlFuturesRateHelper2DataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFuturesRateHelper2DataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlFuturesRateHelper2DataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFuturesRateHelper2DataReaderListenerImpl::on_subscription_matched\n")));
}

void qlFuturesRateHelper2DataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFuturesRateHelper2DataReaderListenerImpl::on_sample_rejected\n")));
}

void qlFuturesRateHelper2DataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFuturesRateHelper2DataReaderListenerImpl::on_sample_rejected\n")));
}

void qlFuturesRateHelper2DataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlFuturesRateHelper2DataReaderListenerImpl::on_reading_start\n")));
}

void qlFuturesRateHelper2DataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlFuturesRateHelper2DataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlFuturesRateHelper2DataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, ratehelpers::qlFuturesRateHelper2& )
{
  return true;
}

bool qlFuturesRateHelper2DataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, ratehelpers::qlFuturesRateHelper2&, std::string& )
{
  return true;
}

void qlFuturesRateHelper2DataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, ratehelpers::qlFuturesRateHelper2&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFuturesRateHelper2DataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlFuturesRateHelper2DataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFuturesRateHelper2DataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlFuturesRateHelper2DataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFuturesRateHelper2DataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlFuturesRateHelper3DataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   ratehelpers::qlFuturesRateHelper3DataReader_var obj_dr
     = ratehelpers::qlFuturesRateHelper3DataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlFuturesRateHelper3DataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    ratehelpers::qlFuturesRateHelper3 obj;
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

              returnObject = QuantLibAddinCpp::qlFuturesRateHelper3 ( 
              obj.ObjectId.in(),
              obj.Price ,
              obj.FuturesType.in(),
              qldds_utils::from_iso_string(obj.FuturesDate.in() ),
              qldds_utils::from_iso_string_to_oh_property(obj.EndDate.in()),
              obj.DayCounter.in(),
              obj.ConvexityAdjQuote ,
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
       std::string err = "ERROR: read qlFuturesRateHelper3: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlFuturesRateHelper3DataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFuturesRateHelper3DataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlFuturesRateHelper3DataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFuturesRateHelper3DataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlFuturesRateHelper3DataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFuturesRateHelper3DataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlFuturesRateHelper3DataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFuturesRateHelper3DataReaderListenerImpl::on_subscription_matched\n")));
}

void qlFuturesRateHelper3DataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFuturesRateHelper3DataReaderListenerImpl::on_sample_rejected\n")));
}

void qlFuturesRateHelper3DataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFuturesRateHelper3DataReaderListenerImpl::on_sample_rejected\n")));
}

void qlFuturesRateHelper3DataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlFuturesRateHelper3DataReaderListenerImpl::on_reading_start\n")));
}

void qlFuturesRateHelper3DataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlFuturesRateHelper3DataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlFuturesRateHelper3DataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, ratehelpers::qlFuturesRateHelper3& )
{
  return true;
}

bool qlFuturesRateHelper3DataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, ratehelpers::qlFuturesRateHelper3&, std::string& )
{
  return true;
}

void qlFuturesRateHelper3DataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, ratehelpers::qlFuturesRateHelper3&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFuturesRateHelper3DataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlFuturesRateHelper3DataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFuturesRateHelper3DataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlFuturesRateHelper3DataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFuturesRateHelper3DataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlFxSwapRateHelperDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   ratehelpers::qlFxSwapRateHelperDataReader_var obj_dr
     = ratehelpers::qlFxSwapRateHelperDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlFxSwapRateHelperDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    ratehelpers::qlFxSwapRateHelper obj;
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

              returnObject = QuantLibAddinCpp::qlFxSwapRateHelper ( 
              obj.ObjectId.in(),
              obj.FwdPoint ,
              obj.SpotFx ,
              obj.Tenor.in(),
              static_cast<long>(obj.FixingDays),
              obj.Calendar.in(),
              obj.Convention.in(),
              static_cast<bool>(obj.EndOfMonth),
              static_cast<bool>(obj.IsFxBaseCurrencyCollateralCurrency),
              obj.CollateralCurve.in(),
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
       std::string err = "ERROR: read qlFxSwapRateHelper: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlFxSwapRateHelperDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFxSwapRateHelperDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlFxSwapRateHelperDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFxSwapRateHelperDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlFxSwapRateHelperDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFxSwapRateHelperDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlFxSwapRateHelperDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFxSwapRateHelperDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlFxSwapRateHelperDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFxSwapRateHelperDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlFxSwapRateHelperDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFxSwapRateHelperDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlFxSwapRateHelperDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlFxSwapRateHelperDataReaderListenerImpl::on_reading_start\n")));
}

void qlFxSwapRateHelperDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlFxSwapRateHelperDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlFxSwapRateHelperDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, ratehelpers::qlFxSwapRateHelper& )
{
  return true;
}

bool qlFxSwapRateHelperDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, ratehelpers::qlFxSwapRateHelper&, std::string& )
{
  return true;
}

void qlFxSwapRateHelperDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, ratehelpers::qlFxSwapRateHelper&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFxSwapRateHelperDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlFxSwapRateHelperDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFxSwapRateHelperDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlFxSwapRateHelperDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFxSwapRateHelperDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlOISRateHelperDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   ratehelpers::qlOISRateHelperDataReader_var obj_dr
     = ratehelpers::qlOISRateHelperDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlOISRateHelperDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    ratehelpers::qlOISRateHelper obj;
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

              returnObject = QuantLibAddinCpp::qlOISRateHelper ( 
              obj.ObjectId.in(),
              static_cast<long>(obj.SettlDays),
              obj.Tenor.in(),
              obj.FixedRate ,
              obj.ONIndex.in(),
              obj.DiscountingCurve.in(),
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
       std::string err = "ERROR: read qlOISRateHelper: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlOISRateHelperDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlOISRateHelperDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlOISRateHelperDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlOISRateHelperDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlOISRateHelperDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlOISRateHelperDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlOISRateHelperDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlOISRateHelperDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlOISRateHelperDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlOISRateHelperDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlOISRateHelperDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlOISRateHelperDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlOISRateHelperDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlOISRateHelperDataReaderListenerImpl::on_reading_start\n")));
}

void qlOISRateHelperDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlOISRateHelperDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlOISRateHelperDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, ratehelpers::qlOISRateHelper& )
{
  return true;
}

bool qlOISRateHelperDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, ratehelpers::qlOISRateHelper&, std::string& )
{
  return true;
}

void qlOISRateHelperDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, ratehelpers::qlOISRateHelper&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlOISRateHelperDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlOISRateHelperDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlOISRateHelperDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlOISRateHelperDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlOISRateHelperDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlRateHelperImpliedQuoteDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   ratehelpers::qlRateHelperImpliedQuoteDataReader_var obj_dr
     = ratehelpers::qlRateHelperImpliedQuoteDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlRateHelperImpliedQuoteDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    ratehelpers::qlRateHelperImpliedQuote obj;
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

              returnObject = QuantLibAddinCpp::qlRateHelperImpliedQuote ( 
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
       std::string err = "ERROR: read qlRateHelperImpliedQuote: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlRateHelperImpliedQuoteDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRateHelperImpliedQuoteDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlRateHelperImpliedQuoteDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRateHelperImpliedQuoteDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlRateHelperImpliedQuoteDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRateHelperImpliedQuoteDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlRateHelperImpliedQuoteDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRateHelperImpliedQuoteDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlRateHelperImpliedQuoteDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRateHelperImpliedQuoteDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlRateHelperImpliedQuoteDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRateHelperImpliedQuoteDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlRateHelperImpliedQuoteDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlRateHelperImpliedQuoteDataReaderListenerImpl::on_reading_start\n")));
}

void qlRateHelperImpliedQuoteDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlRateHelperImpliedQuoteDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlRateHelperImpliedQuoteDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, ratehelpers::qlRateHelperImpliedQuote& )
{
  return true;
}

bool qlRateHelperImpliedQuoteDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, ratehelpers::qlRateHelperImpliedQuote&, double& )
{
  return true;
}

void qlRateHelperImpliedQuoteDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, ratehelpers::qlRateHelperImpliedQuote&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRateHelperImpliedQuoteDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlRateHelperImpliedQuoteDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRateHelperImpliedQuoteDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlRateHelperImpliedQuoteDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRateHelperImpliedQuoteDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlRateHelperQuoteErrorDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   ratehelpers::qlRateHelperQuoteErrorDataReader_var obj_dr
     = ratehelpers::qlRateHelperQuoteErrorDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlRateHelperQuoteErrorDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    ratehelpers::qlRateHelperQuoteError obj;
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

              returnObject = QuantLibAddinCpp::qlRateHelperQuoteError ( 
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
       std::string err = "ERROR: read qlRateHelperQuoteError: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlRateHelperQuoteErrorDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRateHelperQuoteErrorDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlRateHelperQuoteErrorDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRateHelperQuoteErrorDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlRateHelperQuoteErrorDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRateHelperQuoteErrorDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlRateHelperQuoteErrorDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRateHelperQuoteErrorDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlRateHelperQuoteErrorDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRateHelperQuoteErrorDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlRateHelperQuoteErrorDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRateHelperQuoteErrorDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlRateHelperQuoteErrorDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlRateHelperQuoteErrorDataReaderListenerImpl::on_reading_start\n")));
}

void qlRateHelperQuoteErrorDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlRateHelperQuoteErrorDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlRateHelperQuoteErrorDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, ratehelpers::qlRateHelperQuoteError& )
{
  return true;
}

bool qlRateHelperQuoteErrorDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, ratehelpers::qlRateHelperQuoteError&, double& )
{
  return true;
}

void qlRateHelperQuoteErrorDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, ratehelpers::qlRateHelperQuoteError&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRateHelperQuoteErrorDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlRateHelperQuoteErrorDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRateHelperQuoteErrorDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlRateHelperQuoteErrorDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRateHelperQuoteErrorDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlRateHelperQuoteIsValidDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   ratehelpers::qlRateHelperQuoteIsValidDataReader_var obj_dr
     = ratehelpers::qlRateHelperQuoteIsValidDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlRateHelperQuoteIsValidDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    ratehelpers::qlRateHelperQuoteIsValid obj;
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

              returnObject = QuantLibAddinCpp::qlRateHelperQuoteIsValid ( 
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
       std::string err = "ERROR: read qlRateHelperQuoteIsValid: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlRateHelperQuoteIsValidDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRateHelperQuoteIsValidDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlRateHelperQuoteIsValidDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRateHelperQuoteIsValidDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlRateHelperQuoteIsValidDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRateHelperQuoteIsValidDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlRateHelperQuoteIsValidDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRateHelperQuoteIsValidDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlRateHelperQuoteIsValidDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRateHelperQuoteIsValidDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlRateHelperQuoteIsValidDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRateHelperQuoteIsValidDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlRateHelperQuoteIsValidDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlRateHelperQuoteIsValidDataReaderListenerImpl::on_reading_start\n")));
}

void qlRateHelperQuoteIsValidDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlRateHelperQuoteIsValidDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlRateHelperQuoteIsValidDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, ratehelpers::qlRateHelperQuoteIsValid& )
{
  return true;
}

bool qlRateHelperQuoteIsValidDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, ratehelpers::qlRateHelperQuoteIsValid&, double& )
{
  return true;
}

void qlRateHelperQuoteIsValidDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, ratehelpers::qlRateHelperQuoteIsValid&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRateHelperQuoteIsValidDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlRateHelperQuoteIsValidDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRateHelperQuoteIsValidDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlRateHelperQuoteIsValidDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRateHelperQuoteIsValidDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlRateHelperQuoteNameDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   ratehelpers::qlRateHelperQuoteNameDataReader_var obj_dr
     = ratehelpers::qlRateHelperQuoteNameDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlRateHelperQuoteNameDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    ratehelpers::qlRateHelperQuoteName obj;
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

              returnObject = QuantLibAddinCpp::qlRateHelperQuoteName ( 
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
       std::string err = "ERROR: read qlRateHelperQuoteName: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlRateHelperQuoteNameDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRateHelperQuoteNameDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlRateHelperQuoteNameDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRateHelperQuoteNameDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlRateHelperQuoteNameDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRateHelperQuoteNameDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlRateHelperQuoteNameDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRateHelperQuoteNameDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlRateHelperQuoteNameDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRateHelperQuoteNameDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlRateHelperQuoteNameDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRateHelperQuoteNameDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlRateHelperQuoteNameDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlRateHelperQuoteNameDataReaderListenerImpl::on_reading_start\n")));
}

void qlRateHelperQuoteNameDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlRateHelperQuoteNameDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlRateHelperQuoteNameDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, ratehelpers::qlRateHelperQuoteName& )
{
  return true;
}

bool qlRateHelperQuoteNameDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, ratehelpers::qlRateHelperQuoteName&, std::string& )
{
  return true;
}

void qlRateHelperQuoteNameDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, ratehelpers::qlRateHelperQuoteName&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRateHelperQuoteNameDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlRateHelperQuoteNameDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRateHelperQuoteNameDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlRateHelperQuoteNameDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRateHelperQuoteNameDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlRateHelperQuoteValueDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   ratehelpers::qlRateHelperQuoteValueDataReader_var obj_dr
     = ratehelpers::qlRateHelperQuoteValueDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlRateHelperQuoteValueDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    ratehelpers::qlRateHelperQuoteValue obj;
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

              returnObject = QuantLibAddinCpp::qlRateHelperQuoteValue ( 
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
       std::string err = "ERROR: read qlRateHelperQuoteValue: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlRateHelperQuoteValueDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRateHelperQuoteValueDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlRateHelperQuoteValueDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRateHelperQuoteValueDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlRateHelperQuoteValueDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRateHelperQuoteValueDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlRateHelperQuoteValueDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRateHelperQuoteValueDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlRateHelperQuoteValueDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRateHelperQuoteValueDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlRateHelperQuoteValueDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRateHelperQuoteValueDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlRateHelperQuoteValueDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlRateHelperQuoteValueDataReaderListenerImpl::on_reading_start\n")));
}

void qlRateHelperQuoteValueDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlRateHelperQuoteValueDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlRateHelperQuoteValueDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, ratehelpers::qlRateHelperQuoteValue& )
{
  return true;
}

bool qlRateHelperQuoteValueDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, ratehelpers::qlRateHelperQuoteValue&, double& )
{
  return true;
}

void qlRateHelperQuoteValueDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, ratehelpers::qlRateHelperQuoteValue&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRateHelperQuoteValueDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlRateHelperQuoteValueDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRateHelperQuoteValueDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlRateHelperQuoteValueDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRateHelperQuoteValueDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlSwapRateHelperDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   ratehelpers::qlSwapRateHelperDataReader_var obj_dr
     = ratehelpers::qlSwapRateHelperDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlSwapRateHelperDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    ratehelpers::qlSwapRateHelper obj;
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

              returnObject = QuantLibAddinCpp::qlSwapRateHelper ( 
              obj.ObjectId.in(),
              obj.Rate ,
              obj.SwapIndex.in(),
              obj.Spread ,
              obj.ForwardStart.in(),
              obj.DiscountingCurve.in(),
              obj.PillarDate.in(),
              qldds_utils::from_iso_string_to_oh_property(obj.CustomPillarDate.in()),
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
       std::string err = "ERROR: read qlSwapRateHelper: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlSwapRateHelperDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwapRateHelperDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlSwapRateHelperDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwapRateHelperDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlSwapRateHelperDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwapRateHelperDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlSwapRateHelperDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwapRateHelperDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlSwapRateHelperDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwapRateHelperDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlSwapRateHelperDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwapRateHelperDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlSwapRateHelperDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlSwapRateHelperDataReaderListenerImpl::on_reading_start\n")));
}

void qlSwapRateHelperDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlSwapRateHelperDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlSwapRateHelperDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, ratehelpers::qlSwapRateHelper& )
{
  return true;
}

bool qlSwapRateHelperDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, ratehelpers::qlSwapRateHelper&, std::string& )
{
  return true;
}

void qlSwapRateHelperDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, ratehelpers::qlSwapRateHelper&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwapRateHelperDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlSwapRateHelperDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwapRateHelperDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlSwapRateHelperDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwapRateHelperDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlSwapRateHelper2DataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   ratehelpers::qlSwapRateHelper2DataReader_var obj_dr
     = ratehelpers::qlSwapRateHelper2DataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlSwapRateHelper2DataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    ratehelpers::qlSwapRateHelper2 obj;
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

              returnObject = QuantLibAddinCpp::qlSwapRateHelper2 ( 
              obj.ObjectId.in(),
              obj.Rate ,
              static_cast<long>(obj.SettlDays),
              obj.Tenor.in(),
              obj.Calendar.in(),
              obj.FixedLegFrequency.in(),
              obj.FixedLegConvention.in(),
              obj.FixedLegDayCounter.in(),
              obj.IborIndex.in(),
              obj.Spread ,
              obj.ForwardStart.in(),
              obj.DiscountingCurve.in(),
              obj.PillarDate.in(),
              qldds_utils::from_iso_string_to_oh_property(obj.CustomPillarDate.in()),
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
       std::string err = "ERROR: read qlSwapRateHelper2: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlSwapRateHelper2DataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwapRateHelper2DataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlSwapRateHelper2DataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwapRateHelper2DataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlSwapRateHelper2DataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwapRateHelper2DataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlSwapRateHelper2DataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwapRateHelper2DataReaderListenerImpl::on_subscription_matched\n")));
}

void qlSwapRateHelper2DataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwapRateHelper2DataReaderListenerImpl::on_sample_rejected\n")));
}

void qlSwapRateHelper2DataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwapRateHelper2DataReaderListenerImpl::on_sample_rejected\n")));
}

void qlSwapRateHelper2DataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlSwapRateHelper2DataReaderListenerImpl::on_reading_start\n")));
}

void qlSwapRateHelper2DataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlSwapRateHelper2DataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlSwapRateHelper2DataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, ratehelpers::qlSwapRateHelper2& )
{
  return true;
}

bool qlSwapRateHelper2DataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, ratehelpers::qlSwapRateHelper2&, std::string& )
{
  return true;
}

void qlSwapRateHelper2DataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, ratehelpers::qlSwapRateHelper2&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwapRateHelper2DataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlSwapRateHelper2DataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwapRateHelper2DataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlSwapRateHelper2DataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwapRateHelper2DataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}
}
