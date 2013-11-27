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
	 */
	public ProcessGatherer(SystemMonitorWindow gui){
		super.setDelay(5000);
		super.gui = gui;
	}
	
	public ProcessData getProcessData(File dir){
		ProcessData procData = new ProcessData();
		procData.setPid(new Integer(dir.getName()));
		int i = 0;
		BufferedReader statusReader;
		try {
			statusReader = new BufferedReader(new FileReader(dir.getAbsolutePath() + "/status"));
			String line = statusReader.readLine();
			while(line != null){
				Pattern statePattern = Pattern.compile("(.*)");
				Matcher stateMatcher = statePattern.matcher(line);
				
				if(stateMatcher.find()){
					Pattern enumStatePattern = Pattern.compile(" . ");
					Matcher enumStateMatcher = enumStatePattern.matcher(line);
					enumStateMatcher.find();
					String substr = line.substring(enumStateMatcher.start(), enumStateMatcher.end());
					if(substr.equalsIgnoreCase(" S ")){
						procData.setProcessState(ProcessState.Sleeping);
					} else if(substr.equalsIgnoreCase(" R ")){
						procData.setProcessState(ProcessState.Running);
					} else if(substr.equalsIgnoreCase(" Z ")){
						procData.setProcessState(ProcessState.Zombie);
					} else if(substr.equalsIgnoreCase(" T ")){
						procData.setProcessState(ProcessState.TracingStoped);
					} else if(substr.equalsIgnoreCase(" D ")){
						procData.setProcessState(ProcessState.DiskSleep);
					} else if(substr.equalsIgnoreCase(" W ")){
						procData.setProcessState(ProcessState.Paging);
					}
					
				}
				
				Pattern namePattern = Pattern.compile("Name:.*");
				Matcher nameMatcher = namePattern.matcher(line);
				
				if(nameMatcher.find()){
					Pattern nameStringPattern = Pattern.compile("[[:blank:]][A-Za-z].*");
					Matcher nameStringMatcher = nameStringPattern.matcher(line);
					if(nameStringMatcher.find()){
						procData.setName(line.substring(nameStringMatcher.start(), nameStringMatcher.end()));
					}
				}
				
				Pattern threadLinePattern = Pattern.compile("Thread:");
				Matcher threadLineMatcher = threadLinePattern.matcher(line);
				
				if(threadLineMatcher.find()){
					Pattern threadNumberPattern = Pattern.compile("[0-9].*");
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
				
				
			}
			statusReader.close();
			
			gui.addRowToProcList(procData.toStringCollection());
			
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		
		
		return procData;
	}
	/**
	 * This process fills in the data for this process
	 */
	@Override
	public void getInformation(){
		File procDir = new File("/proc");
		for(File f : procDir.listFiles()){
			if(f.isDirectory()){
				Pattern pidPattern = Pattern.compile("/proc/[0-9].*");
				Matcher pidMatcher = pidPattern.matcher(f.getAbsolutePath());
				if(pidMatcher.find()){
					processes.add(getProcessData(f));
				}
			}
		}
	}

	@Override
	public synchronized  void run(){
		while(true){
			gui.removeAllRowsFromProcList();
			getInformation();
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
	
	public void addProcess(ProcessData process){
		this.processes.add(process);
	}

	@Override
	public void updateGUI() {
		// TODO Auto-generated method stub
		
	}
}
