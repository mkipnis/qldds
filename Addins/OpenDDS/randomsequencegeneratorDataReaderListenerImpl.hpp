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
//      Users/mkipnis/qldds/gensrc/stubs/stub.opendds.header

#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <qlo/randomsequencegenerator.hpp>
#include <qlo/valueobjects/vo_randomsequencegenerator.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

#if defined(_MSC_VER) || defined(_WIN32) 
#include <Addins/Cpp/randomsequencegenerator.hpp>
#else
#include <qlo/Addins/Cpp/randomsequencegenerator.hpp>
#endif

#include "randomsequencegeneratorTypeSupportC.h"

#include <DataReaderListener.hpp>

namespace randomsequencegenerator
{
  
  class qlFaureRsgDataReaderListenerImpl
    : public virtual OpenDDS::DCPS::LocalObject<qldds::DataReaderListener< randomsequencegenerator::qlFaureRsg, std::string > >
  {
    public:
    
      qlFaureRsgDataReaderListenerImpl( ACE_Mutex& mutex ) : _mutex( mutex ) {}; 
      virtual void on_data_available( DDS::DataReader_ptr reader) throw (CORBA::SystemException);

      ACE_Mutex& get_ACE_Mutex() { return _mutex; };

      virtual void on_requested_deadline_missed ( DDS::DataReader_ptr reader, const DDS::RequestedDeadlineMissedStatus & status) throw (CORBA::SystemException);
    
      virtual void on_requested_incompatible_qos ( DDS::DataReader_ptr reader, const DDS::RequestedIncompatibleQosStatus & status) throw (CORBA::SystemException);
  
      virtual void on_liveliness_changed ( DDS::DataReader_ptr reader, const DDS::LivelinessChangedStatus & status) throw (CORBA::SystemException);
    
      virtual void on_subscription_matched ( DDS::DataReader_ptr reader, const DDS::SubscriptionMatchedStatus & status) throw (CORBA::SystemException);

      virtual void on_sample_rejected( DDS::DataReader_ptr reader, const DDS::SampleRejectedStatus& status) throw (CORBA::SystemException);

      virtual void on_sample_lost( DDS::DataReader_ptr reader, const DDS::SampleLostStatus& status) throw (CORBA::SystemException); 

      virtual void on_reading_start( DDS::DataReader_ptr reader );

      virtual void on_reading_end( DDS::DataReader_ptr reader, int count );

      virtual bool pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, randomsequencegenerator::qlFaureRsg& );

      virtual bool post_quantlib_addin_call( DDS::DataReader_ptr reader, randomsequencegenerator::qlFaureRsg&, std::string& );

      virtual void on_std_exception( DDS::DataReader_ptr reader, randomsequencegenerator::qlFaureRsg&, std::exception& e );

