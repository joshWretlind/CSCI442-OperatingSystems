package main;

/**
 * This is a 
 * @author Josh Wretlind
 *
 */
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
	private int programSize;
	private int maxProgramSize;
	private int parentPid;
	
	
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
		String[] values = new String[9];
		values[0] = this.name;
		values[1] = Integer.toString(this.pid);
		values[2] = this.processState.name();
		values[3] = Integer.toString(this.numOfThreads);
		values[4] = Integer.toString(this.volCText);
		values[5] = Integer.toString(this.nonVolCText);
		values[6] = Integer.toString(this.programSize);
		values[7] = Integer.toString(this.maxProgramSize);
		values[8] = Integer.toString(this.parentPid);
		
		return values;
	}

	/**
	 * @return the programSize
	 */
	public int getProgramSize() {
		return programSize;
	}

	/**
	 * @param programSize the programSize to set
	 */
	public void setProgramSize(int programSize) {
		this.programSize = programSize;
	}

	/**
	 * @return the maxProgramSize
	 */
	public int getMaxProgramSize() {
		return maxProgramSize;
	}

	/**
	 * @param maxProgramSize the maxProgramSize to set
	 */
	public void setMaxProgramSize(int maxProgramSize) {
		this.maxProgramSize = maxProgramSize;
	}

	/**
	 * @return the parentPid
	 */
	public int getParentPid() {
		return parentPid;
	}

	/**
	 * @param parentPid the parentPid to set
	 */
	public void setParentPid(int parentPid) {
		this.parentPid = parentPid;
	}
}
