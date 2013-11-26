package main;
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
	public ProcessGatherer(){
	}
	
	/**
	 * This process fills in the data for this process
	 */
	@Override
	public void getInformation(){
		
	}

	@Override
	public void run(){
		while(true){
			getInformation();
			try {
				wait(250);
			} catch (InterruptedException ie) {
				ie.printStackTrace();
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
}
