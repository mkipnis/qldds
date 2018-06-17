
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


#include <vector>
#include <oh/repository.hpp>
#include <ql/quantlib.hpp>

#include <Addins/Cpp/addincpp.hpp>

#include <qlo/conversions/coercetermstructure.hpp>
#include <qlo/indexes/swap/liborswap.hpp>
#include <qlo/swaption.hpp>
#include <qlo/vanillaswap.hpp>


#include "SwaptionServerImpl.h"

using namespace QuantLibAddinCpp;


ObjectHandler::property_t ATM_RATE;

::CORBA::Boolean SwaptionServerImpl::CalculateATM (
        const ::SwaptionServer::Swaption& option,
        ::CORBA::Double_out npv,
        ::CORBA::Double_out atm_rate,
        ::CORBA::String_out error )
{
  ACE_Guard<ACE_Mutex> guard( _mutex );

  ACE_DEBUG((LM_DEBUG,
             ACE_TEXT("(%P|%t) INFO: ")
             ACE_TEXT("SwaptionServerImpl::CalculateATM - %s%s\n"), option.option_period.in(), option.swap_period.in() ));

  std::vector< std::string > curve( option.curve_components.length() );

  for ( unsigned int tt = 0; tt < option.curve_components.length(); tt++ )
    curve[tt] = option.curve_components[tt];

  std::vector<bool> existing_objects = ObjectHandler::Repository::instance().objectExists( curve );

  for ( unsigned int rate_helper = 0; rate_helper < curve.size(); rate_helper++ )
  {
     if ( !existing_objects[ rate_helper ] )
     {
       std::cout << "Rate Helper : [" << curve[ rate_helper ] << "] hasn't been setup yet." << std::endl;
       return false;
     }
  }

  QuantLib::Date referenceDate = QuantLib::Settings::instance().evaluationDate();

  try {

     ObjectHandler::property_t OH_NULL;

    std::vector<ObjectHandler::property_t> jumps;

    std::vector< std::string > curve1;

    QuantLibAddinCpp::qlPiecewiseYieldCurve( "PiecewiseYieldCurve", static_cast<long>(2), "Target", curve,
           "Actual/Actual (ISDA)", jumps, jumps, 1.0e-15, "Discount", "LogLinear", OH_NULL, OH_NULL, true);

     std::string engine = QuantLibAddinCpp::qlBlackSwaptionEngine(
            "blackSwaptionEngine",
            "PiecewiseYieldCurve",
            option.surface_name.in(),
            OH_NULL,
            OH_NULL,
            true); 

     std::string liborSwapIndexIsdaFixAm = QuantLibAddinCpp::qlLiborSwap(
            "LiborSwapIsdaFixAm",
            "USD",
            "IsdaFixAm",
            option.swap_period.in(),
            "PiecewiseYieldCurve",
            "PiecewiseYieldCurve",
            OH_NULL,
            OH_NULL,
            true); 

     std::string swaption = QuantLibAddinCpp::qlMakeSwaption(
            "Swaption555",
            "LiborSwapIsdaFixAm",
            option.option_period.in(),
            ATM_RATE,
            "blackSwaptionEngine",
            OH_NULL,
            OH_NULL,
            true);

     OH_GET_REFERENCE(ObjectIdLibObjPtr, swaption, QuantLibAddin::Swaption, QuantLib::Swaption)

     atm_rate = ObjectIdLibObjPtr->underlyingSwap()->fairRate();

     npv = ObjectIdLibObjPtr->NPV();

  

   } catch ( std::exception& exp )
   {
     std::cout << "Exception : " << exp.what() << std::endl;
     error = CORBA::string_dup( exp.what() );
     return false;
   }

  return true;
}
