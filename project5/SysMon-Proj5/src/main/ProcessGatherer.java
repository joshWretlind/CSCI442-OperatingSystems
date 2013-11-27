package main;
import gui.SystemMonitorWindow;

import java.util.ArrayList;
import java.util.List;

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
	
	/**
	 * This process fills in the data for this process
	 */
	@Override
	public void getInformation(){
		System.out.println("ProcessGather running");
	}

	@Override
	public synchronized  void run(){
		while(true){
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
