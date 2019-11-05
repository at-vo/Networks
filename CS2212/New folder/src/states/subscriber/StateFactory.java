package states.subscriber;
import states.subscriber.AbstractState; // EXPR.

/**
 * @author kkontog, ktsiouni, mgrigori
 * creates new States
 * contributes to the State design pattern
 * implements the FactoryMethod design pattern   
 */
public class StateFactory {

	
	/**
	 * creates a new {@link AbstractState} using an entry from the {@link StateName} enumeration
	 * @param stateName a value from the {@link StateName} enumeration specifying the state to be created 
	 * @return the newly created {@link AbstractState} instance 
	 */
	public static AbstractState createState(StateName stateName) {
		switch(stateName) {
			case HighDisposable : 
				return new HighDisposable();
			case MediumDisposable : 
				return new MediumDisposable();
			default :
				return new LowDisposable();
		}
	}
	
	
}
