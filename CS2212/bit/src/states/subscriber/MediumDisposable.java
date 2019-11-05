package states.subscriber;

import events.AbstractEvent;


/** 
* author Fraser Brown 250950435
**/

public class MediumDisposable implements IState{
	
	//TODO this
	
	public MediumDisposable(){

	}

	public int handleEvent(AbstractEvent event, String channelName){
		
		return 1;
	}
}



