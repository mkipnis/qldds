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


#include "CurveBuilderRequestDataReaderListenerImpl.h"

#include <CurveBuilderC.h>
#include <CurveBuilderTypeSupportC.h>
#include <CurveBuilderTypeSupportImpl.h>

#include <ql/quantlib.hpp>
#include <Addins/Cpp/addincpp.hpp>
#include <oh/ohdefines.hpp>
#include <oh/repository.hpp>

#include <qldds_convert_utils.h>


#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <qlo/baseinstruments.hpp>
#include <qlo/pricingengines.hpp>
#include <qlo/vanillaswap.hpp>
#include <ql/instrument.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>


CurveBuilderRequestDataReaderListenerImpl::CurveBuilderRequestDataReaderListenerImpl( CurveBuilder::CurveBuilderReplyDataWriter_var& 
		curveBuilderReplyDataWriter )
{
  _curveBuilderReplyDataWriter = curveBuilderReplyDataWriter;
}

void CurveBuilderRequestDataReaderListenerImpl::on_data_available( DDS::DataReader_ptr reader)
   throw (CORBA::SystemException)
{
  try
  {
    CurveBuilder::CurveBuilderRequestDataReader_var curve_reader_request_dr = 
	CurveBuilder::CurveBuilderRequestDataReader::_narrow( reader );

    if (CORBA::is_nil ( curve_reader_request_dr.in() ) )
    {
       std::cerr << "CurveBuilderRequestDataReaderListenerImpl::on_data_available: _narrow failed." 
		<< std::endl;
       ACE_OS::exit(1);
    }

    while( true )
    {
      CurveBuilder::CurveBuilderRequest curveBuilderRequest;
      DDS::SampleInfo si ;
      DDS::ReturnCode_t status = curve_reader_request_dr->take_next_sample( curveBuilderRequest, si );

      if (status == DDS::RETCODE_OK)
      {
         if ( !si.valid_data )
              continue;

	  //std::cout << curveBuilderRequest.request_id << std::endl;


	  ObjectHandler::Repository::instance().deleteAllObjects();

          QuantLibAddinCpp::qlLibor("USDLibor3M", "USD", "3M", "", false, false, true);

          CurveBuilder::DepositRateSeq deportRateHelpers = curveBuilderRequest.deportRateHelpers;

          for ( int deposit_index=0; deposit_index<deportRateHelpers.length(); deposit_index++)
          {
            ratehelpers::qlDepositRateHelper obj = deportRateHelpers[deposit_index];
            std::string returnObject = QuantLibAddinCpp::qlDepositRateHelper (
              obj.ObjectId.in(),
              obj.Rate ,
              obj.IborIndex.in(),
              static_cast<bool>(obj.Permanent),
              obj.Trigger,
              static_cast<bool>(obj.Overwrite) );
             
             // std::cout << "Deposit Object : " << returnObject << std::endl;
          }

          CurveBuilder::FuturesRateHelperSeq futuresRateHelpers = curveBuilderRequest.futuresRateHelpers;

          for ( int future_index=0; future_index<futuresRateHelpers.length(); future_index++)
          {
            ratehelpers::qlFuturesRateHelper obj = futuresRateHelpers[future_index]; 
              std::string returnObject = QuantLibAddinCpp::qlFuturesRateHelper (
              obj.ObjectId.in(),
              obj.Price ,
              obj.FuturesType.in(),
              qldds_utils::from_iso_string(obj.FuturesDate.in() ),
              obj.IborIndex.in(),
              obj.ConvexityAdjQuote ,
              static_cast<bool>(obj.Permanent),
              obj.Trigger,
              static_cast<bool>(obj.Overwrite) );

             //std::cout << "Futures Rate Helper : " << returnObject << std::endl;
          }

          CurveBuilder::FraRateHelperSeq fraRateHelpers = curveBuilderRequest.fraRateHelpers;
          for ( int fra_index=0; fra_index<fraRateHelpers.length(); fra_index++)
          {
             ratehelpers::qlFraRateHelper obj = fraRateHelpers[fra_index];
		
	      std::string returnObject = QuantLibAddinCpp::qlFraRateHelper (
              obj.ObjectId.in(),
              obj.Rate ,
              obj.PeriodToStart.in(),
              obj.IborIndex.in(),
              obj.PillarDate.in(),
              qldds_utils::from_iso_string_to_oh_property(obj.CustomPillarDate.in()),
              static_cast<bool>(obj.Permanent),
              obj.Trigger,
              static_cast<bool>(obj.Overwrite) );

              //std::cout << "FRA Rate Helper : " << returnObject << std::endl;
          }

          QuantLibAddinCpp::qlLiborSwap("SWAP_5Y", "USD", "IsdaFixPm", "5Y",  "", "", false, false, false);
          QuantLibAddinCpp::qlLiborSwap("SWAP_10Y", "USD", "IsdaFixPm", "10Y", "", "", false, false, false);
          QuantLibAddinCpp::qlLiborSwap("SWAP_20Y", "USD", "IsdaFixPm", "20Y", "", "", false, false, false);
          QuantLibAddinCpp::qlLiborSwap("SWAP_30Y", "USD", "IsdaFixPm", "30Y", "", "", false, false, false);

         CurveBuilder::SwapRateHelperSeq swapRateHelpers = curveBuilderRequest.swapRateHelpers;
          for ( int swap_index=0; swap_index<swapRateHelpers.length(); swap_index++)
          {
             ratehelpers::qlSwapRateHelper obj = swapRateHelpers[swap_index];

              std::string returnObject = QuantLibAddinCpp::qlSwapRateHelper (
              obj.ObjectId.in(),
              obj.Rate ,
              obj.SwapIndex.in(),
              obj.Spread ,
              obj.ForwardStart.in(),
              obj.DiscountingCurve.in(),
              obj.PillarDate.in(),
              qldds_utils::from_iso_string_to_oh_property(obj.CustomPillarDate.in()),
              static_cast<bool>(obj.Permanent),
              obj.Trigger,
              static_cast<bool>(obj.Overwrite) );
              ;


              //std::cout << "Swap Rate Helper : " << returnObject << std::endl;
          }



         piecewiseyieldcurve::qlPiecewiseYieldCurve obj = curveBuilderRequest.yieldCurve;

              std::string curve= QuantLibAddinCpp::qlPiecewiseYieldCurve (
              obj.ObjectId.in(),
              static_cast<long>(obj.NDays),
              obj.Calendar.in(),
             qldds_utils::vector_cast<std::string,qldds_utils::StringSeq>(obj.RateHelpers),
              obj.DayCounter.in(),
             qldds_utils::vector_cast<ObjectHandler::property_t,qldds_utils::DoubleSeq>(obj.Jumps),
             qldds_utils::vector_cast<ObjectHandler::property_t,qldds_utils::StringSeq>(obj.JumpDates),
              static_cast<double>(obj.Accuracy),
              obj.TraitsID.in(),
              obj.InterpolatorID.in(),
              static_cast<bool>(obj.Permanent),
              obj.Trigger,
              static_cast<bool>(obj.Overwrite) );

               QuantLibAddinCpp::qlDiscountingSwapEngine( "discountingSwapEngine", curve , false, OH_NULL, OH_NULL, false, false, true);

               ObjectHandler::Repository::instance().deleteObject( "USDLibor3M" );

               QuantLibAddinCpp::qlLibor("USDLibor3M", "USD", "3M", curve, false, false, true);

		// std::cout << "Number of Tenors: " << curveBuilderRequest.tenors.length() << std::endl;

		CurveBuilder::CurveBuilderReply curveBuilderReply;
		curveBuilderReply.request_id = curveBuilderRequest.request_id;
                curveBuilderReply.curveRates.length( curveBuilderRequest.tenors.length() );

		for ( int tenor_index = 0; tenor_index<curveBuilderRequest.tenors.length(); tenor_index++ )
                {
			char swap_name[128];
			sprintf(swap_name, "SWAP/%s", curveBuilderRequest.tenors[tenor_index].in());
			std::string swapName( swap_name );
			std::string tenor = curveBuilderRequest.tenors[tenor_index].in();

			QuantLibAddinCpp::qlMakeVanillaSwap(swapName, ObjectHandler::property_t(),
				 tenor, "USDLibor3M",0.0, "2D","Actual/Actual",
				 0.0, "discountingSwapEngine" , false, false, false);

			OH_GET_REFERENCE(ObjectIdLibObjPtr, swapName, QuantLibAddin::VanillaSwap, QuantLib::VanillaSwap);

			// std::cout << "Fair Rate: " << ObjectIdLibObjPtr->fairRate() << std::endl;
			CurveBuilder::CurveRate rate;
			rate.tenor = curveBuilderRequest.tenors[tenor_index];
			rate.rate = ObjectIdLibObjPtr->fairRate();
			curveBuilderReply.curveRates[ tenor_index ] = rate;
		}

		int ret_val = _curveBuilderReplyDataWriter->write( curveBuilderReply, DDS::HANDLE_NIL );
		//std::cout << "Curve Price Publish Reply: " << ret_val << std::endl;

          
      } else if ( status == DDS::RETCODE_NO_DATA ) 
      {
        break;
      } else {
        std::cerr << "ERROR: read CurveBuilder::CurveBuilderRequest: Error: " <<  status << std::endl;
      }
    }

  } catch (CORBA::Exception& e) 
  {
    std::cerr << "Exception caught in read:" << std::endl << e << std::endl;
     ACE_OS::exit(1);
  }
}

