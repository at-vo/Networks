package strategies.publisher;

/**
 * @author kkontog, ktsiouni, mgrigori
 * creates new {@link AbstractStrategy } objects
 * contributes to the Strategy design pattern
 * implements the FactoryMethod design pattern   
 */
public class StrategyFactory {

	
	/**
	 * creates a new {@link AbstractStrategy} using an entry from the {@link StrategyName} enumeration
	 * @param strategyName a value from the {@link StrategyName} enumeration specifying the strategy to be created 
	 * @return the newly created {@link AbstractStrategy} instance 
	 */
	public static AbstractStrategy createStrategy(StrategyName strategyName) {
		
		switch(strategyName) {
			case Automotive:
				return new Automotive();
			case Cosmetics:
				return new Cosmetics();
			case Food:
				return new Food();
			default:
				return new General();
				
			// can add apparel, etc.
		}
	}
	
	
}
