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
//      Users/mkipnis/qldds/gensrc/stubs/stub.opendds.body

#include "swaptionvolstructureDataReaderListenerImpl.hpp"

#include <qldds_convert_utils.h>

namespace swaptionvolstructure {

void qlConstantSwaptionVolatilityDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   swaptionvolstructure::qlConstantSwaptionVolatilityDataReader_var obj_dr
     = swaptionvolstructure::qlConstantSwaptionVolatilityDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlConstantSwaptionVolatilityDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    swaptionvolstructure::qlConstantSwaptionVolatility obj;
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

              returnObject = QuantLibAddinCpp::qlConstantSwaptionVolatility ( 
              obj.ObjectId.in(),
              static_cast<long>(obj.NDays),
              obj.Calendar.in(),
              obj.BusinessDayConvention.in(),
              obj.Volatility ,
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
       std::string err = "ERROR: read qlConstantSwaptionVolatility: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlConstantSwaptionVolatilityDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlConstantSwaptionVolatilityDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlConstantSwaptionVolatilityDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlConstantSwaptionVolatilityDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlConstantSwaptionVolatilityDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlConstantSwaptionVolatilityDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlConstantSwaptionVolatilityDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlConstantSwaptionVolatilityDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlConstantSwaptionVolatilityDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlConstantSwaptionVolatilityDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlConstantSwaptionVolatilityDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlConstantSwaptionVolatilityDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlConstantSwaptionVolatilityDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlConstantSwaptionVolatilityDataReaderListenerImpl::on_reading_start\n")));
}

void qlConstantSwaptionVolatilityDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlConstantSwaptionVolatilityDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlConstantSwaptionVolatilityDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, swaptionvolstructure::qlConstantSwaptionVolatility& )
{
  return true;
}

bool qlConstantSwaptionVolatilityDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, swaptionvolstructure::qlConstantSwaptionVolatility&, std::string& )
{
  return true;
}

void qlConstantSwaptionVolatilityDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, swaptionvolstructure::qlConstantSwaptionVolatility&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlConstantSwaptionVolatilityDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlConstantSwaptionVolatilityDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlConstantSwaptionVolatilityDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlConstantSwaptionVolatilityDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlConstantSwaptionVolatilityDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlRelinkableHandleSwaptionVolatilityStructureDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   swaptionvolstructure::qlRelinkableHandleSwaptionVolatilityStructureDataReader_var obj_dr
     = swaptionvolstructure::qlRelinkableHandleSwaptionVolatilityStructureDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlRelinkableHandleSwaptionVolatilityStructureDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    swaptionvolstructure::qlRelinkableHandleSwaptionVolatilityStructure obj;
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

              returnObject = QuantLibAddinCpp::qlRelinkableHandleSwaptionVolatilityStructure ( 
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
       std::string err = "ERROR: read qlRelinkableHandleSwaptionVolatilityStructure: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlRelinkableHandleSwaptionVolatilityStructureDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRelinkableHandleSwaptionVolatilityStructureDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlRelinkableHandleSwaptionVolatilityStructureDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRelinkableHandleSwaptionVolatilityStructureDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlRelinkableHandleSwaptionVolatilityStructureDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRelinkableHandleSwaptionVolatilityStructureDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlRelinkableHandleSwaptionVolatilityStructureDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRelinkableHandleSwaptionVolatilityStructureDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlRelinkableHandleSwaptionVolatilityStructureDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRelinkableHandleSwaptionVolatilityStructureDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlRelinkableHandleSwaptionVolatilityStructureDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRelinkableHandleSwaptionVolatilityStructureDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlRelinkableHandleSwaptionVolatilityStructureDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlRelinkableHandleSwaptionVolatilityStructureDataReaderListenerImpl::on_reading_start\n")));
}

void qlRelinkableHandleSwaptionVolatilityStructureDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlRelinkableHandleSwaptionVolatilityStructureDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlRelinkableHandleSwaptionVolatilityStructureDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, swaptionvolstructure::qlRelinkableHandleSwaptionVolatilityStructure& )
{
  return true;
}

bool qlRelinkableHandleSwaptionVolatilityStructureDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, swaptionvolstructure::qlRelinkableHandleSwaptionVolatilityStructure&, std::string& )
{
  return true;
}

