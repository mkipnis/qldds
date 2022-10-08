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
//      git/qldds/gensrc/stubs/stub.opendds.body

#include "qlIndexDataReaderListenerImpl.hpp"

#include <qldds_convert_utils.h>
#include <ace/Mutex.h>

namespace qlIndex {

void qlBMAIndexDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   qlIndex::qlBMAIndexDataReader_var obj_dr
     = qlIndex::qlBMAIndexDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlBMAIndexDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    qlIndex::qlBMAIndex obj;
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

              returnObject = QuantLibAddinCpp::qlBMAIndex ( 
              obj.ObjectId.in(),
              obj.YieldCurve.in(),
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
       std::string err = "ERROR: read qlBMAIndex: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlBMAIndexDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBMAIndexDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlBMAIndexDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBMAIndexDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlBMAIndexDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBMAIndexDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlBMAIndexDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBMAIndexDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlBMAIndexDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBMAIndexDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlBMAIndexDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBMAIndexDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlBMAIndexDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlBMAIndexDataReaderListenerImpl::on_reading_start\n")));
}

void qlBMAIndexDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlBMAIndexDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlBMAIndexDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, qlIndex::qlBMAIndex& )
{
  return true;
}

bool qlBMAIndexDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, qlIndex::qlBMAIndex&, std::string& )
{
  return true;
}

void qlBMAIndexDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, qlIndex::qlBMAIndex&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBMAIndexDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlBMAIndexDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBMAIndexDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlBMAIndexDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlBMAIndexDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlEoniaDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   qlIndex::qlEoniaDataReader_var obj_dr
     = qlIndex::qlEoniaDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlEoniaDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    qlIndex::qlEonia obj;
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

              returnObject = QuantLibAddinCpp::qlEonia ( 
              obj.ObjectId.in(),
              obj.YieldCurve.in(),
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
       std::string err = "ERROR: read qlEonia: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlEoniaDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEoniaDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlEoniaDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEoniaDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlEoniaDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEoniaDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlEoniaDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEoniaDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlEoniaDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEoniaDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlEoniaDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEoniaDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlEoniaDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlEoniaDataReaderListenerImpl::on_reading_start\n")));
}

void qlEoniaDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlEoniaDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlEoniaDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, qlIndex::qlEonia& )
{
  return true;
}

bool qlEoniaDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, qlIndex::qlEonia&, std::string& )
{
  return true;
}

void qlEoniaDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, qlIndex::qlEonia&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEoniaDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlEoniaDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEoniaDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlEoniaDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEoniaDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlEuriborDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   qlIndex::qlEuriborDataReader_var obj_dr
     = qlIndex::qlEuriborDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlEuriborDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    qlIndex::qlEuribor obj;
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

              returnObject = QuantLibAddinCpp::qlEuribor ( 
              obj.ObjectId.in(),
              obj.Tenor.in(),
              obj.YieldCurve.in(),
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
       std::string err = "ERROR: read qlEuribor: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlEuriborDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEuriborDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlEuriborDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEuriborDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlEuriborDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEuriborDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlEuriborDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEuriborDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlEuriborDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEuriborDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlEuriborDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEuriborDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlEuriborDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlEuriborDataReaderListenerImpl::on_reading_start\n")));
}

void qlEuriborDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlEuriborDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlEuriborDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, qlIndex::qlEuribor& )
{
  return true;
}

bool qlEuriborDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, qlIndex::qlEuribor&, std::string& )
{
  return true;
}

void qlEuriborDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, qlIndex::qlEuribor&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEuriborDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlEuriborDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEuriborDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlEuriborDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEuriborDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlEuribor365DataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   qlIndex::qlEuribor365DataReader_var obj_dr
     = qlIndex::qlEuribor365DataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlEuribor365DataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    qlIndex::qlEuribor365 obj;
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

              returnObject = QuantLibAddinCpp::qlEuribor365 ( 
              obj.ObjectId.in(),
              obj.Tenor.in(),
              obj.YieldCurve.in(),
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
       std::string err = "ERROR: read qlEuribor365: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlEuribor365DataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEuribor365DataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlEuribor365DataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEuribor365DataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlEuribor365DataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEuribor365DataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlEuribor365DataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEuribor365DataReaderListenerImpl::on_subscription_matched\n")));
}

