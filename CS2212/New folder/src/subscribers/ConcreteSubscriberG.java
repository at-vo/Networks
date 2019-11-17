package subscribers;

import events.AbstractEvent;
import pubSubServer.SubscriptionManager;
import states.subscriber.StateFactory;
import states.subscriber.StateName;
import states.subscriber.AbstractState; // EXPR.
import java.util.ArrayList;


/**
 * @author kkontog, ktsiouni, mgrigori
 * an example concrete subscriber
 */
public class ConcreteSubscriberG extends AbstractSubscriber {

	protected AbstractState state;
	protected ArrayList<AbstractEvent> wishList = new ArrayList<AbstractEvent>(); // the wishlist

	protected ConcreteSubscriberG() {
		state = StateFactory.createState(StateName.HighDisposable); // HighDisposable is the default

	}
	
	/* (non-Javadoc)
	 * @see subscribers.ISubscriber#setState(states.subscriber.StateName)
	 */
	public void setState(StateName stateName) {
		state = StateFactory.createState(stateName);
	}
	
	
	/* (non-Javadoc)
	 * @see subscribers.ISubscriber#alert(events.AbstractEvent, java.lang.String)
	 */
	@Override
	public void alert(AbstractEvent event, String channelName) {
		System.out.println("Subscriber " + this + " handling event ::" + event + ":: published on channel " + channelName);
		// if low income add the event to the subscribers wishlist,
		// ... so on and so forth, this function needs to be the one that implements the 
		// wishlist and adds to it

		if (state.handleEvent(event, channelName)) {
			wishList.add(event);
		}
		// else, do nothing; much of the logic is encapsulated within each of state types

		// state.handleEvent(event, channelName);
	}

	/* (non-Javadoc)
	 * @see subscribers.ISubscriber#subscribe(java.lang.String)
	 */
	@Override
	public void subscribe(String channelName) {
		
		SubscriptionManager.getInstance().subscribe(channelName, this);		
	}

	/* (non-Javadoc)
	 * @see subscribers.ISubscriber#unsubscribe(java.lang.String)
	 */
	@Override
	public void unsubscribe(String channelName) {
		SubscriptionManager.getInstance().subscribe(channelName, this);
		
	}
	
	
}