void qlRelinkableHandleSwaptionVolatilityStructureDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, swaptionvolstructure::qlRelinkableHandleSwaptionVolatilityStructure&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRelinkableHandleSwaptionVolatilityStructureDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlRelinkableHandleSwaptionVolatilityStructureDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRelinkableHandleSwaptionVolatilityStructureDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlRelinkableHandleSwaptionVolatilityStructureDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRelinkableHandleSwaptionVolatilityStructureDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlSmileSectionByCubeDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   swaptionvolstructure::qlSmileSectionByCubeDataReader_var obj_dr
     = swaptionvolstructure::qlSmileSectionByCubeDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlSmileSectionByCubeDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    swaptionvolstructure::qlSmileSectionByCube obj;
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

              returnObject = QuantLibAddinCpp::qlSmileSectionByCube ( 
              obj.ObjectId.in(),
              obj.VolCube.in(),
              qldds_utils::from_iso_string(obj.OptionDate.in() ),
              obj.SwapTenor.in(),
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
       std::string err = "ERROR: read qlSmileSectionByCube: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlSmileSectionByCubeDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSmileSectionByCubeDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlSmileSectionByCubeDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSmileSectionByCubeDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlSmileSectionByCubeDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSmileSectionByCubeDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlSmileSectionByCubeDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSmileSectionByCubeDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlSmileSectionByCubeDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSmileSectionByCubeDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlSmileSectionByCubeDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSmileSectionByCubeDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlSmileSectionByCubeDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlSmileSectionByCubeDataReaderListenerImpl::on_reading_start\n")));
}

void qlSmileSectionByCubeDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlSmileSectionByCubeDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlSmileSectionByCubeDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, swaptionvolstructure::qlSmileSectionByCube& )
{
  return true;
}

bool qlSmileSectionByCubeDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, swaptionvolstructure::qlSmileSectionByCube&, std::string& )
{
  return true;
}

void qlSmileSectionByCubeDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, swaptionvolstructure::qlSmileSectionByCube&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSmileSectionByCubeDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlSmileSectionByCubeDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSmileSectionByCubeDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlSmileSectionByCubeDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSmileSectionByCubeDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlSmileSectionByCube2DataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   swaptionvolstructure::qlSmileSectionByCube2DataReader_var obj_dr
     = swaptionvolstructure::qlSmileSectionByCube2DataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlSmileSectionByCube2DataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    swaptionvolstructure::qlSmileSectionByCube2 obj;
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

              returnObject = QuantLibAddinCpp::qlSmileSectionByCube2 ( 
              obj.ObjectId.in(),
              obj.VolCube.in(),
              obj.OptionDate.in(),
              obj.SwapTenor.in(),
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
       std::string err = "ERROR: read qlSmileSectionByCube2: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlSmileSectionByCube2DataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSmileSectionByCube2DataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlSmileSectionByCube2DataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSmileSectionByCube2DataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlSmileSectionByCube2DataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSmileSectionByCube2DataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlSmileSectionByCube2DataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSmileSectionByCube2DataReaderListenerImpl::on_subscription_matched\n")));
}

void qlSmileSectionByCube2DataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSmileSectionByCube2DataReaderListenerImpl::on_sample_rejected\n")));
}

void qlSmileSectionByCube2DataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSmileSectionByCube2DataReaderListenerImpl::on_sample_rejected\n")));
}

void qlSmileSectionByCube2DataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlSmileSectionByCube2DataReaderListenerImpl::on_reading_start\n")));
}

void qlSmileSectionByCube2DataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlSmileSectionByCube2DataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlSmileSectionByCube2DataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, swaptionvolstructure::qlSmileSectionByCube2& )
{
  return true;
}

bool qlSmileSectionByCube2DataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, swaptionvolstructure::qlSmileSectionByCube2&, std::string& )
{
  return true;
}

void qlSmileSectionByCube2DataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, swaptionvolstructure::qlSmileSectionByCube2&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSmileSectionByCube2DataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlSmileSectionByCube2DataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSmileSectionByCube2DataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlSmileSectionByCube2DataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSmileSectionByCube2DataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlSpreadedSwaptionVolatilityDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   swaptionvolstructure::qlSpreadedSwaptionVolatilityDataReader_var obj_dr
     = swaptionvolstructure::qlSpreadedSwaptionVolatilityDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlSpreadedSwaptionVolatilityDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    swaptionvolstructure::qlSpreadedSwaptionVolatility obj;
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

              returnObject = QuantLibAddinCpp::qlSpreadedSwaptionVolatility ( 
              obj.ObjectId.in(),
              obj.BaseVolStructure.in(),
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
       std::string err = "ERROR: read qlSpreadedSwaptionVolatility: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlSpreadedSwaptionVolatilityDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSpreadedSwaptionVolatilityDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlSpreadedSwaptionVolatilityDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSpreadedSwaptionVolatilityDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlSpreadedSwaptionVolatilityDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSpreadedSwaptionVolatilityDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlSpreadedSwaptionVolatilityDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSpreadedSwaptionVolatilityDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlSpreadedSwaptionVolatilityDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSpreadedSwaptionVolatilityDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlSpreadedSwaptionVolatilityDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSpreadedSwaptionVolatilityDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlSpreadedSwaptionVolatilityDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlSpreadedSwaptionVolatilityDataReaderListenerImpl::on_reading_start\n")));
}

void qlSpreadedSwaptionVolatilityDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlSpreadedSwaptionVolatilityDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlSpreadedSwaptionVolatilityDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, swaptionvolstructure::qlSpreadedSwaptionVolatility& )
{
  return true;
}

bool qlSpreadedSwaptionVolatilityDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, swaptionvolstructure::qlSpreadedSwaptionVolatility&, std::string& )
{
  return true;
}

void qlSpreadedSwaptionVolatilityDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, swaptionvolstructure::qlSpreadedSwaptionVolatility&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSpreadedSwaptionVolatilityDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlSpreadedSwaptionVolatilityDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSpreadedSwaptionVolatilityDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlSpreadedSwaptionVolatilityDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSpreadedSwaptionVolatilityDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlSwaptionVTSMatrixDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   swaptionvolstructure::qlSwaptionVTSMatrixDataReader_var obj_dr
     = swaptionvolstructure::qlSwaptionVTSMatrixDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlSwaptionVTSMatrixDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    swaptionvolstructure::qlSwaptionVTSMatrix obj;
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

              returnObject = QuantLibAddinCpp::qlSwaptionVTSMatrix ( 
              obj.ObjectId.in(),
              obj.Calendar.in(),
              obj.BusinessDayConvention.in(),
             qldds_utils::vector_cast_str<ObjectHandler::property_t,qldds_utils::StringSeq>(obj.OptionTenors),
             qldds_utils::vector_cast_str<ObjectHandler::property_t,qldds_utils::StringSeq>(obj.SwapTenors),
             qldds_utils::matrix_cast<ObjectHandler::property_t,qldds_utils::Matrix>(obj.Volatilities),
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
       std::string err = "ERROR: read qlSwaptionVTSMatrix: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlSwaptionVTSMatrixDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwaptionVTSMatrixDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlSwaptionVTSMatrixDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwaptionVTSMatrixDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlSwaptionVTSMatrixDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwaptionVTSMatrixDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlSwaptionVTSMatrixDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwaptionVTSMatrixDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlSwaptionVTSMatrixDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwaptionVTSMatrixDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlSwaptionVTSMatrixDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwaptionVTSMatrixDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlSwaptionVTSMatrixDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlSwaptionVTSMatrixDataReaderListenerImpl::on_reading_start\n")));
}

void qlSwaptionVTSMatrixDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlSwaptionVTSMatrixDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlSwaptionVTSMatrixDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, swaptionvolstructure::qlSwaptionVTSMatrix& )
{
  return true;
}

bool qlSwaptionVTSMatrixDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, swaptionvolstructure::qlSwaptionVTSMatrix&, std::string& )
{
  return true;
}

void qlSwaptionVTSMatrixDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, swaptionvolstructure::qlSwaptionVTSMatrix&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwaptionVTSMatrixDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlSwaptionVTSMatrixDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwaptionVTSMatrixDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlSwaptionVTSMatrixDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwaptionVTSMatrixDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlSwaptionVolCube1DataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   swaptionvolstructure::qlSwaptionVolCube1DataReader_var obj_dr
     = swaptionvolstructure::qlSwaptionVolCube1DataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlSwaptionVolCube1DataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    swaptionvolstructure::qlSwaptionVolCube1 obj;
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

              returnObject = QuantLibAddinCpp::qlSwaptionVolCube1 ( 
              obj.ObjectId.in(),
              obj.AtmVolStructure.in(),
             qldds_utils::vector_cast_str<ObjectHandler::property_t,qldds_utils::StringSeq>(obj.OptionTenors),
             qldds_utils::vector_cast_str<ObjectHandler::property_t,qldds_utils::StringSeq>(obj.SwapTenors),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.StrikeSpreads),
             qldds_utils::matrix_cast<ObjectHandler::property_t,qldds_utils::Matrix>(obj.SpreadVols),
              obj.SwapIndexBase.in(),
              obj.ShortSwapIndexBase.in(),
              static_cast<bool>(obj.VegaWeightedSmileFit),
             qldds_utils::matrix_cast<ObjectHandler::property_t,qldds_utils::Matrix>(obj.Guess),
              qldds_utils::vector_cast<bool,qldds_utils::BooleanSeq>(obj.IsFixed),
              static_cast<bool>(obj.IsAtmCalibrated),
              obj.EndCriteria.in(),
              static_cast<double>(obj.MaxErrorTol),
              obj.OptMethod.in(),
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
       std::string err = "ERROR: read qlSwaptionVolCube1: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlSwaptionVolCube1DataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwaptionVolCube1DataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlSwaptionVolCube1DataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwaptionVolCube1DataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlSwaptionVolCube1DataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwaptionVolCube1DataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlSwaptionVolCube1DataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwaptionVolCube1DataReaderListenerImpl::on_subscription_matched\n")));
}

