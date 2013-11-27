package main;

public class ProcessData {
	private int pid;
	private String name;
	enum ProcessState{
		Running, Sleeping, Zombie, Dead, DiskSleep, Stopped, TracingStoped
	};
	private ProcessState processState;
	private int numOfThreads;
	private String volCText;
	private String nonVolCText;
	
	
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
	public String getVolCText() {
		return volCText;
	}

	/**
	 * @param volCText the volCText to set
	 */
	public void setVolCText(String volCText) {
		this.volCText = volCText;
	}

	/**
	 * @return the nonVolCText
	 */
	public String getNonVolCText() {
		return nonVolCText;
	}

	/**
	 * @param nonVolCText the nonVolCText to set
	 */
	public void setNonVolCText(String nonVolCText) {
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
}
