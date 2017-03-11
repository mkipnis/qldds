
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


#ifndef __CONVERT_UTILS_H__ 
#define __CONVERT_UTILS_H__

#include <vector>
#include <string>
#include <oh/property.hpp>
#include <dds/DdsDcpsSubscriptionS.h>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <ql/quantlib.hpp>

#include "qldds_typesC.h"

#define OH_NULL ObjectHandler::property_t()

namespace qldds_utils
{

  //
  // Converts ISO date string into a SerialNumber
  //
  inline long from_iso_string( const char* iso_date )
  {
    if ( iso_date == NULL || strlen(iso_date) == 0 )
      return 0;

    boost::gregorian::date date ( boost::gregorian::from_string(iso_date) );

    return QuantLib::Date( date.day(), QuantLib::Month(date.month().as_number()), date.year() ).serialNumber();
  }

  //
  // Converts ISO date string into an ObjectHandler::property_t
  //
  inline ObjectHandler::property_t from_iso_string_to_oh_property( std::string iso_date )
  {
    if ( iso_date.empty() )
      return OH_NULL;

    boost::gregorian::date date ( boost::gregorian::from_string(iso_date) );

    return ObjectHandler::property_t(QuantLib::Date( date.day(), QuantLib::Month(date.month().as_number()), date.year() ).serialNumber());
  }

  //
  // Converts double into a QuantLib::RelinkableHandle<QuantLib::Quote>
  //
  inline ObjectHandler::property_t double_to_RelinkableHandle( double quote )
  {
    boost::shared_ptr<QuantLib::SimpleQuote> cp( new QuantLib::SimpleQuote( quote ) );

    QuantLib::RelinkableHandle<QuantLib::Quote> quoteHandle;

    quoteHandle.linkTo( cp );

    return ObjectHandler::property_t(cp);
  }

  //
  // Converts std::vector<type> to CORBA::typeSeq
  //
  template<class QL_TYPE, class DDS_TYPE>
  std::vector<QL_TYPE> vector_cast( DDS_TYPE& data )
  {
    std::vector<QL_TYPE> ql_data( data.length() );

    for ( unsigned int tt = 0; tt<data.length(); tt++ )
      ql_data[tt] = data[tt];

     return ql_data;
  }

  //
  // Converts std::vector<std::string> to CORBA::StringSeq
  //
  template<class QL_TYPE, class DDS_TYPE>
  static std::vector<QL_TYPE> vector_cast_str( DDS_TYPE& data )
  {
    std::vector<QL_TYPE> ql_data( data.length() );

    for ( unsigned int tt = 0; tt<data.length(); tt++ )
    {
      ql_data[tt] = data[tt].in();
    }

     return ql_data;
  }


  //
  // Converts Matrix from CORBA Types to QuantLib types
  //
  template<class QL_TYPE, class DDS_TYPE>
  static std::vector< std::vector < QL_TYPE > > matrix_cast( DDS_TYPE& data )
  {
    std::vector< std::vector< QL_TYPE > > ql_data( data.length() );

    for ( unsigned int tt = 0; tt<data.length(); tt++ )
    {
      std::vector< QL_TYPE > ql_data_x( data[tt].length() );

      for ( unsigned int pp = 0; pp<data[tt].length(); pp++ )
      {
        ql_data_x[pp] = data[tt][pp];
      }

      ql_data[tt] = ql_data_x;
     }

     return ql_data;
  }
};

#endif
