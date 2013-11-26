package main;

public abstract class Gatherer extends Thread {

	private int delay;
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
}
