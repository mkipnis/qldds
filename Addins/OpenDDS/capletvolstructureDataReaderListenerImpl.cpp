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
//      qldds/gensrc/stubs/stub.opendds.body

#include "capletvolstructureDataReaderListenerImpl.hpp"

#include <qldds_convert_utils.h>
#include <ace/Mutex.h>

namespace capletvolstructure {

void qlCapFloorTermVolCurveDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   capletvolstructure::qlCapFloorTermVolCurveDataReader_var obj_dr
     = capletvolstructure::qlCapFloorTermVolCurveDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlCapFloorTermVolCurveDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    capletvolstructure::qlCapFloorTermVolCurve obj;
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

              returnObject = QuantLibAddinCpp::qlCapFloorTermVolCurve ( 
              obj.ObjectId.in(),
              static_cast<long>(obj.SettlementDays),
              obj.Calendar.in(),
              obj.BusinessDayConvention.in(),
             qldds_utils::vector_cast_str<ObjectHandler::property_t,qldds_utils::StringSeq>(obj.OptionTenors),
             qldds_utils::vector_cast<ObjectHandler::property_t,qldds_utils::DoubleSeq>(obj.Volatilities),
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
       std::string err = "ERROR: read qlCapFloorTermVolCurve: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlCapFloorTermVolCurveDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCapFloorTermVolCurveDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlCapFloorTermVolCurveDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCapFloorTermVolCurveDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlCapFloorTermVolCurveDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCapFloorTermVolCurveDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlCapFloorTermVolCurveDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCapFloorTermVolCurveDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlCapFloorTermVolCurveDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCapFloorTermVolCurveDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlCapFloorTermVolCurveDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCapFloorTermVolCurveDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlCapFloorTermVolCurveDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlCapFloorTermVolCurveDataReaderListenerImpl::on_reading_start\n")));
}

void qlCapFloorTermVolCurveDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlCapFloorTermVolCurveDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlCapFloorTermVolCurveDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, capletvolstructure::qlCapFloorTermVolCurve& )
{
  return true;
}

bool qlCapFloorTermVolCurveDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, capletvolstructure::qlCapFloorTermVolCurve&, std::string& )
{
  return true;
}

void qlCapFloorTermVolCurveDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, capletvolstructure::qlCapFloorTermVolCurve&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCapFloorTermVolCurveDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlCapFloorTermVolCurveDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCapFloorTermVolCurveDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlCapFloorTermVolCurveDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCapFloorTermVolCurveDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlCapFloorTermVolSurfaceDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   capletvolstructure::qlCapFloorTermVolSurfaceDataReader_var obj_dr
     = capletvolstructure::qlCapFloorTermVolSurfaceDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlCapFloorTermVolSurfaceDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    capletvolstructure::qlCapFloorTermVolSurface obj;
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

              returnObject = QuantLibAddinCpp::qlCapFloorTermVolSurface ( 
              obj.ObjectId.in(),
              static_cast<long>(obj.SettlementDays),
              obj.Calendar.in(),
              obj.BusinessDayConvention.in(),
             qldds_utils::vector_cast_str<ObjectHandler::property_t,qldds_utils::StringSeq>(obj.OptionTenors),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.Strikes),
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
       std::string err = "ERROR: read qlCapFloorTermVolSurface: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlCapFloorTermVolSurfaceDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCapFloorTermVolSurfaceDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlCapFloorTermVolSurfaceDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCapFloorTermVolSurfaceDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlCapFloorTermVolSurfaceDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCapFloorTermVolSurfaceDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlCapFloorTermVolSurfaceDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCapFloorTermVolSurfaceDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlCapFloorTermVolSurfaceDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCapFloorTermVolSurfaceDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlCapFloorTermVolSurfaceDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCapFloorTermVolSurfaceDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlCapFloorTermVolSurfaceDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlCapFloorTermVolSurfaceDataReaderListenerImpl::on_reading_start\n")));
}

void qlCapFloorTermVolSurfaceDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlCapFloorTermVolSurfaceDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlCapFloorTermVolSurfaceDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, capletvolstructure::qlCapFloorTermVolSurface& )
{
  return true;
}

bool qlCapFloorTermVolSurfaceDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, capletvolstructure::qlCapFloorTermVolSurface&, std::string& )
{
  return true;
}

void qlCapFloorTermVolSurfaceDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, capletvolstructure::qlCapFloorTermVolSurface&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCapFloorTermVolSurfaceDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlCapFloorTermVolSurfaceDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCapFloorTermVolSurfaceDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlCapFloorTermVolSurfaceDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlCapFloorTermVolSurfaceDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlConstantOptionletVolatilityDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   capletvolstructure::qlConstantOptionletVolatilityDataReader_var obj_dr
     = capletvolstructure::qlConstantOptionletVolatilityDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlConstantOptionletVolatilityDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    capletvolstructure::qlConstantOptionletVolatility obj;
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

              returnObject = QuantLibAddinCpp::qlConstantOptionletVolatility ( 
              obj.ObjectId.in(),
              static_cast<long>(obj.NDays),
              obj.Calendar.in(),
              obj.BusinessDayConvention.in(),
              obj.Volatility ,
              obj.DayCounter.in(),
              obj.VolatilityType.in(),
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
       std::string err = "ERROR: read qlConstantOptionletVolatility: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlConstantOptionletVolatilityDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlConstantOptionletVolatilityDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlConstantOptionletVolatilityDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlConstantOptionletVolatilityDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlConstantOptionletVolatilityDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlConstantOptionletVolatilityDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlConstantOptionletVolatilityDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlConstantOptionletVolatilityDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlConstantOptionletVolatilityDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlConstantOptionletVolatilityDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlConstantOptionletVolatilityDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlConstantOptionletVolatilityDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlConstantOptionletVolatilityDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlConstantOptionletVolatilityDataReaderListenerImpl::on_reading_start\n")));
}

void qlConstantOptionletVolatilityDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlConstantOptionletVolatilityDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlConstantOptionletVolatilityDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, capletvolstructure::qlConstantOptionletVolatility& )
{
  return true;
}

bool qlConstantOptionletVolatilityDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, capletvolstructure::qlConstantOptionletVolatility&, std::string& )
{
  return true;
}

void qlConstantOptionletVolatilityDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, capletvolstructure::qlConstantOptionletVolatility&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlConstantOptionletVolatilityDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlConstantOptionletVolatilityDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlConstantOptionletVolatilityDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlConstantOptionletVolatilityDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlConstantOptionletVolatilityDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlRelinkableHandleOptionletVolatilityStructureDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   capletvolstructure::qlRelinkableHandleOptionletVolatilityStructureDataReader_var obj_dr
     = capletvolstructure::qlRelinkableHandleOptionletVolatilityStructureDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlRelinkableHandleOptionletVolatilityStructureDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    capletvolstructure::qlRelinkableHandleOptionletVolatilityStructure obj;
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

              returnObject = QuantLibAddinCpp::qlRelinkableHandleOptionletVolatilityStructure ( 
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
       std::string err = "ERROR: read qlRelinkableHandleOptionletVolatilityStructure: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlRelinkableHandleOptionletVolatilityStructureDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRelinkableHandleOptionletVolatilityStructureDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlRelinkableHandleOptionletVolatilityStructureDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRelinkableHandleOptionletVolatilityStructureDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlRelinkableHandleOptionletVolatilityStructureDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRelinkableHandleOptionletVolatilityStructureDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlRelinkableHandleOptionletVolatilityStructureDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRelinkableHandleOptionletVolatilityStructureDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlRelinkableHandleOptionletVolatilityStructureDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRelinkableHandleOptionletVolatilityStructureDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlRelinkableHandleOptionletVolatilityStructureDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRelinkableHandleOptionletVolatilityStructureDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlRelinkableHandleOptionletVolatilityStructureDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlRelinkableHandleOptionletVolatilityStructureDataReaderListenerImpl::on_reading_start\n")));
}

void qlRelinkableHandleOptionletVolatilityStructureDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlRelinkableHandleOptionletVolatilityStructureDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlRelinkableHandleOptionletVolatilityStructureDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, capletvolstructure::qlRelinkableHandleOptionletVolatilityStructure& )
{
  return true;
}

bool qlRelinkableHandleOptionletVolatilityStructureDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, capletvolstructure::qlRelinkableHandleOptionletVolatilityStructure&, std::string& )
{
  return true;
}

