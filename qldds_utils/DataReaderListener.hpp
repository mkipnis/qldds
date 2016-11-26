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
