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
	
	}
	
	@Override
	void getInformation(){
		
	}
	
	@Override
	public void run(){
		while(true){
			getInformation();
			try{
				wait(250);
			} catch(InterruptedException ie){
				ie.printStackTrace();
			}
		}
	}
	
	
}
