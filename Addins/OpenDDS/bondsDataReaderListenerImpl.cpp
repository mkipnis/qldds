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

#include "bondsDataReaderListenerImpl.hpp"

#include <qldds_convert_utils.h>

namespace bonds {

void qlBondDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   bonds::qlBondDataReader_var obj_dr
     = bonds::qlBondDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlBondDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    bonds::qlBond obj;
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

              returnObject = QuantLibAddinCpp::qlBond ( 
              obj.ObjectId.in(),
              obj.Description.in(),
              obj.Currency.in(),
              static_cast<long>(obj.SettlementDays),
              obj.Calendar.in(),
              static_cast<double>(obj.FaceAmount),
              qldds_utils::from_iso_string_to_oh_property(obj.MaturityDate.in()),
              qldds_utils::from_iso_string_to_oh_property(obj.IssueDate.in()),
              obj.LegID.in(),
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
       std::string err = "ERROR: read qlBond: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlBondDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBondDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlBondDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBondDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlBondDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBondDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlBondDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBondDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlBondDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBondDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlBondDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBondDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlBondDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlBondDataReaderListenerImpl::on_reading_start\n")));
}

void qlBondDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlBondDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlBondDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, bonds::qlBond& )
{
  return true;
}

bool qlBondDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, bonds::qlBond&, std::string& )
{
  return true;
}

void qlBondDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, bonds::qlBond&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBondDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlBondDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBondDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlBondDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBondDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlCmsRateBondDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   bonds::qlCmsRateBondDataReader_var obj_dr
     = bonds::qlCmsRateBondDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlCmsRateBondDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    bonds::qlCmsRateBond obj;
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

              returnObject = QuantLibAddinCpp::qlCmsRateBond ( 
              obj.ObjectId.in(),
              obj.Description.in(),
              obj.Currency.in(),
              static_cast<long>(obj.SettlementDays),
              obj.PaymentBDC.in(),
              static_cast<double>(obj.FaceAmount),
              obj.ScheduleID.in(),
              static_cast<long>(obj.FixingDays),
              static_cast<bool>(obj.IsInArrears),
              obj.DayCounter.in(),
             qldds_utils::vector_cast<double,CORBA::DoubleSeq>(obj.Floors),
             qldds_utils::vector_cast<double,CORBA::DoubleSeq>(obj.Gearings),
              obj.SwapIndex.in(),
             qldds_utils::vector_cast<double,CORBA::DoubleSeq>(obj.Spreads),
             qldds_utils::vector_cast<double,CORBA::DoubleSeq>(obj.Caps),
              static_cast<double>(obj.Redemption),
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
       std::string err = "ERROR: read qlCmsRateBond: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlCmsRateBondDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCmsRateBondDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlCmsRateBondDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCmsRateBondDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlCmsRateBondDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCmsRateBondDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlCmsRateBondDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCmsRateBondDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlCmsRateBondDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCmsRateBondDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlCmsRateBondDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCmsRateBondDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlCmsRateBondDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlCmsRateBondDataReaderListenerImpl::on_reading_start\n")));
}

void qlCmsRateBondDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlCmsRateBondDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlCmsRateBondDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, bonds::qlCmsRateBond& )
{
  return true;
}

bool qlCmsRateBondDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, bonds::qlCmsRateBond&, std::string& )
{
  return true;
}

void qlCmsRateBondDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, bonds::qlCmsRateBond&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCmsRateBondDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlCmsRateBondDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCmsRateBondDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlCmsRateBondDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCmsRateBondDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlFixedRateBondDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   bonds::qlFixedRateBondDataReader_var obj_dr
     = bonds::qlFixedRateBondDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlFixedRateBondDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    bonds::qlFixedRateBond obj;
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

              returnObject = QuantLibAddinCpp::qlFixedRateBond ( 
              obj.ObjectId.in(),
              obj.Description.in(),
              obj.Currency.in(),
              static_cast<long>(obj.SettlementDays),
              static_cast<double>(obj.FaceAmount),
              obj.ScheduleID.in(),
             qldds_utils::vector_cast<double,CORBA::DoubleSeq>(obj.Coupons),
              obj.DayCounter.in(),
              obj.PaymentBDC.in(),
              static_cast<double>(obj.Redemption),
              qldds_utils::from_iso_string_to_oh_property(obj.IssueDate.in()),
              obj.PaymentCalendar.in(),
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
       std::string err = "ERROR: read qlFixedRateBond: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlFixedRateBondDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFixedRateBondDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlFixedRateBondDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFixedRateBondDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlFixedRateBondDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFixedRateBondDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlFixedRateBondDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFixedRateBondDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlFixedRateBondDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFixedRateBondDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlFixedRateBondDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFixedRateBondDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlFixedRateBondDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlFixedRateBondDataReaderListenerImpl::on_reading_start\n")));
}

void qlFixedRateBondDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlFixedRateBondDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlFixedRateBondDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, bonds::qlFixedRateBond& )
{
  return true;
}

bool qlFixedRateBondDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, bonds::qlFixedRateBond&, std::string& )
{
  return true;
}

void qlFixedRateBondDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, bonds::qlFixedRateBond&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFixedRateBondDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlFixedRateBondDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFixedRateBondDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlFixedRateBondDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFixedRateBondDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlFixedRateBond2DataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   bonds::qlFixedRateBond2DataReader_var obj_dr
     = bonds::qlFixedRateBond2DataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlFixedRateBond2DataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    bonds::qlFixedRateBond2 obj;
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

              returnObject = QuantLibAddinCpp::qlFixedRateBond2 ( 
              obj.ObjectId.in(),
              obj.Description.in(),
              obj.Currency.in(),
              static_cast<long>(obj.SettlementDays),
              static_cast<double>(obj.FaceAmount),
              obj.ScheduleID.in(),
             qldds_utils::vector_cast<std::string,CORBA::StringSeq>(obj.Coupons),
              obj.PaymentBDC.in(),
              static_cast<double>(obj.Redemption),
              qldds_utils::from_iso_string_to_oh_property(obj.IssueDate.in()),
              obj.PaymentCalendar.in(),
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
       std::string err = "ERROR: read qlFixedRateBond2: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlFixedRateBond2DataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFixedRateBond2DataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlFixedRateBond2DataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFixedRateBond2DataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlFixedRateBond2DataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFixedRateBond2DataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlFixedRateBond2DataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFixedRateBond2DataReaderListenerImpl::on_subscription_matched\n")));
}

void qlFixedRateBond2DataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFixedRateBond2DataReaderListenerImpl::on_sample_rejected\n")));
}

void qlFixedRateBond2DataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFixedRateBond2DataReaderListenerImpl::on_sample_rejected\n")));
}

void qlFixedRateBond2DataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlFixedRateBond2DataReaderListenerImpl::on_reading_start\n")));
}

void qlFixedRateBond2DataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlFixedRateBond2DataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlFixedRateBond2DataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, bonds::qlFixedRateBond2& )
{
  return true;
}

bool qlFixedRateBond2DataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, bonds::qlFixedRateBond2&, std::string& )
{
  return true;
}

void qlFixedRateBond2DataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, bonds::qlFixedRateBond2&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFixedRateBond2DataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlFixedRateBond2DataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFixedRateBond2DataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlFixedRateBond2DataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFixedRateBond2DataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlFloatingRateBondDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   bonds::qlFloatingRateBondDataReader_var obj_dr
     = bonds::qlFloatingRateBondDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlFloatingRateBondDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    bonds::qlFloatingRateBond obj;
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

              returnObject = QuantLibAddinCpp::qlFloatingRateBond ( 
              obj.ObjectId.in(),
              obj.Description.in(),
              obj.Currency.in(),
              static_cast<long>(obj.SettlementDays),
              obj.PaymentBDC.in(),
              static_cast<double>(obj.FaceAmount),
              obj.ScheduleID.in(),
              static_cast<long>(obj.FixingDays),
              static_cast<bool>(obj.IsInArrears),
              obj.DayCounter.in(),
             qldds_utils::vector_cast<double,CORBA::DoubleSeq>(obj.Floors),
             qldds_utils::vector_cast<double,CORBA::DoubleSeq>(obj.Gearings),
              obj.IborIndex.in(),
             qldds_utils::vector_cast<double,CORBA::DoubleSeq>(obj.Spreads),
             qldds_utils::vector_cast<double,CORBA::DoubleSeq>(obj.Caps),
              static_cast<double>(obj.Redemption),
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
       std::string err = "ERROR: read qlFloatingRateBond: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlFloatingRateBondDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFloatingRateBondDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlFloatingRateBondDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFloatingRateBondDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlFloatingRateBondDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFloatingRateBondDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlFloatingRateBondDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFloatingRateBondDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlFloatingRateBondDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFloatingRateBondDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlFloatingRateBondDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFloatingRateBondDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlFloatingRateBondDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlFloatingRateBondDataReaderListenerImpl::on_reading_start\n")));
}

void qlFloatingRateBondDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlFloatingRateBondDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlFloatingRateBondDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, bonds::qlFloatingRateBond& )
{
  return true;
}

bool qlFloatingRateBondDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, bonds::qlFloatingRateBond&, std::string& )
{
  return true;
}

void qlFloatingRateBondDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, bonds::qlFloatingRateBond&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFloatingRateBondDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlFloatingRateBondDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFloatingRateBondDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlFloatingRateBondDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFloatingRateBondDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlZeroCouponBondDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   bonds::qlZeroCouponBondDataReader_var obj_dr
     = bonds::qlZeroCouponBondDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlZeroCouponBondDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    bonds::qlZeroCouponBond obj;
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

              returnObject = QuantLibAddinCpp::qlZeroCouponBond ( 
              obj.ObjectId.in(),
              obj.Description.in(),
              obj.Currency.in(),
              static_cast<long>(obj.SettlementDays),
              obj.Calendar.in(),
              static_cast<double>(obj.FaceAmount),
              qldds_utils::from_iso_string(obj.Maturity.in() ),
              obj.PaymentBDC.in(),
              static_cast<double>(obj.Redemption),
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
       std::string err = "ERROR: read qlZeroCouponBond: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlZeroCouponBondDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlZeroCouponBondDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlZeroCouponBondDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlZeroCouponBondDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlZeroCouponBondDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlZeroCouponBondDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlZeroCouponBondDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlZeroCouponBondDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlZeroCouponBondDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlZeroCouponBondDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlZeroCouponBondDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlZeroCouponBondDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlZeroCouponBondDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlZeroCouponBondDataReaderListenerImpl::on_reading_start\n")));
}

void qlZeroCouponBondDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlZeroCouponBondDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlZeroCouponBondDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, bonds::qlZeroCouponBond& )
{
  return true;
}

bool qlZeroCouponBondDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, bonds::qlZeroCouponBond&, std::string& )
{
  return true;
}

void qlZeroCouponBondDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, bonds::qlZeroCouponBond&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlZeroCouponBondDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlZeroCouponBondDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlZeroCouponBondDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlZeroCouponBondDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlZeroCouponBondDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}
}
