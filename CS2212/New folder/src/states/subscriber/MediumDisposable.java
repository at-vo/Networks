package states.subscriber;

import events.AbstractEvent;


/**
 * @author dmerkhai, fbrown5
 * 
 */
public class MediumDisposable extends AbstractState{
	
	//TODO this
	
	public MediumDisposable(){

	}

	public boolean handleEvent(AbstractEvent event, String channelName){
          // if eventtype is new, clearance, or sale, then add to wishlist
          if (event.getEventTypeOf() == 0 || event.getEventTypeOf() == 1 || event.getEventTypeOf() == 2) {
            return true;
          } 
          else {
            return false;
          } 

	}

}
