package states.subscriber;

import events.AbstractEvent;
// import events.EventTypeNew;
// import events.EventTypeClearance;
// import events.EventTypeSale;


/**
 * @author dmerkhai, fbrown5
 * 
 */
public class HighDisposable extends AbstractState{ // extends AbstractState
	
	//TODO this
	
	public HighDisposable() {

	}

    // consider putting this in abstract state
//    @Override
	public boolean handleEvent(AbstractEvent event, String channelName) {
      // if the eventType is new, then add the event to the wishlist of channelName, otherwise discard the event
      if (event.getEventTypeOf() == 0) { // 0 if new, 1 if sale, 2 if clearance
        return true;
      } else {
        return false;
      } 

	}

}



