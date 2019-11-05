package subscribers;

import baseEntities.IEntity;
import events.AbstractEvent;
import states.subscriber.StateFactory;
import states.subscriber.StateName;
import states.subscriber.AbstractState;
import java.util.ArrayList;

/**
 * @author kkontog, ktsiouni, mgrigori
 * the base Interface for the Subscriber hierarchy
 */
public abstract class AbstractSubscriber implements IEntity {
	
	
	protected AbstractState state;
	protected ArrayList<AbstractEvent> wishList = new ArrayList<AbstractEvent>(); // the wishlist

	/**
	 * set's the {@link AbstractState} for this ISubscriber implementation using the {@link StateFactory}
	 * @param stateName the entry from the {@link StateName} enumeration that we want the new AbstractState of the ISubscriber to be 
	 */
	public void setState(StateName stateName) {};

	
	/**
	 * is the function called each time an event is published to one of the channels that the 
	 * ISubscriber is sbuscribed to
	 * @param event the AbstractEvent that's received
	 * @param channelName the name of the channel that sent the AbstractEvent to the ISubscriber
	 */
	public void alert(AbstractEvent event, String channelName) {};


	
	/**
	 * subscribes to the channel whose name is provided by the parameter channelName 
	 * @param channelName type String
	 */
	public void subscribe(String channelName) {};
	
	
	/**
	 * getter for the wishList ArrayList
	 */
	public ArrayList<AbstractEvent> getWishlist() {
		return this.wishList;
	}
	
	/**
	 * unsubscribes from the channel whose name is provided by the parameter channelName
	 * @param channelName type String
	 */
	public void unsubscribe(String channelName) {};
	
}
