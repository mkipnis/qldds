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


#include "BasicDomainParticipant.h"

#include <iostream>
#include <sstream>

using namespace qldds_utils;

BasicDomainParticipant::BasicDomainParticipant( DDS::DomainParticipantFactory_var dpf, const DDS::DomainId_t& domainID ) :
 _dpf( dpf )
{
  _participant = _dpf->create_participant( domainID, PARTICIPANT_QOS_DEFAULT, DDS::DomainParticipantListener::_nil(),
    ::OpenDDS::DCPS::DEFAULT_STATUS_MASK);

  if (CORBA::is_nil (_participant.in ()) )
  {
    std::stringstream error;

    error << "Unable to create participant. DomainID : [" <<  domainID << "]";

    ACE_ERROR( (LM_ERROR, "(%T|%P|%t) %s.\n", error.str().c_str() ) );
    throw Exception( error.str() );
  }
}

BasicDomainParticipant::~BasicDomainParticipant()
{
   _participant->delete_contained_entities();
   _dpf->delete_participant( _participant );
};

bool BasicDomainParticipant::createPublisher( const DDS::PublisherQos & qos )
{
  // (PUBLISHER_QOS_DEFAULT is defined in Marked_Default_Qos.h)
  _publisher = _participant->create_publisher( qos , DDS::PublisherListener::_nil(),
       ::OpenDDS::DCPS::DEFAULT_STATUS_MASK);
  if (CORBA::is_nil (_publisher.in ()))
  {
    ACE_ERROR( (LM_ERROR, "(%T|%P|%t) create_publisher failed." ) );
    return false;
  }

  return true;
}

bool BasicDomainParticipant::createSubscriber( const DDS::SubscriberQos & qos )
{
  // (SUBSCRIBER_QOS_DEFAULT is defined in Marked_Default_Qos.h)
  _subscriber = _participant->create_subscriber( qos, DDS::SubscriberListener::_nil(),
       ::OpenDDS::DCPS::DEFAULT_STATUS_MASK);
  if (CORBA::is_nil (_subscriber.in ())) {
    ACE_ERROR( (LM_ERROR, "(%T|%P|%t) create_subscriber failed." ) );
    return false;
  }

  return true;
}

template< class SERVANT_var, class IMPLEMENTATION_var >
DDS::Topic_ptr 
BasicDomainParticipant::createTopicAndRegisterType( const char* topic_name, const char* topic_type )
{
  SERVANT_var servant = new IMPLEMENTATION_var;

  CORBA::String_var type_name;

  if ( strcmp( topic_type, "" ) == 0 )
  {
    servant->register_type(_participant, "");
    type_name = servant->get_type_name();
  } else 
    type_name = CORBA::string_dup( topic_type );

  if (DDS::RETCODE_OK != servant->register_type( _participant.in (), type_name ) )
  {
     std::stringstream error; 

     error << "register_type for [" << type_name << "] failed." << endl;

     throw Exception( error.str() );

  }

  ::DDS::TopicQos topic_qos;
  _participant->get_default_topic_qos(topic_qos);

  DDS::Topic_var topic = _participant->create_topic ( topic_name, type_name,
              topic_qos, DDS::TopicListener::_nil(), ::OpenDDS::DCPS::DEFAULT_STATUS_MASK);
  if (CORBA::is_nil (topic.in ())) 
  {
    std::stringstream error;

    error << "create_topic for [" << topic_name << "] failed." << endl;

    throw Exception( error.str() );
  }

  return DDS::Topic::_duplicate ( topic.in() );
}

