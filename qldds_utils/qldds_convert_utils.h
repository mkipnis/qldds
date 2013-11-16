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

 inline CORBA::StringSeq convertStringVector( std::vector<std::string>& strVector )
 {
   CORBA::StringSeq strSeq;
   strSeq.length( strVector.size() );

   for( unsigned int tt = 0; tt<strVector.size(); tt++ )
     strSeq[tt] = CORBA::string_dup( strVector[tt].c_str() );

   return strSeq;
  }

  inline long from_iso_string( const char* iso_date )
  {
    if ( iso_date == NULL || strlen(iso_date) == 0 )
      return 0;

    boost::gregorian::date date ( boost::gregorian::from_undelimited_string(iso_date) );

    return QuantLib::Date( date.day(), QuantLib::Month(date.month().as_number()), date.year() ).serialNumber();
  }

  inline ObjectHandler::property_t from_iso_string_to_oh_property( std::string iso_date )
  {
    if ( iso_date.empty() )
      return OH_NULL;

    boost::gregorian::date date ( boost::gregorian::from_undelimited_string(iso_date) );

    return ObjectHandler::property_t(QuantLib::Date( date.day(), QuantLib::Month(date.month().as_number()), date.year() ).serialNumber());
  }

  inline ObjectHandler::property_t double_to_RelinkableHandle( double quote )
  {
    boost::shared_ptr<QuantLib::SimpleQuote> cp( new QuantLib::SimpleQuote( quote ) );

    QuantLib::RelinkableHandle<QuantLib::Quote> quoteHandle;

    quoteHandle.linkTo( cp );

    return ObjectHandler::property_t(cp);
  }

  template<class QL_TYPE, class DDS_TYPE>
  std::vector<QL_TYPE> vector_cast( DDS_TYPE& data )
  {
    std::vector<QL_TYPE> ql_data( data.length() );

    for ( unsigned int tt = 0; tt<data.length(); tt++ )
      ql_data[tt] = data[tt];

     return ql_data;
  }

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
