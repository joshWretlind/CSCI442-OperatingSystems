package main;


import gui.SystemMonitorWindow;

public class SystemMonitor {
	
	public static void setUpdateInterval(int updateInterval)
	{
		// This is called when the user selects a new update interval
		// from the GUI
	}
	public static void main (String[] args)
	{

		SystemMonitorWindow mySysMon = new SystemMonitorWindow(8);
		
		Scheduler cpuAndMemoryScheduler = new Scheduler(250) 
							           	  .withTask(new MemoryGatherer(mySysMon))
								          .withTask(new CPUGatherer(mySysMon));
		Scheduler processScheduler = new Scheduler(5000)
		                                 .withTask(new ProcessGatherer(mySysMon));
		
		cpuAndMemoryScheduler.start();
		processScheduler.start();
		
		
	}
}
