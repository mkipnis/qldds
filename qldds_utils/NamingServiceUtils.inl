
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


#include "NamingServiceUtils.h"

using namespace qldds_utils::NamingService;

template< class ServerInterface >
Client< ServerInterface >::Client()
{
}

template< class ServerInterface >
Client< ServerInterface >::~Client()
{
}

template< class ServerInterface >
int Client< ServerInterface >::Init( CORBA::ORB_ptr orb, const char* name )
{
  try
  {
    // Initialize the naming services.
    if ( _naming_client.init ( orb ) != 0 )
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                        ACE_TEXT ("[CLIENT] Process/Thread Id : (%P/%t) Unable to initialize ")
                        ACE_TEXT ("the TAO_Naming_Client. \n")),
                        -1);
    } 

    CosNaming::Name server_name (1);
    server_name.length (1);
    server_name[0].id = CORBA::string_dup (name);
    CORBA::Object_var obj = _naming_client->resolve (server_name);

    _server = ServerInterface::_narrow (obj.in ());

    if (CORBA::is_nil ( _server.in ()))
    {
      ACE_ERROR_RETURN ((LM_ERROR, ACE_TEXT ("Nil Server\n")), -1);
    }
  }
  catch (const CORBA::Exception& ex)
  {
    ex._tao_print_exception ("Client::Init");
    return -1;
  }

  return 0;
}


template< class Servant >
Server< Servant >::Server( ACE_Mutex& mutex )
{
  Servant *tmp = 0;
  ACE_NEW_THROW_EX (tmp, Servant ( mutex ), CORBA::NO_MEMORY ());
  _servant = tmp; 
}


template< class Servant >
Server< Servant >::~Server() 
{
};

template< class Servant >
int 
Server< Servant >::Init( CORBA::ORB_ptr orb, const char* name )
{
  if ( _naming_client.init( orb ) == -1 )
   return -1;

  CosNaming::Name bindName;
  bindName.length (1);
  bindName[0].id = CORBA::string_dup (name);

  try
  {

    CORBA::Object_var object = _servant->_this ();
    _naming_client->rebind (bindName, object.in());

  } catch ( const CosNaming::NamingContext::AlreadyBound& )
  {
    ACE_ERROR_RETURN ((LM_ERROR, ACE_TEXT ("Unable to bind %C \n"), name), -1);
  }

  return 0;
}
