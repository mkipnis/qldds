package com.ocm.qldds_utils;

import DDS.*;
import OpenDDS.DCPS.*;


public class BasicDomainParticipant {
	
	// Instantiate a domain participant for a provided domain id
	public BasicDomainParticipant( DomainParticipantFactory dpf, int domainID)
	{
		_participant = dpf.create_participant(4,
	              PARTICIPANT_QOS_DEFAULT.get(), null, DEFAULT_STATUS_MASK.value);
	          if (_participant == null) {
	              System.err.println("ERROR: Domain Participant creation failed");
	              return;
	          }
	}
	
	// Deletes domain participant
	public void Disconnect() 
	{
		_participant.delete_contained_entities();
		// _dpf.delete_participant( _participant );
	};

	  // Creates a publisher
	  public boolean createPublisher( PublisherQos qos )
	  {
		  _publisher = _participant.create_publisher(qos, null,
                  DEFAULT_STATUS_MASK.value);
          if (_publisher == null) {
        	  System.err.println("ERROR: Publisher creation failed");
        	  return false;
          }
          
          return true;

	  }

	  // Creates a subscriber
	  public boolean createSubscriber( SubscriberQos qos )
	  {
		  _subscriber = _participant.create_subscriber(qos, null,
                  DEFAULT_STATUS_MASK.value);
          if (_subscriber == null) {
        	  System.err.println("ERROR: Subscriber creation failed");
        	  return false;
          }
          
          return true;
	  }
	  
	 public Topic createTopic( 
			 String topic_name, String topic_type_name)
	 {
		 Topic topic = _participant.create_topic(topic_name,
				 topic_type_name,
                 TOPIC_QOS_DEFAULT.get(),
                 null,
                 DEFAULT_STATUS_MASK.value);
		 
		 return topic;
	 }
	 
	 public DataWriterQos getDefaultDataWriterQos()
	 {
                 DataWriterQos dw_qos = new DataWriterQos();
        dw_qos.durability = new DurabilityQosPolicy();
        dw_qos.durability.kind = DurabilityQosPolicyKind.from_int(0);
        dw_qos.durability_service = new DurabilityServiceQosPolicy();
        dw_qos.durability_service.history_kind = HistoryQosPolicyKind.from_int(0);
        dw_qos.durability_service.service_cleanup_delay = new Duration_t();
        dw_qos.deadline = new DeadlineQosPolicy();
        dw_qos.deadline.period = new Duration_t();
        dw_qos.latency_budget = new LatencyBudgetQosPolicy();
        dw_qos.latency_budget.duration = new Duration_t();
        dw_qos.liveliness = new LivelinessQosPolicy();
        dw_qos.liveliness.kind = LivelinessQosPolicyKind.from_int(0);
        dw_qos.liveliness.lease_duration = new Duration_t();
        dw_qos.reliability = new ReliabilityQosPolicy();
        dw_qos.reliability.kind = ReliabilityQosPolicyKind.from_int(0);
        dw_qos.reliability.max_blocking_time = new Duration_t();
        dw_qos.destination_order = new DestinationOrderQosPolicy();
        dw_qos.destination_order.kind = DestinationOrderQosPolicyKind.from_int(0);
        dw_qos.history = new HistoryQosPolicy();
        dw_qos.history.kind = HistoryQosPolicyKind.from_int(0);
        dw_qos.resource_limits = new ResourceLimitsQosPolicy();
        dw_qos.transport_priority = new TransportPriorityQosPolicy();
        dw_qos.lifespan = new LifespanQosPolicy();
        dw_qos.lifespan.duration = new Duration_t();
        dw_qos.user_data = new UserDataQosPolicy();
        dw_qos.user_data.value = new byte[0];
        dw_qos.ownership = new OwnershipQosPolicy();
        dw_qos.ownership.kind = OwnershipQosPolicyKind.from_int(0);
        dw_qos.ownership_strength = new OwnershipStrengthQosPolicy();
        dw_qos.writer_data_lifecycle = new WriterDataLifecycleQosPolicy();
        dw_qos.representation = new DataRepresentationQosPolicy();
        dw_qos.representation.value = new short[0];

         return dw_qos;
 
	 }
	 
