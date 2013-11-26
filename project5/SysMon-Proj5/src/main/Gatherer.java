package main;

public abstract class Gatherer extends Thread {

	abstract void getInformation();
	
	@Override
	public abstract void run();
}
