/*
   Copyright (C) 2013 Mike Kipnis

   This file is part of QLDDS, a free-software/open-source library
   for utilization of QuantLib in the distributed envrionment via DDS.

   QLDDS is free software: you can redistribute it and/or modify it
   under the terms of the QLDDS license.  You should have received a
   copy of the license along with this program; if not, please email
   <dev@qldds.org>. The license is also available online at
   <http://qldds.org/qldds-license/>.

   This program is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
   FOR A PARTICULAR PURPOSE.  See the license for more details.
*/


#ifndef __COMMON_H__
#define __COMMON_H__

static const DDS::DomainId_t IRS_DOMAIN_ID = 1066;

// Calculator Topics IN
const char* VANILLA_SWAP_TOPIC_NAME = "VANILLA_SWAP_TOPIC";
const char* SCHEDULE_TOPIC_NAME = "SCHEDULE_TOPIC";
const char* DEPOSIT_RATE_HELPER2_TOPIC_NAME = "DEPOSIT_RATE2_HELPER_TOPIC";
const char* FRA_RATE_HELPER2_TOPIC_NAME = "FRA_RATE_HELPER2_TOPIC";
const char* SWAP_RATE_HELPER2_TOPIC_NAME = "SWAP_RATE_HELPER2_TOPIC";

// Calculator Topic OUT
const char* IRS_PORTFOLIO_TOPIC_NAME = "IRS_PORTFOLIO_TOPIC";

#endif
