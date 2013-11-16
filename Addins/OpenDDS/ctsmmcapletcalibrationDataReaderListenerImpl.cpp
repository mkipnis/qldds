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

#include "ctsmmcapletcalibrationDataReaderListenerImpl.hpp"

#include <qldds_convert_utils.h>

namespace ctsmmcapletcalibration {

void qlCTSMMCapletAlphaFormCalibrationDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   ctsmmcapletcalibration::qlCTSMMCapletAlphaFormCalibrationDataReader_var obj_dr
     = ctsmmcapletcalibration::qlCTSMMCapletAlphaFormCalibrationDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlCTSMMCapletAlphaFormCalibrationDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    ctsmmcapletcalibration::qlCTSMMCapletAlphaFormCalibration obj;
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

              returnObject = QuantLibAddinCpp::qlCTSMMCapletAlphaFormCalibration ( 
              obj.ObjectId.in(),
              obj.Evolution.in(),
              obj.Correlations.in(),
             qldds_utils::vector_cast<std::string,CORBA::StringSeq>(obj.SwapPiecewiseConstantVariances),
             qldds_utils::vector_cast<double,CORBA::DoubleSeq>(obj.CapletVols),
              obj.CurveState.in(),
              static_cast<double>(obj.Displacement),
             qldds_utils::vector_cast<double,CORBA::DoubleSeq>(obj.AlphaInitial),
             qldds_utils::vector_cast<double,CORBA::DoubleSeq>(obj.AlphaMax),
             qldds_utils::vector_cast<double,CORBA::DoubleSeq>(obj.AlphaMin),
              static_cast<bool>(obj.MaximizeHomogeneity),
              obj.AlphaForm.in(),
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
       std::string err = "ERROR: read qlCTSMMCapletAlphaFormCalibration: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlCTSMMCapletAlphaFormCalibrationDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCTSMMCapletAlphaFormCalibrationDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlCTSMMCapletAlphaFormCalibrationDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCTSMMCapletAlphaFormCalibrationDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlCTSMMCapletAlphaFormCalibrationDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCTSMMCapletAlphaFormCalibrationDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlCTSMMCapletAlphaFormCalibrationDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCTSMMCapletAlphaFormCalibrationDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlCTSMMCapletAlphaFormCalibrationDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCTSMMCapletAlphaFormCalibrationDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlCTSMMCapletAlphaFormCalibrationDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCTSMMCapletAlphaFormCalibrationDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlCTSMMCapletAlphaFormCalibrationDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlCTSMMCapletAlphaFormCalibrationDataReaderListenerImpl::on_reading_start\n")));
}

void qlCTSMMCapletAlphaFormCalibrationDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlCTSMMCapletAlphaFormCalibrationDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlCTSMMCapletAlphaFormCalibrationDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, ctsmmcapletcalibration::qlCTSMMCapletAlphaFormCalibration& )
{
  return true;
}

bool qlCTSMMCapletAlphaFormCalibrationDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, ctsmmcapletcalibration::qlCTSMMCapletAlphaFormCalibration&, std::string& )
{
  return true;
}

void qlCTSMMCapletAlphaFormCalibrationDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, ctsmmcapletcalibration::qlCTSMMCapletAlphaFormCalibration&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCTSMMCapletAlphaFormCalibrationDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlCTSMMCapletAlphaFormCalibrationDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCTSMMCapletAlphaFormCalibrationDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlCTSMMCapletAlphaFormCalibrationDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCTSMMCapletAlphaFormCalibrationDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlCTSMMCapletMaxHomogeneityCalibrationDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   ctsmmcapletcalibration::qlCTSMMCapletMaxHomogeneityCalibrationDataReader_var obj_dr
     = ctsmmcapletcalibration::qlCTSMMCapletMaxHomogeneityCalibrationDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlCTSMMCapletMaxHomogeneityCalibrationDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    ctsmmcapletcalibration::qlCTSMMCapletMaxHomogeneityCalibration obj;
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

              returnObject = QuantLibAddinCpp::qlCTSMMCapletMaxHomogeneityCalibration ( 
              obj.ObjectId.in(),
              obj.Evolution.in(),
              obj.Correlations.in(),
             qldds_utils::vector_cast<std::string,CORBA::StringSeq>(obj.SwapPiecewiseConstantVariances),
             qldds_utils::vector_cast<double,CORBA::DoubleSeq>(obj.CapletVols),
              obj.CurveState.in(),
              static_cast<double>(obj.Displacement),
              static_cast<double>(obj.Caplet0Swaption1Priority),
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
       std::string err = "ERROR: read qlCTSMMCapletMaxHomogeneityCalibration: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlCTSMMCapletMaxHomogeneityCalibrationDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCTSMMCapletMaxHomogeneityCalibrationDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlCTSMMCapletMaxHomogeneityCalibrationDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCTSMMCapletMaxHomogeneityCalibrationDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlCTSMMCapletMaxHomogeneityCalibrationDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCTSMMCapletMaxHomogeneityCalibrationDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlCTSMMCapletMaxHomogeneityCalibrationDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCTSMMCapletMaxHomogeneityCalibrationDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlCTSMMCapletMaxHomogeneityCalibrationDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCTSMMCapletMaxHomogeneityCalibrationDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlCTSMMCapletMaxHomogeneityCalibrationDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCTSMMCapletMaxHomogeneityCalibrationDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlCTSMMCapletMaxHomogeneityCalibrationDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlCTSMMCapletMaxHomogeneityCalibrationDataReaderListenerImpl::on_reading_start\n")));
}

