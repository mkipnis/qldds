
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


#ifndef __COMMON_H__
#define __COMMON_H__

static const DDS::DomainId_t SWAPTION_DOMAIN_ID = 1066;

// Calculator Topics IN
const char* DEPOSIT_RATE_HELPER2_TOPIC_NAME = "DEPOSIT_RATE2_HELPER_TOPIC";
const char* FRA_RATE_HELPER2_TOPIC_NAME = "FRA_RATE_HELPER2_TOPIC";
const char* SWAP_RATE_HELPER2_TOPIC_NAME = "SWAP_RATE_HELPER2_TOPIC";
const char* SWAPTION_VTS_MATRIX_TOPIC_NAME = "SWAPTION_VTS_MATRIX_TOPIC";

#endif
