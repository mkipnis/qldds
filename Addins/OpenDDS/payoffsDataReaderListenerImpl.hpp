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
//      ocm/qldds/gensrc/stubs/stub.opendds.header

#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <qlo/stickyratchet.hpp>
#include <qlo/valueobjects/vo_payoffs.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

#if defined(_MSC_VER) || defined(_WIN32) 
#include <Addins/Cpp/payoffs.hpp>
#else
#include <qlo/Addins/Cpp/payoffs.hpp>
#endif

#include "payoffsTypeSupportC.h"

#include <DataReaderListener.hpp>

namespace payoffs
{
  
  class qlDoubleStickyRatchetPayoffDataReaderListenerImpl
    : public virtual OpenDDS::DCPS::LocalObject<qldds::DataReaderListener< payoffs::qlDoubleStickyRatchetPayoff, std::string > >
  {
    public:
    
      qlDoubleStickyRatchetPayoffDataReaderListenerImpl( ACE_Mutex& mutex ) : _mutex( mutex ) {}; 
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

      virtual bool pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, payoffs::qlDoubleStickyRatchetPayoff& );

      virtual bool post_quantlib_addin_call( DDS::DataReader_ptr reader, payoffs::qlDoubleStickyRatchetPayoff&, std::string& );

      virtual void on_std_exception( DDS::DataReader_ptr reader, payoffs::qlDoubleStickyRatchetPayoff&, std::exception& e );

      virtual void on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err );

      virtual void on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp );

    protected:
      ACE_Mutex& _mutex;

  };

  
  class qlRatchetMaxPayoffDataReaderListenerImpl
    : public virtual OpenDDS::DCPS::LocalObject<qldds::DataReaderListener< payoffs::qlRatchetMaxPayoff, std::string > >
  {
    public:
    
      qlRatchetMaxPayoffDataReaderListenerImpl( ACE_Mutex& mutex ) : _mutex( mutex ) {}; 
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

      virtual bool pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, payoffs::qlRatchetMaxPayoff& );

      virtual bool post_quantlib_addin_call( DDS::DataReader_ptr reader, payoffs::qlRatchetMaxPayoff&, std::string& );

      virtual void on_std_exception( DDS::DataReader_ptr reader, payoffs::qlRatchetMaxPayoff&, std::exception& e );

      virtual void on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err );

      virtual void on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp );

    protected:
      ACE_Mutex& _mutex;

  };

  
  class qlRatchetMinPayoffDataReaderListenerImpl
    : public virtual OpenDDS::DCPS::LocalObject<qldds::DataReaderListener< payoffs::qlRatchetMinPayoff, std::string > >
  {
    public:
    
      qlRatchetMinPayoffDataReaderListenerImpl( ACE_Mutex& mutex ) : _mutex( mutex ) {}; 
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

      virtual bool pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, payoffs::qlRatchetMinPayoff& );

      virtual bool post_quantlib_addin_call( DDS::DataReader_ptr reader, payoffs::qlRatchetMinPayoff&, std::string& );

      virtual void on_std_exception( DDS::DataReader_ptr reader, payoffs::qlRatchetMinPayoff&, std::exception& e );

      virtual void on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err );

      virtual void on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp );

    protected:
      ACE_Mutex& _mutex;

  };

  
  class qlRatchetPayoffDataReaderListenerImpl
    : public virtual OpenDDS::DCPS::LocalObject<qldds::DataReaderListener< payoffs::qlRatchetPayoff, std::string > >
  {
    public:
    
      qlRatchetPayoffDataReaderListenerImpl( ACE_Mutex& mutex ) : _mutex( mutex ) {}; 
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

      virtual bool pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, payoffs::qlRatchetPayoff& );

      virtual bool post_quantlib_addin_call( DDS::DataReader_ptr reader, payoffs::qlRatchetPayoff&, std::string& );

      virtual void on_std_exception( DDS::DataReader_ptr reader, payoffs::qlRatchetPayoff&, std::exception& e );

      virtual void on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err );

      virtual void on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp );

    protected:
      ACE_Mutex& _mutex;

  };

  
  class qlStickyMaxPayoffDataReaderListenerImpl
    : public virtual OpenDDS::DCPS::LocalObject<qldds::DataReaderListener< payoffs::qlStickyMaxPayoff, std::string > >
  {
    public:
    
      qlStickyMaxPayoffDataReaderListenerImpl( ACE_Mutex& mutex ) : _mutex( mutex ) {}; 
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

      virtual bool pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, payoffs::qlStickyMaxPayoff& );

      virtual bool post_quantlib_addin_call( DDS::DataReader_ptr reader, payoffs::qlStickyMaxPayoff&, std::string& );

      virtual void on_std_exception( DDS::DataReader_ptr reader, payoffs::qlStickyMaxPayoff&, std::exception& e );

      virtual void on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err );

      virtual void on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp );

    protected:
      ACE_Mutex& _mutex;

  };

  
  class qlStickyMinPayoffDataReaderListenerImpl
    : public virtual OpenDDS::DCPS::LocalObject<qldds::DataReaderListener< payoffs::qlStickyMinPayoff, std::string > >
  {
    public:
    
      qlStickyMinPayoffDataReaderListenerImpl( ACE_Mutex& mutex ) : _mutex( mutex ) {}; 
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

      virtual bool pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, payoffs::qlStickyMinPayoff& );

      virtual bool post_quantlib_addin_call( DDS::DataReader_ptr reader, payoffs::qlStickyMinPayoff&, std::string& );

      virtual void on_std_exception( DDS::DataReader_ptr reader, payoffs::qlStickyMinPayoff&, std::exception& e );

      virtual void on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err );

      virtual void on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp );

    protected:
      ACE_Mutex& _mutex;

  };

  
  class qlStickyPayoffDataReaderListenerImpl
    : public virtual OpenDDS::DCPS::LocalObject<qldds::DataReaderListener< payoffs::qlStickyPayoff, std::string > >
  {
    public:
    
      qlStickyPayoffDataReaderListenerImpl( ACE_Mutex& mutex ) : _mutex( mutex ) {}; 
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

      virtual bool pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, payoffs::qlStickyPayoff& );

      virtual bool post_quantlib_addin_call( DDS::DataReader_ptr reader, payoffs::qlStickyPayoff&, std::string& );

      virtual void on_std_exception( DDS::DataReader_ptr reader, payoffs::qlStickyPayoff&, std::exception& e );

      virtual void on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err );

      virtual void on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp );

    protected:
      ACE_Mutex& _mutex;

  };

  
  class qlStrikedTypePayoffDataReaderListenerImpl
    : public virtual OpenDDS::DCPS::LocalObject<qldds::DataReaderListener< payoffs::qlStrikedTypePayoff, std::string > >
  {
    public:
    
      qlStrikedTypePayoffDataReaderListenerImpl( ACE_Mutex& mutex ) : _mutex( mutex ) {}; 
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

      virtual bool pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, payoffs::qlStrikedTypePayoff& );

      virtual bool post_quantlib_addin_call( DDS::DataReader_ptr reader, payoffs::qlStrikedTypePayoff&, std::string& );

      virtual void on_std_exception( DDS::DataReader_ptr reader, payoffs::qlStrikedTypePayoff&, std::exception& e );

      virtual void on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err );

      virtual void on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp );

    protected:
      ACE_Mutex& _mutex;

  };

;
}
