package main;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

import gui.SystemMonitorWindow;

public class SystemMonitor {
	
	public static void setUpdateInterval(int updateInterval)
	{
		// This is called when the user selects a new update interval
		// from the GUI
	}
	public static void main (String[] args)
	{

		SystemMonitorWindow mySysMon = new SystemMonitorWindow();
		Scheduler cpuAndMemoryScheduler = new Scheduler(250)
									.withTask(new MemoryGatherer(mySysMon))
									.withTask(new CPUGatherer(mySysMon));
		Scheduler processScheduler = new Scheduler(500)
		                            .withTask(new ProcessGatherer(mySysMon));
		cpuAndMemoryScheduler.start();
		processScheduler.start();
	}
}
