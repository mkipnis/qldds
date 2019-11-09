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

#include "rangeaccrualDataReaderListenerImpl.hpp"

#include <qldds_convert_utils.h>
#include <ace/Mutex.h>

namespace rangeaccrual {

void qlRangeAccrualFloatersCouponDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   rangeaccrual::qlRangeAccrualFloatersCouponDataReader_var obj_dr
     = rangeaccrual::qlRangeAccrualFloatersCouponDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlRangeAccrualFloatersCouponDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    rangeaccrual::qlRangeAccrualFloatersCoupon obj;
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

              returnObject = QuantLibAddinCpp::qlRangeAccrualFloatersCoupon ( 
              obj.ObjectId.in(),
              static_cast<double>(obj.Nominal),
              qldds_utils::from_iso_string(obj.PaymentDate.in() ),
              obj.IborIndex.in(),
              qldds_utils::from_iso_string(obj.StartDate.in() ),
              qldds_utils::from_iso_string(obj.EndDate.in() ),
              static_cast<long>(obj.FixingDays),
              obj.DayCountID.in(),
              static_cast<double>(obj.Gearings),
              static_cast<double>(obj.Spreads),
              qldds_utils::from_iso_string(obj.RefPeriodStart.in() ),
              qldds_utils::from_iso_string(obj.RefPeriodEnd.in() ),
              obj.ObserSchedID.in(),
              static_cast<double>(obj.LowerTrigger),
              static_cast<double>(obj.UpperTrigger),
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
       std::string err = "ERROR: read qlRangeAccrualFloatersCoupon: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlRangeAccrualFloatersCouponDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRangeAccrualFloatersCouponDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlRangeAccrualFloatersCouponDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRangeAccrualFloatersCouponDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlRangeAccrualFloatersCouponDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRangeAccrualFloatersCouponDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlRangeAccrualFloatersCouponDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRangeAccrualFloatersCouponDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlRangeAccrualFloatersCouponDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRangeAccrualFloatersCouponDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlRangeAccrualFloatersCouponDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRangeAccrualFloatersCouponDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlRangeAccrualFloatersCouponDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlRangeAccrualFloatersCouponDataReaderListenerImpl::on_reading_start\n")));
}

void qlRangeAccrualFloatersCouponDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlRangeAccrualFloatersCouponDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlRangeAccrualFloatersCouponDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, rangeaccrual::qlRangeAccrualFloatersCoupon& )
{
  return true;
}

bool qlRangeAccrualFloatersCouponDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, rangeaccrual::qlRangeAccrualFloatersCoupon&, std::string& )
{
  return true;
}

void qlRangeAccrualFloatersCouponDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, rangeaccrual::qlRangeAccrualFloatersCoupon&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRangeAccrualFloatersCouponDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlRangeAccrualFloatersCouponDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRangeAccrualFloatersCouponDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlRangeAccrualFloatersCouponDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRangeAccrualFloatersCouponDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlRangeAccrualFloatersCouponFromLegDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   rangeaccrual::qlRangeAccrualFloatersCouponFromLegDataReader_var obj_dr
     = rangeaccrual::qlRangeAccrualFloatersCouponFromLegDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlRangeAccrualFloatersCouponFromLegDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    rangeaccrual::qlRangeAccrualFloatersCouponFromLeg obj;
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

              returnObject = QuantLibAddinCpp::qlRangeAccrualFloatersCouponFromLeg ( 
              obj.ObjectId.in(),
              obj.RangeAccrualLeg.in(),
              static_cast<long>(obj.Position),
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
       std::string err = "ERROR: read qlRangeAccrualFloatersCouponFromLeg: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlRangeAccrualFloatersCouponFromLegDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRangeAccrualFloatersCouponFromLegDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlRangeAccrualFloatersCouponFromLegDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRangeAccrualFloatersCouponFromLegDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlRangeAccrualFloatersCouponFromLegDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRangeAccrualFloatersCouponFromLegDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlRangeAccrualFloatersCouponFromLegDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRangeAccrualFloatersCouponFromLegDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlRangeAccrualFloatersCouponFromLegDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRangeAccrualFloatersCouponFromLegDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlRangeAccrualFloatersCouponFromLegDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRangeAccrualFloatersCouponFromLegDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlRangeAccrualFloatersCouponFromLegDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlRangeAccrualFloatersCouponFromLegDataReaderListenerImpl::on_reading_start\n")));
}

void qlRangeAccrualFloatersCouponFromLegDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlRangeAccrualFloatersCouponFromLegDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlRangeAccrualFloatersCouponFromLegDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, rangeaccrual::qlRangeAccrualFloatersCouponFromLeg& )
{
  return true;
}

bool qlRangeAccrualFloatersCouponFromLegDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, rangeaccrual::qlRangeAccrualFloatersCouponFromLeg&, std::string& )
{
  return true;
}

void qlRangeAccrualFloatersCouponFromLegDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, rangeaccrual::qlRangeAccrualFloatersCouponFromLeg&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRangeAccrualFloatersCouponFromLegDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlRangeAccrualFloatersCouponFromLegDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRangeAccrualFloatersCouponFromLegDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlRangeAccrualFloatersCouponFromLegDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRangeAccrualFloatersCouponFromLegDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlRangeAccrualPricerByBgmDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   rangeaccrual::qlRangeAccrualPricerByBgmDataReader_var obj_dr
     = rangeaccrual::qlRangeAccrualPricerByBgmDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlRangeAccrualPricerByBgmDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    rangeaccrual::qlRangeAccrualPricerByBgm obj;
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

              returnObject = QuantLibAddinCpp::qlRangeAccrualPricerByBgm ( 
              obj.ObjectId.in(),
              static_cast<double>(obj.Correlation),
              obj.SmileOnStartDateID.in(),
              obj.SmileOnEndDateID.in(),
              static_cast<bool>(obj.WithSmile),
              static_cast<bool>(obj.ByCallSpread),
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
       std::string err = "ERROR: read qlRangeAccrualPricerByBgm: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlRangeAccrualPricerByBgmDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRangeAccrualPricerByBgmDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlRangeAccrualPricerByBgmDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRangeAccrualPricerByBgmDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlRangeAccrualPricerByBgmDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRangeAccrualPricerByBgmDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlRangeAccrualPricerByBgmDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRangeAccrualPricerByBgmDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlRangeAccrualPricerByBgmDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRangeAccrualPricerByBgmDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlRangeAccrualPricerByBgmDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRangeAccrualPricerByBgmDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlRangeAccrualPricerByBgmDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlRangeAccrualPricerByBgmDataReaderListenerImpl::on_reading_start\n")));
}

void qlRangeAccrualPricerByBgmDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlRangeAccrualPricerByBgmDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlRangeAccrualPricerByBgmDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, rangeaccrual::qlRangeAccrualPricerByBgm& )
{
  return true;
}

bool qlRangeAccrualPricerByBgmDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, rangeaccrual::qlRangeAccrualPricerByBgm&, std::string& )
{
  return true;
}

void qlRangeAccrualPricerByBgmDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, rangeaccrual::qlRangeAccrualPricerByBgm&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRangeAccrualPricerByBgmDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlRangeAccrualPricerByBgmDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRangeAccrualPricerByBgmDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlRangeAccrualPricerByBgmDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRangeAccrualPricerByBgmDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}
}
