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

#include "interpolationDataReaderListenerImpl.hpp"

#include <qldds_convert_utils.h>

namespace interpolation {

void qlAbcdInterpolationDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   interpolation::qlAbcdInterpolationDataReader_var obj_dr
     = interpolation::qlAbcdInterpolationDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlAbcdInterpolationDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    interpolation::qlAbcdInterpolation obj;
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

              returnObject = QuantLibAddinCpp::qlAbcdInterpolation ( 
              obj.ObjectId.in(),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.XArray),
             qldds_utils::vector_cast<ObjectHandler::property_t,qldds_utils::DoubleSeq>(obj.YArray),
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
              obj.OptimizationMeth.in(),
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
       std::string err = "ERROR: read qlAbcdInterpolation: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlAbcdInterpolationDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlAbcdInterpolationDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlAbcdInterpolationDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlAbcdInterpolationDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlAbcdInterpolationDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlAbcdInterpolationDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlAbcdInterpolationDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlAbcdInterpolationDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlAbcdInterpolationDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlAbcdInterpolationDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlAbcdInterpolationDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlAbcdInterpolationDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlAbcdInterpolationDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlAbcdInterpolationDataReaderListenerImpl::on_reading_start\n")));
}

void qlAbcdInterpolationDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlAbcdInterpolationDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlAbcdInterpolationDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, interpolation::qlAbcdInterpolation& )
{
  return true;
}

bool qlAbcdInterpolationDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, interpolation::qlAbcdInterpolation&, std::string& )
{
  return true;
}

void qlAbcdInterpolationDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, interpolation::qlAbcdInterpolation&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlAbcdInterpolationDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlAbcdInterpolationDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlAbcdInterpolationDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlAbcdInterpolationDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlAbcdInterpolationDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlCubicInterpolationDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   interpolation::qlCubicInterpolationDataReader_var obj_dr
     = interpolation::qlCubicInterpolationDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlCubicInterpolationDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    interpolation::qlCubicInterpolation obj;
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

              returnObject = QuantLibAddinCpp::qlCubicInterpolation ( 
              obj.ObjectId.in(),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.XArray),
             qldds_utils::vector_cast<ObjectHandler::property_t,qldds_utils::DoubleSeq>(obj.YArray),
              obj.DerApprox.in(),
              static_cast<bool>(obj.Monotonic),
              obj.LeftConditionType.in(),
              static_cast<double>(obj.LeftConditionValue),
              obj.RightConditionType.in(),
              static_cast<double>(obj.RightConditionValue),
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
       std::string err = "ERROR: read qlCubicInterpolation: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlCubicInterpolationDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCubicInterpolationDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlCubicInterpolationDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCubicInterpolationDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlCubicInterpolationDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCubicInterpolationDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlCubicInterpolationDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCubicInterpolationDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlCubicInterpolationDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCubicInterpolationDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlCubicInterpolationDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCubicInterpolationDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlCubicInterpolationDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlCubicInterpolationDataReaderListenerImpl::on_reading_start\n")));
}

void qlCubicInterpolationDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlCubicInterpolationDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlCubicInterpolationDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, interpolation::qlCubicInterpolation& )
{
  return true;
}

bool qlCubicInterpolationDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, interpolation::qlCubicInterpolation&, std::string& )
{
  return true;
}

void qlCubicInterpolationDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, interpolation::qlCubicInterpolation&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCubicInterpolationDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlCubicInterpolationDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCubicInterpolationDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlCubicInterpolationDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCubicInterpolationDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlExtrapolatorEnableExtrapolationDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   interpolation::qlExtrapolatorEnableExtrapolationDataReader_var obj_dr
     = interpolation::qlExtrapolatorEnableExtrapolationDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlExtrapolatorEnableExtrapolationDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    interpolation::qlExtrapolatorEnableExtrapolation obj;
    DDS::SampleInfo si ;
    DDS::ReturnCode_t status = obj_dr->take_next_sample(obj, si) ;

    if ( status == DDS::RETCODE_OK )
    {
      if ( si.valid_data == true )
      {
         ++count;

         if ( pre_quantlib_addin_call( reader, si, obj ) )
         {
            bool returnObject;;

            try {

              ACE_Guard<ACE_Mutex> guard( get_ACE_Mutex() );

              returnObject = QuantLibAddinCpp::qlExtrapolatorEnableExtrapolation ( 
              obj.ObjectId.in(),
              static_cast<bool>(obj.ExtrapolationFlag),
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
       std::string err = "ERROR: read qlExtrapolatorEnableExtrapolation: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlExtrapolatorEnableExtrapolationDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlExtrapolatorEnableExtrapolationDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlExtrapolatorEnableExtrapolationDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlExtrapolatorEnableExtrapolationDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlExtrapolatorEnableExtrapolationDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlExtrapolatorEnableExtrapolationDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlExtrapolatorEnableExtrapolationDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlExtrapolatorEnableExtrapolationDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlExtrapolatorEnableExtrapolationDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlExtrapolatorEnableExtrapolationDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlExtrapolatorEnableExtrapolationDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlExtrapolatorEnableExtrapolationDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlExtrapolatorEnableExtrapolationDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlExtrapolatorEnableExtrapolationDataReaderListenerImpl::on_reading_start\n")));
}

void qlExtrapolatorEnableExtrapolationDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlExtrapolatorEnableExtrapolationDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlExtrapolatorEnableExtrapolationDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, interpolation::qlExtrapolatorEnableExtrapolation& )
{
  return true;
}

bool qlExtrapolatorEnableExtrapolationDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, interpolation::qlExtrapolatorEnableExtrapolation&, bool& )
{
  return true;
}

void qlExtrapolatorEnableExtrapolationDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, interpolation::qlExtrapolatorEnableExtrapolation&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlExtrapolatorEnableExtrapolationDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlExtrapolatorEnableExtrapolationDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlExtrapolatorEnableExtrapolationDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlExtrapolatorEnableExtrapolationDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlExtrapolatorEnableExtrapolationDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlInterpolationDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   interpolation::qlInterpolationDataReader_var obj_dr
     = interpolation::qlInterpolationDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlInterpolationDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    interpolation::qlInterpolation obj;
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

              returnObject = QuantLibAddinCpp::qlInterpolation ( 
              obj.ObjectId.in(),
              obj.InterpolationType.in(),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.XArray),
             qldds_utils::vector_cast<ObjectHandler::property_t,qldds_utils::DoubleSeq>(obj.YArray),
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
       std::string err = "ERROR: read qlInterpolation: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlInterpolationDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInterpolationDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlInterpolationDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInterpolationDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlInterpolationDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInterpolationDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlInterpolationDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInterpolationDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlInterpolationDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInterpolationDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlInterpolationDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInterpolationDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlInterpolationDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlInterpolationDataReaderListenerImpl::on_reading_start\n")));
}

void qlInterpolationDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlInterpolationDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlInterpolationDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, interpolation::qlInterpolation& )
{
  return true;
}

bool qlInterpolationDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, interpolation::qlInterpolation&, std::string& )
{
  return true;
}

void qlInterpolationDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, interpolation::qlInterpolation&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInterpolationDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlInterpolationDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInterpolationDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlInterpolationDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInterpolationDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlMixedLinearCubicInterpolationDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   interpolation::qlMixedLinearCubicInterpolationDataReader_var obj_dr
     = interpolation::qlMixedLinearCubicInterpolationDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlMixedLinearCubicInterpolationDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    interpolation::qlMixedLinearCubicInterpolation obj;
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

              returnObject = QuantLibAddinCpp::qlMixedLinearCubicInterpolation ( 
              obj.ObjectId.in(),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.XArray),
             qldds_utils::vector_cast<ObjectHandler::property_t,qldds_utils::DoubleSeq>(obj.YArray),
              static_cast<long>(obj.SwitchIndex),
              obj.DerApprox.in(),
              static_cast<bool>(obj.Monotonic),
              obj.LeftConditionType.in(),
              static_cast<double>(obj.LeftConditionValue),
              obj.RightConditionType.in(),
              static_cast<double>(obj.RightConditionValue),
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
       std::string err = "ERROR: read qlMixedLinearCubicInterpolation: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlMixedLinearCubicInterpolationDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMixedLinearCubicInterpolationDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlMixedLinearCubicInterpolationDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMixedLinearCubicInterpolationDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlMixedLinearCubicInterpolationDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMixedLinearCubicInterpolationDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlMixedLinearCubicInterpolationDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMixedLinearCubicInterpolationDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlMixedLinearCubicInterpolationDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMixedLinearCubicInterpolationDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlMixedLinearCubicInterpolationDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMixedLinearCubicInterpolationDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlMixedLinearCubicInterpolationDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlMixedLinearCubicInterpolationDataReaderListenerImpl::on_reading_start\n")));
}

void qlMixedLinearCubicInterpolationDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlMixedLinearCubicInterpolationDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlMixedLinearCubicInterpolationDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, interpolation::qlMixedLinearCubicInterpolation& )
{
  return true;
}

bool qlMixedLinearCubicInterpolationDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, interpolation::qlMixedLinearCubicInterpolation&, std::string& )
{
  return true;
}

void qlMixedLinearCubicInterpolationDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, interpolation::qlMixedLinearCubicInterpolation&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMixedLinearCubicInterpolationDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlMixedLinearCubicInterpolationDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMixedLinearCubicInterpolationDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlMixedLinearCubicInterpolationDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMixedLinearCubicInterpolationDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlSABRInterpolationDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   interpolation::qlSABRInterpolationDataReader_var obj_dr
     = interpolation::qlSABRInterpolationDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlSABRInterpolationDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    interpolation::qlSABRInterpolation obj;
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

              returnObject = QuantLibAddinCpp::qlSABRInterpolation ( 
              obj.ObjectId.in(),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.XArray),
             qldds_utils::vector_cast<ObjectHandler::property_t,qldds_utils::DoubleSeq>(obj.YArray),
              static_cast<double>(obj.Expiry),
              obj.Forward ,
              static_cast<double>(obj.Alpha),
              static_cast<double>(obj.Beta),
              static_cast<double>(obj.Nu),
              static_cast<double>(obj.Rho),
              static_cast<bool>(obj.AlphaIsFixed),
              static_cast<bool>(obj.BetaIsFixed),
              static_cast<bool>(obj.NuIsFixed),
              static_cast<bool>(obj.RhoIsFixed),
              static_cast<bool>(obj.VegaWeighted),
              obj.EndCriteria.in(),
              obj.OptimizationMeth.in(),
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
       std::string err = "ERROR: read qlSABRInterpolation: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlSABRInterpolationDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSABRInterpolationDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlSABRInterpolationDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSABRInterpolationDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlSABRInterpolationDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSABRInterpolationDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlSABRInterpolationDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSABRInterpolationDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlSABRInterpolationDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSABRInterpolationDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlSABRInterpolationDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSABRInterpolationDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlSABRInterpolationDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlSABRInterpolationDataReaderListenerImpl::on_reading_start\n")));
}

void qlSABRInterpolationDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlSABRInterpolationDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlSABRInterpolationDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, interpolation::qlSABRInterpolation& )
{
  return true;
}

bool qlSABRInterpolationDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, interpolation::qlSABRInterpolation&, std::string& )
{
  return true;
}

void qlSABRInterpolationDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, interpolation::qlSABRInterpolation&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSABRInterpolationDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlSABRInterpolationDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSABRInterpolationDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlSABRInterpolationDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSABRInterpolationDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}
}
