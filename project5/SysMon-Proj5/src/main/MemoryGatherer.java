/**
 * This is a class for all of the memory gathering procedure
 */
package main;

/**
 * @author Josh Wretlind
 *
 */
public class MemoryGatherer extends Gatherer {
	
	public MemoryGatherer(){
		super.setDelay(250);
	}
	
	@Override
	void getInformation(){
		
	}
	
	@Override
	public void run(){
		while(true){
			getInformation();
			try{
				wait();
			} catch(InterruptedException ie){
			}
		}
	}
	
	
}
