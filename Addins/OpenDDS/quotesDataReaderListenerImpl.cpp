/*
   Copyright (C) 2016 Mike Kipnis

   This file is part of QLDDS, a free-software/open-source library
   for utilization of QuantLib in the distributed envrionment via DDS.

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
*/
// This file was generated automatically by qldds_gensrc.py.  If you edit this file
// manually then your changes will be lost the next time gensrc runs.

// This source code file was generated from the following stub:
//      dds.no_nt/gensrc/stubs/stub.opendds.body

#include "quotesDataReaderListenerImpl.hpp"

#include <qldds_convert_utils.h>
#include <ace/Mutex.h>

namespace quotes {

void qlCompositeQuoteDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   quotes::qlCompositeQuoteDataReader_var obj_dr
     = quotes::qlCompositeQuoteDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlCompositeQuoteDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    quotes::qlCompositeQuote obj;
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

              returnObject = QuantLibAddinCpp::qlCompositeQuote ( 
              obj.ObjectId.in(),
              obj.Element1 ,
              obj.Element2 ,
              obj.Operator.in(),
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
       std::string err = "ERROR: read qlCompositeQuote: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlCompositeQuoteDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCompositeQuoteDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlCompositeQuoteDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCompositeQuoteDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlCompositeQuoteDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCompositeQuoteDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlCompositeQuoteDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCompositeQuoteDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlCompositeQuoteDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCompositeQuoteDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlCompositeQuoteDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCompositeQuoteDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlCompositeQuoteDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlCompositeQuoteDataReaderListenerImpl::on_reading_start\n")));
}

void qlCompositeQuoteDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlCompositeQuoteDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlCompositeQuoteDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, quotes::qlCompositeQuote& )
{
  return true;
}

bool qlCompositeQuoteDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, quotes::qlCompositeQuote&, std::string& )
{
  return true;
}

void qlCompositeQuoteDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, quotes::qlCompositeQuote&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCompositeQuoteDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlCompositeQuoteDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCompositeQuoteDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlCompositeQuoteDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCompositeQuoteDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlEurodollarFuturesImpliedStdDevQuoteDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   quotes::qlEurodollarFuturesImpliedStdDevQuoteDataReader_var obj_dr
     = quotes::qlEurodollarFuturesImpliedStdDevQuoteDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlEurodollarFuturesImpliedStdDevQuoteDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    quotes::qlEurodollarFuturesImpliedStdDevQuote obj;
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

              returnObject = QuantLibAddinCpp::qlEurodollarFuturesImpliedStdDevQuote ( 
              obj.ObjectId.in(),
              obj.AtmForwardValue ,
              obj.CallPrice ,
              obj.PutPrice ,
              static_cast<double>(obj.Strike),
              static_cast<double>(obj.Guess),
              static_cast<double>(obj.Accuracy),
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
       std::string err = "ERROR: read qlEurodollarFuturesImpliedStdDevQuote: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlEurodollarFuturesImpliedStdDevQuoteDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEurodollarFuturesImpliedStdDevQuoteDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlEurodollarFuturesImpliedStdDevQuoteDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEurodollarFuturesImpliedStdDevQuoteDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlEurodollarFuturesImpliedStdDevQuoteDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEurodollarFuturesImpliedStdDevQuoteDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlEurodollarFuturesImpliedStdDevQuoteDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEurodollarFuturesImpliedStdDevQuoteDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlEurodollarFuturesImpliedStdDevQuoteDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEurodollarFuturesImpliedStdDevQuoteDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlEurodollarFuturesImpliedStdDevQuoteDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEurodollarFuturesImpliedStdDevQuoteDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlEurodollarFuturesImpliedStdDevQuoteDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlEurodollarFuturesImpliedStdDevQuoteDataReaderListenerImpl::on_reading_start\n")));
}

void qlEurodollarFuturesImpliedStdDevQuoteDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlEurodollarFuturesImpliedStdDevQuoteDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlEurodollarFuturesImpliedStdDevQuoteDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, quotes::qlEurodollarFuturesImpliedStdDevQuote& )
{
  return true;
}

bool qlEurodollarFuturesImpliedStdDevQuoteDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, quotes::qlEurodollarFuturesImpliedStdDevQuote&, std::string& )
{
  return true;
}