	 public DataReaderQos getDefaultDataReaderQos()
	 {
		       DataReaderQos dr_qos = new DataReaderQos();
        dr_qos.durability = new DurabilityQosPolicy();
        dr_qos.durability.kind = DurabilityQosPolicyKind.from_int(0);
        dr_qos.deadline = new DeadlineQosPolicy();
        dr_qos.deadline.period = new Duration_t();
        dr_qos.latency_budget = new LatencyBudgetQosPolicy();
        dr_qos.latency_budget.duration = new Duration_t();
        dr_qos.liveliness = new LivelinessQosPolicy();
        dr_qos.liveliness.kind = LivelinessQosPolicyKind.from_int(0);
        dr_qos.liveliness.lease_duration = new Duration_t();
        dr_qos.reliability = new ReliabilityQosPolicy();
        dr_qos.reliability.kind = ReliabilityQosPolicyKind.from_int(0);
        dr_qos.reliability.max_blocking_time = new Duration_t();
        dr_qos.destination_order = new DestinationOrderQosPolicy();
        dr_qos.destination_order.kind = DestinationOrderQosPolicyKind.from_int(0);
        dr_qos.history = new HistoryQosPolicy();
        dr_qos.history.kind = HistoryQosPolicyKind.from_int(0);
        dr_qos.resource_limits = new ResourceLimitsQosPolicy();
        dr_qos.user_data = new UserDataQosPolicy();
        dr_qos.user_data.value = new byte[0];
        dr_qos.ownership = new OwnershipQosPolicy();
        dr_qos.ownership.kind = OwnershipQosPolicyKind.from_int(0);
        dr_qos.time_based_filter = new TimeBasedFilterQosPolicy();
        dr_qos.time_based_filter.minimum_separation = new Duration_t();
        dr_qos.reader_data_lifecycle = new ReaderDataLifecycleQosPolicy();
        dr_qos.reader_data_lifecycle.autopurge_nowriter_samples_delay = new Duration_t();
        dr_qos.reader_data_lifecycle.autopurge_disposed_samples_delay = new Duration_t();
        dr_qos.representation = new DataRepresentationQosPolicy();
        dr_qos.representation.value = new short[0];
        dr_qos.type_consistency = new TypeConsistencyEnforcementQosPolicy();
        dr_qos.type_consistency.kind = 2;
        dr_qos.type_consistency.ignore_member_names = false;
        dr_qos.type_consistency.force_type_validation = false;

	        
	        return dr_qos;
	 }
	 
	 
	 public DataWriter createDataWriter( Topic topic, int matchedPublications, DataWriterQos dataWriterQos, boolean reliable )
	 {

         DataWriterQosHolder qosh = new DataWriterQosHolder(dataWriterQos);
         _publisher.get_default_datawriter_qos(qosh);
         qosh.value.history.kind = HistoryQosPolicyKind.KEEP_ALL_HISTORY_QOS;
         if (reliable) {
           qosh.value.reliability.kind =
             ReliabilityQosPolicyKind.RELIABLE_RELIABILITY_QOS;
         }

         
         DataWriter dw = _publisher.create_datawriter(topic,
                                               qosh.value,
                                               null,
                                               DEFAULT_STATUS_MASK.value);
         if (dw == null) {
             System.err.println("ERROR: DataWriter creation failed");
             return null;
         }
         System.out.println("Publisher Created DataWriter");

         StatusCondition sc = dw.get_statuscondition();
         sc.set_enabled_statuses(PUBLICATION_MATCHED_STATUS.value);
         WaitSet ws = new WaitSet();
         ws.attach_condition(sc);
         PublicationMatchedStatusHolder matched =
           new PublicationMatchedStatusHolder(new PublicationMatchedStatus());
         Duration_t timeout = new Duration_t(DURATION_INFINITE_SEC.value,
                                             DURATION_INFINITE_NSEC.value);
         
         while (true) {
             final int result = dw.get_publication_matched_status(matched);
             if (result != RETCODE_OK.value) {
                 System.err.println("ERROR: get_publication_matched_status()" +
                                    "failed.");
                 return null;
             }

             if (matched.value.current_count >= matchedPublications) {
                 System.out.println("Publisher Matched");
                 break;
             }

             ConditionSeqHolder cond = new ConditionSeqHolder(new Condition[]{});
             if (ws.wait(cond, timeout) != RETCODE_OK.value) {
                 System.err.println("ERROR: wait() failed.");
                 return null;
             }
         }

         ws.detach_condition(sc);
         
         return dw;

	 }
	 
	 public void createDataReaderListener( Topic topic, DataReaderQos dataReaderQos, DDS.DataReaderListener listener, boolean reliable)
	 {
	     DataReaderQosHolder qosh = new DataReaderQosHolder(dataReaderQos);
	        _subscriber.get_default_datareader_qos(qosh);
	        if (reliable) {
	          qosh.value.reliability.kind =
	            ReliabilityQosPolicyKind.RELIABLE_RELIABILITY_QOS;
	        }
	        qosh.value.history.kind = HistoryQosPolicyKind.KEEP_ALL_HISTORY_QOS;

	        //DataReaderListenerImpl listener = new DataReaderListenerImpl();
	        DataReader dr = _subscriber.create_datareader(topic,
	        									 dataReaderQos,
	                                              listener,
	                                              DEFAULT_STATUS_MASK.value);

	        if (dr == null) {
	            System.err.println("ERROR: DataReader creation failed");
	            return;
	        }

	        /* StatusCondition sc = dr.get_statuscondition();
	        sc.set_enabled_statuses(SUBSCRIPTION_MATCHED_STATUS.value);
	        WaitSet ws = new WaitSet();
	        ws.attach_condition(sc);
	        SubscriptionMatchedStatusHolder matched =
	          new SubscriptionMatchedStatusHolder(new SubscriptionMatchedStatus());
	        Duration_t timeout = new Duration_t(DURATION_INFINITE_SEC.value,
	                                            DURATION_INFINITE_NSEC.value);

	        boolean matched_pub = false;
	        while (true) {
	            final int result = dr.get_subscription_matched_status(matched);
	            if (result != RETCODE_OK.value) {
	                System.err.println("ERROR: get_subscription_matched_status()" +
	                                   "failed.");
	                return;
	            }

	            if (matched.value.current_count == 0
	                && matched.value.total_count > 0) {
	                System.out.println("Subscriber No Longer Matched");
	                break;
	            }
	            else if (matched.value.current_count > 0 &&
	                     !matched_pub) {
	                System.out.println("Subscriber Matched");
	                matched_pub = true;
	            }

	            ConditionSeqHolder cond = new ConditionSeqHolder(new Condition[]{});
	            if (ws.wait(cond, timeout) != RETCODE_OK.value) {
	                System.err.println("ERROR: wait() failed.");
	                return;
	            }
	        }
	        
	        System.out.println("Subscriber Report Validity");
	        //listener.report_validity();

	        ws.detach_condition(sc);*/

	 }
	 
	 public DomainParticipant getParticipant()
	 {
		 return _participant;
	 }


	
	private DomainParticipant _participant;
	private DomainParticipantFactory _dpf;
	private Publisher _publisher;
	private Subscriber _subscriber;
}
