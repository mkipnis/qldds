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

#include "productsDataReaderListenerImpl.hpp"

#include <qldds_convert_utils.h>

namespace products {

void qlMarketModelMultiProductCompositeDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   products::qlMarketModelMultiProductCompositeDataReader_var obj_dr
     = products::qlMarketModelMultiProductCompositeDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlMarketModelMultiProductCompositeDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    products::qlMarketModelMultiProductComposite obj;
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

              returnObject = QuantLibAddinCpp::qlMarketModelMultiProductComposite ( 
              obj.ObjectId.in(),
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
       std::string err = "ERROR: read qlMarketModelMultiProductComposite: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlMarketModelMultiProductCompositeDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMarketModelMultiProductCompositeDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlMarketModelMultiProductCompositeDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMarketModelMultiProductCompositeDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlMarketModelMultiProductCompositeDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMarketModelMultiProductCompositeDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlMarketModelMultiProductCompositeDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMarketModelMultiProductCompositeDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlMarketModelMultiProductCompositeDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMarketModelMultiProductCompositeDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlMarketModelMultiProductCompositeDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMarketModelMultiProductCompositeDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlMarketModelMultiProductCompositeDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlMarketModelMultiProductCompositeDataReaderListenerImpl::on_reading_start\n")));
}

void qlMarketModelMultiProductCompositeDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlMarketModelMultiProductCompositeDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlMarketModelMultiProductCompositeDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, products::qlMarketModelMultiProductComposite& )
{
  return true;
}

bool qlMarketModelMultiProductCompositeDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, products::qlMarketModelMultiProductComposite&, std::string& )
{
  return true;
}

void qlMarketModelMultiProductCompositeDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, products::qlMarketModelMultiProductComposite&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMarketModelMultiProductCompositeDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlMarketModelMultiProductCompositeDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMarketModelMultiProductCompositeDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlMarketModelMultiProductCompositeDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMarketModelMultiProductCompositeDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlMarketModelMultiStepRatchetDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   products::qlMarketModelMultiStepRatchetDataReader_var obj_dr
     = products::qlMarketModelMultiStepRatchetDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlMarketModelMultiStepRatchetDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    products::qlMarketModelMultiStepRatchet obj;
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

              returnObject = QuantLibAddinCpp::qlMarketModelMultiStepRatchet ( 
              obj.ObjectId.in(),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.RateTimes),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.Accruals),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.PaymentTimes),
              static_cast<double>(obj.GearingOfFloor),
              static_cast<double>(obj.GearingOfFixing),
              static_cast<double>(obj.SpreadOfFloor),
              static_cast<double>(obj.SpreadOfFixing),
              static_cast<double>(obj.InitialFloor),
              static_cast<bool>(obj.Payer),
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
       std::string err = "ERROR: read qlMarketModelMultiStepRatchet: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlMarketModelMultiStepRatchetDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMarketModelMultiStepRatchetDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlMarketModelMultiStepRatchetDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMarketModelMultiStepRatchetDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlMarketModelMultiStepRatchetDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMarketModelMultiStepRatchetDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlMarketModelMultiStepRatchetDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMarketModelMultiStepRatchetDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlMarketModelMultiStepRatchetDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMarketModelMultiStepRatchetDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlMarketModelMultiStepRatchetDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMarketModelMultiStepRatchetDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlMarketModelMultiStepRatchetDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlMarketModelMultiStepRatchetDataReaderListenerImpl::on_reading_start\n")));
}

void qlMarketModelMultiStepRatchetDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlMarketModelMultiStepRatchetDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlMarketModelMultiStepRatchetDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, products::qlMarketModelMultiStepRatchet& )
{
  return true;
}

bool qlMarketModelMultiStepRatchetDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, products::qlMarketModelMultiStepRatchet&, std::string& )
{
  return true;
}

void qlMarketModelMultiStepRatchetDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, products::qlMarketModelMultiStepRatchet&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMarketModelMultiStepRatchetDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlMarketModelMultiStepRatchetDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMarketModelMultiStepRatchetDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlMarketModelMultiStepRatchetDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMarketModelMultiStepRatchetDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlMarketModelOneStepForwardsDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   products::qlMarketModelOneStepForwardsDataReader_var obj_dr
     = products::qlMarketModelOneStepForwardsDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlMarketModelOneStepForwardsDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    products::qlMarketModelOneStepForwards obj;
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

              returnObject = QuantLibAddinCpp::qlMarketModelOneStepForwards ( 
              obj.ObjectId.in(),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.RateTimes),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.Accruals),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.PaymentTimes),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.Strikes),
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
       std::string err = "ERROR: read qlMarketModelOneStepForwards: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlMarketModelOneStepForwardsDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMarketModelOneStepForwardsDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlMarketModelOneStepForwardsDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMarketModelOneStepForwardsDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlMarketModelOneStepForwardsDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMarketModelOneStepForwardsDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlMarketModelOneStepForwardsDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMarketModelOneStepForwardsDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlMarketModelOneStepForwardsDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMarketModelOneStepForwardsDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlMarketModelOneStepForwardsDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMarketModelOneStepForwardsDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlMarketModelOneStepForwardsDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlMarketModelOneStepForwardsDataReaderListenerImpl::on_reading_start\n")));
}

void qlMarketModelOneStepForwardsDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlMarketModelOneStepForwardsDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlMarketModelOneStepForwardsDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, products::qlMarketModelOneStepForwards& )
{
  return true;
}

bool qlMarketModelOneStepForwardsDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, products::qlMarketModelOneStepForwards&, std::string& )
{
  return true;
}

void qlMarketModelOneStepForwardsDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, products::qlMarketModelOneStepForwards&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMarketModelOneStepForwardsDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlMarketModelOneStepForwardsDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMarketModelOneStepForwardsDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlMarketModelOneStepForwardsDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMarketModelOneStepForwardsDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlMarketModelOneStepOptionletsDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   products::qlMarketModelOneStepOptionletsDataReader_var obj_dr
     = products::qlMarketModelOneStepOptionletsDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlMarketModelOneStepOptionletsDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    products::qlMarketModelOneStepOptionlets obj;
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

              returnObject = QuantLibAddinCpp::qlMarketModelOneStepOptionlets ( 
              obj.ObjectId.in(),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.RateTimes),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.Accruals),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.PaymentTimes),
             qldds_utils::vector_cast<std::string,qldds_utils::StringSeq>(obj.Payoffs),
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
       std::string err = "ERROR: read qlMarketModelOneStepOptionlets: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlMarketModelOneStepOptionletsDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMarketModelOneStepOptionletsDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlMarketModelOneStepOptionletsDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMarketModelOneStepOptionletsDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlMarketModelOneStepOptionletsDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMarketModelOneStepOptionletsDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlMarketModelOneStepOptionletsDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMarketModelOneStepOptionletsDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlMarketModelOneStepOptionletsDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMarketModelOneStepOptionletsDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlMarketModelOneStepOptionletsDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMarketModelOneStepOptionletsDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlMarketModelOneStepOptionletsDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlMarketModelOneStepOptionletsDataReaderListenerImpl::on_reading_start\n")));
}

void qlMarketModelOneStepOptionletsDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlMarketModelOneStepOptionletsDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlMarketModelOneStepOptionletsDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, products::qlMarketModelOneStepOptionlets& )
{
  return true;
}

bool qlMarketModelOneStepOptionletsDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, products::qlMarketModelOneStepOptionlets&, std::string& )
{
  return true;
}

void qlMarketModelOneStepOptionletsDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, products::qlMarketModelOneStepOptionlets&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMarketModelOneStepOptionletsDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlMarketModelOneStepOptionletsDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMarketModelOneStepOptionletsDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlMarketModelOneStepOptionletsDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMarketModelOneStepOptionletsDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}
}
