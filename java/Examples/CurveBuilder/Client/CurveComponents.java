
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

import ratehelpers.*;

class CurveComponents
{
  public CurveComponents()
  {
  }

  qlDepositRateHelper[] getDeposits( double delta )
  {
    qlDepositRateHelper[] deposits = new qlDepositRateHelper[1];

    qlDepositRateHelper deposit3M = new qlDepositRateHelper();
    deposit3M.ObjectId = "DEPOSIT_3M";
    deposit3M.Rate = 0.01 + delta;
    deposit3M.IborIndex = "USDLibor3M";
    deposits[0] = deposit3M;

    return deposits; 
  }

  qlFuturesRateHelper[] getFutures( double delta )
  {
    qlFuturesRateHelper[] futures = new qlFuturesRateHelper[2];

    qlFuturesRateHelper futureNear = new qlFuturesRateHelper();
    futureNear.ObjectId = "FUTURE_NEAR";
    futureNear.Price = 99.00 + delta;
    futureNear.FuturesType="IMM";
    futureNear.FuturesDate="20161221";
    futureNear.IborIndex = "USDLibor3M";
    futures[0] = futureNear;

    qlFuturesRateHelper futureFar = new qlFuturesRateHelper();
    futureFar.ObjectId = "FUTURE_FAR";
    futureFar.Price = 99.50;
    futureFar.FuturesType="IMM";
    futureFar.FuturesDate="20170315";
    futureFar.IborIndex = "USDLibor3M";
    futures[1] = futureFar;

    return futures;
  }

  qlFraRateHelper[] getFraRates( double delta )
  {
    qlFraRateHelper[] fraRates = new qlFraRateHelper[2];

    qlFraRateHelper fraRate3m = new qlFraRateHelper();
    fraRate3m.ObjectId = "FRA_3M";
    fraRate3m.PeriodToStart = "3M";
    fraRate3m.IborIndex = "USDLibor3M";
    fraRate3m.PillarDate = "LastRelevantDate";
    fraRate3m.Rate = 0.02 + delta;
    fraRates[0] = fraRate3m;

    qlFraRateHelper fraRate6m = new qlFraRateHelper();
    fraRate6m.ObjectId = "FRA_6M";
    fraRate6m.PeriodToStart = "6M";
    fraRate6m.IborIndex = "USDLibor3M";
    fraRate6m.PillarDate = "LastRelevantDate";
    fraRate6m.Rate = 0.03;
    fraRates[1] = fraRate6m;

    return fraRates;
  }

  qlSwapRateHelper[] getSwapRates( double delta )
  {
    qlSwapRateHelper[] swapRates = new qlSwapRateHelper[4];

    qlSwapRateHelper swap5y = new qlSwapRateHelper();
    swap5y.ObjectId = "SWAP_5Y_RATE";
    swap5y.ForwardStart = "0D";
    swap5y.Rate = 0.05 + delta;
    swap5y.Spread = 0.0;
    swap5y.SwapIndex = "SWAP_5Y";
    swap5y.PillarDate = "LastRelevantDate";
    swapRates[0] = swap5y;

    qlSwapRateHelper swap10y = new qlSwapRateHelper();
    swap10y.ObjectId = "SWAP_10Y_RATE";
    swap10y.ForwardStart = "0D";
    swap10y.Rate = 0.06 + delta;
    swap10y.Spread = 0.0;
    swap10y.SwapIndex = "SWAP_10Y";
    swap10y.PillarDate = "LastRelevantDate";
    swapRates[1] = swap10y;

    qlSwapRateHelper swap20y = new qlSwapRateHelper();
    swap20y.ObjectId = "SWAP_20Y_RATE";
    swap20y.ForwardStart = "0D";
    swap20y.Rate = 0.07 + delta;
    swap20y.Spread = 0.0;
    swap20y.SwapIndex = "SWAP_20Y";
    swap20y.PillarDate = "LastRelevantDate";
    swapRates[2] = swap20y;

    qlSwapRateHelper swap30y = new qlSwapRateHelper();
    swap30y.ObjectId = "SWAP_30Y_RATE";
    swap30y.ForwardStart = "0D";
    swap30y.Rate = 0.08 + delta;
    swap30y.Spread = 0.0;
    swap30y.SwapIndex = "SWAP_30Y";
    swap30y.PillarDate = "LastRelevantDate";
    swapRates[3] = swap30y;
 
    return swapRates;
  }

};
