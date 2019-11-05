package states.subscriber;

import events.AbstractEvent;


/**
 * @author dmerkhai, fbrown5
 * 
 */
public class LowDisposable extends AbstractState{
	
	//TODO this
	
	public LowDisposable() {

	}

      /**
       * the handleEvent method will behave appropriately depending on the implementation.
       * In general it will do something, after an AbstractEvent is published on an 
       * AbstractChannel to which the ConcreteState's host Object is subscribed
       * @param event
       * @param channelName
       */
	public boolean handleEvent(AbstractEvent event, String channelName){
	     // if the eventtype is sale or clearance (1 or 2) then add to wishlist 
          if (event.getEventTypeOf() == 1 || event.getEventTypeOf() == 2) {
            return true;
          } 
          else {
		  return false;
          }	
  }

}
