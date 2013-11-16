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

#include "smilesectionDataReaderListenerImpl.hpp"

#include <qldds_convert_utils.h>

namespace smilesection {

void qlFlatSmileSectionDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   smilesection::qlFlatSmileSectionDataReader_var obj_dr
     = smilesection::qlFlatSmileSectionDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlFlatSmileSectionDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    smilesection::qlFlatSmileSection obj;
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

              returnObject = QuantLibAddinCpp::qlFlatSmileSection ( 
              obj.ObjectId.in(),
              qldds_utils::from_iso_string(obj.OptionDate.in() ),
              static_cast<double>(obj.Volatility),
              obj.DayCounter.in(),
              qldds_utils::from_iso_string(obj.RefDate.in() ),
              static_cast<double>(obj.AtmValue),
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
       std::string err = "ERROR: read qlFlatSmileSection: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlFlatSmileSectionDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFlatSmileSectionDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlFlatSmileSectionDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFlatSmileSectionDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlFlatSmileSectionDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFlatSmileSectionDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlFlatSmileSectionDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFlatSmileSectionDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlFlatSmileSectionDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFlatSmileSectionDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlFlatSmileSectionDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFlatSmileSectionDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlFlatSmileSectionDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlFlatSmileSectionDataReaderListenerImpl::on_reading_start\n")));
}

void qlFlatSmileSectionDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlFlatSmileSectionDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlFlatSmileSectionDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, smilesection::qlFlatSmileSection& )
{
  return true;
}

bool qlFlatSmileSectionDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, smilesection::qlFlatSmileSection&, std::string& )
{
  return true;
}

void qlFlatSmileSectionDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, smilesection::qlFlatSmileSection&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFlatSmileSectionDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlFlatSmileSectionDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFlatSmileSectionDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlFlatSmileSectionDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlFlatSmileSectionDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlInterpolatedSmileSectionDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   smilesection::qlInterpolatedSmileSectionDataReader_var obj_dr
     = smilesection::qlInterpolatedSmileSectionDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlInterpolatedSmileSectionDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    smilesection::qlInterpolatedSmileSection obj;
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

              returnObject = QuantLibAddinCpp::qlInterpolatedSmileSection ( 
              obj.ObjectId.in(),
              qldds_utils::from_iso_string(obj.OptionDate.in() ),
             qldds_utils::vector_cast<double,CORBA::DoubleSeq>(obj.Strikes),
             qldds_utils::vector_cast<ObjectHandler::property_t,CORBA::DoubleSeq>(obj.StdDevs),
              obj.AtmLevel ,
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
       std::string err = "ERROR: read qlInterpolatedSmileSection: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlInterpolatedSmileSectionDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInterpolatedSmileSectionDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlInterpolatedSmileSectionDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInterpolatedSmileSectionDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlInterpolatedSmileSectionDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInterpolatedSmileSectionDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlInterpolatedSmileSectionDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInterpolatedSmileSectionDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlInterpolatedSmileSectionDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInterpolatedSmileSectionDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlInterpolatedSmileSectionDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInterpolatedSmileSectionDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlInterpolatedSmileSectionDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlInterpolatedSmileSectionDataReaderListenerImpl::on_reading_start\n")));
}

void qlInterpolatedSmileSectionDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlInterpolatedSmileSectionDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlInterpolatedSmileSectionDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, smilesection::qlInterpolatedSmileSection& )
{
  return true;
}

bool qlInterpolatedSmileSectionDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, smilesection::qlInterpolatedSmileSection&, std::string& )
{
  return true;
}

void qlInterpolatedSmileSectionDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, smilesection::qlInterpolatedSmileSection&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInterpolatedSmileSectionDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlInterpolatedSmileSectionDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInterpolatedSmileSectionDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlInterpolatedSmileSectionDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlInterpolatedSmileSectionDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlSabrInterpolatedSmileSectionDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   smilesection::qlSabrInterpolatedSmileSectionDataReader_var obj_dr
     = smilesection::qlSabrInterpolatedSmileSectionDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlSabrInterpolatedSmileSectionDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    smilesection::qlSabrInterpolatedSmileSection obj;
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

              returnObject = QuantLibAddinCpp::qlSabrInterpolatedSmileSection ( 
              obj.ObjectId.in(),
              qldds_utils::from_iso_string(obj.OptionDate.in() ),
              static_cast<double>(obj.ForwardRate),
             qldds_utils::vector_cast<double,CORBA::DoubleSeq>(obj.Strike),
              static_cast<bool>(obj.FloatingStrike),
              static_cast<double>(obj.AtmVolatility),
             qldds_utils::vector_cast<double,CORBA::DoubleSeq>(obj.VolatilitySpreads),
              static_cast<double>(obj.Alpha),
              static_cast<double>(obj.Beta),
              static_cast<double>(obj.Nu),
              static_cast<double>(obj.Rho),
              static_cast<bool>(obj.AlphaIsFixed),
              static_cast<bool>(obj.BetaIsFixed),
              static_cast<bool>(obj.NuIsFixed),
              static_cast<bool>(obj.RhoIsFixed),
              static_cast<bool>(obj.VegaWeighted),
              obj.EndCriteria.in(),
              obj.Method.in(),
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
       std::string err = "ERROR: read qlSabrInterpolatedSmileSection: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlSabrInterpolatedSmileSectionDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSabrInterpolatedSmileSectionDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlSabrInterpolatedSmileSectionDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSabrInterpolatedSmileSectionDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlSabrInterpolatedSmileSectionDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSabrInterpolatedSmileSectionDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlSabrInterpolatedSmileSectionDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSabrInterpolatedSmileSectionDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlSabrInterpolatedSmileSectionDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSabrInterpolatedSmileSectionDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlSabrInterpolatedSmileSectionDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSabrInterpolatedSmileSectionDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlSabrInterpolatedSmileSectionDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlSabrInterpolatedSmileSectionDataReaderListenerImpl::on_reading_start\n")));
}

void qlSabrInterpolatedSmileSectionDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlSabrInterpolatedSmileSectionDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlSabrInterpolatedSmileSectionDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, smilesection::qlSabrInterpolatedSmileSection& )
{
  return true;
}

bool qlSabrInterpolatedSmileSectionDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, smilesection::qlSabrInterpolatedSmileSection&, std::string& )
{
  return true;
}

void qlSabrInterpolatedSmileSectionDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, smilesection::qlSabrInterpolatedSmileSection&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSabrInterpolatedSmileSectionDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlSabrInterpolatedSmileSectionDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSabrInterpolatedSmileSectionDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlSabrInterpolatedSmileSectionDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSabrInterpolatedSmileSectionDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlSabrInterpolatedSmileSection1DataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   smilesection::qlSabrInterpolatedSmileSection1DataReader_var obj_dr
     = smilesection::qlSabrInterpolatedSmileSection1DataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlSabrInterpolatedSmileSection1DataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    smilesection::qlSabrInterpolatedSmileSection1 obj;
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

              returnObject = QuantLibAddinCpp::qlSabrInterpolatedSmileSection1 ( 
              obj.ObjectId.in(),
              qldds_utils::from_iso_string(obj.OptionDate.in() ),
              obj.ForwardRate ,
             qldds_utils::vector_cast<double,CORBA::DoubleSeq>(obj.Strike),
              static_cast<bool>(obj.FloatingStrike),
              obj.AtmVolatility ,
             qldds_utils::vector_cast<ObjectHandler::property_t,CORBA::DoubleSeq>(obj.VolatilitySpreads),
              static_cast<double>(obj.Alpha),
              static_cast<double>(obj.Beta),
              static_cast<double>(obj.Nu),
              static_cast<double>(obj.Rho),
              static_cast<bool>(obj.AlphaIsFixed),
              static_cast<bool>(obj.BetaIsFixed),
              static_cast<bool>(obj.NuIsFixed),
              static_cast<bool>(obj.RhoIsFixed),
              static_cast<bool>(obj.VegaWeighted),
              obj.EndCriteria.in(),
              obj.Method.in(),
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
       std::string err = "ERROR: read qlSabrInterpolatedSmileSection1: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlSabrInterpolatedSmileSection1DataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSabrInterpolatedSmileSection1DataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlSabrInterpolatedSmileSection1DataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSabrInterpolatedSmileSection1DataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlSabrInterpolatedSmileSection1DataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSabrInterpolatedSmileSection1DataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlSabrInterpolatedSmileSection1DataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSabrInterpolatedSmileSection1DataReaderListenerImpl::on_subscription_matched\n")));
}

void qlSabrInterpolatedSmileSection1DataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSabrInterpolatedSmileSection1DataReaderListenerImpl::on_sample_rejected\n")));
}

void qlSabrInterpolatedSmileSection1DataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSabrInterpolatedSmileSection1DataReaderListenerImpl::on_sample_rejected\n")));
}

void qlSabrInterpolatedSmileSection1DataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlSabrInterpolatedSmileSection1DataReaderListenerImpl::on_reading_start\n")));
}

void qlSabrInterpolatedSmileSection1DataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlSabrInterpolatedSmileSection1DataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlSabrInterpolatedSmileSection1DataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, smilesection::qlSabrInterpolatedSmileSection1& )
{
  return true;
}

bool qlSabrInterpolatedSmileSection1DataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, smilesection::qlSabrInterpolatedSmileSection1&, std::string& )
{
  return true;
}

