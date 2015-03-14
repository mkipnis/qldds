OpenDDS data types are defined using IDL [(see Defining the Data Types in OpenDDS Developer Guide).](http://download.ociweb.com/OpenDDS/OpenDDS-latest.pdf)
The auto generated IDL data types are located in [$QLDDS\_ROOT/Addins/OpenDDS.](https://code.google.com/p/qldds/source/browse/Addins/OpenDDS/)

Example of _qlSwapRateHelper2_ Data Type from _[ratehelpers.idl:](https://code.google.com/p/qldds/source/browse/Addins/OpenDDS/ratehelpers.idl)_
```
#pragma DCPS_DATA_TYPE "ratehelpers::qlSwapRateHelper2"
#pragma DCPS_DATA_KEY "ratehelpers::qlSwapRateHelper2 instanceID"

   struct qlSwapRateHelper2 {
          string instanceID;

             string ObjectId;
             double Rate;
             string Tenor;
             string Calendar;
             string FixedLegFrequency;
             string FixedLegConvention;
             string FixedLegDayCounter;
             string IborIndex;
             double Spread;
             string ForwardStart;
             string DiscountingCurve;
             boolean Permanent;
             boolean Trigger;
             boolean Overwrite;
   };
```


OpenDDS provides a compiler that generates the code to marshal and demarshal idl messages, as well as type support code for data readers and writers [(see Processing the IDL in OpenDDS Developers Guide).](http://download.ociweb.com/OpenDDS/OpenDDS-latest.pdf)

Example of using generated C++ code for _qlSwapRateHelper2_:
```
ratehelpers::qlSwapRateHelper2 swap_rate_helper2;

swap_rate_helper2.ObjectId = CORBA::string_dup(“IRS_10Y”);
swap_rate_helper2.Rate = 0.03165;
swap_rate_helper2.Tenor = CORBA::string_dup(“10Y”);
swap_rate_helper2.Calendar = CORBA::string_dup("TARGET");
swap_rate_helper2.FixedLegFrequency = CORBA::string_dup("Annual");
swap_rate_helper2.FixedLegConvention=CORBA::string_dup("Unadjusted");
swap_rate_helper2.FixedLegDayCounter = CORBA::string_dup("30/360");
swap_rate_helper2.IborIndex =  CORBA::string_dup("Libor");
swap_rate_helper2.ForwardStart =  CORBA::string_dup("0D");
swap_rate_helper2.Spread = 0.0;
swap_rate_helper2.Overwrite = true;
```