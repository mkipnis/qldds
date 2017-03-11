
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


#include <BasicDomainParticipant.h>
#include <ace/Get_Opt.h>

#include <NamingServiceUtils.h>

#include "SwaptionServerC.h"

#include "Common.h"

int ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
  try {

    DDS::DomainParticipantFactory_var dpf = DDS::DomainParticipantFactory::_nil();
    DDS::DomainParticipant_var participant = DDS::DomainParticipant::_nil();


    // Initialize, and create a DomainParticipant
    dpf = TheParticipantFactoryWithArgs(argc, argv);

    qldds_utils::BasicDomainParticipant volPublisher( dpf, SWAPTION_DOMAIN_ID );
    volPublisher.createPublisher();

    CORBA::ORB_var orb = CORBA::ORB_init(argc, argv, "SwaptionServerORB");

    // CORBA Client to facilitate calculator calls
    qldds_utils::NamingService::Client< SwaptionServer::SwaptionCalculator > ns_client1;
    ns_client1.Init( orb, "SwaptionServer1");

    qldds_utils::NamingService::Client< SwaptionServer::SwaptionCalculator > ns_client2;
    ns_client2.Init( orb, "SwaptionServer2");

    ACE_Get_Opt cmd_opts( argc, argv, ":c:" ); 

    int option;
    
    std::vector<std::string> curve_components;

    while ( (option = cmd_opts()) != EOF )
    {
      switch( option )
      { 
        case 'c' :

         std::istringstream f( cmd_opts.opt_arg() );
         std::string s;

         while (std::getline(f, s, '|')) {
           curve_components.push_back(s);
         }

        break;
      }
    } 

	CORBA::StringSeq curve;
    curve.length( curve_components.size() ); 
    
    // Copy curve from std::vector to CORBA string array
    for ( int cc = 0; cc < curve_components.size(); cc++ ) 
    {
      std::cout <<  curve_components[cc] << std::endl;
      curve[cc] = CORBA::string_dup( curve_components[cc].c_str() );
    }

    // for ( int tt = 0; tt<10; tt++ )
    {
      SwaptionServer::Swaption ss;
      CORBA::Double npv;
      CORBA::Double rate;
      CORBA::String_var error;

      ss.curve_components = curve;

      ss.surface_name = CORBA::string_dup( "SwaptionVTSMatrix" );
 
      for ( int month = 1; month<=12; month++ )
      {
        for ( int year = 1; year<=15; year++ )
        {
          std::stringstream swaption_tenor;
          swaption_tenor << month << "M";

          std::stringstream swap_tenor;
          swap_tenor << year << "Y";

          ss.option_period = CORBA::string_dup( swaption_tenor.str().c_str() );
          ss.swap_period = CORBA::string_dup( swap_tenor.str().c_str() );

          bool status;

	  // Round Robin between servers
          if ( (month+year)%2 == 0 )
             status = ns_client1->CalculateATM( ss, npv, rate, error );
          else
             status = ns_client2->CalculateATM( ss, npv, rate, error );
 
          if ( status )
          {
            std::string swaption;
            swaption = swaption_tenor.str();
            swaption += "/"; 
            swaption += swap_tenor.str(); 

            std::cout << "Swaption : " 
                    << std::setprecision(5)  
                    << std::setw(10) << swaption << " | "
                    << std::setw(10) << "NPV=" << std::setw(10) << npv << " | "
                    << std::setw(10) << "Swap Rate=" << std::setw(10) << rate << std::endl;
          }
        }
      }
    }

    std::cout << "Done." << std::endl;

    orb->destroy ();

  } catch (CORBA::Exception& e) {
    e._tao_print_exception("CORBA Exception caught in main():");
    return 0;
  } catch (...)
  {
    std::cerr << "Exception caught in main():" << std::endl;
    return 0;
  }

  TheServiceParticipant->shutdown(); 

  return 0;
}
