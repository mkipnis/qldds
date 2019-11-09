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


import DDS.*;
import OpenDDS.DCPS.*;
import org.omg.CORBA.StringSeqHolder;
import CurveBuilder.*;
import ratehelpers.*;
import piecewiseyieldcurve.*;
import java.util.UUID;
import com.ocm.qldds_utils.BasicDomainParticipant;

class Client
{
  public static void main( String args[] )
  {

    try {
    System.out.println("Curve Request Publisher.");

 //   System.loadLibrary("qldds_utils_java");

    DomainParticipantFactory dpf = TheParticipantFactory.WithArgs(new StringSeqHolder(args));

    if (dpf == null) {
        System.err.println("ERROR: Domain Participant Factory not found");
        return;
    }

    BasicDomainParticipant domainParticipant = new BasicDomainParticipant(dpf, 1);

    domainParticipant.createPublisher( PUBLISHER_QOS_DEFAULT.get() );
    domainParticipant.createSubscriber( SUBSCRIBER_QOS_DEFAULT.get() );


    CurveBuilderRequestTypeSupportImpl servantRequest = new CurveBuilderRequestTypeSupportImpl();
    if (servantRequest.register_type(domainParticipant.getParticipant(), "") != RETCODE_OK.value) {
        System.err.println("ERROR: register_type failed");
        return;
    }

    CurveBuilderReplyTypeSupportImpl servantReply = new CurveBuilderReplyTypeSupportImpl();
    if (servantReply.register_type(domainParticipant.getParticipant(), "") != RETCODE_OK.value) {
        System.err.println("ERROR: register_type failed");
        return;
    }


    Topic requestTopic = domainParticipant.createTopic("CURVE_BUILDER_REQUEST_TOPIC", servantRequest.get_type_name() );
    Topic replyTopic = domainParticipant.createTopic("CURVE_BUILDER_REPLY_TOPIC", servantReply.get_type_name() );


    DataReaderQos drq = domainParticipant.getDefaultDataReaderQos();

    CurveBuilderReplyReader listener = new CurveBuilderReplyReader();
    domainParticipant.createDataReaderListener( replyTopic, drq, listener, false);


    DataWriterQos defaultDataWriter = domainParticipant.getDefaultDataWriterQos();

    DataWriter publisherDataWriter = domainParticipant.createDataWriter( requestTopic, 0, defaultDataWriter, true); 

    CurveBuilderRequestDataWriter cbrdw = CurveBuilderRequestDataWriterHelper.narrow(publisherDataWriter);
    CurveBuilderRequest curveBuilderRequest = new CurveBuilderRequest();


    CurveComponents curveComponents = new CurveComponents();

    curveBuilderRequest.yieldCurve = new qlPiecewiseYieldCurve();
    curveBuilderRequest.yieldCurve.ObjectId = "IsdaFixPmCurve";
    curveBuilderRequest.yieldCurve.RateHelpers = new String[9];

    curveBuilderRequest.yieldCurve.RateHelpers[0] = "DEPOSIT_3M";
    curveBuilderRequest.yieldCurve.RateHelpers[1] = "FUTURE_NEAR";
    curveBuilderRequest.yieldCurve.RateHelpers[2] = "FUTURE_FAR";
    curveBuilderRequest.yieldCurve.RateHelpers[3] = "FRA_3M";
    curveBuilderRequest.yieldCurve.RateHelpers[4] = "FRA_6M";
    curveBuilderRequest.yieldCurve.RateHelpers[5] = "SWAP_5Y_RATE";
    curveBuilderRequest.yieldCurve.RateHelpers[6] = "SWAP_10Y_RATE";
    curveBuilderRequest.yieldCurve.RateHelpers[7] = "SWAP_20Y_RATE";
    curveBuilderRequest.yieldCurve.RateHelpers[8] = "SWAP_30Y_RATE";

    curveBuilderRequest.yieldCurve.Jumps = new double[0];
    curveBuilderRequest.yieldCurve.JumpDates = new String[0];
    curveBuilderRequest.yieldCurve.Calendar = "US Settlement";
    curveBuilderRequest.yieldCurve.NDays = 0;
    curveBuilderRequest.yieldCurve.Accuracy=0.01;
    curveBuilderRequest.yieldCurve.TraitsID="DISCOUNT";
    curveBuilderRequest.yieldCurve.InterpolatorID="LOGLINEAR";
    curveBuilderRequest.yieldCurve.DayCounter="Actual/Actual (ISDA)";

    curveBuilderRequest.tenors = new String[10];
    curveBuilderRequest.tenors[0] = "3M";
    curveBuilderRequest.tenors[1] = "6M";
    curveBuilderRequest.tenors[2] = "1Y";
    curveBuilderRequest.tenors[3] = "2Y";
    curveBuilderRequest.tenors[4] = "3Y"; 
    curveBuilderRequest.tenors[5] = "5Y"; 
    curveBuilderRequest.tenors[6] = "10Y";
    curveBuilderRequest.tenors[7] = "15Y";
    curveBuilderRequest.tenors[8] = "20Y";
    curveBuilderRequest.tenors[9] = "25Y";

    for ( int delta=0; delta<100; delta++)
    {
      curveBuilderRequest.deportRateHelpers = curveComponents.getDeposits( delta/100000.0 );
      curveBuilderRequest.futuresRateHelpers = curveComponents.getFutures( delta/100 );
      curveBuilderRequest.fraRateHelpers = curveComponents.getFraRates( delta/100000.0 );
      curveBuilderRequest.swapRateHelpers = curveComponents.getSwapRates( delta/100000.0 );

      curveBuilderRequest.request_id = UUID.randomUUID().toString();
      int ret_value = cbrdw.write( curveBuilderRequest, 0 );

      try {
         Thread.sleep(100);
      } catch(Exception exp)
      {
      }
    };

    

    //domainParticipant.Disconnect();
    TheServiceParticipant.shutdown();
    } catch(Exception exp )
    {
	System.err.println(exp);
    };
  }; 
};
