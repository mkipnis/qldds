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

#include "btpDataReaderListenerImpl.hpp"

#include <qldds_convert_utils.h>

namespace btp {

void qlBTPDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   btp::qlBTPDataReader_var obj_dr
     = btp::qlBTPDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlBTPDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    btp::qlBTP obj;
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

              returnObject = QuantLibAddinCpp::qlBTP ( 
              obj.ObjectId.in(),
              obj.Description.in(),
              qldds_utils::from_iso_string(obj.MaturityDate.in() ),
              static_cast<double>(obj.Coupon),
              qldds_utils::from_iso_string_to_oh_property(obj.StartDate.in()),
              qldds_utils::from_iso_string_to_oh_property(obj.IssueDate.in()),
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
       std::string err = "ERROR: read qlBTP: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlBTPDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBTPDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlBTPDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBTPDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlBTPDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBTPDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlBTPDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBTPDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlBTPDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBTPDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlBTPDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBTPDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlBTPDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlBTPDataReaderListenerImpl::on_reading_start\n")));
}

void qlBTPDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlBTPDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlBTPDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, btp::qlBTP& )
{
  return true;
}

bool qlBTPDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, btp::qlBTP&, std::string& )
{
  return true;
}

void qlBTPDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, btp::qlBTP&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBTPDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlBTPDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBTPDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlBTPDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBTPDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlBTP2DataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   btp::qlBTP2DataReader_var obj_dr
     = btp::qlBTP2DataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlBTP2DataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    btp::qlBTP2 obj;
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

              returnObject = QuantLibAddinCpp::qlBTP2 ( 
              obj.ObjectId.in(),
              obj.Description.in(),
              qldds_utils::from_iso_string(obj.MaturityDate.in() ),
              static_cast<double>(obj.Coupon),
              static_cast<double>(obj.Redemption),
              qldds_utils::from_iso_string_to_oh_property(obj.StartDate.in()),
              qldds_utils::from_iso_string_to_oh_property(obj.IssueDate.in()),
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
       std::string err = "ERROR: read qlBTP2: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlBTP2DataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBTP2DataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlBTP2DataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBTP2DataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlBTP2DataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBTP2DataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlBTP2DataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBTP2DataReaderListenerImpl::on_subscription_matched\n")));
}

void qlBTP2DataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBTP2DataReaderListenerImpl::on_sample_rejected\n")));
}

void qlBTP2DataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBTP2DataReaderListenerImpl::on_sample_rejected\n")));
}

void qlBTP2DataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlBTP2DataReaderListenerImpl::on_reading_start\n")));
}

void qlBTP2DataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlBTP2DataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlBTP2DataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, btp::qlBTP2& )
{
  return true;
}

bool qlBTP2DataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, btp::qlBTP2&, std::string& )
{
  return true;
}

void qlBTP2DataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, btp::qlBTP2&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBTP2DataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlBTP2DataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBTP2DataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlBTP2DataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBTP2DataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlCCTEUDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   btp::qlCCTEUDataReader_var obj_dr
     = btp::qlCCTEUDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlCCTEUDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    btp::qlCCTEU obj;
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

              returnObject = QuantLibAddinCpp::qlCCTEU ( 
              obj.ObjectId.in(),
              obj.Description.in(),
              qldds_utils::from_iso_string(obj.MaturityDate.in() ),
              static_cast<double>(obj.Spread),
              obj.FwdCurve.in(),
              qldds_utils::from_iso_string_to_oh_property(obj.StartDate.in()),
              qldds_utils::from_iso_string_to_oh_property(obj.IssueDate.in()),
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
       std::string err = "ERROR: read qlCCTEU: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlCCTEUDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCCTEUDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlCCTEUDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCCTEUDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlCCTEUDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCCTEUDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlCCTEUDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCCTEUDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlCCTEUDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCCTEUDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlCCTEUDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCCTEUDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlCCTEUDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlCCTEUDataReaderListenerImpl::on_reading_start\n")));
}

void qlCCTEUDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlCCTEUDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlCCTEUDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, btp::qlCCTEU& )
{
  return true;
}