void qlSwaptionVolCube1DataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwaptionVolCube1DataReaderListenerImpl::on_sample_rejected\n")));
}

void qlSwaptionVolCube1DataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwaptionVolCube1DataReaderListenerImpl::on_sample_rejected\n")));
}

void qlSwaptionVolCube1DataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlSwaptionVolCube1DataReaderListenerImpl::on_reading_start\n")));
}

void qlSwaptionVolCube1DataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlSwaptionVolCube1DataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlSwaptionVolCube1DataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, swaptionvolstructure::qlSwaptionVolCube1& )
{
  return true;
}

bool qlSwaptionVolCube1DataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, swaptionvolstructure::qlSwaptionVolCube1&, std::string& )
{
  return true;
}

void qlSwaptionVolCube1DataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, swaptionvolstructure::qlSwaptionVolCube1&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwaptionVolCube1DataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlSwaptionVolCube1DataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwaptionVolCube1DataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlSwaptionVolCube1DataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwaptionVolCube1DataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlSwaptionVolCube2DataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   swaptionvolstructure::qlSwaptionVolCube2DataReader_var obj_dr
     = swaptionvolstructure::qlSwaptionVolCube2DataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlSwaptionVolCube2DataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    swaptionvolstructure::qlSwaptionVolCube2 obj;
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

              returnObject = QuantLibAddinCpp::qlSwaptionVolCube2 ( 
              obj.ObjectId.in(),
              obj.AtmVolStructure.in(),
             qldds_utils::vector_cast_str<ObjectHandler::property_t,qldds_utils::StringSeq>(obj.OptionTenor),
             qldds_utils::vector_cast_str<ObjectHandler::property_t,qldds_utils::StringSeq>(obj.SwapTenor),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.StrikeSpreads),
             qldds_utils::matrix_cast<ObjectHandler::property_t,qldds_utils::Matrix>(obj.SpreadVols),
              obj.SwapIndexBase.in(),
              obj.ShortSwapIndexBase.in(),
              static_cast<bool>(obj.VegaWeightedSmileFit),
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
       std::string err = "ERROR: read qlSwaptionVolCube2: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlSwaptionVolCube2DataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwaptionVolCube2DataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlSwaptionVolCube2DataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwaptionVolCube2DataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlSwaptionVolCube2DataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwaptionVolCube2DataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlSwaptionVolCube2DataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwaptionVolCube2DataReaderListenerImpl::on_subscription_matched\n")));
}

void qlSwaptionVolCube2DataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwaptionVolCube2DataReaderListenerImpl::on_sample_rejected\n")));
}

void qlSwaptionVolCube2DataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwaptionVolCube2DataReaderListenerImpl::on_sample_rejected\n")));
}

void qlSwaptionVolCube2DataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlSwaptionVolCube2DataReaderListenerImpl::on_reading_start\n")));
}

void qlSwaptionVolCube2DataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlSwaptionVolCube2DataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlSwaptionVolCube2DataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, swaptionvolstructure::qlSwaptionVolCube2& )
{
  return true;
}

bool qlSwaptionVolCube2DataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, swaptionvolstructure::qlSwaptionVolCube2&, std::string& )
{
  return true;
}

void qlSwaptionVolCube2DataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, swaptionvolstructure::qlSwaptionVolCube2&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwaptionVolCube2DataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlSwaptionVolCube2DataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwaptionVolCube2DataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlSwaptionVolCube2DataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSwaptionVolCube2DataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}
}
