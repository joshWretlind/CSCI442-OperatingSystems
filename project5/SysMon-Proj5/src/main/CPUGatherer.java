/**
 * 
 */
package main;

import java.util.ArrayList;
import java.util.List;

/**
 * @author Josh Wretlind
 *
 */
public class CPUGatherer extends Gatherer {
	
	private List<CPUData> cpuData = new ArrayList<CPUData>();
	
	public CPUGatherer(){
		
	}
	
	@Override
	void getInformation(){
		
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
	 * @return the cpuData
	 */
	public List<CPUData> getCpuData() {
		return cpuData;
	}

	/**
	 * @param cpuData the cpuData to set
	 */
	public void setCpuData(List<CPUData> cpuData) {
		this.cpuData = cpuData;
	}
	
}