void qlRelinkableHandleOptionletVolatilityStructureDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, capletvolstructure::qlRelinkableHandleOptionletVolatilityStructure&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRelinkableHandleOptionletVolatilityStructureDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlRelinkableHandleOptionletVolatilityStructureDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRelinkableHandleOptionletVolatilityStructureDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlRelinkableHandleOptionletVolatilityStructureDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlRelinkableHandleOptionletVolatilityStructureDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlSpreadedOptionletVolatilityDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   capletvolstructure::qlSpreadedOptionletVolatilityDataReader_var obj_dr
     = capletvolstructure::qlSpreadedOptionletVolatilityDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlSpreadedOptionletVolatilityDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    capletvolstructure::qlSpreadedOptionletVolatility obj;
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

              returnObject = QuantLibAddinCpp::qlSpreadedOptionletVolatility ( 
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
       std::string err = "ERROR: read qlSpreadedOptionletVolatility: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlSpreadedOptionletVolatilityDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSpreadedOptionletVolatilityDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlSpreadedOptionletVolatilityDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSpreadedOptionletVolatilityDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlSpreadedOptionletVolatilityDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSpreadedOptionletVolatilityDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlSpreadedOptionletVolatilityDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSpreadedOptionletVolatilityDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlSpreadedOptionletVolatilityDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSpreadedOptionletVolatilityDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlSpreadedOptionletVolatilityDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSpreadedOptionletVolatilityDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlSpreadedOptionletVolatilityDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlSpreadedOptionletVolatilityDataReaderListenerImpl::on_reading_start\n")));
}

void qlSpreadedOptionletVolatilityDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlSpreadedOptionletVolatilityDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlSpreadedOptionletVolatilityDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, capletvolstructure::qlSpreadedOptionletVolatility& )
{
  return true;
}

bool qlSpreadedOptionletVolatilityDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, capletvolstructure::qlSpreadedOptionletVolatility&, std::string& )
{
  return true;
}

void qlSpreadedOptionletVolatilityDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, capletvolstructure::qlSpreadedOptionletVolatility&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSpreadedOptionletVolatilityDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlSpreadedOptionletVolatilityDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSpreadedOptionletVolatilityDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlSpreadedOptionletVolatilityDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSpreadedOptionletVolatilityDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlStrippedOptionletDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   capletvolstructure::qlStrippedOptionletDataReader_var obj_dr
     = capletvolstructure::qlStrippedOptionletDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlStrippedOptionletDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    capletvolstructure::qlStrippedOptionlet obj;
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

              returnObject = QuantLibAddinCpp::qlStrippedOptionlet ( 
              obj.ObjectId.in(),
              static_cast<long>(obj.SettlementDays),
              obj.Calendar.in(),
              obj.BusinessDayConvention.in(),
              obj.IborIndex.in(),
             qldds_utils::vector_cast<ObjectHandler::property_t,qldds_utils::StringSeq>(obj.OptionletDates),
             qldds_utils::vector_cast<double,qldds_utils::DoubleSeq>(obj.Strikes),
             qldds_utils::matrix_cast<ObjectHandler::property_t,qldds_utils::Matrix>(obj.Volatilities),
              obj.DayCounter.in(),
              obj.VolatilityType.in(),
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
       std::string err = "ERROR: read qlStrippedOptionlet: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlStrippedOptionletDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStrippedOptionletDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlStrippedOptionletDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStrippedOptionletDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlStrippedOptionletDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStrippedOptionletDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlStrippedOptionletDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStrippedOptionletDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlStrippedOptionletDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStrippedOptionletDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlStrippedOptionletDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStrippedOptionletDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlStrippedOptionletDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlStrippedOptionletDataReaderListenerImpl::on_reading_start\n")));
}

void qlStrippedOptionletDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlStrippedOptionletDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlStrippedOptionletDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, capletvolstructure::qlStrippedOptionlet& )
{
  return true;
}

bool qlStrippedOptionletDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, capletvolstructure::qlStrippedOptionlet&, std::string& )
{
  return true;
}

void qlStrippedOptionletDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, capletvolstructure::qlStrippedOptionlet&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStrippedOptionletDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlStrippedOptionletDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStrippedOptionletDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlStrippedOptionletDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStrippedOptionletDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlStrippedOptionletAdapterDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   capletvolstructure::qlStrippedOptionletAdapterDataReader_var obj_dr
     = capletvolstructure::qlStrippedOptionletAdapterDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlStrippedOptionletAdapterDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    capletvolstructure::qlStrippedOptionletAdapter obj;
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

              returnObject = QuantLibAddinCpp::qlStrippedOptionletAdapter ( 
              obj.ObjectId.in(),
              obj.StrippedOptionletBase.in(),
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
       std::string err = "ERROR: read qlStrippedOptionletAdapter: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlStrippedOptionletAdapterDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStrippedOptionletAdapterDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlStrippedOptionletAdapterDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStrippedOptionletAdapterDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlStrippedOptionletAdapterDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStrippedOptionletAdapterDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlStrippedOptionletAdapterDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStrippedOptionletAdapterDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlStrippedOptionletAdapterDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStrippedOptionletAdapterDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlStrippedOptionletAdapterDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStrippedOptionletAdapterDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlStrippedOptionletAdapterDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlStrippedOptionletAdapterDataReaderListenerImpl::on_reading_start\n")));
}

void qlStrippedOptionletAdapterDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlStrippedOptionletAdapterDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlStrippedOptionletAdapterDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, capletvolstructure::qlStrippedOptionletAdapter& )
{
  return true;
}

bool qlStrippedOptionletAdapterDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, capletvolstructure::qlStrippedOptionletAdapter&, std::string& )
{
  return true;
}

void qlStrippedOptionletAdapterDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, capletvolstructure::qlStrippedOptionletAdapter&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStrippedOptionletAdapterDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlStrippedOptionletAdapterDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStrippedOptionletAdapterDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlStrippedOptionletAdapterDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStrippedOptionletAdapterDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlStrippedOptionletBaseSettlementDaysDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   capletvolstructure::qlStrippedOptionletBaseSettlementDaysDataReader_var obj_dr
     = capletvolstructure::qlStrippedOptionletBaseSettlementDaysDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlStrippedOptionletBaseSettlementDaysDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    capletvolstructure::qlStrippedOptionletBaseSettlementDays obj;
    DDS::SampleInfo si ;
    DDS::ReturnCode_t status = obj_dr->take_next_sample(obj, si) ;

    if ( status == DDS::RETCODE_OK )
    {
      if ( si.valid_data == true )
      {
         ++count;

         if ( pre_quantlib_addin_call( reader, si, obj ) )
         {
            long returnObject;;

            try {

              ACE_Guard<ACE_Mutex> guard( get_ACE_Mutex() );

              returnObject = QuantLibAddinCpp::qlStrippedOptionletBaseSettlementDays ( 
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
       std::string err = "ERROR: read qlStrippedOptionletBaseSettlementDays: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlStrippedOptionletBaseSettlementDaysDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStrippedOptionletBaseSettlementDaysDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlStrippedOptionletBaseSettlementDaysDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStrippedOptionletBaseSettlementDaysDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlStrippedOptionletBaseSettlementDaysDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStrippedOptionletBaseSettlementDaysDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlStrippedOptionletBaseSettlementDaysDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStrippedOptionletBaseSettlementDaysDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlStrippedOptionletBaseSettlementDaysDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStrippedOptionletBaseSettlementDaysDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlStrippedOptionletBaseSettlementDaysDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStrippedOptionletBaseSettlementDaysDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlStrippedOptionletBaseSettlementDaysDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlStrippedOptionletBaseSettlementDaysDataReaderListenerImpl::on_reading_start\n")));
}

void qlStrippedOptionletBaseSettlementDaysDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlStrippedOptionletBaseSettlementDaysDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlStrippedOptionletBaseSettlementDaysDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, capletvolstructure::qlStrippedOptionletBaseSettlementDays& )
{
  return true;
}

bool qlStrippedOptionletBaseSettlementDaysDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, capletvolstructure::qlStrippedOptionletBaseSettlementDays&, long& )
{
  return true;
}

void qlStrippedOptionletBaseSettlementDaysDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, capletvolstructure::qlStrippedOptionletBaseSettlementDays&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStrippedOptionletBaseSettlementDaysDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlStrippedOptionletBaseSettlementDaysDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStrippedOptionletBaseSettlementDaysDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlStrippedOptionletBaseSettlementDaysDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlStrippedOptionletBaseSettlementDaysDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}
}
