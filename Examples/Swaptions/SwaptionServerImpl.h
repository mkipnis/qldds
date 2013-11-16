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


#ifndef __SWAPTION_SERVER_IMPL_H__
#define __SWAPTION_SERVER_IMPL_H__

#include "SwaptionServerS.h"

#include <ace/Mutex.h>

class SwaptionServerImpl :
    public POA_SwaptionServer::SwaptionCalculator
{
  public:
    SwaptionServerImpl( ACE_Mutex& mutex ) : _mutex( mutex ) {};
    virtual ~SwaptionServerImpl() {};

    virtual ::CORBA::Boolean CalculateATM(
        const ::SwaptionServer::Swaption& option,
        ::CORBA::Double_out npv,
        ::CORBA::Double_out atm_rate,
        ::CORBA::String_out error );

  private:
    ACE_Mutex& _mutex;

};

#endif
