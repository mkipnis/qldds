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

#include "garbagecollectionDataReaderListenerImpl.hpp"

#include <qldds_convert_utils.h>
#include <ace/Mutex.h>

namespace garbagecollection {

void ohRepositoryDeleteAllObjectsDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   garbagecollection::ohRepositoryDeleteAllObjectsDataReader_var obj_dr
     = garbagecollection::ohRepositoryDeleteAllObjectsDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("ohRepositoryDeleteAllObjectsDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    garbagecollection::ohRepositoryDeleteAllObjects obj;
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

              returnObject = QuantLibAddinCpp::ohRepositoryDeleteAllObjects ( 
              static_cast<bool>(obj.DeletePermanent),
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
       std::string err = "ERROR: read ohRepositoryDeleteAllObjects: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void ohRepositoryDeleteAllObjectsDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("ohRepositoryDeleteAllObjectsDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void ohRepositoryDeleteAllObjectsDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("ohRepositoryDeleteAllObjectsDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void ohRepositoryDeleteAllObjectsDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("ohRepositoryDeleteAllObjectsDataReaderListenerImpl::on_liveliness_changed\n")));
}

void ohRepositoryDeleteAllObjectsDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("ohRepositoryDeleteAllObjectsDataReaderListenerImpl::on_subscription_matched\n")));
}

void ohRepositoryDeleteAllObjectsDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("ohRepositoryDeleteAllObjectsDataReaderListenerImpl::on_sample_rejected\n")));
}

void ohRepositoryDeleteAllObjectsDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("ohRepositoryDeleteAllObjectsDataReaderListenerImpl::on_sample_rejected\n")));
}

void ohRepositoryDeleteAllObjectsDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("ohRepositoryDeleteAllObjectsDataReaderListenerImpl::on_reading_start\n")));
}

void ohRepositoryDeleteAllObjectsDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("ohRepositoryDeleteAllObjectsDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool ohRepositoryDeleteAllObjectsDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, garbagecollection::ohRepositoryDeleteAllObjects& )
{
  return true;
}

bool ohRepositoryDeleteAllObjectsDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, garbagecollection::ohRepositoryDeleteAllObjects&, bool& )
{
  return true;
}

void ohRepositoryDeleteAllObjectsDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, garbagecollection::ohRepositoryDeleteAllObjects&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("ohRepositoryDeleteAllObjectsDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void ohRepositoryDeleteAllObjectsDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("ohRepositoryDeleteAllObjectsDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void ohRepositoryDeleteAllObjectsDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("ohRepositoryDeleteAllObjectsDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void ohRepositoryLogObjectDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   garbagecollection::ohRepositoryLogObjectDataReader_var obj_dr
     = garbagecollection::ohRepositoryLogObjectDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("ohRepositoryLogObjectDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    garbagecollection::ohRepositoryLogObject obj;
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

              returnObject = QuantLibAddinCpp::ohRepositoryLogObject ( 
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
       std::string err = "ERROR: read ohRepositoryLogObject: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void ohRepositoryLogObjectDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("ohRepositoryLogObjectDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void ohRepositoryLogObjectDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("ohRepositoryLogObjectDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void ohRepositoryLogObjectDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("ohRepositoryLogObjectDataReaderListenerImpl::on_liveliness_changed\n")));
}

void ohRepositoryLogObjectDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("ohRepositoryLogObjectDataReaderListenerImpl::on_subscription_matched\n")));
}

void ohRepositoryLogObjectDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("ohRepositoryLogObjectDataReaderListenerImpl::on_sample_rejected\n")));
}

void ohRepositoryLogObjectDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("ohRepositoryLogObjectDataReaderListenerImpl::on_sample_rejected\n")));
}

void ohRepositoryLogObjectDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("ohRepositoryLogObjectDataReaderListenerImpl::on_reading_start\n")));
}

void ohRepositoryLogObjectDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("ohRepositoryLogObjectDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool ohRepositoryLogObjectDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, garbagecollection::ohRepositoryLogObject& )
{
  return true;
}

bool ohRepositoryLogObjectDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, garbagecollection::ohRepositoryLogObject&, bool& )
{
  return true;
}

void ohRepositoryLogObjectDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, garbagecollection::ohRepositoryLogObject&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("ohRepositoryLogObjectDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void ohRepositoryLogObjectDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("ohRepositoryLogObjectDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void ohRepositoryLogObjectDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("ohRepositoryLogObjectDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}
}