      virtual void on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err );

      virtual void on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp );

    protected:
      ACE_Mutex& _mutex;

  };

  
  class qlHaltonRsgDataReaderListenerImpl
    : public virtual OpenDDS::DCPS::LocalObject<qldds::DataReaderListener< randomsequencegenerator::qlHaltonRsg, std::string > >
  {
    public:
    
      qlHaltonRsgDataReaderListenerImpl( ACE_Mutex& mutex ) : _mutex( mutex ) {}; 
      virtual void on_data_available( DDS::DataReader_ptr reader) throw (CORBA::SystemException);

      ACE_Mutex& get_ACE_Mutex() { return _mutex; };

      virtual void on_requested_deadline_missed ( DDS::DataReader_ptr reader, const DDS::RequestedDeadlineMissedStatus & status) throw (CORBA::SystemException);
    
      virtual void on_requested_incompatible_qos ( DDS::DataReader_ptr reader, const DDS::RequestedIncompatibleQosStatus & status) throw (CORBA::SystemException);
  
      virtual void on_liveliness_changed ( DDS::DataReader_ptr reader, const DDS::LivelinessChangedStatus & status) throw (CORBA::SystemException);
    
      virtual void on_subscription_matched ( DDS::DataReader_ptr reader, const DDS::SubscriptionMatchedStatus & status) throw (CORBA::SystemException);

      virtual void on_sample_rejected( DDS::DataReader_ptr reader, const DDS::SampleRejectedStatus& status) throw (CORBA::SystemException);

      virtual void on_sample_lost( DDS::DataReader_ptr reader, const DDS::SampleLostStatus& status) throw (CORBA::SystemException); 

      virtual void on_reading_start( DDS::DataReader_ptr reader );

      virtual void on_reading_end( DDS::DataReader_ptr reader, int count );

      virtual bool pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, randomsequencegenerator::qlHaltonRsg& );

      virtual bool post_quantlib_addin_call( DDS::DataReader_ptr reader, randomsequencegenerator::qlHaltonRsg&, std::string& );

      virtual void on_std_exception( DDS::DataReader_ptr reader, randomsequencegenerator::qlHaltonRsg&, std::exception& e );

      virtual void on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err );

      virtual void on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp );

    protected:
      ACE_Mutex& _mutex;

  };

  
  class qlMersenneTwisterRsgDataReaderListenerImpl
    : public virtual OpenDDS::DCPS::LocalObject<qldds::DataReaderListener< randomsequencegenerator::qlMersenneTwisterRsg, std::string > >
  {
    public:
    
      qlMersenneTwisterRsgDataReaderListenerImpl( ACE_Mutex& mutex ) : _mutex( mutex ) {}; 
      virtual void on_data_available( DDS::DataReader_ptr reader) throw (CORBA::SystemException);

      ACE_Mutex& get_ACE_Mutex() { return _mutex; };

      virtual void on_requested_deadline_missed ( DDS::DataReader_ptr reader, const DDS::RequestedDeadlineMissedStatus & status) throw (CORBA::SystemException);
    
      virtual void on_requested_incompatible_qos ( DDS::DataReader_ptr reader, const DDS::RequestedIncompatibleQosStatus & status) throw (CORBA::SystemException);
  
      virtual void on_liveliness_changed ( DDS::DataReader_ptr reader, const DDS::LivelinessChangedStatus & status) throw (CORBA::SystemException);
    
      virtual void on_subscription_matched ( DDS::DataReader_ptr reader, const DDS::SubscriptionMatchedStatus & status) throw (CORBA::SystemException);

      virtual void on_sample_rejected( DDS::DataReader_ptr reader, const DDS::SampleRejectedStatus& status) throw (CORBA::SystemException);

      virtual void on_sample_lost( DDS::DataReader_ptr reader, const DDS::SampleLostStatus& status) throw (CORBA::SystemException); 

      virtual void on_reading_start( DDS::DataReader_ptr reader );

      virtual void on_reading_end( DDS::DataReader_ptr reader, int count );

      virtual bool pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, randomsequencegenerator::qlMersenneTwisterRsg& );

      virtual bool post_quantlib_addin_call( DDS::DataReader_ptr reader, randomsequencegenerator::qlMersenneTwisterRsg&, std::string& );

      virtual void on_std_exception( DDS::DataReader_ptr reader, randomsequencegenerator::qlMersenneTwisterRsg&, std::exception& e );

      virtual void on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err );

      virtual void on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp );

    protected:
      ACE_Mutex& _mutex;

  };

  
  class qlSobolRsgDataReaderListenerImpl
    : public virtual OpenDDS::DCPS::LocalObject<qldds::DataReaderListener< randomsequencegenerator::qlSobolRsg, std::string > >
  {
    public:
    
      qlSobolRsgDataReaderListenerImpl( ACE_Mutex& mutex ) : _mutex( mutex ) {}; 
      virtual void on_data_available( DDS::DataReader_ptr reader) throw (CORBA::SystemException);

      ACE_Mutex& get_ACE_Mutex() { return _mutex; };

      virtual void on_requested_deadline_missed ( DDS::DataReader_ptr reader, const DDS::RequestedDeadlineMissedStatus & status) throw (CORBA::SystemException);
    
      virtual void on_requested_incompatible_qos ( DDS::DataReader_ptr reader, const DDS::RequestedIncompatibleQosStatus & status) throw (CORBA::SystemException);
  
      virtual void on_liveliness_changed ( DDS::DataReader_ptr reader, const DDS::LivelinessChangedStatus & status) throw (CORBA::SystemException);
    
      virtual void on_subscription_matched ( DDS::DataReader_ptr reader, const DDS::SubscriptionMatchedStatus & status) throw (CORBA::SystemException);

      virtual void on_sample_rejected( DDS::DataReader_ptr reader, const DDS::SampleRejectedStatus& status) throw (CORBA::SystemException);

      virtual void on_sample_lost( DDS::DataReader_ptr reader, const DDS::SampleLostStatus& status) throw (CORBA::SystemException); 

      virtual void on_reading_start( DDS::DataReader_ptr reader );

      virtual void on_reading_end( DDS::DataReader_ptr reader, int count );

      virtual bool pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, randomsequencegenerator::qlSobolRsg& );

      virtual bool post_quantlib_addin_call( DDS::DataReader_ptr reader, randomsequencegenerator::qlSobolRsg&, std::string& );

      virtual void on_std_exception( DDS::DataReader_ptr reader, randomsequencegenerator::qlSobolRsg&, std::exception& e );

      virtual void on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err );

      virtual void on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp );

    protected:
      ACE_Mutex& _mutex;

  };

;
}
