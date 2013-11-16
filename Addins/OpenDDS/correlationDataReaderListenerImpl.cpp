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

#include "correlationDataReaderListenerImpl.hpp"

#include <qldds_convert_utils.h>

namespace correlation {

void qlCotSwapFromFwdCorrelationDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   correlation::qlCotSwapFromFwdCorrelationDataReader_var obj_dr
     = correlation::qlCotSwapFromFwdCorrelationDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlCotSwapFromFwdCorrelationDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    correlation::qlCotSwapFromFwdCorrelation obj;
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

              returnObject = QuantLibAddinCpp::qlCotSwapFromFwdCorrelation ( 
              obj.ObjectId.in(),
              obj.FwdCorr.in(),
              obj.CurveState.in(),
              static_cast<double>(obj.Displacement),
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
       std::string err = "ERROR: read qlCotSwapFromFwdCorrelation: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlCotSwapFromFwdCorrelationDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCotSwapFromFwdCorrelationDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlCotSwapFromFwdCorrelationDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCotSwapFromFwdCorrelationDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlCotSwapFromFwdCorrelationDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCotSwapFromFwdCorrelationDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlCotSwapFromFwdCorrelationDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCotSwapFromFwdCorrelationDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlCotSwapFromFwdCorrelationDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCotSwapFromFwdCorrelationDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlCotSwapFromFwdCorrelationDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCotSwapFromFwdCorrelationDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlCotSwapFromFwdCorrelationDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlCotSwapFromFwdCorrelationDataReaderListenerImpl::on_reading_start\n")));
}

void qlCotSwapFromFwdCorrelationDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlCotSwapFromFwdCorrelationDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlCotSwapFromFwdCorrelationDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, correlation::qlCotSwapFromFwdCorrelation& )
{
  return true;
}

bool qlCotSwapFromFwdCorrelationDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, correlation::qlCotSwapFromFwdCorrelation&, std::string& )
{
  return true;
}

void qlCotSwapFromFwdCorrelationDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, correlation::qlCotSwapFromFwdCorrelation&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCotSwapFromFwdCorrelationDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlCotSwapFromFwdCorrelationDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCotSwapFromFwdCorrelationDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlCotSwapFromFwdCorrelationDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCotSwapFromFwdCorrelationDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlExponentialForwardCorrelationDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   correlation::qlExponentialForwardCorrelationDataReader_var obj_dr
     = correlation::qlExponentialForwardCorrelationDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlExponentialForwardCorrelationDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    correlation::qlExponentialForwardCorrelation obj;
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

              returnObject = QuantLibAddinCpp::qlExponentialForwardCorrelation ( 
              obj.ObjectId.in(),
             qldds_utils::vector_cast<double,CORBA::DoubleSeq>(obj.RateTimes),
              static_cast<double>(obj.LongTermCorr),
              static_cast<double>(obj.Beta),
              static_cast<double>(obj.Gamma),
             qldds_utils::vector_cast<double,CORBA::DoubleSeq>(obj.Times),
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
       std::string err = "ERROR: read qlExponentialForwardCorrelation: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlExponentialForwardCorrelationDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlExponentialForwardCorrelationDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlExponentialForwardCorrelationDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlExponentialForwardCorrelationDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlExponentialForwardCorrelationDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlExponentialForwardCorrelationDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlExponentialForwardCorrelationDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlExponentialForwardCorrelationDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlExponentialForwardCorrelationDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlExponentialForwardCorrelationDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlExponentialForwardCorrelationDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlExponentialForwardCorrelationDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlExponentialForwardCorrelationDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlExponentialForwardCorrelationDataReaderListenerImpl::on_reading_start\n")));
}

void qlExponentialForwardCorrelationDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlExponentialForwardCorrelationDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlExponentialForwardCorrelationDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, correlation::qlExponentialForwardCorrelation& )
{
  return true;
}

bool qlExponentialForwardCorrelationDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, correlation::qlExponentialForwardCorrelation&, std::string& )
{
  return true;
}

void qlExponentialForwardCorrelationDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, correlation::qlExponentialForwardCorrelation&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlExponentialForwardCorrelationDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlExponentialForwardCorrelationDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlExponentialForwardCorrelationDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlExponentialForwardCorrelationDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlExponentialForwardCorrelationDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlHistoricalForwardRatesAnalysisDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   correlation::qlHistoricalForwardRatesAnalysisDataReader_var obj_dr
     = correlation::qlHistoricalForwardRatesAnalysisDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlHistoricalForwardRatesAnalysisDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    correlation::qlHistoricalForwardRatesAnalysis obj;
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

              returnObject = QuantLibAddinCpp::qlHistoricalForwardRatesAnalysis ( 
              obj.ObjectId.in(),
              obj.SequenceStats.in(),
              qldds_utils::from_iso_string(obj.StartDate.in() ),
              qldds_utils::from_iso_string(obj.EndDate.in() ),
              obj.Step.in(),
              obj.IborIndex.in(),
              obj.InitialGap.in(),
              obj.Horizon.in(),
             qldds_utils::vector_cast<std::string,CORBA::StringSeq>(obj.IborIndexes),
             qldds_utils::vector_cast<std::string,CORBA::StringSeq>(obj.SwapIndexes),
              obj.DayCounter.in(),
              obj.TraitsID.in(),
              obj.InterpolatorID.in(),
              static_cast<double>(obj.BootstrapAccuracy),
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
       std::string err = "ERROR: read qlHistoricalForwardRatesAnalysis: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlHistoricalForwardRatesAnalysisDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlHistoricalForwardRatesAnalysisDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlHistoricalForwardRatesAnalysisDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlHistoricalForwardRatesAnalysisDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlHistoricalForwardRatesAnalysisDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlHistoricalForwardRatesAnalysisDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlHistoricalForwardRatesAnalysisDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlHistoricalForwardRatesAnalysisDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlHistoricalForwardRatesAnalysisDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlHistoricalForwardRatesAnalysisDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlHistoricalForwardRatesAnalysisDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlHistoricalForwardRatesAnalysisDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlHistoricalForwardRatesAnalysisDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlHistoricalForwardRatesAnalysisDataReaderListenerImpl::on_reading_start\n")));
}

void qlHistoricalForwardRatesAnalysisDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlHistoricalForwardRatesAnalysisDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlHistoricalForwardRatesAnalysisDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, correlation::qlHistoricalForwardRatesAnalysis& )
{
  return true;
}

bool qlHistoricalForwardRatesAnalysisDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, correlation::qlHistoricalForwardRatesAnalysis&, std::string& )
{
  return true;
}

void qlHistoricalForwardRatesAnalysisDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, correlation::qlHistoricalForwardRatesAnalysis&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlHistoricalForwardRatesAnalysisDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlHistoricalForwardRatesAnalysisDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlHistoricalForwardRatesAnalysisDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlHistoricalForwardRatesAnalysisDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlHistoricalForwardRatesAnalysisDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlHistoricalRatesAnalysisDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   correlation::qlHistoricalRatesAnalysisDataReader_var obj_dr
     = correlation::qlHistoricalRatesAnalysisDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlHistoricalRatesAnalysisDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    correlation::qlHistoricalRatesAnalysis obj;
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

              returnObject = QuantLibAddinCpp::qlHistoricalRatesAnalysis ( 
              obj.ObjectId.in(),
              obj.SequenceStats.in(),
              qldds_utils::from_iso_string(obj.StartDate.in() ),
              qldds_utils::from_iso_string(obj.EndDate.in() ),
              obj.Step.in(),
             qldds_utils::vector_cast<std::string,CORBA::StringSeq>(obj.InterestRateIndexes),
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
       std::string err = "ERROR: read qlHistoricalRatesAnalysis: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlHistoricalRatesAnalysisDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlHistoricalRatesAnalysisDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlHistoricalRatesAnalysisDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlHistoricalRatesAnalysisDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlHistoricalRatesAnalysisDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlHistoricalRatesAnalysisDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlHistoricalRatesAnalysisDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlHistoricalRatesAnalysisDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlHistoricalRatesAnalysisDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlHistoricalRatesAnalysisDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlHistoricalRatesAnalysisDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlHistoricalRatesAnalysisDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlHistoricalRatesAnalysisDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlHistoricalRatesAnalysisDataReaderListenerImpl::on_reading_start\n")));
}

void qlHistoricalRatesAnalysisDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlHistoricalRatesAnalysisDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlHistoricalRatesAnalysisDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, correlation::qlHistoricalRatesAnalysis& )
{
  return true;
}

bool qlHistoricalRatesAnalysisDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, correlation::qlHistoricalRatesAnalysis&, std::string& )
{
  return true;
}

void qlHistoricalRatesAnalysisDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, correlation::qlHistoricalRatesAnalysis&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlHistoricalRatesAnalysisDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlHistoricalRatesAnalysisDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlHistoricalRatesAnalysisDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlHistoricalRatesAnalysisDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlHistoricalRatesAnalysisDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlMarketModelLmLinearExponentialCorrelationModelDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   correlation::qlMarketModelLmLinearExponentialCorrelationModelDataReader_var obj_dr
     = correlation::qlMarketModelLmLinearExponentialCorrelationModelDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlMarketModelLmLinearExponentialCorrelationModelDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    correlation::qlMarketModelLmLinearExponentialCorrelationModel obj;
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

              returnObject = QuantLibAddinCpp::qlMarketModelLmLinearExponentialCorrelationModel ( 
              obj.ObjectId.in(),
              static_cast<long>(obj.Size),
              static_cast<double>(obj.Rho),
              static_cast<double>(obj.Beta),
              static_cast<long>(obj.Factors),
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
       std::string err = "ERROR: read qlMarketModelLmLinearExponentialCorrelationModel: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlMarketModelLmLinearExponentialCorrelationModelDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMarketModelLmLinearExponentialCorrelationModelDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlMarketModelLmLinearExponentialCorrelationModelDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMarketModelLmLinearExponentialCorrelationModelDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlMarketModelLmLinearExponentialCorrelationModelDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMarketModelLmLinearExponentialCorrelationModelDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlMarketModelLmLinearExponentialCorrelationModelDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMarketModelLmLinearExponentialCorrelationModelDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlMarketModelLmLinearExponentialCorrelationModelDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMarketModelLmLinearExponentialCorrelationModelDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlMarketModelLmLinearExponentialCorrelationModelDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMarketModelLmLinearExponentialCorrelationModelDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlMarketModelLmLinearExponentialCorrelationModelDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlMarketModelLmLinearExponentialCorrelationModelDataReaderListenerImpl::on_reading_start\n")));
}

void qlMarketModelLmLinearExponentialCorrelationModelDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlMarketModelLmLinearExponentialCorrelationModelDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlMarketModelLmLinearExponentialCorrelationModelDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, correlation::qlMarketModelLmLinearExponentialCorrelationModel& )
{
  return true;
}

bool qlMarketModelLmLinearExponentialCorrelationModelDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, correlation::qlMarketModelLmLinearExponentialCorrelationModel&, std::string& )
{
  return true;
}

void qlMarketModelLmLinearExponentialCorrelationModelDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, correlation::qlMarketModelLmLinearExponentialCorrelationModel&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMarketModelLmLinearExponentialCorrelationModelDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlMarketModelLmLinearExponentialCorrelationModelDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMarketModelLmLinearExponentialCorrelationModelDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlMarketModelLmLinearExponentialCorrelationModelDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlMarketModelLmLinearExponentialCorrelationModelDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}
}
