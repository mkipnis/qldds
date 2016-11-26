
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
import OpenDDS.DCPS.transport.*;
import org.omg.CORBA.StringSeqHolder;
import CurveBuilder.*;
import java.util.ArrayList;
import java.text.DecimalFormat;
import java.math.RoundingMode;

public class CurveBuilderReplyReader extends DDS._DataReaderListenerLocalBase 
{
      public void on_data_available(DDS.DataReader reader) {

        CurveBuilderReplyDataReader cpr = CurveBuilderReplyDataReaderHelper.narrow(reader);
        if (cpr == null) {
            System.err.println("ERROR: read: narrow failed.");
            return;
        } 

        CurveBuilderReplyHolder cbrh = new CurveBuilderReplyHolder(new CurveBuilderReply());
        cbrh.value.curveRates = new CurveRate[0];
        SampleInfoHolder sih = new SampleInfoHolder(new SampleInfo(0, 0, 0,
            new DDS.Time_t(), 0, 0, 0, 0, 0, 0, 0, false, 0));
        int status = cpr.take_next_sample(cbrh, sih);

        if (status == RETCODE_OK.value) {

            System.out.println("------------------------------------------------------------------------------------------");

            if (sih.value.valid_data) {

              System.out.println("Request ID:" +  cbrh.value.request_id);

              for ( int curve_tenor=0; curve_tenor<cbrh.value.curveRates.length; curve_tenor++ )
              {
                System.out.format(  " %6s |", cbrh.value.curveRates[curve_tenor].tenor ); 
              }

              System.out.println();

              for ( int curve_tenor=0; curve_tenor<cbrh.value.curveRates.length; curve_tenor++ )
              {
                System.out.format( " %-2.4f |", cbrh.value.curveRates[curve_tenor].rate*100 );
              }

              System.out.println();
                
            }
            else if (sih.value.instance_state ==
                     NOT_ALIVE_DISPOSED_INSTANCE_STATE.value) {
                System.out.println("instance is disposed");
            }
            else if (sih.value.instance_state ==
                     NOT_ALIVE_NO_WRITERS_INSTANCE_STATE.value) {
                System.out.println("instance is unregistered");
            }
            else {
                System.out.println("DataReaderListenerImpl::on_data_available: "
                                   + "ERROR: received unknown instance state "
                                   + sih.value.instance_state);
            }

        } else if (status == RETCODE_NO_DATA.value) {
            System.err.println("ERROR: reader received DDS::RETCODE_NO_DATA!");
        } else {
            System.err.println("ERROR: read Message: Error: " + status);
        }
    }


      public void on_requested_deadline_missed(DDS.DataReader reader, DDS.RequestedDeadlineMissedStatus status) {
        System.err.println("DataReaderListenerImpl.on_requested_deadline_missed");
    }

    public void on_requested_incompatible_qos(DDS.DataReader reader, DDS.RequestedIncompatibleQosStatus status) {
        System.err.println("DataReaderListenerImpl.on_requested_incompatible_qos");
    }

    public void on_sample_rejected(DDS.DataReader reader, DDS.SampleRejectedStatus status) {
        System.err.println("DataReaderListenerImpl.on_sample_rejected");
    }

    public void on_liveliness_changed(DDS.DataReader reader, DDS.LivelinessChangedStatus status) {
        System.err.println("DataReaderListenerImpl.on_liveliness_changed");
    }

    public void on_subscription_matched(DDS.DataReader reader, DDS.SubscriptionMatchedStatus status) {
        System.err.println("DataReaderListenerImpl.on_subscription_matched");
    }

    public void on_sample_lost(DDS.DataReader reader, DDS.SampleLostStatus status) {
        System.err.println("DataReaderListenerImpl.on_sample_lost");
    }


};