template<class DataWriter_var, class DataWriter>
DataWriter_var 
BasicDomainParticipant::createDataWriter( DDS::Topic_var topic, int matchedPublications, const DDS::DataWriterQos dataWriterQos )
{
  ::DDS::DataWriterQos dw_qos;
  _publisher->get_default_datawriter_qos (dw_qos);

  ::DDS::TopicQos topic_qos;

  topic->get_qos( topic_qos );  
  _publisher->copy_from_topic_qos (dw_qos, topic_qos);

  DDS::DataWriter_var base_dw = _publisher->create_datawriter( topic.in (), dw_qos,
       DDS::DataWriterListener::_nil(), ::OpenDDS::DCPS::DEFAULT_STATUS_MASK);

  if (CORBA::is_nil ( base_dw.in ())) {

    std::stringstream error;

    error << "create_datawriter for [" << topic->get_name() << "] failed.";

    throw Exception( error.str() );
  }

  DataWriter_var dw = DataWriter::_narrow(base_dw.in());
  if (CORBA::is_nil (dw.in ())) {

    std::stringstream error;

    error << "DataWriter for [" << topic->get_name() << "] could not be narrowed.";

    throw Exception( error.str() );

  }

  // Block until Subscriber is available
  DDS::StatusCondition_var condition = dw->get_statuscondition();
  condition->set_enabled_statuses(DDS::PUBLICATION_MATCHED_STATUS);

  DDS::WaitSet_var ws = new DDS::WaitSet;
  ws->attach_condition(condition);

  while (true) 
  {
    DDS::PublicationMatchedStatus matches;
    if (dw->get_publication_matched_status(matches) != DDS::RETCODE_OK) 
    {
      std::stringstream warn;

      warn << "get_publication_matched_status for [" << topic->get_name() << "] failed.";

      ACE_ERROR( (LM_WARNING, "(%T|%P|%t) %s.", warn.str().c_str() ) );

      return dw;
    }

    if ( matches.current_count >= matchedPublications ) 
      break;

    DDS::ConditionSeq conditions;
    DDS::Duration_t timeout = { 30, 0 };
    if (ws->wait(conditions, timeout) != DDS::RETCODE_OK) {
     
      std::stringstream warn;

      warn << "wait for [" << topic->get_name() << "] failed.";

      ACE_ERROR( (LM_WARNING, "(%T|%P|%t) %s.", warn.str().c_str() ) );

      return dw;
    }
   }

  ws->detach_condition(condition); 

  return dw;
}

template< class DRListener_var >
DDS::DataReader_ptr 
BasicDomainParticipant::createDataReaderListener( ACE_Mutex& mutex, DDS::Topic_var topic, DDS::DataReaderQos dataReaderQos  )
{
  DDS::DataReaderListener_var listener (new DRListener_var( mutex ) );

  if (CORBA::is_nil ( listener.in ()) ) {
   cerr << "listener is nil." << endl;
   ACE_OS::exit(1);
  }

  ::DDS::DataReaderQos dr_qos;
  _subscriber->get_default_datareader_qos (dr_qos);

  ::DDS::TopicQos topic_qos;

  topic->get_qos( topic_qos );
  _subscriber->copy_from_topic_qos (dr_qos, topic_qos);

  DDS::DataReader_var dr =
     _subscriber->create_datareader(topic.in (), dr_qos, listener.in (),
     ::OpenDDS::DCPS::DEFAULT_STATUS_MASK);

  return DDS::DataReader::_duplicate( dr.in() );
}

template< class DRListener_var >
DDS::DataReader_ptr 
BasicDomainParticipant::createDataReaderListener( DDS::Topic_var topic, DDS::DataReaderQos dataReaderQos )
{
  DDS::DataReaderListener_var listener (new DRListener_var );

  if (CORBA::is_nil ( listener.in ()) ) {
   cerr << "listener is nil." << endl;
   ACE_OS::exit(1);
  }

  ::DDS::DataReaderQos dr_qos;
  _subscriber->get_default_datareader_qos (dr_qos);

  ::DDS::TopicQos topic_qos;

  topic->get_qos( topic_qos );
  _subscriber->copy_from_topic_qos (dr_qos, topic_qos);

  DDS::DataReader_var dr =
     _subscriber->create_datareader(topic.in (), dr_qos, listener.in (),
        ::OpenDDS::DCPS::DEFAULT_STATUS_MASK);

  return DDS::DataReader::_duplicate( dr.in() );
};

DDS::DataReader_ptr BasicDomainParticipant::createDataReaderListener( DDS::Topic_var topic,DDS::DataReaderListener_var listener, DDS::DataReaderQos dataReaderQos  )
{
  //DDS::DataReaderListener_var listener (new DRListener_var );

  if (CORBA::is_nil ( listener.in ()) ) {
   cerr << "listener is nil." << endl;
   ACE_OS::exit(1);
  }

  ::DDS::DataReaderQos dr_qos;
  _subscriber->get_default_datareader_qos (dr_qos);

  ::DDS::TopicQos topic_qos;

  topic->get_qos( topic_qos );
  _subscriber->copy_from_topic_qos (dr_qos, topic_qos);

 DDS::DataReader_var dr =
     _subscriber->create_datareader(topic.in (), dr_qos, listener.in (),
        ::OpenDDS::DCPS::DEFAULT_STATUS_MASK);

  return DDS::DataReader::_duplicate( dr.in() );

}
 
