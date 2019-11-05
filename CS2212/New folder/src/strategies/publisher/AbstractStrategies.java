package strategies.publisher;

import events.AbstractEvent;
import publishers.AbstractPublisher;

/**
 * @author dmerkhai
 */
public abstract class AbstractStrategy {
  // forms the default: for General department

  /**
   * Whenever a publisher's {@link AbstractPublisher#publish()} is called, the
   * call is forwarded to the particular Publisher's AbstractStrategy
   * implementation of this method
   * 
   * @param publisherId the hashCode or any other unique identifier of the
   *                    publisher of an AbstractEvent
   */
  public void doPublish(int publisherId) {
  }

  /**
   * 
   * Whenever a publisher's {@link AbstractPublisher#publish(AbstractEvent)} is
   * called, the call is forwarded to the particular Publisher's AbstractStrategy
   * implementation of this method
   * 
   * @param event       the event to be published
   * @param publisherId the hashCode or any other unique identifier of the
   *                    publisher of an AbstractEvent
   */
  public void doPublish(AbstractEvent event, int publisherId) {
  }

}
