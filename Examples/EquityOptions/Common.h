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

const DDS::DomainId_t EQUITY_OPTIONS_DOMAIN_ID = 1066;

const char* QL_BLACK_CONSTANT_VOLS_TOPIC_NAME = "QL_BLACK_CONSTANT_VOLS_TOPIC";
const char* QL_GENERALIZED_BLACK_SCHOLES_PROCESSES_TOPIC_NAME = "QL_GENERALIZED_BLACK_SCHOLES_PROCESSES_TOPIC";
const char* QL_STRIKED_TYPE_PAYOFFS_TOPIC_NAME = "QL_STRIKED_TYPE_PAYOFFS_TOPIC"; 
const char* QL_EUROPEAN_EXERCISES_TOPIC_NAME = "QL_EUROPEAN_EXERCISES_TOPIC";

const char* STRADDLES_TOPIC_NAME = "STRADDLES";

std::string PUT("Put");
std::string CALL("Call");

#endif

