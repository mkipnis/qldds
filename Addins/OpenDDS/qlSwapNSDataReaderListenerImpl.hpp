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
//      git/qldds/gensrc/stubs/stub.opendds.header

#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <qlo/swap.hpp>
#include <qlo/termstructures.hpp>
#include <qlo/conundrumpricer.hpp>
#include <qlo/indexes/iborindex.hpp>
#include <qlo/indexes/swapindex.hpp>
#include <ql/instruments/swap.hpp>
#include <ql/indexes/iborindex.hpp>
#include <ql/indexes/swapindex.hpp>
#include <ql/termstructures/yieldtermstructure.hpp>
#include <qlo/valueobjects/vo_swap.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

#if defined(_MSC_VER) || defined(_WIN32) 
#include <Addins/Cpp/swap.hpp>
#else
#include <qlo/Addins/Cpp/swap.hpp>
#endif

#include "qlSwapNSTypeSupportC.h"

#include <DataReaderListener.hpp>

namespace qlSwapNS
{
  
  class qlMakeCmsDataReaderListenerImpl
    : public virtual OpenDDS::DCPS::LocalObject<qldds::DataReaderListener< qlSwapNS::qlMakeCms, std::string > >
  {
    public:
    
      qlMakeCmsDataReaderListenerImpl( ACE_Mutex& mutex ) : _mutex( mutex ) {}; 
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

      virtual bool pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, qlSwapNS::qlMakeCms& );

      virtual bool post_quantlib_addin_call( DDS::DataReader_ptr reader, qlSwapNS::qlMakeCms&, std::string& );

      virtual void on_std_exception( DDS::DataReader_ptr reader, qlSwapNS::qlMakeCms&, std::exception& e );

      virtual void on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err );

      virtual void on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp );

    protected:
      ACE_Mutex& _mutex;

  };

  
  class qlSwapDataReaderListenerImpl
    : public virtual OpenDDS::DCPS::LocalObject<qldds::DataReaderListener< qlSwapNS::qlSwap, std::string > >
  {
    public:
    
      qlSwapDataReaderListenerImpl( ACE_Mutex& mutex ) : _mutex( mutex ) {}; 
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

      virtual bool pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, qlSwapNS::qlSwap& );

      virtual bool post_quantlib_addin_call( DDS::DataReader_ptr reader, qlSwapNS::qlSwap&, std::string& );

      virtual void on_std_exception( DDS::DataReader_ptr reader, qlSwapNS::qlSwap&, std::exception& e );

      virtual void on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err );

      virtual void on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp );

    protected:
      ACE_Mutex& _mutex;

  };

;
}
