/**
 * This is a class for all of the memory gathering procedure
 */
package main;

/**
 * @author Josh Wretlind
 *
 */
public class MemoryGatherer extends Thread {
	
	public MemoryGatherer(){
	
	}
	
	private void getInfo(){
		
	}
	
	@Override
	public void run(){
		while(true){
			getInfo();
			try{
				wait(250);
			} catch(InterruptedException ie){
				ie.printStackTrace();
			}
		}
	}
	
	
}
