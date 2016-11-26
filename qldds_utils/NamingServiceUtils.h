
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