void qlEurodollarFuturesImpliedStdDevQuoteDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, quotes::qlEurodollarFuturesImpliedStdDevQuote&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEurodollarFuturesImpliedStdDevQuoteDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlEurodollarFuturesImpliedStdDevQuoteDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEurodollarFuturesImpliedStdDevQuoteDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlEurodollarFuturesImpliedStdDevQuoteDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEurodollarFuturesImpliedStdDevQuoteDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlForwardSwapQuoteDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   quotes::qlForwardSwapQuoteDataReader_var obj_dr
     = quotes::qlForwardSwapQuoteDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlForwardSwapQuoteDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    quotes::qlForwardSwapQuote obj;
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

              returnObject = QuantLibAddinCpp::qlForwardSwapQuote ( 
              obj.ObjectId.in(),
              obj.SwapIndex.in(),
              obj.Spread ,
              obj.ForwardStart.in(),
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
       std::string err = "ERROR: read qlForwardSwapQuote: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlForwardSwapQuoteDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlForwardSwapQuoteDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlForwardSwapQuoteDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlForwardSwapQuoteDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlForwardSwapQuoteDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlForwardSwapQuoteDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlForwardSwapQuoteDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlForwardSwapQuoteDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlForwardSwapQuoteDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlForwardSwapQuoteDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlForwardSwapQuoteDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlForwardSwapQuoteDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlForwardSwapQuoteDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlForwardSwapQuoteDataReaderListenerImpl::on_reading_start\n")));
}

void qlForwardSwapQuoteDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlForwardSwapQuoteDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlForwardSwapQuoteDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, quotes::qlForwardSwapQuote& )
{
  return true;
}

bool qlForwardSwapQuoteDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, quotes::qlForwardSwapQuote&, std::string& )
{
  return true;
}

void qlForwardSwapQuoteDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, quotes::qlForwardSwapQuote&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlForwardSwapQuoteDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlForwardSwapQuoteDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlForwardSwapQuoteDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlForwardSwapQuoteDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlForwardSwapQuoteDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlForwardValueQuoteDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   quotes::qlForwardValueQuoteDataReader_var obj_dr
     = quotes::qlForwardValueQuoteDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlForwardValueQuoteDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    quotes::qlForwardValueQuote obj;
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

              returnObject = QuantLibAddinCpp::qlForwardValueQuote ( 
              obj.ObjectId.in(),
              obj.IborIndex.in(),
              qldds_utils::from_iso_string(obj.FixingDate.in() ),
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
       std::string err = "ERROR: read qlForwardValueQuote: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlForwardValueQuoteDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlForwardValueQuoteDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlForwardValueQuoteDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlForwardValueQuoteDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlForwardValueQuoteDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlForwardValueQuoteDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlForwardValueQuoteDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlForwardValueQuoteDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlForwardValueQuoteDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlForwardValueQuoteDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlForwardValueQuoteDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlForwardValueQuoteDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlForwardValueQuoteDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlForwardValueQuoteDataReaderListenerImpl::on_reading_start\n")));
}

void qlForwardValueQuoteDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlForwardValueQuoteDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlForwardValueQuoteDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, quotes::qlForwardValueQuote& )
{
  return true;
}

bool qlForwardValueQuoteDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, quotes::qlForwardValueQuote&, std::string& )
{
  return true;
}

void qlForwardValueQuoteDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, quotes::qlForwardValueQuote&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlForwardValueQuoteDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlForwardValueQuoteDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlForwardValueQuoteDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlForwardValueQuoteDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlForwardValueQuoteDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlFuturesConvAdjustmentQuoteDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   quotes::qlFuturesConvAdjustmentQuoteDataReader_var obj_dr
     = quotes::qlFuturesConvAdjustmentQuoteDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlFuturesConvAdjustmentQuoteDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    quotes::qlFuturesConvAdjustmentQuote obj;
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

              returnObject = QuantLibAddinCpp::qlFuturesConvAdjustmentQuote ( 
              obj.ObjectId.in(),
              obj.IborIndex.in(),
              obj.ImmCode.in(),
              obj.FuturesQuote ,
              obj.Volatility ,
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
       std::string err = "ERROR: read qlFuturesConvAdjustmentQuote: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlFuturesConvAdjustmentQuoteDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFuturesConvAdjustmentQuoteDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlFuturesConvAdjustmentQuoteDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFuturesConvAdjustmentQuoteDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlFuturesConvAdjustmentQuoteDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFuturesConvAdjustmentQuoteDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlFuturesConvAdjustmentQuoteDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFuturesConvAdjustmentQuoteDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlFuturesConvAdjustmentQuoteDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFuturesConvAdjustmentQuoteDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlFuturesConvAdjustmentQuoteDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFuturesConvAdjustmentQuoteDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlFuturesConvAdjustmentQuoteDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlFuturesConvAdjustmentQuoteDataReaderListenerImpl::on_reading_start\n")));
}

void qlFuturesConvAdjustmentQuoteDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlFuturesConvAdjustmentQuoteDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlFuturesConvAdjustmentQuoteDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, quotes::qlFuturesConvAdjustmentQuote& )
{
  return true;
}

bool qlFuturesConvAdjustmentQuoteDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, quotes::qlFuturesConvAdjustmentQuote&, std::string& )
{
  return true;
}

void qlFuturesConvAdjustmentQuoteDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, quotes::qlFuturesConvAdjustmentQuote&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFuturesConvAdjustmentQuoteDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlFuturesConvAdjustmentQuoteDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFuturesConvAdjustmentQuoteDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlFuturesConvAdjustmentQuoteDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFuturesConvAdjustmentQuoteDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlImpliedStdDevQuoteDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   quotes::qlImpliedStdDevQuoteDataReader_var obj_dr
     = quotes::qlImpliedStdDevQuoteDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlImpliedStdDevQuoteDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    quotes::qlImpliedStdDevQuote obj;
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

              returnObject = QuantLibAddinCpp::qlImpliedStdDevQuote ( 
              obj.ObjectId.in(),
              obj.OptionType.in(),
              obj.AtmForwardValue ,
              obj.OptionPrice ,
              static_cast<double>(obj.Strike),
              static_cast<double>(obj.Guess),
              static_cast<double>(obj.Accuracy),
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
       std::string err = "ERROR: read qlImpliedStdDevQuote: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlImpliedStdDevQuoteDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlImpliedStdDevQuoteDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlImpliedStdDevQuoteDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlImpliedStdDevQuoteDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlImpliedStdDevQuoteDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlImpliedStdDevQuoteDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlImpliedStdDevQuoteDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlImpliedStdDevQuoteDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlImpliedStdDevQuoteDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlImpliedStdDevQuoteDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlImpliedStdDevQuoteDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlImpliedStdDevQuoteDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlImpliedStdDevQuoteDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlImpliedStdDevQuoteDataReaderListenerImpl::on_reading_start\n")));
}

void qlImpliedStdDevQuoteDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlImpliedStdDevQuoteDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlImpliedStdDevQuoteDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, quotes::qlImpliedStdDevQuote& )
{
  return true;
}

bool qlImpliedStdDevQuoteDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, quotes::qlImpliedStdDevQuote&, std::string& )
{
  return true;
}

void qlImpliedStdDevQuoteDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, quotes::qlImpliedStdDevQuote&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlImpliedStdDevQuoteDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlImpliedStdDevQuoteDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlImpliedStdDevQuoteDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlImpliedStdDevQuoteDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlImpliedStdDevQuoteDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlLastFixingQuoteDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   quotes::qlLastFixingQuoteDataReader_var obj_dr
     = quotes::qlLastFixingQuoteDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlLastFixingQuoteDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    quotes::qlLastFixingQuote obj;
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

              returnObject = QuantLibAddinCpp::qlLastFixingQuote ( 
              obj.ObjectId.in(),
              obj.Index.in(),
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
       std::string err = "ERROR: read qlLastFixingQuote: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlLastFixingQuoteDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlLastFixingQuoteDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlLastFixingQuoteDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlLastFixingQuoteDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlLastFixingQuoteDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlLastFixingQuoteDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlLastFixingQuoteDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlLastFixingQuoteDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlLastFixingQuoteDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlLastFixingQuoteDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlLastFixingQuoteDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlLastFixingQuoteDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlLastFixingQuoteDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlLastFixingQuoteDataReaderListenerImpl::on_reading_start\n")));
}

void qlLastFixingQuoteDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlLastFixingQuoteDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlLastFixingQuoteDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, quotes::qlLastFixingQuote& )
{
  return true;
}

bool qlLastFixingQuoteDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, quotes::qlLastFixingQuote&, std::string& )
{
  return true;
}

void qlLastFixingQuoteDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, quotes::qlLastFixingQuote&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlLastFixingQuoteDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlLastFixingQuoteDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlLastFixingQuoteDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlLastFixingQuoteDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlLastFixingQuoteDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlRelinkableHandleQuoteDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   quotes::qlRelinkableHandleQuoteDataReader_var obj_dr
     = quotes::qlRelinkableHandleQuoteDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlRelinkableHandleQuoteDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    quotes::qlRelinkableHandleQuote obj;
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

              returnObject = QuantLibAddinCpp::qlRelinkableHandleQuote ( 
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
       std::string err = "ERROR: read qlRelinkableHandleQuote: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlRelinkableHandleQuoteDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRelinkableHandleQuoteDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlRelinkableHandleQuoteDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRelinkableHandleQuoteDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlRelinkableHandleQuoteDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRelinkableHandleQuoteDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlRelinkableHandleQuoteDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRelinkableHandleQuoteDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlRelinkableHandleQuoteDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRelinkableHandleQuoteDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlRelinkableHandleQuoteDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRelinkableHandleQuoteDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlRelinkableHandleQuoteDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlRelinkableHandleQuoteDataReaderListenerImpl::on_reading_start\n")));
}

void qlRelinkableHandleQuoteDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlRelinkableHandleQuoteDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlRelinkableHandleQuoteDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, quotes::qlRelinkableHandleQuote& )
{
  return true;
}

bool qlRelinkableHandleQuoteDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, quotes::qlRelinkableHandleQuote&, std::string& )
{
  return true;
}

void qlRelinkableHandleQuoteDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, quotes::qlRelinkableHandleQuote&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRelinkableHandleQuoteDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlRelinkableHandleQuoteDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRelinkableHandleQuoteDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlRelinkableHandleQuoteDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRelinkableHandleQuoteDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlSimpleQuoteDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   quotes::qlSimpleQuoteDataReader_var obj_dr
     = quotes::qlSimpleQuoteDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlSimpleQuoteDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    quotes::qlSimpleQuote obj;
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

              returnObject = QuantLibAddinCpp::qlSimpleQuote ( 
              obj.ObjectId.in(),
              static_cast<double>(obj.Value),
              static_cast<double>(obj.TickValue),
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
       std::string err = "ERROR: read qlSimpleQuote: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlSimpleQuoteDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSimpleQuoteDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlSimpleQuoteDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSimpleQuoteDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlSimpleQuoteDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSimpleQuoteDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlSimpleQuoteDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSimpleQuoteDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlSimpleQuoteDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSimpleQuoteDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlSimpleQuoteDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSimpleQuoteDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlSimpleQuoteDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlSimpleQuoteDataReaderListenerImpl::on_reading_start\n")));
}

void qlSimpleQuoteDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlSimpleQuoteDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlSimpleQuoteDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, quotes::qlSimpleQuote& )
{
  return true;
}

bool qlSimpleQuoteDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, quotes::qlSimpleQuote&, std::string& )
{
  return true;
}

void qlSimpleQuoteDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, quotes::qlSimpleQuote&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSimpleQuoteDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlSimpleQuoteDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSimpleQuoteDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlSimpleQuoteDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSimpleQuoteDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlSimpleQuoteSetValueDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   quotes::qlSimpleQuoteSetValueDataReader_var obj_dr
     = quotes::qlSimpleQuoteSetValueDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlSimpleQuoteSetValueDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    quotes::qlSimpleQuoteSetValue obj;
    DDS::SampleInfo si ;
    DDS::ReturnCode_t status = obj_dr->take_next_sample(obj, si) ;

    if ( status == DDS::RETCODE_OK )
    {
      if ( si.valid_data == true )
      {
         ++count;

         if ( pre_quantlib_addin_call( reader, si, obj ) )
         {
            double returnObject;;

            try {

              ACE_Guard<ACE_Mutex> guard( get_ACE_Mutex() );

              returnObject = QuantLibAddinCpp::qlSimpleQuoteSetValue ( 
              obj.ObjectId.in(),
              static_cast<double>(obj.Value),
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
       std::string err = "ERROR: read qlSimpleQuoteSetValue: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlSimpleQuoteSetValueDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSimpleQuoteSetValueDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlSimpleQuoteSetValueDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSimpleQuoteSetValueDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlSimpleQuoteSetValueDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSimpleQuoteSetValueDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlSimpleQuoteSetValueDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSimpleQuoteSetValueDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlSimpleQuoteSetValueDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSimpleQuoteSetValueDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlSimpleQuoteSetValueDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSimpleQuoteSetValueDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlSimpleQuoteSetValueDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlSimpleQuoteSetValueDataReaderListenerImpl::on_reading_start\n")));
}

void qlSimpleQuoteSetValueDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlSimpleQuoteSetValueDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlSimpleQuoteSetValueDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, quotes::qlSimpleQuoteSetValue& )
{
  return true;
}

bool qlSimpleQuoteSetValueDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, quotes::qlSimpleQuoteSetValue&, double& )
{
  return true;
}

void qlSimpleQuoteSetValueDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, quotes::qlSimpleQuoteSetValue&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSimpleQuoteSetValueDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlSimpleQuoteSetValueDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSimpleQuoteSetValueDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlSimpleQuoteSetValueDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSimpleQuoteSetValueDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}
}
