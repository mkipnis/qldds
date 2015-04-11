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

#include "abcdDataReaderListenerImpl.hpp"

#include <qldds_convert_utils.h>

namespace abcd {

void qlAbcdCalibrationDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   abcd::qlAbcdCalibrationDataReader_var obj_dr
     = abcd::qlAbcdCalibrationDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlAbcdCalibrationDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    abcd::qlAbcdCalibration obj;
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

              returnObject = QuantLibAddinCpp::qlAbcdCalibration ( 
              obj.ObjectId.in(),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.Times),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.BlackVols),
              static_cast<double>(obj.A),
              static_cast<double>(obj.B),
              static_cast<double>(obj.C),
              static_cast<double>(obj.D),
              static_cast<bool>(obj.AIsFixed),
              static_cast<bool>(obj.BIsFixed),
              static_cast<bool>(obj.CIsFixed),
              static_cast<bool>(obj.DIsFixed),
              static_cast<bool>(obj.VegaWeighted),
              obj.EndCriteria.in(),
              obj.Method.in(),
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
       std::string err = "ERROR: read qlAbcdCalibration: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlAbcdCalibrationDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlAbcdCalibrationDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlAbcdCalibrationDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlAbcdCalibrationDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlAbcdCalibrationDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlAbcdCalibrationDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlAbcdCalibrationDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlAbcdCalibrationDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlAbcdCalibrationDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlAbcdCalibrationDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlAbcdCalibrationDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlAbcdCalibrationDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlAbcdCalibrationDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlAbcdCalibrationDataReaderListenerImpl::on_reading_start\n")));
}

void qlAbcdCalibrationDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlAbcdCalibrationDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlAbcdCalibrationDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, abcd::qlAbcdCalibration& )
{
  return true;
}

bool qlAbcdCalibrationDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, abcd::qlAbcdCalibration&, std::string& )
{
  return true;
}

void qlAbcdCalibrationDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, abcd::qlAbcdCalibration&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlAbcdCalibrationDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlAbcdCalibrationDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlAbcdCalibrationDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlAbcdCalibrationDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlAbcdCalibrationDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlAbcdFunctionDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   abcd::qlAbcdFunctionDataReader_var obj_dr
     = abcd::qlAbcdFunctionDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlAbcdFunctionDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    abcd::qlAbcdFunction obj;
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

              returnObject = QuantLibAddinCpp::qlAbcdFunction ( 
              obj.ObjectId.in(),
              static_cast<double>(obj.A),
              static_cast<double>(obj.B),
              static_cast<double>(obj.C),
              static_cast<double>(obj.D),
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
       std::string err = "ERROR: read qlAbcdFunction: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlAbcdFunctionDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlAbcdFunctionDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlAbcdFunctionDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlAbcdFunctionDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlAbcdFunctionDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlAbcdFunctionDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlAbcdFunctionDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlAbcdFunctionDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlAbcdFunctionDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlAbcdFunctionDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlAbcdFunctionDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlAbcdFunctionDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlAbcdFunctionDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlAbcdFunctionDataReaderListenerImpl::on_reading_start\n")));
}

void qlAbcdFunctionDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlAbcdFunctionDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlAbcdFunctionDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, abcd::qlAbcdFunction& )
{
  return true;
}

bool qlAbcdFunctionDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, abcd::qlAbcdFunction&, std::string& )
{
  return true;
}

void qlAbcdFunctionDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, abcd::qlAbcdFunction&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlAbcdFunctionDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlAbcdFunctionDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlAbcdFunctionDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlAbcdFunctionDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlAbcdFunctionDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}
}
