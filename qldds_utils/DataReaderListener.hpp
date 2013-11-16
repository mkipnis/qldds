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


#ifndef DATAREADERLISTENER_HPP
#define DATAREADERLISTENER_HPP

#include <dds/DdsDcpsSubscriptionS.h>
#include <dds/DCPS/Service_Participant.h>

namespace qldds 
{
  template < class QLDDS_Object, class QuantLibAddin_Return_Object >
  class DataReaderListener : public virtual DDS::DataReaderListener
  {
    public:

      // Methods below will be called from on_data_available method in each of the *DataReaderListenerImpl in Addins/OpenDDS
      virtual void on_reading_start( DDS::DataReader_ptr reader ) = 0;

      virtual void on_reading_end( DDS::DataReader_ptr reader, int count ) = 0;

      virtual bool pre_quantlib_addin_call( DDS::DataReader_ptr reader, DDS::SampleInfo&, QLDDS_Object& ) = 0;
 
      virtual bool post_quantlib_addin_call( DDS::DataReader_ptr reader, QLDDS_Object&, QuantLibAddin_Return_Object& ) = 0;

      virtual void on_std_exception( DDS::DataReader_ptr reader, QLDDS_Object&, std::exception& e ) = 0;

      virtual void on_dds_reading_error( DDS::DataReader_ptr reader, std::string& err ) = 0;
 
      virtual void on_dds_exception( DDS::DataReader_ptr reader, CORBA::Exception& exp ) = 0;
  };

};

#endif
