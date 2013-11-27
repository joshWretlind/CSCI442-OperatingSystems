package main;

import gui.SystemMonitorWindow;

public abstract class Gatherer extends Thread {

	private int delay;
	SystemMonitorWindow gui;
	
	abstract void getInformation();
	
	@Override
	public abstract void run();

	/**
	 * @return the delay
	 */
	public int getDelay() {
		return delay;
	}

	/**
	 * @param delay the delay to set
	 */
	public void setDelay(int delay) {
		this.delay = delay;
	}
	
	public abstract void updateGUI();
}