bool qlCCTEUDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, btp::qlCCTEU&, std::string& )
{
  return true;
}

void qlCCTEUDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, btp::qlCCTEU&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCCTEUDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlCCTEUDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCCTEUDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlCCTEUDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCCTEUDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlRendistatoBasketDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   btp::qlRendistatoBasketDataReader_var obj_dr
     = btp::qlRendistatoBasketDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlRendistatoBasketDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    btp::qlRendistatoBasket obj;
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

              returnObject = QuantLibAddinCpp::qlRendistatoBasket ( 
              obj.ObjectId.in(),
             qldds_utils::vector_cast<std::string,qldds_utils::StringSeq>(obj.BTPs),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.Outstandings),
             qldds_utils::vector_cast<ObjectHandler::property_t,qldds_utils::DoubleSeq>(obj.Prices),
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
       std::string err = "ERROR: read qlRendistatoBasket: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlRendistatoBasketDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRendistatoBasketDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlRendistatoBasketDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRendistatoBasketDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlRendistatoBasketDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRendistatoBasketDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlRendistatoBasketDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRendistatoBasketDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlRendistatoBasketDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRendistatoBasketDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlRendistatoBasketDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRendistatoBasketDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlRendistatoBasketDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlRendistatoBasketDataReaderListenerImpl::on_reading_start\n")));
}

void qlRendistatoBasketDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlRendistatoBasketDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlRendistatoBasketDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, btp::qlRendistatoBasket& )
{
  return true;
}

bool qlRendistatoBasketDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, btp::qlRendistatoBasket&, std::string& )
{
  return true;
}

void qlRendistatoBasketDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, btp::qlRendistatoBasket&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRendistatoBasketDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlRendistatoBasketDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRendistatoBasketDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlRendistatoBasketDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRendistatoBasketDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlRendistatoCalculatorDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   btp::qlRendistatoCalculatorDataReader_var obj_dr
     = btp::qlRendistatoCalculatorDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlRendistatoCalculatorDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    btp::qlRendistatoCalculator obj;
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

              returnObject = QuantLibAddinCpp::qlRendistatoCalculator ( 
              obj.ObjectId.in(),
              obj.RendistatoBasket.in(),
              obj.Euribor.in(),
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
       std::string err = "ERROR: read qlRendistatoCalculator: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlRendistatoCalculatorDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRendistatoCalculatorDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlRendistatoCalculatorDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRendistatoCalculatorDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlRendistatoCalculatorDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRendistatoCalculatorDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlRendistatoCalculatorDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRendistatoCalculatorDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlRendistatoCalculatorDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRendistatoCalculatorDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlRendistatoCalculatorDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRendistatoCalculatorDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlRendistatoCalculatorDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlRendistatoCalculatorDataReaderListenerImpl::on_reading_start\n")));
}

void qlRendistatoCalculatorDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlRendistatoCalculatorDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlRendistatoCalculatorDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, btp::qlRendistatoCalculator& )
{
  return true;
}

bool qlRendistatoCalculatorDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, btp::qlRendistatoCalculator&, std::string& )
{
  return true;
}

void qlRendistatoCalculatorDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, btp::qlRendistatoCalculator&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRendistatoCalculatorDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlRendistatoCalculatorDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRendistatoCalculatorDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlRendistatoCalculatorDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRendistatoCalculatorDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlRendistatoEquivalentSwapLengthQuoteDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   btp::qlRendistatoEquivalentSwapLengthQuoteDataReader_var obj_dr
     = btp::qlRendistatoEquivalentSwapLengthQuoteDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlRendistatoEquivalentSwapLengthQuoteDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    btp::qlRendistatoEquivalentSwapLengthQuote obj;
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

              returnObject = QuantLibAddinCpp::qlRendistatoEquivalentSwapLengthQuote ( 
              obj.ObjectId.in(),
              obj.RendistatoCalculator.in(),
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
       std::string err = "ERROR: read qlRendistatoEquivalentSwapLengthQuote: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlRendistatoEquivalentSwapLengthQuoteDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRendistatoEquivalentSwapLengthQuoteDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlRendistatoEquivalentSwapLengthQuoteDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRendistatoEquivalentSwapLengthQuoteDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlRendistatoEquivalentSwapLengthQuoteDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRendistatoEquivalentSwapLengthQuoteDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlRendistatoEquivalentSwapLengthQuoteDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRendistatoEquivalentSwapLengthQuoteDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlRendistatoEquivalentSwapLengthQuoteDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRendistatoEquivalentSwapLengthQuoteDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlRendistatoEquivalentSwapLengthQuoteDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRendistatoEquivalentSwapLengthQuoteDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlRendistatoEquivalentSwapLengthQuoteDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlRendistatoEquivalentSwapLengthQuoteDataReaderListenerImpl::on_reading_start\n")));
}

