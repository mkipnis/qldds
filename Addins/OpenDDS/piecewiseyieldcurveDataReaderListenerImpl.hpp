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
#include <qlo/piecewiseyieldcurve.hpp>
#include <qlo/ratehelpers.hpp>
#include <qlo/handleimpl.hpp>
#include <ql/interestrate.hpp>
#include <qlo/conversions/coercetermstructure.hpp>
#include <qlo/valueobjects/vo_piecewiseyieldcurve.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

#if defined(_MSC_VER) || defined(_WIN32) 
#include <Addins/Cpp/piecewiseyieldcurve.hpp>
#else
#include <qlo/Addins/Cpp/piecewiseyieldcurve.hpp>
#endif

#include "piecewiseyieldcurveTypeSupportC.h"

#include <DataReaderListener.hpp>

namespace piecewiseyieldcurve
{
  
  class qlPiecewiseYieldCurveDataReaderListenerImpl
    : public virtual OpenDDS::DCPS::LocalObject<qldds::DataReaderListener< piecewiseyieldcurve::qlPiecewiseYieldCurve, std::string > >
  {
    public:
    
      qlPiecewiseYieldCurveDataReaderListenerImpl( ACE_Mutex& mutex ) : _mutex( mutex ) {}; 
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

      virtual bool pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, piecewiseyieldcurve::qlPiecewiseYieldCurve& );

      virtual bool post_quantlib_addin_call( DDS::DataReader_ptr reader, piecewiseyieldcurve::qlPiecewiseYieldCurve&, std::string& );

      virtual void on_std_exception( DDS::DataReader_ptr reader, piecewiseyieldcurve::qlPiecewiseYieldCurve&, std::exception& e );

      virtual void on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err );

      virtual void on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp );

    protected:
      ACE_Mutex& _mutex;

  };

;
}
