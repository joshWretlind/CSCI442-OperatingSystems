/**
 * 
 */
package main;

/**
 * @author Josh wretlind
 *
 */
public class CPUData {

	private int userModeTime;
	private int systemModeTime;
	private int userIdleTime;
	private int idleTaskTime;
	
	/**
	 * @return the userModeTime
	 */
	public int getUserModeTime() {
		return userModeTime;
	}
	
	/**
	 * @param userModeTime the userModeTime to set
	 */
	public void setUserModeTime(int userModeTime) {
		this.userModeTime = userModeTime;
	}

	/**
	 * @return the systemModeTime
	 */
	public int getSystemModeTime() {
		return systemModeTime;
	}

	/**
	 * @param systemModeTime the systemModeTime to set
	 */
	public void setSystemModeTime(int systemModeTime) {
		this.systemModeTime = systemModeTime;
	}

	/**
	 * @return the userIdleTime
	 */
	public int getUserIdleTime() {
		return userIdleTime;
	}

	/**
	 * @param userIdleTime the userIdleTime to set
	 */
	public void setUserIdleTime(int userIdleTime) {
		this.userIdleTime = userIdleTime;
	}

	/**
	 * @return the idleTaskTime
	 */
	public int getIdleTaskTime() {
		return idleTaskTime;
	}

	/**
	 * @param idleTaskTime the idleTaskTime to set
	 */
	public void setIdleTaskTime(int idleTaskTime) {
		this.idleTaskTime = idleTaskTime;
	}
}