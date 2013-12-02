package main;


import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
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
		//Figure out how many CPU's there are
		BufferedReader reader;
		int i = 0;
		try {
			reader = new BufferedReader(new FileReader("/proc/stat"));
			String line = reader.readLine();
			Pattern cpuPattern = Pattern.compile("cpu[0-9][0-9]*");
			while(line != null){
				Matcher cpuMatcher = cpuPattern.matcher(line);
				if(cpuMatcher.find()){
					i++;
				}
				line = reader.readLine();
			}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		//Set up the Schedulers and system monitor
		SystemMonitorWindow mySysMon = new SystemMonitorWindow(i);
		
		Scheduler cpuAndMemoryScheduler = new Scheduler(350) 
							           	  .withTask(new MemoryGatherer(mySysMon))
								          .withTask(new CPUGatherer(mySysMon));
		Scheduler processScheduler = new Scheduler(5000)
		                                 .withTask(new ProcessGatherer(mySysMon));
		
		//Start Schedulers with execution threads
		cpuAndMemoryScheduler.start();
		processScheduler.start();
		
		
	}
}