void qlRendistatoEquivalentSwapLengthQuoteDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlRendistatoEquivalentSwapLengthQuoteDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlRendistatoEquivalentSwapLengthQuoteDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, btp::qlRendistatoEquivalentSwapLengthQuote& )
{
  return true;
}

bool qlRendistatoEquivalentSwapLengthQuoteDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, btp::qlRendistatoEquivalentSwapLengthQuote&, std::string& )
{
  return true;
}

void qlRendistatoEquivalentSwapLengthQuoteDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, btp::qlRendistatoEquivalentSwapLengthQuote&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRendistatoEquivalentSwapLengthQuoteDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlRendistatoEquivalentSwapLengthQuoteDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRendistatoEquivalentSwapLengthQuoteDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlRendistatoEquivalentSwapLengthQuoteDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRendistatoEquivalentSwapLengthQuoteDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlRendistatoEquivalentSwapSpreadQuoteDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   btp::qlRendistatoEquivalentSwapSpreadQuoteDataReader_var obj_dr
     = btp::qlRendistatoEquivalentSwapSpreadQuoteDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlRendistatoEquivalentSwapSpreadQuoteDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    btp::qlRendistatoEquivalentSwapSpreadQuote obj;
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

              returnObject = QuantLibAddinCpp::qlRendistatoEquivalentSwapSpreadQuote ( 
              obj.ObjectId.in(),
              obj.RendistatoCalculator.in(),
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
       std::string err = "ERROR: read qlRendistatoEquivalentSwapSpreadQuote: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlRendistatoEquivalentSwapSpreadQuoteDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRendistatoEquivalentSwapSpreadQuoteDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlRendistatoEquivalentSwapSpreadQuoteDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRendistatoEquivalentSwapSpreadQuoteDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlRendistatoEquivalentSwapSpreadQuoteDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRendistatoEquivalentSwapSpreadQuoteDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlRendistatoEquivalentSwapSpreadQuoteDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRendistatoEquivalentSwapSpreadQuoteDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlRendistatoEquivalentSwapSpreadQuoteDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRendistatoEquivalentSwapSpreadQuoteDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlRendistatoEquivalentSwapSpreadQuoteDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRendistatoEquivalentSwapSpreadQuoteDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlRendistatoEquivalentSwapSpreadQuoteDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlRendistatoEquivalentSwapSpreadQuoteDataReaderListenerImpl::on_reading_start\n")));
}

void qlRendistatoEquivalentSwapSpreadQuoteDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlRendistatoEquivalentSwapSpreadQuoteDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlRendistatoEquivalentSwapSpreadQuoteDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, btp::qlRendistatoEquivalentSwapSpreadQuote& )
{
  return true;
}

bool qlRendistatoEquivalentSwapSpreadQuoteDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, btp::qlRendistatoEquivalentSwapSpreadQuote&, std::string& )
{
  return true;
}

void qlRendistatoEquivalentSwapSpreadQuoteDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, btp::qlRendistatoEquivalentSwapSpreadQuote&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRendistatoEquivalentSwapSpreadQuoteDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlRendistatoEquivalentSwapSpreadQuoteDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRendistatoEquivalentSwapSpreadQuoteDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlRendistatoEquivalentSwapSpreadQuoteDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRendistatoEquivalentSwapSpreadQuoteDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}
}
