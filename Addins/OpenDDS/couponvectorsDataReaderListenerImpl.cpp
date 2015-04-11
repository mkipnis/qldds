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

#include "couponvectorsDataReaderListenerImpl.hpp"

#include <qldds_convert_utils.h>

namespace couponvectors {

void qlCmsCouponPricerDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   couponvectors::qlCmsCouponPricerDataReader_var obj_dr
     = couponvectors::qlCmsCouponPricerDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlCmsCouponPricerDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    couponvectors::qlCmsCouponPricer obj;
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

              returnObject = QuantLibAddinCpp::qlCmsCouponPricer ( 
              obj.ObjectId.in(),
              obj.Volatility.in(),
              obj.CmsCouponPricerType.in(),
              obj.YieldCurveModel.in(),
              obj.MeanReversion ,
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
       std::string err = "ERROR: read qlCmsCouponPricer: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlCmsCouponPricerDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCmsCouponPricerDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlCmsCouponPricerDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCmsCouponPricerDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlCmsCouponPricerDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCmsCouponPricerDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlCmsCouponPricerDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCmsCouponPricerDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlCmsCouponPricerDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCmsCouponPricerDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlCmsCouponPricerDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCmsCouponPricerDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlCmsCouponPricerDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlCmsCouponPricerDataReaderListenerImpl::on_reading_start\n")));
}

void qlCmsCouponPricerDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlCmsCouponPricerDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlCmsCouponPricerDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, couponvectors::qlCmsCouponPricer& )
{
  return true;
}

bool qlCmsCouponPricerDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, couponvectors::qlCmsCouponPricer&, std::string& )
{
  return true;
}

void qlCmsCouponPricerDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, couponvectors::qlCmsCouponPricer&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCmsCouponPricerDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlCmsCouponPricerDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCmsCouponPricerDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlCmsCouponPricerDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCmsCouponPricerDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlCmsLegDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   couponvectors::qlCmsLegDataReader_var obj_dr
     = couponvectors::qlCmsLegDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlCmsLegDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    couponvectors::qlCmsLeg obj;
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

              returnObject = QuantLibAddinCpp::qlCmsLeg ( 
              obj.ObjectId.in(),
              obj.PaymentBDC.in(),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.Nominals),
              obj.ScheduleID.in(),
              qldds_utils::vector_cast<long,qldds_utils::LongSeq>(obj.FixingDays),
              static_cast<bool>(obj.IsInArrears),
              obj.DayCounter.in(),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.Floors),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.Gearings),
              obj.SwapIndex.in(),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.Spreads),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.Caps),
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
       std::string err = "ERROR: read qlCmsLeg: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlCmsLegDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCmsLegDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlCmsLegDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCmsLegDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlCmsLegDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCmsLegDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlCmsLegDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCmsLegDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlCmsLegDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCmsLegDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlCmsLegDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCmsLegDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlCmsLegDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlCmsLegDataReaderListenerImpl::on_reading_start\n")));
}

void qlCmsLegDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlCmsLegDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlCmsLegDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, couponvectors::qlCmsLeg& )
{
  return true;
}

bool qlCmsLegDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, couponvectors::qlCmsLeg&, std::string& )
{
  return true;
}

void qlCmsLegDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, couponvectors::qlCmsLeg&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCmsLegDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlCmsLegDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCmsLegDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlCmsLegDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCmsLegDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlCmsZeroLegDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   couponvectors::qlCmsZeroLegDataReader_var obj_dr
     = couponvectors::qlCmsZeroLegDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlCmsZeroLegDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    couponvectors::qlCmsZeroLeg obj;
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

              returnObject = QuantLibAddinCpp::qlCmsZeroLeg ( 
              obj.ObjectId.in(),
              obj.PaymentBDC.in(),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.Nominals),
              obj.ScheduleID.in(),
              qldds_utils::vector_cast<long,qldds_utils::LongSeq>(obj.FixingDays),
              static_cast<bool>(obj.IsInArrears),
              obj.DayCounter.in(),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.Floors),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.Gearings),
              obj.SwapIndex.in(),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.Spreads),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.Caps),
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
       std::string err = "ERROR: read qlCmsZeroLeg: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlCmsZeroLegDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCmsZeroLegDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlCmsZeroLegDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCmsZeroLegDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlCmsZeroLegDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCmsZeroLegDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlCmsZeroLegDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCmsZeroLegDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlCmsZeroLegDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCmsZeroLegDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlCmsZeroLegDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCmsZeroLegDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlCmsZeroLegDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlCmsZeroLegDataReaderListenerImpl::on_reading_start\n")));
}

void qlCmsZeroLegDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlCmsZeroLegDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlCmsZeroLegDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, couponvectors::qlCmsZeroLeg& )
{
  return true;
}

bool qlCmsZeroLegDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, couponvectors::qlCmsZeroLeg&, std::string& )
{
  return true;
}

void qlCmsZeroLegDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, couponvectors::qlCmsZeroLeg&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCmsZeroLegDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlCmsZeroLegDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCmsZeroLegDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlCmsZeroLegDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCmsZeroLegDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlConundrumPricerByNumericalIntegrationDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   couponvectors::qlConundrumPricerByNumericalIntegrationDataReader_var obj_dr
     = couponvectors::qlConundrumPricerByNumericalIntegrationDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlConundrumPricerByNumericalIntegrationDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    couponvectors::qlConundrumPricerByNumericalIntegration obj;
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

              returnObject = QuantLibAddinCpp::qlConundrumPricerByNumericalIntegration ( 
              obj.ObjectId.in(),
              obj.SwaptionVol.in(),
              obj.YieldCurveModel.in(),
              obj.MeanReversion ,
              static_cast<double>(obj.LowerLimit),
              static_cast<double>(obj.UpperLimit),
              static_cast<double>(obj.Precision),
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
       std::string err = "ERROR: read qlConundrumPricerByNumericalIntegration: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlConundrumPricerByNumericalIntegrationDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlConundrumPricerByNumericalIntegrationDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlConundrumPricerByNumericalIntegrationDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlConundrumPricerByNumericalIntegrationDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlConundrumPricerByNumericalIntegrationDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlConundrumPricerByNumericalIntegrationDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlConundrumPricerByNumericalIntegrationDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlConundrumPricerByNumericalIntegrationDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlConundrumPricerByNumericalIntegrationDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlConundrumPricerByNumericalIntegrationDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlConundrumPricerByNumericalIntegrationDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlConundrumPricerByNumericalIntegrationDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlConundrumPricerByNumericalIntegrationDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlConundrumPricerByNumericalIntegrationDataReaderListenerImpl::on_reading_start\n")));
}

void qlConundrumPricerByNumericalIntegrationDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlConundrumPricerByNumericalIntegrationDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlConundrumPricerByNumericalIntegrationDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, couponvectors::qlConundrumPricerByNumericalIntegration& )
{
  return true;
}

bool qlConundrumPricerByNumericalIntegrationDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, couponvectors::qlConundrumPricerByNumericalIntegration&, std::string& )
{
  return true;
}

void qlConundrumPricerByNumericalIntegrationDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, couponvectors::qlConundrumPricerByNumericalIntegration&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlConundrumPricerByNumericalIntegrationDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlConundrumPricerByNumericalIntegrationDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlConundrumPricerByNumericalIntegrationDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlConundrumPricerByNumericalIntegrationDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlConundrumPricerByNumericalIntegrationDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlDigitalCmsLegDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   couponvectors::qlDigitalCmsLegDataReader_var obj_dr
     = couponvectors::qlDigitalCmsLegDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlDigitalCmsLegDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    couponvectors::qlDigitalCmsLeg obj;
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

              returnObject = QuantLibAddinCpp::qlDigitalCmsLeg ( 
              obj.ObjectId.in(),
              obj.PaymentBDC.in(),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.Nominals),
              obj.ScheduleID.in(),
              qldds_utils::vector_cast<long,qldds_utils::LongSeq>(obj.FixingDays),
              static_cast<bool>(obj.IsInArrears),
              obj.DayCounter.in(),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.Gearings),
              obj.SwapIndex.in(),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.Spreads),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.CallStrikes),
              obj.CallSpecs.in(),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.CallPayoff),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.PutStrikes),
              obj.PutSpecs.in(),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.PutPayoff),
              obj.Replication.in(),
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
       std::string err = "ERROR: read qlDigitalCmsLeg: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlDigitalCmsLegDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDigitalCmsLegDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlDigitalCmsLegDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDigitalCmsLegDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlDigitalCmsLegDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDigitalCmsLegDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlDigitalCmsLegDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDigitalCmsLegDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlDigitalCmsLegDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDigitalCmsLegDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlDigitalCmsLegDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDigitalCmsLegDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlDigitalCmsLegDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlDigitalCmsLegDataReaderListenerImpl::on_reading_start\n")));
}

void qlDigitalCmsLegDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlDigitalCmsLegDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlDigitalCmsLegDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, couponvectors::qlDigitalCmsLeg& )
{
  return true;
}

bool qlDigitalCmsLegDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, couponvectors::qlDigitalCmsLeg&, std::string& )
{
  return true;
}

void qlDigitalCmsLegDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, couponvectors::qlDigitalCmsLeg&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDigitalCmsLegDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlDigitalCmsLegDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDigitalCmsLegDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlDigitalCmsLegDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDigitalCmsLegDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlDigitalIborLegDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   couponvectors::qlDigitalIborLegDataReader_var obj_dr
     = couponvectors::qlDigitalIborLegDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlDigitalIborLegDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    couponvectors::qlDigitalIborLeg obj;
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

              returnObject = QuantLibAddinCpp::qlDigitalIborLeg ( 
              obj.ObjectId.in(),
              obj.PaymentBDC.in(),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.Nominals),
              obj.ScheduleID.in(),
              qldds_utils::vector_cast<long,qldds_utils::LongSeq>(obj.FixingDays),
              static_cast<bool>(obj.IsInArrears),
              obj.DayCounter.in(),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.Gearings),
              obj.IborIndex.in(),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.Spreads),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.CallStrikes),
              obj.CallSpecs.in(),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.CallPayoff),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.PutStrikes),
              obj.PutSpecs.in(),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.PutPayoff),
              obj.Replication.in(),
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
       std::string err = "ERROR: read qlDigitalIborLeg: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlDigitalIborLegDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDigitalIborLegDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlDigitalIborLegDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDigitalIborLegDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlDigitalIborLegDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDigitalIborLegDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlDigitalIborLegDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDigitalIborLegDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlDigitalIborLegDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDigitalIborLegDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlDigitalIborLegDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDigitalIborLegDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlDigitalIborLegDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlDigitalIborLegDataReaderListenerImpl::on_reading_start\n")));
}

void qlDigitalIborLegDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlDigitalIborLegDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlDigitalIborLegDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, couponvectors::qlDigitalIborLeg& )
{
  return true;
}

bool qlDigitalIborLegDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, couponvectors::qlDigitalIborLeg&, std::string& )
{
  return true;
}

void qlDigitalIborLegDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, couponvectors::qlDigitalIborLeg&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDigitalIborLegDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlDigitalIborLegDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDigitalIborLegDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlDigitalIborLegDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDigitalIborLegDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlFixedRateLegDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   couponvectors::qlFixedRateLegDataReader_var obj_dr
     = couponvectors::qlFixedRateLegDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlFixedRateLegDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    couponvectors::qlFixedRateLeg obj;
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

              returnObject = QuantLibAddinCpp::qlFixedRateLeg ( 
              obj.ObjectId.in(),
              obj.PaymentBDC.in(),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.Nominals),
              obj.ScheduleID.in(),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.Coupons),
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
       std::string err = "ERROR: read qlFixedRateLeg: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlFixedRateLegDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFixedRateLegDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlFixedRateLegDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFixedRateLegDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlFixedRateLegDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFixedRateLegDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlFixedRateLegDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFixedRateLegDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlFixedRateLegDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFixedRateLegDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlFixedRateLegDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFixedRateLegDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlFixedRateLegDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlFixedRateLegDataReaderListenerImpl::on_reading_start\n")));
}

void qlFixedRateLegDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlFixedRateLegDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlFixedRateLegDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, couponvectors::qlFixedRateLeg& )
{
  return true;
}

bool qlFixedRateLegDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, couponvectors::qlFixedRateLeg&, std::string& )
{
  return true;
}

void qlFixedRateLegDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, couponvectors::qlFixedRateLeg&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFixedRateLegDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlFixedRateLegDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFixedRateLegDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlFixedRateLegDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFixedRateLegDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlFixedRateLeg2DataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   couponvectors::qlFixedRateLeg2DataReader_var obj_dr
     = couponvectors::qlFixedRateLeg2DataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlFixedRateLeg2DataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    couponvectors::qlFixedRateLeg2 obj;
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

              returnObject = QuantLibAddinCpp::qlFixedRateLeg2 ( 
              obj.ObjectId.in(),
              obj.PaymentBDC.in(),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.Nominals),
              obj.ScheduleID.in(),
             qldds_utils::vector_cast<std::string,qldds_utils::StringSeq>(obj.Coupons),
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
       std::string err = "ERROR: read qlFixedRateLeg2: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlFixedRateLeg2DataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFixedRateLeg2DataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlFixedRateLeg2DataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFixedRateLeg2DataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlFixedRateLeg2DataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFixedRateLeg2DataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlFixedRateLeg2DataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFixedRateLeg2DataReaderListenerImpl::on_subscription_matched\n")));
}

void qlFixedRateLeg2DataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFixedRateLeg2DataReaderListenerImpl::on_sample_rejected\n")));
}

void qlFixedRateLeg2DataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFixedRateLeg2DataReaderListenerImpl::on_sample_rejected\n")));
}

void qlFixedRateLeg2DataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlFixedRateLeg2DataReaderListenerImpl::on_reading_start\n")));
}

void qlFixedRateLeg2DataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlFixedRateLeg2DataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlFixedRateLeg2DataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, couponvectors::qlFixedRateLeg2& )
{
  return true;
}

bool qlFixedRateLeg2DataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, couponvectors::qlFixedRateLeg2&, std::string& )
{
  return true;
}

void qlFixedRateLeg2DataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, couponvectors::qlFixedRateLeg2&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFixedRateLeg2DataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlFixedRateLeg2DataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFixedRateLeg2DataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlFixedRateLeg2DataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFixedRateLeg2DataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlIborCouponPricerDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   couponvectors::qlIborCouponPricerDataReader_var obj_dr
     = couponvectors::qlIborCouponPricerDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlIborCouponPricerDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    couponvectors::qlIborCouponPricer obj;
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

              returnObject = QuantLibAddinCpp::qlIborCouponPricer ( 
              obj.ObjectId.in(),
              obj.Volatility.in(),
              obj.IborCouponPricerType.in(),
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
       std::string err = "ERROR: read qlIborCouponPricer: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlIborCouponPricerDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIborCouponPricerDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlIborCouponPricerDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIborCouponPricerDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlIborCouponPricerDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIborCouponPricerDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlIborCouponPricerDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIborCouponPricerDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlIborCouponPricerDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIborCouponPricerDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlIborCouponPricerDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIborCouponPricerDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlIborCouponPricerDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlIborCouponPricerDataReaderListenerImpl::on_reading_start\n")));
}

void qlIborCouponPricerDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlIborCouponPricerDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlIborCouponPricerDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, couponvectors::qlIborCouponPricer& )
{
  return true;
}

bool qlIborCouponPricerDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, couponvectors::qlIborCouponPricer&, std::string& )
{
  return true;
}

void qlIborCouponPricerDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, couponvectors::qlIborCouponPricer&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIborCouponPricerDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlIborCouponPricerDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIborCouponPricerDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlIborCouponPricerDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIborCouponPricerDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlIborLegDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   couponvectors::qlIborLegDataReader_var obj_dr
     = couponvectors::qlIborLegDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlIborLegDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    couponvectors::qlIborLeg obj;
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

              returnObject = QuantLibAddinCpp::qlIborLeg ( 
              obj.ObjectId.in(),
              obj.PaymentBDC.in(),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.Nominals),
              obj.ScheduleID.in(),
              qldds_utils::vector_cast<long,qldds_utils::LongSeq>(obj.FixingDays),
              static_cast<bool>(obj.IsInArrears),
              obj.DayCounter.in(),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.Floors),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.Gearings),
              obj.IborIndex.in(),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.Spreads),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.Caps),
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
       std::string err = "ERROR: read qlIborLeg: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlIborLegDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIborLegDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlIborLegDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIborLegDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlIborLegDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIborLegDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlIborLegDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIborLegDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlIborLegDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIborLegDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlIborLegDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIborLegDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlIborLegDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlIborLegDataReaderListenerImpl::on_reading_start\n")));
}

void qlIborLegDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlIborLegDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlIborLegDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, couponvectors::qlIborLeg& )
{
  return true;
}

bool qlIborLegDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, couponvectors::qlIborLeg&, std::string& )
{
  return true;
}

void qlIborLegDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, couponvectors::qlIborLeg&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIborLegDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlIborLegDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIborLegDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlIborLegDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIborLegDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlRangeAccrualLegDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   couponvectors::qlRangeAccrualLegDataReader_var obj_dr
     = couponvectors::qlRangeAccrualLegDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlRangeAccrualLegDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    couponvectors::qlRangeAccrualLeg obj;
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

              returnObject = QuantLibAddinCpp::qlRangeAccrualLeg ( 
              obj.ObjectId.in(),
              obj.PaymentBDC.in(),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.Nominals),
              obj.ScheduleID.in(),
              qldds_utils::vector_cast<long,qldds_utils::LongSeq>(obj.FixingDays),
              obj.DayCounter.in(),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.LowerStrikes),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.Gearings),
              obj.IborIndex.in(),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.Spreads),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.UpperStrikes),
              obj.ObservationsTenor.in(),
              obj.ObservationsBDC.in(),
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
       std::string err = "ERROR: read qlRangeAccrualLeg: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlRangeAccrualLegDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRangeAccrualLegDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlRangeAccrualLegDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRangeAccrualLegDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlRangeAccrualLegDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRangeAccrualLegDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlRangeAccrualLegDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRangeAccrualLegDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlRangeAccrualLegDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRangeAccrualLegDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlRangeAccrualLegDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRangeAccrualLegDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlRangeAccrualLegDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlRangeAccrualLegDataReaderListenerImpl::on_reading_start\n")));
}

void qlRangeAccrualLegDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlRangeAccrualLegDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlRangeAccrualLegDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, couponvectors::qlRangeAccrualLeg& )
{
  return true;
}

bool qlRangeAccrualLegDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, couponvectors::qlRangeAccrualLeg&, std::string& )
{
  return true;
}

void qlRangeAccrualLegDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, couponvectors::qlRangeAccrualLeg&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRangeAccrualLegDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlRangeAccrualLegDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRangeAccrualLegDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlRangeAccrualLegDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRangeAccrualLegDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}
}
