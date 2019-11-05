package events;


/**
 * @author kkontog, ktsiouni, mgrigori
 * sample event type, simply creates a new event using the constructor 
 * {@link AbstractEvent#AbstractEvent(long, int, EventMessage)}   
 */
public class EventTypeSale extends AbstractEvent {


	/**
	 * shouldn't be used outside the EventFactory
	 * for information on how to call it and what the parameters are please look 
	 * at the documentation {@link EventFactory#createEvent(EventType, int, EventMessage)}
	 * 
	 * @param eventID
	 * @param eventPublisherId
	 * @param payload
	 */
	protected EventTypeSale(long eventID, int eventPublisherId, EventMessage payload) {
		super(eventID, eventPublisherId, payload);
	}

	public int getEventTypeOf() {
		return 1; // return 0 if new, 1 if sale, 2 if clearance
	}

}