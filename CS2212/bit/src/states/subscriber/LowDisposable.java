package states.subscriber;

import events.AbstractEvent;


/** 
* author Fraser Brown 250950435
**/

public class LowDisposable implements IState{
	
	//TODO this
	
	public LowDisposable(){

	}

	public int handleEvent(AbstractEvent event, String channelName){
		
		return 1;
	}
}



