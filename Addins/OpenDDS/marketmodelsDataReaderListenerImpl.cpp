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

#include "marketmodelsDataReaderListenerImpl.hpp"

#include <qldds_convert_utils.h>

namespace marketmodels {

void qlAbcdVolDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   marketmodels::qlAbcdVolDataReader_var obj_dr
     = marketmodels::qlAbcdVolDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlAbcdVolDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    marketmodels::qlAbcdVol obj;
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

              returnObject = QuantLibAddinCpp::qlAbcdVol ( 
              obj.ObjectId.in(),
              static_cast<double>(obj.A),
              static_cast<double>(obj.B),
              static_cast<double>(obj.C),
              static_cast<double>(obj.D),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.Ks),
              obj.Correlations.in(),
              obj.EvolutionDescription.in(),
              static_cast<long>(obj.Factors),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.InitialRates),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.Displacements),
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
       std::string err = "ERROR: read qlAbcdVol: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlAbcdVolDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlAbcdVolDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlAbcdVolDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlAbcdVolDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlAbcdVolDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlAbcdVolDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlAbcdVolDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlAbcdVolDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlAbcdVolDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlAbcdVolDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlAbcdVolDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlAbcdVolDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlAbcdVolDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlAbcdVolDataReaderListenerImpl::on_reading_start\n")));
}

void qlAbcdVolDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlAbcdVolDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlAbcdVolDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, marketmodels::qlAbcdVol& )
{
  return true;
}

bool qlAbcdVolDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, marketmodels::qlAbcdVol&, std::string& )
{
  return true;
}

void qlAbcdVolDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, marketmodels::qlAbcdVol&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlAbcdVolDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlAbcdVolDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlAbcdVolDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlAbcdVolDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlAbcdVolDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlCotSwapToFwdAdapterDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   marketmodels::qlCotSwapToFwdAdapterDataReader_var obj_dr
     = marketmodels::qlCotSwapToFwdAdapterDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlCotSwapToFwdAdapterDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    marketmodels::qlCotSwapToFwdAdapter obj;
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

              returnObject = QuantLibAddinCpp::qlCotSwapToFwdAdapter ( 
              obj.ObjectId.in(),
              obj.CoterminalModel.in(),
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
       std::string err = "ERROR: read qlCotSwapToFwdAdapter: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlCotSwapToFwdAdapterDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCotSwapToFwdAdapterDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlCotSwapToFwdAdapterDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCotSwapToFwdAdapterDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlCotSwapToFwdAdapterDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCotSwapToFwdAdapterDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlCotSwapToFwdAdapterDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCotSwapToFwdAdapterDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlCotSwapToFwdAdapterDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCotSwapToFwdAdapterDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlCotSwapToFwdAdapterDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCotSwapToFwdAdapterDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlCotSwapToFwdAdapterDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlCotSwapToFwdAdapterDataReaderListenerImpl::on_reading_start\n")));
}

void qlCotSwapToFwdAdapterDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlCotSwapToFwdAdapterDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlCotSwapToFwdAdapterDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, marketmodels::qlCotSwapToFwdAdapter& )
{
  return true;
}

bool qlCotSwapToFwdAdapterDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, marketmodels::qlCotSwapToFwdAdapter&, std::string& )
{
  return true;
}

void qlCotSwapToFwdAdapterDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, marketmodels::qlCotSwapToFwdAdapter&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCotSwapToFwdAdapterDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlCotSwapToFwdAdapterDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCotSwapToFwdAdapterDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlCotSwapToFwdAdapterDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCotSwapToFwdAdapterDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlFlatVolDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   marketmodels::qlFlatVolDataReader_var obj_dr
     = marketmodels::qlFlatVolDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlFlatVolDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    marketmodels::qlFlatVol obj;
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

              returnObject = QuantLibAddinCpp::qlFlatVol ( 
              obj.ObjectId.in(),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.Volatilities),
              obj.Correlations.in(),
              obj.EvolutionDescription.in(),
              static_cast<long>(obj.Factors),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.InitialRates),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.Displacements),
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
       std::string err = "ERROR: read qlFlatVol: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlFlatVolDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFlatVolDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlFlatVolDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFlatVolDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlFlatVolDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFlatVolDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlFlatVolDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFlatVolDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlFlatVolDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFlatVolDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlFlatVolDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFlatVolDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlFlatVolDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlFlatVolDataReaderListenerImpl::on_reading_start\n")));
}

void qlFlatVolDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlFlatVolDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlFlatVolDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, marketmodels::qlFlatVol& )
{
  return true;
}

bool qlFlatVolDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, marketmodels::qlFlatVol&, std::string& )
{
  return true;
}

void qlFlatVolDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, marketmodels::qlFlatVol&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFlatVolDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlFlatVolDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFlatVolDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlFlatVolDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFlatVolDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlFlatVolFactoryDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   marketmodels::qlFlatVolFactoryDataReader_var obj_dr
     = marketmodels::qlFlatVolFactoryDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlFlatVolFactoryDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    marketmodels::qlFlatVolFactory obj;
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

              returnObject = QuantLibAddinCpp::qlFlatVolFactory ( 
              obj.ObjectId.in(),
              static_cast<double>(obj.LongTermCorr),
              static_cast<double>(obj.Beta),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.Times),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.Volatilities),
              obj.YieldCurve.in(),
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
       std::string err = "ERROR: read qlFlatVolFactory: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlFlatVolFactoryDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFlatVolFactoryDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlFlatVolFactoryDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFlatVolFactoryDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlFlatVolFactoryDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFlatVolFactoryDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlFlatVolFactoryDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFlatVolFactoryDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlFlatVolFactoryDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFlatVolFactoryDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlFlatVolFactoryDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFlatVolFactoryDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlFlatVolFactoryDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlFlatVolFactoryDataReaderListenerImpl::on_reading_start\n")));
}

void qlFlatVolFactoryDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlFlatVolFactoryDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlFlatVolFactoryDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, marketmodels::qlFlatVolFactory& )
{
  return true;
}

bool qlFlatVolFactoryDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, marketmodels::qlFlatVolFactory&, std::string& )
{
  return true;
}

void qlFlatVolFactoryDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, marketmodels::qlFlatVolFactory&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFlatVolFactoryDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlFlatVolFactoryDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFlatVolFactoryDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlFlatVolFactoryDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFlatVolFactoryDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlFwdPeriodAdapterDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   marketmodels::qlFwdPeriodAdapterDataReader_var obj_dr
     = marketmodels::qlFwdPeriodAdapterDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlFwdPeriodAdapterDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    marketmodels::qlFwdPeriodAdapter obj;
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

              returnObject = QuantLibAddinCpp::qlFwdPeriodAdapter ( 
              obj.ObjectId.in(),
              obj.LargeModel.in(),
              static_cast<long>(obj.Period),
              static_cast<long>(obj.Offset),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.Displacements),
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
       std::string err = "ERROR: read qlFwdPeriodAdapter: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlFwdPeriodAdapterDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFwdPeriodAdapterDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlFwdPeriodAdapterDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFwdPeriodAdapterDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlFwdPeriodAdapterDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFwdPeriodAdapterDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlFwdPeriodAdapterDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFwdPeriodAdapterDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlFwdPeriodAdapterDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFwdPeriodAdapterDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlFwdPeriodAdapterDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFwdPeriodAdapterDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlFwdPeriodAdapterDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlFwdPeriodAdapterDataReaderListenerImpl::on_reading_start\n")));
}

void qlFwdPeriodAdapterDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlFwdPeriodAdapterDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlFwdPeriodAdapterDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, marketmodels::qlFwdPeriodAdapter& )
{
  return true;
}

bool qlFwdPeriodAdapterDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, marketmodels::qlFwdPeriodAdapter&, std::string& )
{
  return true;
}

void qlFwdPeriodAdapterDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, marketmodels::qlFwdPeriodAdapter&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFwdPeriodAdapterDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlFwdPeriodAdapterDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFwdPeriodAdapterDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlFwdPeriodAdapterDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFwdPeriodAdapterDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlFwdToCotSwapAdapterDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   marketmodels::qlFwdToCotSwapAdapterDataReader_var obj_dr
     = marketmodels::qlFwdToCotSwapAdapterDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlFwdToCotSwapAdapterDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    marketmodels::qlFwdToCotSwapAdapter obj;
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

              returnObject = QuantLibAddinCpp::qlFwdToCotSwapAdapter ( 
              obj.ObjectId.in(),
              obj.ForwardModel.in(),
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
       std::string err = "ERROR: read qlFwdToCotSwapAdapter: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlFwdToCotSwapAdapterDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFwdToCotSwapAdapterDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlFwdToCotSwapAdapterDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFwdToCotSwapAdapterDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlFwdToCotSwapAdapterDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFwdToCotSwapAdapterDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlFwdToCotSwapAdapterDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFwdToCotSwapAdapterDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlFwdToCotSwapAdapterDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFwdToCotSwapAdapterDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlFwdToCotSwapAdapterDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFwdToCotSwapAdapterDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlFwdToCotSwapAdapterDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlFwdToCotSwapAdapterDataReaderListenerImpl::on_reading_start\n")));
}

void qlFwdToCotSwapAdapterDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlFwdToCotSwapAdapterDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlFwdToCotSwapAdapterDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, marketmodels::qlFwdToCotSwapAdapter& )
{
  return true;
}

bool qlFwdToCotSwapAdapterDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, marketmodels::qlFwdToCotSwapAdapter&, std::string& )
{
  return true;
}

void qlFwdToCotSwapAdapterDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, marketmodels::qlFwdToCotSwapAdapter&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFwdToCotSwapAdapterDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlFwdToCotSwapAdapterDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFwdToCotSwapAdapterDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlFwdToCotSwapAdapterDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFwdToCotSwapAdapterDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlPseudoRootFacadeDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   marketmodels::qlPseudoRootFacadeDataReader_var obj_dr
     = marketmodels::qlPseudoRootFacadeDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlPseudoRootFacadeDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    marketmodels::qlPseudoRootFacade obj;
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

              returnObject = QuantLibAddinCpp::qlPseudoRootFacade ( 
              obj.ObjectId.in(),
              obj.Calibrator.in(),
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
       std::string err = "ERROR: read qlPseudoRootFacade: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlPseudoRootFacadeDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlPseudoRootFacadeDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlPseudoRootFacadeDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlPseudoRootFacadeDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlPseudoRootFacadeDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlPseudoRootFacadeDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlPseudoRootFacadeDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlPseudoRootFacadeDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlPseudoRootFacadeDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlPseudoRootFacadeDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlPseudoRootFacadeDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlPseudoRootFacadeDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlPseudoRootFacadeDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlPseudoRootFacadeDataReaderListenerImpl::on_reading_start\n")));
}

void qlPseudoRootFacadeDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlPseudoRootFacadeDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlPseudoRootFacadeDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, marketmodels::qlPseudoRootFacade& )
{
  return true;
}

bool qlPseudoRootFacadeDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, marketmodels::qlPseudoRootFacade&, std::string& )
{
  return true;
}

void qlPseudoRootFacadeDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, marketmodels::qlPseudoRootFacade&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlPseudoRootFacadeDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlPseudoRootFacadeDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlPseudoRootFacadeDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlPseudoRootFacadeDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlPseudoRootFacadeDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}
}
