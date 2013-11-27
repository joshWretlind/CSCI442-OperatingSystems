/**
 * 
 */
package main;

/**
 * @author Josh Wretlind
 *
 */

public class MemoryData {
	private int totalRam;
	private int freeRam;
	private int activeRam;
	private int inactiveRam;
	private int totalSwap;
	private int freeSwap;
	private int numOfDirtyPages;
	private int writeBack;
	
	/**
	 * @return the totalRam
	 */
	public int getTotalRam() {
		return totalRam;
	}
	
	/**
	 * @param totalRam the totalRam to set
	 */
	public void setTotalRam(int totalRam) {
		this.totalRam = totalRam;
	}

	/**
	 * @return the freeRam
	 */
	public int getFreeRam() {
		return freeRam;
	}

	/**
	 * @param freeRam the freeRam to set
	 */
	public void setFreeRam(int freeRam) {
		this.freeRam = freeRam;
	}

	/**
	 * @return the activeRam
	 */
	public int getActiveRam() {
		return activeRam;
	}

	/**
	 * @param activeRam the activeRam to set
	 */
	public void setActiveRam(int activeRam) {
		this.activeRam = activeRam;
	}

	/**
	 * @return the inactiveRam
	 */
	public int getInactiveRam() {
		return inactiveRam;
	}

	/**
	 * @param inactiveRam the inactiveRam to set
	 */
	public void setInactiveRam(int inactiveRam) {
		this.inactiveRam = inactiveRam;
	}

	/**
	 * @return the totalSwap
	 */
	public int getTotalSwap() {
		return totalSwap;
	}

	/**
	 * @param totalSwap the totalSwap to set
	 */
	public void setTotalSwap(int totalSwap) {
		this.totalSwap = totalSwap;
	}

	/**
	 * @return the freeSwap
	 */
	public int getFreeSwap() {
		return freeSwap;
	}

	/**
	 * @param freeSwap the freeSwap to set
	 */
	public void setFreeSwap(int freeSwap) {
		this.freeSwap = freeSwap;
	}

	/**
	 * @return the numOfDirtyPages
	 */
	public int getNumOfDirtyPages() {
		return numOfDirtyPages;
	}

	/**
	 * @param numOfDirtyPages the numOfDirtyPages to set
	 */
	public void setNumOfDirtyPages(int numOfDirtyPages) {
		this.numOfDirtyPages = numOfDirtyPages;
	}

	/**
	 * @return the writeBack
	 */
	public int getWriteBack() {
		return writeBack;
	}

	/**
	 * @param writeBack the writeBack to set
	 */
	public void setWriteBack(int writeBack) {
		this.writeBack = writeBack;
	}
}