void qlEuribor365DataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEuribor365DataReaderListenerImpl::on_sample_rejected\n")));
}

void qlEuribor365DataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEuribor365DataReaderListenerImpl::on_sample_rejected\n")));
}

void qlEuribor365DataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlEuribor365DataReaderListenerImpl::on_reading_start\n")));
}

void qlEuribor365DataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlEuribor365DataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlEuribor365DataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, qlIndex::qlEuribor365& )
{
  return true;
}

bool qlEuribor365DataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, qlIndex::qlEuribor365&, std::string& )
{
  return true;
}

void qlEuribor365DataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, qlIndex::qlEuribor365&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEuribor365DataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlEuribor365DataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEuribor365DataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlEuribor365DataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEuribor365DataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlEuriborSwapDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   qlIndex::qlEuriborSwapDataReader_var obj_dr
     = qlIndex::qlEuriborSwapDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlEuriborSwapDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    qlIndex::qlEuriborSwap obj;
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

              returnObject = QuantLibAddinCpp::qlEuriborSwap ( 
              obj.ObjectId.in(),
              obj.FixingType.in(),
              obj.Tenor.in(),
              obj.FwdCurve.in(),
              obj.DiscCurve.in(),
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
       std::string err = "ERROR: read qlEuriborSwap: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlEuriborSwapDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEuriborSwapDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlEuriborSwapDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEuriborSwapDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlEuriborSwapDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEuriborSwapDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlEuriborSwapDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEuriborSwapDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlEuriborSwapDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEuriborSwapDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlEuriborSwapDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEuriborSwapDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlEuriborSwapDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlEuriborSwapDataReaderListenerImpl::on_reading_start\n")));
}

void qlEuriborSwapDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlEuriborSwapDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlEuriborSwapDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, qlIndex::qlEuriborSwap& )
{
  return true;
}

bool qlEuriborSwapDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, qlIndex::qlEuriborSwap&, std::string& )
{
  return true;
}

void qlEuriborSwapDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, qlIndex::qlEuriborSwap&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEuriborSwapDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlEuriborSwapDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEuriborSwapDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlEuriborSwapDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEuriborSwapDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlEuriborSwapIsdaFixADataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   qlIndex::qlEuriborSwapIsdaFixADataReader_var obj_dr
     = qlIndex::qlEuriborSwapIsdaFixADataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlEuriborSwapIsdaFixADataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    qlIndex::qlEuriborSwapIsdaFixA obj;
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

              returnObject = QuantLibAddinCpp::qlEuriborSwapIsdaFixA ( 
              obj.ObjectId.in(),
              obj.Tenor.in(),
              obj.FwdCurve.in(),
              obj.DiscCurve.in(),
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
       std::string err = "ERROR: read qlEuriborSwapIsdaFixA: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlEuriborSwapIsdaFixADataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEuriborSwapIsdaFixADataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlEuriborSwapIsdaFixADataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEuriborSwapIsdaFixADataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlEuriborSwapIsdaFixADataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEuriborSwapIsdaFixADataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlEuriborSwapIsdaFixADataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEuriborSwapIsdaFixADataReaderListenerImpl::on_subscription_matched\n")));
}

void qlEuriborSwapIsdaFixADataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEuriborSwapIsdaFixADataReaderListenerImpl::on_sample_rejected\n")));
}

void qlEuriborSwapIsdaFixADataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEuriborSwapIsdaFixADataReaderListenerImpl::on_sample_rejected\n")));
}

void qlEuriborSwapIsdaFixADataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlEuriborSwapIsdaFixADataReaderListenerImpl::on_reading_start\n")));
}

void qlEuriborSwapIsdaFixADataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlEuriborSwapIsdaFixADataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlEuriborSwapIsdaFixADataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, qlIndex::qlEuriborSwapIsdaFixA& )
{
  return true;
}

bool qlEuriborSwapIsdaFixADataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, qlIndex::qlEuriborSwapIsdaFixA&, std::string& )
{
  return true;
}

void qlEuriborSwapIsdaFixADataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, qlIndex::qlEuriborSwapIsdaFixA&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEuriborSwapIsdaFixADataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlEuriborSwapIsdaFixADataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEuriborSwapIsdaFixADataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlEuriborSwapIsdaFixADataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlEuriborSwapIsdaFixADataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlIborIndexDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   qlIndex::qlIborIndexDataReader_var obj_dr
     = qlIndex::qlIborIndexDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlIborIndexDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    qlIndex::qlIborIndex obj;
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

              returnObject = QuantLibAddinCpp::qlIborIndex ( 
              obj.ObjectId.in(),
              obj.FamilyName.in(),
              obj.Tenor.in(),
              static_cast<long>(obj.FixingDays),
              obj.Currency.in(),
              obj.Calendar.in(),
              obj.BDayConvention.in(),
              static_cast<bool>(obj.EndOfMonth),
              obj.DayCounter.in(),
              obj.FwdCurve.in(),
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
       std::string err = "ERROR: read qlIborIndex: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlIborIndexDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIborIndexDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlIborIndexDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIborIndexDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlIborIndexDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIborIndexDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlIborIndexDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIborIndexDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlIborIndexDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIborIndexDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlIborIndexDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIborIndexDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlIborIndexDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlIborIndexDataReaderListenerImpl::on_reading_start\n")));
}

void qlIborIndexDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlIborIndexDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlIborIndexDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, qlIndex::qlIborIndex& )
{
  return true;
}

bool qlIborIndexDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, qlIndex::qlIborIndex&, std::string& )
{
  return true;
}

void qlIborIndexDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, qlIndex::qlIborIndex&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIborIndexDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlIborIndexDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIborIndexDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlIborIndexDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIborIndexDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlIndexAddFixingsDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   qlIndex::qlIndexAddFixingsDataReader_var obj_dr
     = qlIndex::qlIndexAddFixingsDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlIndexAddFixingsDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    qlIndex::qlIndexAddFixings obj;
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

              returnObject = QuantLibAddinCpp::qlIndexAddFixings ( 
              obj.ObjectId.in(),
             qldds_utils::vector_cast<ObjectHandler::property_t,qldds_utils::StringSeq>(obj.FixingDates),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.FixingValues),
              static_cast<bool>(obj.ForceOverwrite),
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
       std::string err = "ERROR: read qlIndexAddFixings: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlIndexAddFixingsDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIndexAddFixingsDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlIndexAddFixingsDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIndexAddFixingsDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlIndexAddFixingsDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIndexAddFixingsDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlIndexAddFixingsDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIndexAddFixingsDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlIndexAddFixingsDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIndexAddFixingsDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlIndexAddFixingsDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIndexAddFixingsDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlIndexAddFixingsDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlIndexAddFixingsDataReaderListenerImpl::on_reading_start\n")));
}

void qlIndexAddFixingsDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlIndexAddFixingsDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlIndexAddFixingsDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, qlIndex::qlIndexAddFixings& )
{
  return true;
}

bool qlIndexAddFixingsDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, qlIndex::qlIndexAddFixings&, bool& )
{
  return true;
}

void qlIndexAddFixingsDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, qlIndex::qlIndexAddFixings&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIndexAddFixingsDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlIndexAddFixingsDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIndexAddFixingsDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlIndexAddFixingsDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlIndexAddFixingsDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlLiborDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   qlIndex::qlLiborDataReader_var obj_dr
     = qlIndex::qlLiborDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlLiborDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    qlIndex::qlLibor obj;
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

              returnObject = QuantLibAddinCpp::qlLibor ( 
              obj.ObjectId.in(),
              obj.Currency.in(),
              obj.Tenor.in(),
              obj.YieldCurve.in(),
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
       std::string err = "ERROR: read qlLibor: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlLiborDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlLiborDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlLiborDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlLiborDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlLiborDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlLiborDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlLiborDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlLiborDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlLiborDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlLiborDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlLiborDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlLiborDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlLiborDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlLiborDataReaderListenerImpl::on_reading_start\n")));
}

void qlLiborDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlLiborDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlLiborDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, qlIndex::qlLibor& )
{
  return true;
}

bool qlLiborDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, qlIndex::qlLibor&, std::string& )
{
  return true;
}

void qlLiborDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, qlIndex::qlLibor&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlLiborDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlLiborDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlLiborDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlLiborDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlLiborDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlLiborSwapDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   qlIndex::qlLiborSwapDataReader_var obj_dr
     = qlIndex::qlLiborSwapDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlLiborSwapDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    qlIndex::qlLiborSwap obj;
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

              returnObject = QuantLibAddinCpp::qlLiborSwap ( 
              obj.ObjectId.in(),
              obj.Currency.in(),
              obj.FixingType.in(),
              obj.Tenor.in(),
              obj.FwdCurve.in(),
              obj.DiscCurve.in(),
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
       std::string err = "ERROR: read qlLiborSwap: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlLiborSwapDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlLiborSwapDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlLiborSwapDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlLiborSwapDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlLiborSwapDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlLiborSwapDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlLiborSwapDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlLiborSwapDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlLiborSwapDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlLiborSwapDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlLiborSwapDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlLiborSwapDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlLiborSwapDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlLiborSwapDataReaderListenerImpl::on_reading_start\n")));
}

void qlLiborSwapDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlLiborSwapDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlLiborSwapDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, qlIndex::qlLiborSwap& )
{
  return true;
}

bool qlLiborSwapDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, qlIndex::qlLiborSwap&, std::string& )
{
  return true;
}

void qlLiborSwapDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, qlIndex::qlLiborSwap&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlLiborSwapDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlLiborSwapDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlLiborSwapDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlLiborSwapDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlLiborSwapDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlOvernightIndexDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   qlIndex::qlOvernightIndexDataReader_var obj_dr
     = qlIndex::qlOvernightIndexDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlOvernightIndexDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    qlIndex::qlOvernightIndex obj;
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

              returnObject = QuantLibAddinCpp::qlOvernightIndex ( 
              obj.ObjectId.in(),
              obj.FamilyName.in(),
              static_cast<long>(obj.FixingDays),
              obj.Currency.in(),
              obj.Calendar.in(),
              obj.DayCounter.in(),
              obj.YieldCurve.in(),
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
       std::string err = "ERROR: read qlOvernightIndex: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlOvernightIndexDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlOvernightIndexDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlOvernightIndexDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlOvernightIndexDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlOvernightIndexDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlOvernightIndexDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlOvernightIndexDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlOvernightIndexDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlOvernightIndexDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlOvernightIndexDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlOvernightIndexDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlOvernightIndexDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlOvernightIndexDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlOvernightIndexDataReaderListenerImpl::on_reading_start\n")));
}

void qlOvernightIndexDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlOvernightIndexDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlOvernightIndexDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, qlIndex::qlOvernightIndex& )
{
  return true;
}

bool qlOvernightIndexDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, qlIndex::qlOvernightIndex&, std::string& )
{
  return true;
}

void qlOvernightIndexDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, qlIndex::qlOvernightIndex&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlOvernightIndexDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlOvernightIndexDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlOvernightIndexDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlOvernightIndexDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlOvernightIndexDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlProxyIborDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   qlIndex::qlProxyIborDataReader_var obj_dr
     = qlIndex::qlProxyIborDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlProxyIborDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    qlIndex::qlProxyIbor obj;
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

              returnObject = QuantLibAddinCpp::qlProxyIbor ( 
              obj.ObjectId.in(),
              obj.FamilyName.in(),
              obj.Tenor.in(),
              static_cast<long>(obj.FixingDays),
              obj.Currency.in(),
              obj.Calendar.in(),
              obj.BDayConvention.in(),
              static_cast<bool>(obj.EndOfMonth),
              obj.DayCounter.in(),
              obj.Gearing ,
              obj.IborIndex.in(),
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
       std::string err = "ERROR: read qlProxyIbor: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlProxyIborDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlProxyIborDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlProxyIborDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlProxyIborDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlProxyIborDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlProxyIborDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlProxyIborDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlProxyIborDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlProxyIborDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlProxyIborDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlProxyIborDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlProxyIborDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlProxyIborDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlProxyIborDataReaderListenerImpl::on_reading_start\n")));
}

void qlProxyIborDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlProxyIborDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlProxyIborDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, qlIndex::qlProxyIbor& )
{
  return true;
}

bool qlProxyIborDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, qlIndex::qlProxyIbor&, std::string& )
{
  return true;
}

void qlProxyIborDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, qlIndex::qlProxyIbor&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlProxyIborDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlProxyIborDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlProxyIborDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlProxyIborDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlProxyIborDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlSoniaDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   qlIndex::qlSoniaDataReader_var obj_dr
     = qlIndex::qlSoniaDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlSoniaDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    qlIndex::qlSonia obj;
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

              returnObject = QuantLibAddinCpp::qlSonia ( 
              obj.ObjectId.in(),
              obj.YieldCurve.in(),
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
       std::string err = "ERROR: read qlSonia: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlSoniaDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSoniaDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlSoniaDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSoniaDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlSoniaDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSoniaDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlSoniaDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSoniaDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlSoniaDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSoniaDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlSoniaDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSoniaDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlSoniaDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlSoniaDataReaderListenerImpl::on_reading_start\n")));
}

void qlSoniaDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlSoniaDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlSoniaDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, qlIndex::qlSonia& )
{
  return true;
}

bool qlSoniaDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, qlIndex::qlSonia&, std::string& )
{
  return true;
}

void qlSoniaDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, qlIndex::qlSonia&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSoniaDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlSoniaDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSoniaDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlSoniaDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSoniaDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlSwapIndexDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   qlIndex::qlSwapIndexDataReader_var obj_dr
     = qlIndex::qlSwapIndexDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlSwapIndexDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    qlIndex::qlSwapIndex obj;
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

              returnObject = QuantLibAddinCpp::qlSwapIndex ( 
              obj.ObjectId.in(),
              obj.FamilyName.in(),
              obj.Tenor.in(),
              static_cast<long>(obj.FixingDays),
              obj.Currency.in(),
              obj.Calendar.in(),
              obj.FixedLegTenor.in(),
              obj.FixedLegBDC.in(),
              obj.FixedLegDayCounter.in(),
              obj.IborIndex.in(),
              obj.DiscCurve.in(),
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
       std::string err = "ERROR: read qlSwapIndex: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlSwapIndexDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwapIndexDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlSwapIndexDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwapIndexDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlSwapIndexDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwapIndexDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlSwapIndexDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwapIndexDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlSwapIndexDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwapIndexDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlSwapIndexDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwapIndexDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlSwapIndexDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlSwapIndexDataReaderListenerImpl::on_reading_start\n")));
}

void qlSwapIndexDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlSwapIndexDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlSwapIndexDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, qlIndex::qlSwapIndex& )
{
  return true;
}

bool qlSwapIndexDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, qlIndex::qlSwapIndex&, std::string& )
{
  return true;
}

void qlSwapIndexDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, qlIndex::qlSwapIndex&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwapIndexDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlSwapIndexDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwapIndexDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlSwapIndexDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwapIndexDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}
}
