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


#ifndef __BASIC_DOMAIN_PARTICIPANT_H__
#define __BASIC_DOMAIN_PARTICIPANT_H__

#include <dds/DCPS/Service_Participant.h>
#include <dds/DCPS/Marked_Default_Qos.h>
#include <dds/DCPS/PublisherImpl.h>
#include <dds/DCPS/SubscriberImpl.h>
#include <dds/DCPS/WaitSet.h>
#include <ace/streams.h>

namespace qldds_utils 
{

 /* 
    BasicDomainParticipant provides convenience functions to create publishers, 
    subscribers, thread safe default data readers and data writers.  
    This class is essentially a wrapper around DDS API.
  */

class BasicDomainParticipant
{
 public:

  // Instantiate a domain participant for a provided domain id
  BasicDomainParticipant( DDS::DomainParticipantFactory_var, const DDS::DomainId_t& );

  // Deletes domain participant
  virtual ~BasicDomainParticipant();
 
  // Creates a publisher
  bool createPublisher( const DDS::PublisherQos & qos = PUBLISHER_QOS_DEFAULT );
  
  // Creates a subscriber
  bool createSubscriber( const DDS::SubscriberQos & qos = SUBSCRIBER_QOS_DEFAULT );

  //
  // Registers a topic and a type for a given DataType, see Registering the Data Type and Creating a Topic 
  // in OpenDDS developers guide.
  // 
  // Example, Topic and Type for ratehelpers::qlSwapRateHelper :
  //
  // createTopicAndRegisterType
  //   < ratehelpers::qlSwapRateHelperTypeSupport_var, ratehelpers::qlSwapRateHelperTypeSupportImpl >
  //    (  "SWAP_RATE_HELPER_TOPIC" );
  // 
  template< class SERVANT_var, class IMPLEMENTATION_var >
  DDS::Topic_ptr createTopicAndRegisterType( const char* topic_name, const char* topic_type = "" );

  //
  // Creates DataWriter
  //
  template<class DataWriter_var, class DataWriter>
  DataWriter_var createDataWriter( DDS::Topic_var topic, int matchedPublications = 0, const DDS::DataWriterQos dataWriterQos = DATAWRITER_QOS_DEFAULT );

  //
  // Creates a DataReader and supplies it with a reference to a mutex lock.
  // This mutex is  being locked before making a QuantLibAddin call
  // and unlocked after.
  //  
  template< class DRListener_var >
  DDS::DataReader_ptr createDataReaderListener( ACE_Mutex& mutex, DDS::Topic_var topic, DDS::DataReaderQos dataReaderQos = DATAREADER_QOS_DEFAULT );

  DDS::DataReader_ptr createDataReaderListener( DDS::Topic_var topic,DDS::DataReaderListener_var listener, DDS::DataReaderQos dataReaderQos = DATAREADER_QOS_DEFAULT );
  //
  // Creates a DataReader without a lock.
  // This method can be used for creating DataReaders that don't require QuantLibAddin synchronization.
  //
  template< class DRListener_var >
  DDS::DataReader_ptr createDataReaderListener( DDS::Topic_var topic, DDS::DataReaderQos dataReaderQos = DATAREADER_QOS_DEFAULT );

  DDS::DomainParticipant_ptr getDomainParticipant()
  {
    return DDS::DomainParticipant::_duplicate( _participant.in() );
  }

  DDS::Publisher_ptr getPublisher()
  {
    return DDS::Publisher::_duplicate( _publisher.in() );
  }

  DDS::Subscriber_ptr getSubscriber()
  {
    return DDS::Subscriber::_duplicate( _subscriber.in() );
  }

  void setPublisher( DDS::Publisher_ptr publisher )
  {
    _publisher = publisher;
  }

  void setSubscriber( DDS::Subscriber_ptr subscriber )
  {
    _subscriber = subscriber;
  }

  class Exception : public std::exception
  {
    public:
      explicit Exception ( const std::string& what ) : _what( what ) {};  

      ~Exception() throw() {};

      const char* what() const throw()  
      {
        return _what.c_str();
      }

    protected:
      std::string _what;
  };

 public:
   // OpenDDS Initialization
   DDS::DomainParticipant_var _participant;
   DDS::DomainParticipantFactory_var _dpf;
   DDS::Publisher_var _publisher;
   DDS::Subscriber_var _subscriber;

};

};

#include "BasicDomainParticipant.inl"

#endif 
