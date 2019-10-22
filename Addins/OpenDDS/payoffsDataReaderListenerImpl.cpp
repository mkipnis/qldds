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

#include "payoffsDataReaderListenerImpl.hpp"

#include <qldds_convert_utils.h>
#include <ace/Mutex.h>

namespace payoffs {

void qlDoubleStickyRatchetPayoffDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   payoffs::qlDoubleStickyRatchetPayoffDataReader_var obj_dr
     = payoffs::qlDoubleStickyRatchetPayoffDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlDoubleStickyRatchetPayoffDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    payoffs::qlDoubleStickyRatchetPayoff obj;
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

              returnObject = QuantLibAddinCpp::qlDoubleStickyRatchetPayoff ( 
              obj.ObjectId.in(),
              static_cast<double>(obj.Type1),
              static_cast<double>(obj.Type2),
              static_cast<double>(obj.Gearing1),
              static_cast<double>(obj.Gearing2),
              static_cast<double>(obj.Gearing3),
              static_cast<double>(obj.Spread1),
              static_cast<double>(obj.Spread2),
              static_cast<double>(obj.Spread3),
              static_cast<double>(obj.InitialValue1),
              static_cast<double>(obj.InitialValue2),
              static_cast<double>(obj.AccrualFactor),
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
       std::string err = "ERROR: read qlDoubleStickyRatchetPayoff: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlDoubleStickyRatchetPayoffDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDoubleStickyRatchetPayoffDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlDoubleStickyRatchetPayoffDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDoubleStickyRatchetPayoffDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlDoubleStickyRatchetPayoffDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDoubleStickyRatchetPayoffDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlDoubleStickyRatchetPayoffDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDoubleStickyRatchetPayoffDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlDoubleStickyRatchetPayoffDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDoubleStickyRatchetPayoffDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlDoubleStickyRatchetPayoffDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDoubleStickyRatchetPayoffDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlDoubleStickyRatchetPayoffDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlDoubleStickyRatchetPayoffDataReaderListenerImpl::on_reading_start\n")));
}

void qlDoubleStickyRatchetPayoffDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlDoubleStickyRatchetPayoffDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlDoubleStickyRatchetPayoffDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, payoffs::qlDoubleStickyRatchetPayoff& )
{
  return true;
}

bool qlDoubleStickyRatchetPayoffDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, payoffs::qlDoubleStickyRatchetPayoff&, std::string& )
{
  return true;
}

void qlDoubleStickyRatchetPayoffDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, payoffs::qlDoubleStickyRatchetPayoff&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDoubleStickyRatchetPayoffDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlDoubleStickyRatchetPayoffDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDoubleStickyRatchetPayoffDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlDoubleStickyRatchetPayoffDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlDoubleStickyRatchetPayoffDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlRatchetMaxPayoffDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   payoffs::qlRatchetMaxPayoffDataReader_var obj_dr
     = payoffs::qlRatchetMaxPayoffDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlRatchetMaxPayoffDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    payoffs::qlRatchetMaxPayoff obj;
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

              returnObject = QuantLibAddinCpp::qlRatchetMaxPayoff ( 
              obj.ObjectId.in(),
              static_cast<double>(obj.Gearing1),
              static_cast<double>(obj.Gearing2),
              static_cast<double>(obj.Gearing3),
              static_cast<double>(obj.Spread1),
              static_cast<double>(obj.Spread2),
              static_cast<double>(obj.Spread3),
              static_cast<double>(obj.InitialValue1),
              static_cast<double>(obj.InitialValue2),
              static_cast<double>(obj.AccrualFactor),
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
       std::string err = "ERROR: read qlRatchetMaxPayoff: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlRatchetMaxPayoffDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRatchetMaxPayoffDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlRatchetMaxPayoffDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRatchetMaxPayoffDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlRatchetMaxPayoffDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRatchetMaxPayoffDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlRatchetMaxPayoffDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRatchetMaxPayoffDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlRatchetMaxPayoffDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRatchetMaxPayoffDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlRatchetMaxPayoffDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRatchetMaxPayoffDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlRatchetMaxPayoffDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlRatchetMaxPayoffDataReaderListenerImpl::on_reading_start\n")));
}

void qlRatchetMaxPayoffDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlRatchetMaxPayoffDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlRatchetMaxPayoffDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, payoffs::qlRatchetMaxPayoff& )
{
  return true;
}

bool qlRatchetMaxPayoffDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, payoffs::qlRatchetMaxPayoff&, std::string& )
{
  return true;
}

void qlRatchetMaxPayoffDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, payoffs::qlRatchetMaxPayoff&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRatchetMaxPayoffDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlRatchetMaxPayoffDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRatchetMaxPayoffDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlRatchetMaxPayoffDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRatchetMaxPayoffDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlRatchetMinPayoffDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   payoffs::qlRatchetMinPayoffDataReader_var obj_dr
     = payoffs::qlRatchetMinPayoffDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlRatchetMinPayoffDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    payoffs::qlRatchetMinPayoff obj;
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

              returnObject = QuantLibAddinCpp::qlRatchetMinPayoff ( 
              obj.ObjectId.in(),
              static_cast<double>(obj.Gearing1),
              static_cast<double>(obj.Gearing2),
              static_cast<double>(obj.Gearing3),
              static_cast<double>(obj.Spread1),
              static_cast<double>(obj.Spread2),
              static_cast<double>(obj.Spread3),
              static_cast<double>(obj.InitialValue1),
              static_cast<double>(obj.InitialValue2),
              static_cast<double>(obj.AccrualFactor),
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
       std::string err = "ERROR: read qlRatchetMinPayoff: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlRatchetMinPayoffDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRatchetMinPayoffDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlRatchetMinPayoffDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRatchetMinPayoffDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlRatchetMinPayoffDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRatchetMinPayoffDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlRatchetMinPayoffDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRatchetMinPayoffDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlRatchetMinPayoffDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRatchetMinPayoffDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlRatchetMinPayoffDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRatchetMinPayoffDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlRatchetMinPayoffDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlRatchetMinPayoffDataReaderListenerImpl::on_reading_start\n")));
}

void qlRatchetMinPayoffDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlRatchetMinPayoffDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlRatchetMinPayoffDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, payoffs::qlRatchetMinPayoff& )
{
  return true;
}

bool qlRatchetMinPayoffDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, payoffs::qlRatchetMinPayoff&, std::string& )
{
  return true;
}

void qlRatchetMinPayoffDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, payoffs::qlRatchetMinPayoff&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRatchetMinPayoffDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlRatchetMinPayoffDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRatchetMinPayoffDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlRatchetMinPayoffDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRatchetMinPayoffDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlRatchetPayoffDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   payoffs::qlRatchetPayoffDataReader_var obj_dr
     = payoffs::qlRatchetPayoffDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlRatchetPayoffDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    payoffs::qlRatchetPayoff obj;
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

              returnObject = QuantLibAddinCpp::qlRatchetPayoff ( 
              obj.ObjectId.in(),
              static_cast<double>(obj.Gearing1),
              static_cast<double>(obj.Gearing2),
              static_cast<double>(obj.Spread1),
              static_cast<double>(obj.Spread2),
              static_cast<double>(obj.InitialValue),
              static_cast<double>(obj.AccrualFactor),
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
       std::string err = "ERROR: read qlRatchetPayoff: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlRatchetPayoffDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRatchetPayoffDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlRatchetPayoffDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRatchetPayoffDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlRatchetPayoffDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRatchetPayoffDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlRatchetPayoffDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRatchetPayoffDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlRatchetPayoffDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRatchetPayoffDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlRatchetPayoffDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRatchetPayoffDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlRatchetPayoffDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlRatchetPayoffDataReaderListenerImpl::on_reading_start\n")));
}

void qlRatchetPayoffDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlRatchetPayoffDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlRatchetPayoffDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, payoffs::qlRatchetPayoff& )
{
  return true;
}

bool qlRatchetPayoffDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, payoffs::qlRatchetPayoff&, std::string& )
{
  return true;
}

void qlRatchetPayoffDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, payoffs::qlRatchetPayoff&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRatchetPayoffDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlRatchetPayoffDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRatchetPayoffDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlRatchetPayoffDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRatchetPayoffDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlStickyMaxPayoffDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   payoffs::qlStickyMaxPayoffDataReader_var obj_dr
     = payoffs::qlStickyMaxPayoffDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlStickyMaxPayoffDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    payoffs::qlStickyMaxPayoff obj;
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

              returnObject = QuantLibAddinCpp::qlStickyMaxPayoff ( 
              obj.ObjectId.in(),
              static_cast<double>(obj.Gearing1),
              static_cast<double>(obj.Gearing2),
              static_cast<double>(obj.Gearing3),
              static_cast<double>(obj.Spread1),
              static_cast<double>(obj.Spread2),
              static_cast<double>(obj.Spread3),
              static_cast<double>(obj.InitialValue1),
              static_cast<double>(obj.InitialValue2),
              static_cast<double>(obj.AccrualFactor),
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
       std::string err = "ERROR: read qlStickyMaxPayoff: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlStickyMaxPayoffDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStickyMaxPayoffDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlStickyMaxPayoffDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStickyMaxPayoffDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlStickyMaxPayoffDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStickyMaxPayoffDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlStickyMaxPayoffDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStickyMaxPayoffDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlStickyMaxPayoffDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStickyMaxPayoffDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlStickyMaxPayoffDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStickyMaxPayoffDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlStickyMaxPayoffDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlStickyMaxPayoffDataReaderListenerImpl::on_reading_start\n")));
}

void qlStickyMaxPayoffDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlStickyMaxPayoffDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlStickyMaxPayoffDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, payoffs::qlStickyMaxPayoff& )
{
  return true;
}

bool qlStickyMaxPayoffDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, payoffs::qlStickyMaxPayoff&, std::string& )
{
  return true;
}

void qlStickyMaxPayoffDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, payoffs::qlStickyMaxPayoff&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStickyMaxPayoffDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlStickyMaxPayoffDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStickyMaxPayoffDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlStickyMaxPayoffDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStickyMaxPayoffDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlStickyMinPayoffDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   payoffs::qlStickyMinPayoffDataReader_var obj_dr
     = payoffs::qlStickyMinPayoffDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlStickyMinPayoffDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    payoffs::qlStickyMinPayoff obj;
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

              returnObject = QuantLibAddinCpp::qlStickyMinPayoff ( 
              obj.ObjectId.in(),
              static_cast<double>(obj.Gearing1),
              static_cast<double>(obj.Gearing2),
              static_cast<double>(obj.Gearing3),
              static_cast<double>(obj.Spread1),
              static_cast<double>(obj.Spread2),
              static_cast<double>(obj.Spread3),
              static_cast<double>(obj.InitialValue1),
              static_cast<double>(obj.InitialValue2),
              static_cast<double>(obj.AccrualFactor),
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
       std::string err = "ERROR: read qlStickyMinPayoff: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlStickyMinPayoffDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStickyMinPayoffDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlStickyMinPayoffDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStickyMinPayoffDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlStickyMinPayoffDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStickyMinPayoffDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlStickyMinPayoffDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStickyMinPayoffDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlStickyMinPayoffDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStickyMinPayoffDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlStickyMinPayoffDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStickyMinPayoffDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlStickyMinPayoffDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlStickyMinPayoffDataReaderListenerImpl::on_reading_start\n")));
}

void qlStickyMinPayoffDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlStickyMinPayoffDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlStickyMinPayoffDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, payoffs::qlStickyMinPayoff& )
{
  return true;
}

bool qlStickyMinPayoffDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, payoffs::qlStickyMinPayoff&, std::string& )
{
  return true;
}

void qlStickyMinPayoffDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, payoffs::qlStickyMinPayoff&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStickyMinPayoffDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlStickyMinPayoffDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStickyMinPayoffDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlStickyMinPayoffDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStickyMinPayoffDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlStickyPayoffDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   payoffs::qlStickyPayoffDataReader_var obj_dr
     = payoffs::qlStickyPayoffDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlStickyPayoffDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    payoffs::qlStickyPayoff obj;
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

              returnObject = QuantLibAddinCpp::qlStickyPayoff ( 
              obj.ObjectId.in(),
              static_cast<double>(obj.Gearing1),
              static_cast<double>(obj.Gearing2),
              static_cast<double>(obj.Spread1),
              static_cast<double>(obj.Spread2),
              static_cast<double>(obj.InitialValue),
              static_cast<double>(obj.AccrualFactor),
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
       std::string err = "ERROR: read qlStickyPayoff: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlStickyPayoffDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStickyPayoffDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlStickyPayoffDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStickyPayoffDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlStickyPayoffDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStickyPayoffDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlStickyPayoffDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStickyPayoffDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlStickyPayoffDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStickyPayoffDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlStickyPayoffDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStickyPayoffDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlStickyPayoffDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlStickyPayoffDataReaderListenerImpl::on_reading_start\n")));
}

void qlStickyPayoffDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlStickyPayoffDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlStickyPayoffDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, payoffs::qlStickyPayoff& )
{
  return true;
}

bool qlStickyPayoffDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, payoffs::qlStickyPayoff&, std::string& )
{
  return true;
}

void qlStickyPayoffDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, payoffs::qlStickyPayoff&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStickyPayoffDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlStickyPayoffDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStickyPayoffDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlStickyPayoffDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStickyPayoffDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlStrikedTypePayoffDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   payoffs::qlStrikedTypePayoffDataReader_var obj_dr
     = payoffs::qlStrikedTypePayoffDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlStrikedTypePayoffDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    payoffs::qlStrikedTypePayoff obj;
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

              returnObject = QuantLibAddinCpp::qlStrikedTypePayoff ( 
              obj.ObjectId.in(),
              obj.PayoffID.in(),
              obj.OptionType.in(),
              static_cast<double>(obj.Strike),
              static_cast<double>(obj.ThirdParameter),
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
       std::string err = "ERROR: read qlStrikedTypePayoff: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlStrikedTypePayoffDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStrikedTypePayoffDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlStrikedTypePayoffDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStrikedTypePayoffDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlStrikedTypePayoffDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStrikedTypePayoffDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlStrikedTypePayoffDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStrikedTypePayoffDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlStrikedTypePayoffDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStrikedTypePayoffDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlStrikedTypePayoffDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStrikedTypePayoffDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlStrikedTypePayoffDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlStrikedTypePayoffDataReaderListenerImpl::on_reading_start\n")));
}

void qlStrikedTypePayoffDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlStrikedTypePayoffDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlStrikedTypePayoffDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, payoffs::qlStrikedTypePayoff& )
{
  return true;
}

bool qlStrikedTypePayoffDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, payoffs::qlStrikedTypePayoff&, std::string& )
{
  return true;
}

void qlStrikedTypePayoffDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, payoffs::qlStrikedTypePayoff&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStrikedTypePayoffDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlStrikedTypePayoffDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStrikedTypePayoffDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlStrikedTypePayoffDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStrikedTypePayoffDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}
}
