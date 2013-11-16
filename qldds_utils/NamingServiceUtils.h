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


#ifndef __NAMING_SERVICE_UTILS_H__
#define __NAMING_SERVICE_UTILS_H__

#include <orbsvcs/Naming/Naming_Client.h>
#include <tao/Intrusive_Ref_Count_Handle_T.h>

// Wrapper classes for TAO Naming Service

namespace qldds_utils
{
  namespace NamingService 
  {

    // TAO Naming Service Client
    template< class ServerInterface >
    class Client
    {
      public:
        Client();
        virtual ~Client();

        virtual int Init( CORBA::ORB_ptr orb, const char* name );

        ServerInterface *operator-> () { return _server.in (); }
      
        typedef TAO_Intrusive_Ref_Count_Handle<ServerInterface> ServerInterface_var;
        typedef ServerInterface* ServerInterface_ptr;

        ServerInterface_ptr ServerInterfaceVar()
        {
          return CORBA::ORB::_duplicate ( _server.in() );
        }

      private:    
        ServerInterface_var _server;

        TAO_Naming_Client _naming_client;
    };


    // TAO Naming Service Server 
    template< class Servant > 
    class Server
    {
      public:
        //
        // This constructor instantiate a Servant and passes a reference to a mutex lock
        // which is being used to synchronize QuantLibAddin calls. 
        // 
        Server( ACE_Mutex& mutex );
        virtual ~Server();

        int Init(  CORBA::ORB_ptr orb, const char* name );

        typedef TAO_Intrusive_Ref_Count_Handle<Servant> Servant_var;
        typedef Servant* Servant_ptr;

        Servant_ptr ServantVar()
        {
          return CORBA::ORB::_duplicate ( _servant.in() );
        }

      private:

        Servant_var _servant;

        TAO_Naming_Client _naming_client;
    };
  }
}

#include "NamingServiceUtils.inl"

#endif __NAMING_SERVICE_UTILS_H__
