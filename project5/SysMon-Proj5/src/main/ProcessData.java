package main;

import java.util.ArrayList;
import java.util.List;

public class ProcessData {
	private int pid;
	private String name;
	enum ProcessState{
		Running, Sleeping, Zombie, DiskSleep, Dead, TracingStoped
	};
	private ProcessState processState;
	private int numOfThreads;
	private int volCText;
	private int nonVolCText;
	
	
	/**
	 * @return the pid
	 */
	public int getPid() {
		return pid;
	}
	
	/**
	 * @param pid the pid to set
	 */
	public void setPid(int pid) {
		this.pid = pid;
	}

	/**
	 * @return the name
	 */
	public String getName() {
		return name;
	}

	/**
	 * @param name the name to set
	 */
	public void setName(String name) {
		this.name = name;
	}

	/**
	 * @return the numOfThreads
	 */
	public int getNumOfThreads() {
		return numOfThreads;
	}

	/**
	 * @param numOfThreads the numOfThreads to set
	 */
	public void setNumOfThreads(int numOfThreads) {
		this.numOfThreads = numOfThreads;
	}

	/**
	 * @return the volCText
	 */
	public int getVolCText() {
		return volCText;
	}

	/**
	 * @param volCText the volCText to set
	 */
	public void setVolCText(int volCText) {
		this.volCText = volCText;
	}

	/**
	 * @return the nonVolCText
	 */
	public int getNonVolCText() {
		return nonVolCText;
	}

	/**
	 * @param nonVolCText the nonVolCText to set
	 */
	public void setNonVolCText(int nonVolCText) {
		this.nonVolCText = nonVolCText;
	}

	/**
	 * @return the processState
	 */
	public ProcessState getProcessState() {
		return processState;
	}

	/**
	 * @param processState the processState to set
	 */
	public void setProcessState(ProcessState processState) {
		this.processState = processState;
	}
	
	public String[] toStringCollection(){
		String[] values = new String[6];
		values[0] = this.name;
		values[1] = Integer.toString(this.pid);
		values[2] = this.processState.name();
		values[3] = Integer.toString(this.numOfThreads);
		values[4] = Integer.toString(this.volCText);
		values[5] = Integer.toString(this.nonVolCText);
		
		return values;
	}
}
