package main;

import java.util.ArrayList;
import java.util.List;


public class Scheduler extends Thread {
	
	private int delay;
	private List<Gatherer> tasks = new ArrayList<Gatherer>();
	
	public Scheduler(int delay) // , ArrayList<Harvester> taskList)
	{
		this.delay = delay;
	}

	private synchronized void delay()
	{
		// Here we acquire the lock for our current instance of our scheduler
		// and wait for the specified timeout
		try
		{
			wait(delay);
		} catch (InterruptedException e) {}
	}
	
	public void run()
	{
		while (true)
		{
			// Wait for the specified timeout
			delay();
			
			for(Gatherer gatherer: tasks){
				gatherer.run();
			}
		}
	}
	
	public Scheduler withTask(Gatherer task){
		tasks.add(task);
		return this;
	}
}