void qlCTSMMCapletMaxHomogeneityCalibrationDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlCTSMMCapletMaxHomogeneityCalibrationDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlCTSMMCapletMaxHomogeneityCalibrationDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, ctsmmcapletcalibration::qlCTSMMCapletMaxHomogeneityCalibration& )
{
  return true;
}

bool qlCTSMMCapletMaxHomogeneityCalibrationDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, ctsmmcapletcalibration::qlCTSMMCapletMaxHomogeneityCalibration&, std::string& )
{
  return true;
}

void qlCTSMMCapletMaxHomogeneityCalibrationDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, ctsmmcapletcalibration::qlCTSMMCapletMaxHomogeneityCalibration&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCTSMMCapletMaxHomogeneityCalibrationDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlCTSMMCapletMaxHomogeneityCalibrationDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCTSMMCapletMaxHomogeneityCalibrationDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlCTSMMCapletMaxHomogeneityCalibrationDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCTSMMCapletMaxHomogeneityCalibrationDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlCTSMMCapletOriginalCalibrationDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   ctsmmcapletcalibration::qlCTSMMCapletOriginalCalibrationDataReader_var obj_dr
     = ctsmmcapletcalibration::qlCTSMMCapletOriginalCalibrationDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlCTSMMCapletOriginalCalibrationDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    ctsmmcapletcalibration::qlCTSMMCapletOriginalCalibration obj;
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

              returnObject = QuantLibAddinCpp::qlCTSMMCapletOriginalCalibration ( 
              obj.ObjectId.in(),
              obj.Evolution.in(),
              obj.Correlations.in(),
             qldds_utils::vector_cast<std::string,CORBA::StringSeq>(obj.SwapPiecewiseConstantVariances),
             qldds_utils::vector_cast<double,CORBA::DoubleSeq>(obj.CapletVols),
              obj.CurveState.in(),
              static_cast<double>(obj.Displacement),
             qldds_utils::vector_cast<double,CORBA::DoubleSeq>(obj.Alphas),
              static_cast<bool>(obj.LowestRoot),
              static_cast<bool>(obj.UseFullApprox),
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
       std::string err = "ERROR: read qlCTSMMCapletOriginalCalibration: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlCTSMMCapletOriginalCalibrationDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCTSMMCapletOriginalCalibrationDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlCTSMMCapletOriginalCalibrationDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCTSMMCapletOriginalCalibrationDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlCTSMMCapletOriginalCalibrationDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCTSMMCapletOriginalCalibrationDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlCTSMMCapletOriginalCalibrationDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCTSMMCapletOriginalCalibrationDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlCTSMMCapletOriginalCalibrationDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCTSMMCapletOriginalCalibrationDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlCTSMMCapletOriginalCalibrationDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCTSMMCapletOriginalCalibrationDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlCTSMMCapletOriginalCalibrationDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlCTSMMCapletOriginalCalibrationDataReaderListenerImpl::on_reading_start\n")));
}

void qlCTSMMCapletOriginalCalibrationDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlCTSMMCapletOriginalCalibrationDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlCTSMMCapletOriginalCalibrationDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, ctsmmcapletcalibration::qlCTSMMCapletOriginalCalibration& )
{
  return true;
}

bool qlCTSMMCapletOriginalCalibrationDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, ctsmmcapletcalibration::qlCTSMMCapletOriginalCalibration&, std::string& )
{
  return true;
}

void qlCTSMMCapletOriginalCalibrationDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, ctsmmcapletcalibration::qlCTSMMCapletOriginalCalibration&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCTSMMCapletOriginalCalibrationDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlCTSMMCapletOriginalCalibrationDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCTSMMCapletOriginalCalibrationDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlCTSMMCapletOriginalCalibrationDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCTSMMCapletOriginalCalibrationDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}
}
