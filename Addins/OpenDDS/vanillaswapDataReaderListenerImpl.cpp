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
//      Users/mkipnis/qldds/gensrc/stubs/stub.opendds.body

#include "vanillaswapDataReaderListenerImpl.hpp"

#include <qldds_convert_utils.h>

namespace vanillaswap {

void qlMakeIMMSwapDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   vanillaswap::qlMakeIMMSwapDataReader_var obj_dr
     = vanillaswap::qlMakeIMMSwapDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlMakeIMMSwapDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    vanillaswap::qlMakeIMMSwap obj;
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

              returnObject = QuantLibAddinCpp::qlMakeIMMSwap ( 
              obj.ObjectId.in(),
              obj.SwapTenor.in(),
              obj.IborIndex.in(),
              static_cast<double>(obj.FixedRate),
              qldds_utils::from_iso_string_to_oh_property(obj.FirstImmDate.in()),
              obj.FixDayCounter.in(),
              static_cast<double>(obj.Spread),
              obj.PricingEngineID.in(),
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
       std::string err = "ERROR: read qlMakeIMMSwap: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlMakeIMMSwapDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMakeIMMSwapDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlMakeIMMSwapDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMakeIMMSwapDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlMakeIMMSwapDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMakeIMMSwapDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlMakeIMMSwapDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMakeIMMSwapDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlMakeIMMSwapDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMakeIMMSwapDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlMakeIMMSwapDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMakeIMMSwapDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlMakeIMMSwapDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlMakeIMMSwapDataReaderListenerImpl::on_reading_start\n")));
}

void qlMakeIMMSwapDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlMakeIMMSwapDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlMakeIMMSwapDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, vanillaswap::qlMakeIMMSwap& )
{
  return true;
}

bool qlMakeIMMSwapDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, vanillaswap::qlMakeIMMSwap&, std::string& )
{
  return true;
}

void qlMakeIMMSwapDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, vanillaswap::qlMakeIMMSwap&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMakeIMMSwapDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlMakeIMMSwapDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMakeIMMSwapDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlMakeIMMSwapDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMakeIMMSwapDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlMakeVanillaSwapDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   vanillaswap::qlMakeVanillaSwapDataReader_var obj_dr
     = vanillaswap::qlMakeVanillaSwapDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlMakeVanillaSwapDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    vanillaswap::qlMakeVanillaSwap obj;
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

              returnObject = QuantLibAddinCpp::qlMakeVanillaSwap ( 
              obj.ObjectId.in(),
              obj.SwapTenor.in(),
              obj.IborIndex.in(),
              static_cast<double>(obj.FixedRate),
              obj.ForwardStart.in(),
              obj.FixDayCounter.in(),
              static_cast<double>(obj.Spread),
              obj.PricingEngineID.in(),
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
       std::string err = "ERROR: read qlMakeVanillaSwap: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlMakeVanillaSwapDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMakeVanillaSwapDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlMakeVanillaSwapDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMakeVanillaSwapDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlMakeVanillaSwapDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMakeVanillaSwapDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlMakeVanillaSwapDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMakeVanillaSwapDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlMakeVanillaSwapDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMakeVanillaSwapDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlMakeVanillaSwapDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMakeVanillaSwapDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlMakeVanillaSwapDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlMakeVanillaSwapDataReaderListenerImpl::on_reading_start\n")));
}

void qlMakeVanillaSwapDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlMakeVanillaSwapDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlMakeVanillaSwapDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, vanillaswap::qlMakeVanillaSwap& )
{
  return true;
}

bool qlMakeVanillaSwapDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, vanillaswap::qlMakeVanillaSwap&, std::string& )
{
  return true;
}

void qlMakeVanillaSwapDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, vanillaswap::qlMakeVanillaSwap&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMakeVanillaSwapDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlMakeVanillaSwapDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMakeVanillaSwapDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlMakeVanillaSwapDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMakeVanillaSwapDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlVanillaSwapDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   vanillaswap::qlVanillaSwapDataReader_var obj_dr
     = vanillaswap::qlVanillaSwapDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlVanillaSwapDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    vanillaswap::qlVanillaSwap obj;
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

              returnObject = QuantLibAddinCpp::qlVanillaSwap ( 
              obj.ObjectId.in(),
              obj.PayerReceiver.in(),
              static_cast<double>(obj.Nominal),
              obj.FixSchedule.in(),
              static_cast<double>(obj.FixedRate),
              obj.FixDayCounter.in(),
              obj.FloatingLegSchedule.in(),
              obj.IborIndex.in(),
              static_cast<double>(obj.Spread),
              obj.FloatingLegDayCounter.in(),
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
       std::string err = "ERROR: read qlVanillaSwap: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlVanillaSwapDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlVanillaSwapDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlVanillaSwapDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlVanillaSwapDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlVanillaSwapDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlVanillaSwapDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlVanillaSwapDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlVanillaSwapDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlVanillaSwapDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlVanillaSwapDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlVanillaSwapDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlVanillaSwapDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlVanillaSwapDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlVanillaSwapDataReaderListenerImpl::on_reading_start\n")));
}

void qlVanillaSwapDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlVanillaSwapDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlVanillaSwapDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, vanillaswap::qlVanillaSwap& )
{
  return true;
}

bool qlVanillaSwapDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, vanillaswap::qlVanillaSwap&, std::string& )
{
  return true;
}

void qlVanillaSwapDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, vanillaswap::qlVanillaSwap&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlVanillaSwapDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlVanillaSwapDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlVanillaSwapDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlVanillaSwapDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlVanillaSwapDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlVanillaSwapFromSwapIndexDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   vanillaswap::qlVanillaSwapFromSwapIndexDataReader_var obj_dr
     = vanillaswap::qlVanillaSwapFromSwapIndexDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlVanillaSwapFromSwapIndexDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    vanillaswap::qlVanillaSwapFromSwapIndex obj;
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

              returnObject = QuantLibAddinCpp::qlVanillaSwapFromSwapIndex ( 
              obj.ObjectId.in(),
              obj.SwapIndex.in(),
              qldds_utils::from_iso_string(obj.FixingDate.in() ),
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
       std::string err = "ERROR: read qlVanillaSwapFromSwapIndex: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlVanillaSwapFromSwapIndexDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlVanillaSwapFromSwapIndexDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlVanillaSwapFromSwapIndexDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlVanillaSwapFromSwapIndexDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlVanillaSwapFromSwapIndexDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlVanillaSwapFromSwapIndexDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlVanillaSwapFromSwapIndexDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlVanillaSwapFromSwapIndexDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlVanillaSwapFromSwapIndexDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlVanillaSwapFromSwapIndexDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlVanillaSwapFromSwapIndexDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlVanillaSwapFromSwapIndexDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlVanillaSwapFromSwapIndexDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlVanillaSwapFromSwapIndexDataReaderListenerImpl::on_reading_start\n")));
}

void qlVanillaSwapFromSwapIndexDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlVanillaSwapFromSwapIndexDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlVanillaSwapFromSwapIndexDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, vanillaswap::qlVanillaSwapFromSwapIndex& )
{
  return true;
}

bool qlVanillaSwapFromSwapIndexDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, vanillaswap::qlVanillaSwapFromSwapIndex&, std::string& )
{
  return true;
}

void qlVanillaSwapFromSwapIndexDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, vanillaswap::qlVanillaSwapFromSwapIndex&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlVanillaSwapFromSwapIndexDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlVanillaSwapFromSwapIndexDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlVanillaSwapFromSwapIndexDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlVanillaSwapFromSwapIndexDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlVanillaSwapFromSwapIndexDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlVanillaSwapFromSwapRateHelperDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   vanillaswap::qlVanillaSwapFromSwapRateHelperDataReader_var obj_dr
     = vanillaswap::qlVanillaSwapFromSwapRateHelperDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlVanillaSwapFromSwapRateHelperDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    vanillaswap::qlVanillaSwapFromSwapRateHelper obj;
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

              returnObject = QuantLibAddinCpp::qlVanillaSwapFromSwapRateHelper ( 
              obj.ObjectId.in(),
              obj.SwapRateHelper.in(),
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
       std::string err = "ERROR: read qlVanillaSwapFromSwapRateHelper: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlVanillaSwapFromSwapRateHelperDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlVanillaSwapFromSwapRateHelperDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlVanillaSwapFromSwapRateHelperDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlVanillaSwapFromSwapRateHelperDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlVanillaSwapFromSwapRateHelperDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlVanillaSwapFromSwapRateHelperDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlVanillaSwapFromSwapRateHelperDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlVanillaSwapFromSwapRateHelperDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlVanillaSwapFromSwapRateHelperDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlVanillaSwapFromSwapRateHelperDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlVanillaSwapFromSwapRateHelperDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlVanillaSwapFromSwapRateHelperDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlVanillaSwapFromSwapRateHelperDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlVanillaSwapFromSwapRateHelperDataReaderListenerImpl::on_reading_start\n")));
}

void qlVanillaSwapFromSwapRateHelperDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlVanillaSwapFromSwapRateHelperDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlVanillaSwapFromSwapRateHelperDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, vanillaswap::qlVanillaSwapFromSwapRateHelper& )
{
  return true;
}

bool qlVanillaSwapFromSwapRateHelperDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, vanillaswap::qlVanillaSwapFromSwapRateHelper&, std::string& )
{
  return true;
}

void qlVanillaSwapFromSwapRateHelperDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, vanillaswap::qlVanillaSwapFromSwapRateHelper&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlVanillaSwapFromSwapRateHelperDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlVanillaSwapFromSwapRateHelperDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlVanillaSwapFromSwapRateHelperDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlVanillaSwapFromSwapRateHelperDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlVanillaSwapFromSwapRateHelperDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}
}
