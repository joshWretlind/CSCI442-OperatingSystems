package main;
import gui.SystemMonitorWindow;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import main.ProcessData.ProcessState;

/**
 * ProcessGatherer is the threads that gather process information for the system monitor.
 * @author Josh Wretlind
 */
public class ProcessGatherer extends Gatherer {

	private List<ProcessData> processes = new ArrayList<ProcessData>();
	
	/**
	 * Constructor for a processGatherer thread
	 * @param gui the gui to update with our info
	 */
	public ProcessGatherer(SystemMonitorWindow gui){
		super.setDelay(5000);
		super.gui = gui;
	    
	}
	
	/**
	 * This method basically extracts data from a /proc/<pid> directory and puts it into a process data object
	 * @param dir the directiory file object for the process that we've found
	 * @return a ProcessData object with its feilds filled in
	 */
	public ProcessData getProcessData(File dir){
		ProcessData procData = new ProcessData();
		procData.setPid(new Integer(dir.getName()));
		int i = 0;
		BufferedReader statusReader;
		try {
			statusReader = new BufferedReader(new FileReader(dir.getAbsolutePath() + "/status"));
			String line = statusReader.readLine();
			while(line != null){
				Pattern statePattern = Pattern.compile("[(][a-zA-Z][a-zA-Z]*[)]");
				Matcher stateMatcher = statePattern.matcher(line);
				
				if(stateMatcher.find()){
					String substr = line.substring(stateMatcher.start(), stateMatcher.end());
					if(substr.equalsIgnoreCase("(sleeping)")){
						procData.setProcessState(ProcessState.Sleeping);
					} else if(substr.equalsIgnoreCase("(running)")){
						procData.setProcessState(ProcessState.Running);
					} else if(substr.equalsIgnoreCase("(zombie)")){
						procData.setProcessState(ProcessState.Zombie);
					} else if(substr.equalsIgnoreCase("(stopped)")){
						procData.setProcessState(ProcessState.TracingStoped);
					} else if(substr.equalsIgnoreCase("(disk sleep)")){
						procData.setProcessState(ProcessState.DiskSleep);
					} else if(substr.equalsIgnoreCase("(dead)")){
						procData.setProcessState(ProcessState.Dead);
					} else {
						procData.setProcessState(ProcessState.Running);
					}
					
				}
				
				Pattern namePattern = Pattern.compile("Name:.*");
				Matcher nameMatcher = namePattern.matcher(line);
				
				if(nameMatcher.find()){
					Pattern nameStringPattern = Pattern.compile(":.*[a-zA-Z].*");
					Matcher nameStringMatcher = nameStringPattern.matcher(line);
					if(nameStringMatcher.find()){
						procData.setName(line.substring(nameStringMatcher.start() + 1, nameStringMatcher.end()));
					}
				}
				
				Pattern threadLinePattern = Pattern.compile("Threads:.*");
				Matcher threadLineMatcher = threadLinePattern.matcher(line);
				
				if(threadLineMatcher.find()){
					Pattern threadNumberPattern = Pattern.compile("[0-9][0-9]*");
					Matcher threadNumberMatcher = threadNumberPattern.matcher(line);
					while(threadNumberMatcher.find()){
						if(threadNumberMatcher.end() != threadNumberMatcher.start()){
							procData.setNumOfThreads(new Integer(line.substring(threadNumberMatcher.start(), threadNumberMatcher.end())));
						}
					}
				}
				
				Pattern vountaryCTextSwitchesPattern = Pattern.compile("voluntary_ctxt_switches:.*");
				Matcher vountaryCTextSwitchesMatches = vountaryCTextSwitchesPattern.matcher(line);
				
				if(vountaryCTextSwitchesMatches.find()){
					i++;
					Pattern vountaryCTextSwitchesNumberPattern = Pattern.compile("[0-9].*");
					Matcher vountaryCTextSwitchesNumberMatcher = vountaryCTextSwitchesNumberPattern.matcher(line);
					while(vountaryCTextSwitchesNumberMatcher.find()){
						
						if(vountaryCTextSwitchesNumberMatcher.end() != vountaryCTextSwitchesNumberMatcher.start()){
							if(i == 1){
								procData.setVolCText(new Integer(line.substring(vountaryCTextSwitchesNumberMatcher.start(), vountaryCTextSwitchesNumberMatcher.end())));
							} else if(i ==2){
								procData.setNonVolCText(new Integer(line.substring(vountaryCTextSwitchesNumberMatcher.start(), vountaryCTextSwitchesNumberMatcher.end())));
							}
						}
					}
				}
				
				Pattern programSizePattern = Pattern.compile("VmSize:.*");
				Matcher programSizeMatcher = programSizePattern.matcher(line);
				if(programSizeMatcher.find()){
					Matcher programSizeNumber = numberPattern.matcher(line);
					if(programSizeNumber.find()){
						procData.setProgramSize(new Integer(line.substring(programSizeNumber.start(), programSizeNumber.end())));
					}
				}
				
				Pattern maxSizePattern = Pattern.compile("VmPeak:.*");
				Matcher maxSizeMatcher = maxSizePattern.matcher(line);
				if(maxSizeMatcher.find()){
					Matcher maxSizeNumber = numberPattern.matcher(line);
					if(maxSizeNumber.find()){
						procData.setMaxProgramSize(new Integer(line.substring(maxSizeNumber.start(), maxSizeNumber.end())));
					}
				}
				
				Pattern parentPidPattern = Pattern.compile("PPid:.*");
				Matcher parentPidMatcher = parentPidPattern.matcher(line);
				if(parentPidMatcher.find()){
					Matcher parentPidNumber = numberPattern.matcher(line);
					if(parentPidNumber.find()){
						procData.setParentPid(new Integer(line.substring(parentPidNumber.start(), parentPidNumber.end())));
					}
				}
				
				line = statusReader.readLine();

			}
			statusReader.close();
			
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		} catch(Exception e) {
			
		}
		
		
		
		return procData;
	}
	/**
	 * This process finds all of the processes, puts them into a list, and adds them to the gui
	 */
	@Override
	public void getInformation(){
		Thread.setDefaultUncaughtExceptionHandler(new Thread.UncaughtExceptionHandler() {
			public void uncaughtException(Thread t, Throwable e) {
				if(e instanceof NullPointerException){
					e.printStackTrace();
				}
			}
		});
		File procDir = new File("/proc");
		processes = new ArrayList<ProcessData>();
		for(File f : procDir.listFiles()){
			if(f.isDirectory()){
				Pattern pidPattern = Pattern.compile("/proc/[0-9].*");
				Matcher pidMatcher = pidPattern.matcher(f.getAbsolutePath());
				if(pidMatcher.find()){
					processes.add(getProcessData(f));
				}
			}
		}
		for(ProcessData proc: processes){
			if(proc.getProcessState() == null){
				System.out.println("Null process: " + proc.getName());
				System.out.println("Null Process: " + proc.getPid());
			}
			gui.addRowToProcList(proc.toStringCollection());
		}
		
	}

	@Override
	public synchronized  void run(){
		while(true){
			synchronized(gui){
				gui.removeAllRowsFromProcList();
				getInformation();
			}
			try {
				wait();
			} catch (InterruptedException ie) {
			}
		}
	}

	/**
	 * @return the processes
	 */
	public List<ProcessData> getProcesses() {
		return processes;
	}

	/**
	 * @param processes the processes to set
	 */
	public void setProcesses(List<ProcessData> processes) {
		this.processes = processes;
	}
	
	/**
	 * Add a process' data to the process list
	 * @param process process data to add to the list
	 */
	public void addProcess(ProcessData process){
		this.processes.add(process);
	}

	
	@Override
	public void updateGUI() {
		
	}
	


}
