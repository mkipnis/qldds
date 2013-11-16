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


#ifndef DATAREADERIMPLHANDLER_HPP
#define DATAREADERIMPLHANDLER_HPP

#include <dds/DdsDcpsSubscriptionS.h>
#include <dds/DCPS/Service_Participant.h>

namespace qldds_utils 
{
  class DataReaderImplHandler : public virtual OpenDDS::DCPS::LocalObject<DDS::DataReaderListener>
  {
    public:

      // Methods below will be called from on_data_available method in each of the *DataReaderListenerImpl in Addins/OpenDDS
      virtual void on_reading_start( DDS::DataReader_ptr& reader );
      virtual void on_reading_end( DDS::DataReader_ptr& reader, int count ); 
      virtual bool pre_quantlib_addin_call( DDS::DataReader_ptr& reader, const char* qlType, void* qlddsObj );
      virtual bool post_quantlib_addin_call( DDS::DataReader_ptr& reader, const char* qlType, void* qlddsObj, const char* returnType, void* returnObject );
      virtual void on_std_exception( DDS::DataReader_ptr& reader, void* obj, std::exception& e );
      virtual void on_dds_reading_error( DDS::DataReader_ptr& reader, std::string& err ); 
      virtual void on_dds_exception( DDS::DataReader_ptr& reader, CORBA::Exception& exp );

      // Methods below will be called from other methods in each of the *DataReaderListenerImpl in Addins/DDS
      virtual void on_data_available( DDS::DataReader_ptr reader)
        throw (CORBA::SystemException);

      virtual void on_requested_deadline_missed ( DDS::DataReader_ptr reader, const DDS::RequestedDeadlineMissedStatus & status)
        throw (CORBA::SystemException);

      virtual void on_requested_incompatible_qos ( DDS::DataReader_ptr reader, const DDS::RequestedIncompatibleQosStatus & status)
        throw (CORBA::SystemException);

      virtual void on_liveliness_changed ( DDS::DataReader_ptr reader, const DDS::LivelinessChangedStatus & status)
        throw (CORBA::SystemException);

      virtual void on_subscription_matched ( DDS::DataReader_ptr reader, const DDS::SubscriptionMatchedStatus & status)
        throw (CORBA::SystemException);

      virtual void on_sample_rejected( DDS::DataReader_ptr reader, const DDS::SampleRejectedStatus& status)
        throw (CORBA::SystemException);

      virtual void on_sample_lost( DDS::DataReader_ptr reader, const DDS::SampleLostStatus& status)
        throw (CORBA::SystemException);

  };

};

#include "DataReaderImplHandler.inl"

#endif
