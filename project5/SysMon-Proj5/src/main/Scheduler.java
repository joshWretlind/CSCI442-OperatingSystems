package main;


public class Scheduler extends Thread {
	
	public Scheduler(int delay) // , ArrayList<Harvester> taskList)
	{
	}

	private synchronized void delay()
	{
		// Here we acquire the lock for our current instance of our scheduler
		// and wait for the specified timeout
		try
		{
			wait(500);
		} catch (InterruptedException e) {}
	}
	
	public void run()
	{
		while (true)
		{
			// Wait for the specified timeout
			delay();
			
			// Dispatch each harvester to collect data/update gui.
			
			// For those unfamiliar with Java, this is the equivalent of
			// a for-each loop... For each Harvester h in Tasks...do...
			// for (Harvester h : Tasks)
			// {
			// 	 h.collect();
			// }
		}
	}
}