void qlSabrInterpolatedSmileSection1DataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, smilesection::qlSabrInterpolatedSmileSection1&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSabrInterpolatedSmileSection1DataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlSabrInterpolatedSmileSection1DataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSabrInterpolatedSmileSection1DataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlSabrInterpolatedSmileSection1DataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSabrInterpolatedSmileSection1DataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}

void qlSabrSmileSectionDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader )
  throw (CORBA::SystemException)
{

  try {
   smilesection::qlSabrSmileSectionDataReader_var obj_dr
     = smilesection::qlSabrSmileSectionDataReader::_narrow(reader);
   if (CORBA::is_nil (obj_dr.in ())) {
     ACE_ERROR((LM_ERROR,
               ACE_TEXT("(%P|%t) ERROR: ")
               ACE_TEXT("qlSabrSmileSectionDataReaderListenerImpl::on_data_available: _narrow failed.\n")));
  } 

  on_reading_start( reader );

  int count = 0;
  while ( true )
  {
    smilesection::qlSabrSmileSection obj;
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

              returnObject = QuantLibAddinCpp::qlSabrSmileSection ( 
              obj.ObjectId.in(),
              static_cast<double>(obj.OptionTime),
             qldds_utils::vector_cast<double,CORBA::DoubleSeq>(obj.Strikes),
             qldds_utils::vector_cast<ObjectHandler::property_t,CORBA::DoubleSeq>(obj.StdDevs),
              obj.Forward ,
              static_cast<double>(obj.Alpha),
              static_cast<double>(obj.Beta),
              static_cast<double>(obj.Nu),
              static_cast<double>(obj.Rho),
              static_cast<bool>(obj.AlphaIsFixed),
              static_cast<bool>(obj.BetaIsFixed),
              static_cast<bool>(obj.NuIsFixed),
              static_cast<bool>(obj.RhoIsFixed),
              static_cast<bool>(obj.VegaWeighted),
              obj.EndCriteria.in(),
              obj.Method.in(),
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
       std::string err = "ERROR: read qlSabrSmileSection: Error: ";
       err += status;

       on_dds_reading_error( reader, err );
    }
  }

  } catch (CORBA::Exception& e) {
       on_dds_exception( reader, e );
  }

}

void qlSabrSmileSectionDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &ms)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSabrSmileSectionDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlSabrSmileSectionDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &qs )
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSabrSmileSectionDataReaderListenerImpl::on_requested_deadline_missed\n")));
}

void qlSabrSmileSectionDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &ls )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSabrSmileSectionDataReaderListenerImpl::on_liveliness_changed\n")));
}

void qlSabrSmileSectionDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus &ms )
  throw (CORBA::SystemException)
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSabrSmileSectionDataReaderListenerImpl::on_subscription_matched\n")));
}

void qlSabrSmileSectionDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& sr)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSabrSmileSectionDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlSabrSmileSectionDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr reader,
  const DDS::SampleLostStatus& sl)
  throw (CORBA::SystemException)
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSabrSmileSectionDataReaderListenerImpl::on_sample_rejected\n")));
}

void qlSabrSmileSectionDataReaderListenerImpl::on_reading_start( DDS::DataReader_ptr reader )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlSabrSmileSectionDataReaderListenerImpl::on_reading_start\n")));
}

void qlSabrSmileSectionDataReaderListenerImpl::on_reading_end( DDS::DataReader_ptr reader, int count )
{
  ACE_DEBUG((LM_INFO,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("qlSabrSmileSectionDataReaderListenerImpl::on_reading_end with %d items.\n"), count));
}

bool qlSabrSmileSectionDataReaderListenerImpl::pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, smilesection::qlSabrSmileSection& )
{
  return true;
}

bool qlSabrSmileSectionDataReaderListenerImpl::post_quantlib_addin_call( DDS::DataReader_ptr reader, smilesection::qlSabrSmileSection&, std::string& )
{
  return true;
}

void qlSabrSmileSectionDataReaderListenerImpl::on_std_exception( DDS::DataReader_ptr reader, smilesection::qlSabrSmileSection&, std::exception& e )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSabrSmileSectionDataReaderListenerImpl::on_std_exception %s\n"), e.what() ));
}

void qlSabrSmileSectionDataReaderListenerImpl::on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSabrSmileSectionDataReaderListenerImpl::on_dds_reading_error %s\n"), err.c_str() ));
}

void qlSabrSmileSectionDataReaderListenerImpl::on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp )
{
  ACE_ERROR((LM_WARNING,
             ACE_TEXT("(%P|%t) WARNING: ")
             ACE_TEXT("qlSabrSmileSectionDataReaderListenerImpl::on_dds_reading_error %s\n"), exp._info().c_str() ));
}
}
