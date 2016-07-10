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

#include "termstructuresDataReaderListenerImpl.hpp"

#include <qldds_convert_utils.h>

namespace termstructures {

void qlDiscountCurveDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   termstructures::qlDiscountCurveDataReader_var obj_dr
     = termstructures::qlDiscountCurveDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlDiscountCurveDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    termstructures::qlDiscountCurve obj;
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

              returnObject = QuantLibAddinCpp::qlDiscountCurve ( 
              obj.ObjectId.in(),
             qldds_utils::vector_cast<ObjectHandler::property_t,qldds_utils::StringSeq>(obj.CurveDates),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.CurveDiscounts),
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
       std::string err = "ERROR: read qlDiscountCurve: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlDiscountCurveDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDiscountCurveDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlDiscountCurveDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDiscountCurveDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlDiscountCurveDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDiscountCurveDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlDiscountCurveDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDiscountCurveDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlDiscountCurveDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDiscountCurveDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlDiscountCurveDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDiscountCurveDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlDiscountCurveDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlDiscountCurveDataReaderListenerImpl::on_reading_start\n")));
}

void qlDiscountCurveDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlDiscountCurveDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlDiscountCurveDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, termstructures::qlDiscountCurve& )
{
  return true;
}

bool qlDiscountCurveDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, termstructures::qlDiscountCurve&, std::string& )
{
  return true;
}

void qlDiscountCurveDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, termstructures::qlDiscountCurve&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDiscountCurveDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlDiscountCurveDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDiscountCurveDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlDiscountCurveDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDiscountCurveDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlFlatForwardDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   termstructures::qlFlatForwardDataReader_var obj_dr
     = termstructures::qlFlatForwardDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlFlatForwardDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    termstructures::qlFlatForward obj;
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

              returnObject = QuantLibAddinCpp::qlFlatForward ( 
              obj.ObjectId.in(),
              static_cast<long>(obj.NDays),
              obj.Calendar.in(),
              obj.Rate ,
              obj.DayCounter.in(),
              obj.Compounding.in(),
              obj.Frequency.in(),
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
       std::string err = "ERROR: read qlFlatForward: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlFlatForwardDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFlatForwardDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlFlatForwardDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFlatForwardDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlFlatForwardDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFlatForwardDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlFlatForwardDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFlatForwardDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlFlatForwardDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFlatForwardDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlFlatForwardDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFlatForwardDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlFlatForwardDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlFlatForwardDataReaderListenerImpl::on_reading_start\n")));
}

void qlFlatForwardDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlFlatForwardDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlFlatForwardDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, termstructures::qlFlatForward& )
{
  return true;
}

bool qlFlatForwardDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, termstructures::qlFlatForward&, std::string& )
{
  return true;
}

void qlFlatForwardDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, termstructures::qlFlatForward&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFlatForwardDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlFlatForwardDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFlatForwardDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlFlatForwardDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFlatForwardDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlForwardCurveDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   termstructures::qlForwardCurveDataReader_var obj_dr
     = termstructures::qlForwardCurveDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlForwardCurveDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    termstructures::qlForwardCurve obj;
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

              returnObject = QuantLibAddinCpp::qlForwardCurve ( 
              obj.ObjectId.in(),
             qldds_utils::vector_cast<ObjectHandler::property_t,qldds_utils::StringSeq>(obj.CurveDates),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.ForwardYields),
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
       std::string err = "ERROR: read qlForwardCurve: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlForwardCurveDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlForwardCurveDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlForwardCurveDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlForwardCurveDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlForwardCurveDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlForwardCurveDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlForwardCurveDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlForwardCurveDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlForwardCurveDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlForwardCurveDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlForwardCurveDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlForwardCurveDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlForwardCurveDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlForwardCurveDataReaderListenerImpl::on_reading_start\n")));
}

void qlForwardCurveDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlForwardCurveDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlForwardCurveDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, termstructures::qlForwardCurve& )
{
  return true;
}

bool qlForwardCurveDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, termstructures::qlForwardCurve&, std::string& )
{
  return true;
}

void qlForwardCurveDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, termstructures::qlForwardCurve&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlForwardCurveDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlForwardCurveDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlForwardCurveDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlForwardCurveDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlForwardCurveDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlForwardSpreadedTermStructureDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   termstructures::qlForwardSpreadedTermStructureDataReader_var obj_dr
     = termstructures::qlForwardSpreadedTermStructureDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlForwardSpreadedTermStructureDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    termstructures::qlForwardSpreadedTermStructure obj;
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

              returnObject = QuantLibAddinCpp::qlForwardSpreadedTermStructure ( 
              obj.ObjectId.in(),
              obj.BaseYieldCurve.in(),
              obj.Spread ,
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
       std::string err = "ERROR: read qlForwardSpreadedTermStructure: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlForwardSpreadedTermStructureDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlForwardSpreadedTermStructureDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlForwardSpreadedTermStructureDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlForwardSpreadedTermStructureDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlForwardSpreadedTermStructureDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlForwardSpreadedTermStructureDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlForwardSpreadedTermStructureDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlForwardSpreadedTermStructureDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlForwardSpreadedTermStructureDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlForwardSpreadedTermStructureDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlForwardSpreadedTermStructureDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlForwardSpreadedTermStructureDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlForwardSpreadedTermStructureDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlForwardSpreadedTermStructureDataReaderListenerImpl::on_reading_start\n")));
}

void qlForwardSpreadedTermStructureDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlForwardSpreadedTermStructureDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlForwardSpreadedTermStructureDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, termstructures::qlForwardSpreadedTermStructure& )
{
  return true;
}

bool qlForwardSpreadedTermStructureDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, termstructures::qlForwardSpreadedTermStructure&, std::string& )
{
  return true;
}

void qlForwardSpreadedTermStructureDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, termstructures::qlForwardSpreadedTermStructure&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlForwardSpreadedTermStructureDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlForwardSpreadedTermStructureDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlForwardSpreadedTermStructureDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlForwardSpreadedTermStructureDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlForwardSpreadedTermStructureDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlImpliedTermStructureDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   termstructures::qlImpliedTermStructureDataReader_var obj_dr
     = termstructures::qlImpliedTermStructureDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlImpliedTermStructureDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    termstructures::qlImpliedTermStructure obj;
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

              returnObject = QuantLibAddinCpp::qlImpliedTermStructure ( 
              obj.ObjectId.in(),
              obj.BaseYieldCurve.in(),
              qldds_utils::from_iso_string(obj.ReferenceDate.in() ),
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
       std::string err = "ERROR: read qlImpliedTermStructure: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlImpliedTermStructureDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlImpliedTermStructureDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlImpliedTermStructureDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlImpliedTermStructureDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlImpliedTermStructureDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlImpliedTermStructureDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlImpliedTermStructureDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlImpliedTermStructureDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlImpliedTermStructureDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlImpliedTermStructureDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlImpliedTermStructureDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlImpliedTermStructureDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlImpliedTermStructureDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlImpliedTermStructureDataReaderListenerImpl::on_reading_start\n")));
}

void qlImpliedTermStructureDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlImpliedTermStructureDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlImpliedTermStructureDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, termstructures::qlImpliedTermStructure& )
{
  return true;
}

bool qlImpliedTermStructureDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, termstructures::qlImpliedTermStructure&, std::string& )
{
  return true;
}

void qlImpliedTermStructureDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, termstructures::qlImpliedTermStructure&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlImpliedTermStructureDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlImpliedTermStructureDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlImpliedTermStructureDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlImpliedTermStructureDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlImpliedTermStructureDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlInterpolatedYieldCurveDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   termstructures::qlInterpolatedYieldCurveDataReader_var obj_dr
     = termstructures::qlInterpolatedYieldCurveDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlInterpolatedYieldCurveDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    termstructures::qlInterpolatedYieldCurve obj;
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

              returnObject = QuantLibAddinCpp::qlInterpolatedYieldCurve ( 
              obj.ObjectId.in(),
             qldds_utils::vector_cast<ObjectHandler::property_t,qldds_utils::StringSeq>(obj.Dates),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.Data),
              obj.Calendar.in(),
              obj.DayCounter.in(),
             qldds_utils::vector_cast<ObjectHandler::property_t,qldds_utils::DoubleSeq>(obj.Jumps),
             qldds_utils::vector_cast<ObjectHandler::property_t,qldds_utils::StringSeq>(obj.JumpDates),
              obj.TraitsID.in(),
              obj.InterpolatorID.in(),
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
       std::string err = "ERROR: read qlInterpolatedYieldCurve: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlInterpolatedYieldCurveDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInterpolatedYieldCurveDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlInterpolatedYieldCurveDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInterpolatedYieldCurveDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlInterpolatedYieldCurveDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInterpolatedYieldCurveDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlInterpolatedYieldCurveDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInterpolatedYieldCurveDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlInterpolatedYieldCurveDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInterpolatedYieldCurveDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlInterpolatedYieldCurveDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInterpolatedYieldCurveDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlInterpolatedYieldCurveDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlInterpolatedYieldCurveDataReaderListenerImpl::on_reading_start\n")));
}

void qlInterpolatedYieldCurveDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlInterpolatedYieldCurveDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlInterpolatedYieldCurveDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, termstructures::qlInterpolatedYieldCurve& )
{
  return true;
}

bool qlInterpolatedYieldCurveDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, termstructures::qlInterpolatedYieldCurve&, std::string& )
{
  return true;
}

void qlInterpolatedYieldCurveDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, termstructures::qlInterpolatedYieldCurve&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInterpolatedYieldCurveDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlInterpolatedYieldCurveDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInterpolatedYieldCurveDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlInterpolatedYieldCurveDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInterpolatedYieldCurveDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlRelinkableHandleYieldTermStructureDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   termstructures::qlRelinkableHandleYieldTermStructureDataReader_var obj_dr
     = termstructures::qlRelinkableHandleYieldTermStructureDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlRelinkableHandleYieldTermStructureDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    termstructures::qlRelinkableHandleYieldTermStructure obj;
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

              returnObject = QuantLibAddinCpp::qlRelinkableHandleYieldTermStructure ( 
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
       std::string err = "ERROR: read qlRelinkableHandleYieldTermStructure: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlRelinkableHandleYieldTermStructureDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRelinkableHandleYieldTermStructureDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlRelinkableHandleYieldTermStructureDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRelinkableHandleYieldTermStructureDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlRelinkableHandleYieldTermStructureDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRelinkableHandleYieldTermStructureDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlRelinkableHandleYieldTermStructureDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRelinkableHandleYieldTermStructureDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlRelinkableHandleYieldTermStructureDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRelinkableHandleYieldTermStructureDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlRelinkableHandleYieldTermStructureDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRelinkableHandleYieldTermStructureDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlRelinkableHandleYieldTermStructureDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlRelinkableHandleYieldTermStructureDataReaderListenerImpl::on_reading_start\n")));
}

void qlRelinkableHandleYieldTermStructureDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlRelinkableHandleYieldTermStructureDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlRelinkableHandleYieldTermStructureDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, termstructures::qlRelinkableHandleYieldTermStructure& )
{
  return true;
}

bool qlRelinkableHandleYieldTermStructureDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, termstructures::qlRelinkableHandleYieldTermStructure&, std::string& )
{
  return true;
}

void qlRelinkableHandleYieldTermStructureDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, termstructures::qlRelinkableHandleYieldTermStructure&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRelinkableHandleYieldTermStructureDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlRelinkableHandleYieldTermStructureDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRelinkableHandleYieldTermStructureDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlRelinkableHandleYieldTermStructureDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRelinkableHandleYieldTermStructureDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlTermStructureMaxDateDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   termstructures::qlTermStructureMaxDateDataReader_var obj_dr
     = termstructures::qlTermStructureMaxDateDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlTermStructureMaxDateDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    termstructures::qlTermStructureMaxDate obj;
    DDS::SampleInfo si ;
    DDS::ReturnCode_t status = obj_dr->take_next_sample(obj, si) ;

    if ( status == DDS::RETCODE_OK )
    {
      if ( si.valid_data == true )
      {
         ++count;

         if ( pre_quantlib_addin_call( reader, si, obj ) )
         {
            long returnObject;;

            try {

              ACE_Guard<ACE_Mutex> guard( get_ACE_Mutex() );

              returnObject = QuantLibAddinCpp::qlTermStructureMaxDate ( 
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
       std::string err = "ERROR: read qlTermStructureMaxDate: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlTermStructureMaxDateDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlTermStructureMaxDateDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlTermStructureMaxDateDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlTermStructureMaxDateDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlTermStructureMaxDateDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlTermStructureMaxDateDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlTermStructureMaxDateDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlTermStructureMaxDateDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlTermStructureMaxDateDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlTermStructureMaxDateDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlTermStructureMaxDateDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlTermStructureMaxDateDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlTermStructureMaxDateDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlTermStructureMaxDateDataReaderListenerImpl::on_reading_start\n")));
}

void qlTermStructureMaxDateDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlTermStructureMaxDateDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlTermStructureMaxDateDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, termstructures::qlTermStructureMaxDate& )
{
  return true;
}

bool qlTermStructureMaxDateDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, termstructures::qlTermStructureMaxDate&, long& )
{
  return true;
}

void qlTermStructureMaxDateDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, termstructures::qlTermStructureMaxDate&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlTermStructureMaxDateDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlTermStructureMaxDateDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlTermStructureMaxDateDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlTermStructureMaxDateDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlTermStructureMaxDateDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlTermStructureReferenceDateDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   termstructures::qlTermStructureReferenceDateDataReader_var obj_dr
     = termstructures::qlTermStructureReferenceDateDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlTermStructureReferenceDateDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    termstructures::qlTermStructureReferenceDate obj;
    DDS::SampleInfo si ;
    DDS::ReturnCode_t status = obj_dr->take_next_sample(obj, si) ;

    if ( status == DDS::RETCODE_OK )
    {
      if ( si.valid_data == true )
      {
         ++count;

         if ( pre_quantlib_addin_call( reader, si, obj ) )
         {
            long returnObject;;

            try {

              ACE_Guard<ACE_Mutex> guard( get_ACE_Mutex() );

              returnObject = QuantLibAddinCpp::qlTermStructureReferenceDate ( 
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
       std::string err = "ERROR: read qlTermStructureReferenceDate: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlTermStructureReferenceDateDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlTermStructureReferenceDateDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlTermStructureReferenceDateDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlTermStructureReferenceDateDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlTermStructureReferenceDateDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlTermStructureReferenceDateDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlTermStructureReferenceDateDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlTermStructureReferenceDateDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlTermStructureReferenceDateDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlTermStructureReferenceDateDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlTermStructureReferenceDateDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlTermStructureReferenceDateDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlTermStructureReferenceDateDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlTermStructureReferenceDateDataReaderListenerImpl::on_reading_start\n")));
}

void qlTermStructureReferenceDateDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlTermStructureReferenceDateDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlTermStructureReferenceDateDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, termstructures::qlTermStructureReferenceDate& )
{
  return true;
}

bool qlTermStructureReferenceDateDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, termstructures::qlTermStructureReferenceDate&, long& )
{
  return true;
}

void qlTermStructureReferenceDateDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, termstructures::qlTermStructureReferenceDate&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlTermStructureReferenceDateDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlTermStructureReferenceDateDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlTermStructureReferenceDateDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlTermStructureReferenceDateDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlTermStructureReferenceDateDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlTermStructureSettlementDaysDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   termstructures::qlTermStructureSettlementDaysDataReader_var obj_dr
     = termstructures::qlTermStructureSettlementDaysDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlTermStructureSettlementDaysDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    termstructures::qlTermStructureSettlementDays obj;
    DDS::SampleInfo si ;
    DDS::ReturnCode_t status = obj_dr->take_next_sample(obj, si) ;

    if ( status == DDS::RETCODE_OK )
    {
      if ( si.valid_data == true )
      {
         ++count;

         if ( pre_quantlib_addin_call( reader, si, obj ) )
         {
            long returnObject;;

            try {

              ACE_Guard<ACE_Mutex> guard( get_ACE_Mutex() );

              returnObject = QuantLibAddinCpp::qlTermStructureSettlementDays ( 
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
       std::string err = "ERROR: read qlTermStructureSettlementDays: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlTermStructureSettlementDaysDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlTermStructureSettlementDaysDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlTermStructureSettlementDaysDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlTermStructureSettlementDaysDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlTermStructureSettlementDaysDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlTermStructureSettlementDaysDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlTermStructureSettlementDaysDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlTermStructureSettlementDaysDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlTermStructureSettlementDaysDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlTermStructureSettlementDaysDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlTermStructureSettlementDaysDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlTermStructureSettlementDaysDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlTermStructureSettlementDaysDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlTermStructureSettlementDaysDataReaderListenerImpl::on_reading_start\n")));
}

void qlTermStructureSettlementDaysDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlTermStructureSettlementDaysDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlTermStructureSettlementDaysDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, termstructures::qlTermStructureSettlementDays& )
{
  return true;
}

bool qlTermStructureSettlementDaysDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, termstructures::qlTermStructureSettlementDays&, long& )
{
  return true;
}

void qlTermStructureSettlementDaysDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, termstructures::qlTermStructureSettlementDays&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlTermStructureSettlementDaysDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlTermStructureSettlementDaysDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlTermStructureSettlementDaysDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlTermStructureSettlementDaysDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlTermStructureSettlementDaysDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlZeroCurveDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   termstructures::qlZeroCurveDataReader_var obj_dr
     = termstructures::qlZeroCurveDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlZeroCurveDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    termstructures::qlZeroCurve obj;
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

              returnObject = QuantLibAddinCpp::qlZeroCurve ( 
              obj.ObjectId.in(),
             qldds_utils::vector_cast<ObjectHandler::property_t,qldds_utils::StringSeq>(obj.CurveDates),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.CurveYields),
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
       std::string err = "ERROR: read qlZeroCurve: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlZeroCurveDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlZeroCurveDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlZeroCurveDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlZeroCurveDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlZeroCurveDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlZeroCurveDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlZeroCurveDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlZeroCurveDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlZeroCurveDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlZeroCurveDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlZeroCurveDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlZeroCurveDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlZeroCurveDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlZeroCurveDataReaderListenerImpl::on_reading_start\n")));
}

void qlZeroCurveDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlZeroCurveDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlZeroCurveDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, termstructures::qlZeroCurve& )
{
  return true;
}

bool qlZeroCurveDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, termstructures::qlZeroCurve&, std::string& )
{
  return true;
}

void qlZeroCurveDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, termstructures::qlZeroCurve&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlZeroCurveDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlZeroCurveDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlZeroCurveDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlZeroCurveDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlZeroCurveDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}
}
