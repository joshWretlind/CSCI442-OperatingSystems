package main;

public class ProcessData {
	private int pid;
	private String name;
	private String state;
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
	 * @return the state
	 */
	public String getState() {
		return state;
	}

	/**
	 * @param state the state to set
	 */
	public void setState(String state) {
		this.state = state;
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
}
