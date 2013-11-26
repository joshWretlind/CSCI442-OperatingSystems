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
	
	private List<List<CPUData>> cpuData = new ArrayList<List<CPUData>>();
	private List<Double> cpuUsagePercentageList;
	
	public CPUGatherer(){
		super.setDelay(250);
	}
	
	@Override
	void getInformation(){
		
	}
	
	@Override
	public void run(){
		while(true){
			getInformation();
			try {
				wait(super.getDelay());
			} catch (InterruptedException ie) {
				ie.printStackTrace();
			}
		}
	}

	/**
	 * @return the cpuData
	 */
	public List<List<CPUData>> getCpuData() {
		return cpuData;
	}

	/**
	 * @param cpuData the cpuData to set
	 */
	public void setCpuData(List<List<CPUData>> cpuData) {
		this.cpuData = cpuData;
	}
	
	public void addNewCPUsData(List<CPUData>  newCPUData){
		cpuData.add(newCPUData);
	}
	
	public void addNewDataToACPU(int whichCPUToAddDataTo, CPUData data){
		cpuData.get(whichCPUToAddDataTo).add(data);
	}

	/**
	 * @return the cpuUsagePercentageList
	 */
	public List<Double> getCpuUsagePercentageList() {
		return cpuUsagePercentageList;
	}

	/**
	 * @param cpuUsagePercentageList the cpuUsagePercentageList to set
	 */
	public void setCpuUsagePercentageList(List<Double> cpuUsagePercentageList) {
		this.cpuUsagePercentageList = cpuUsagePercentageList;
	}
	
	public double calculateCPUUsage(int whichCPUToCalculcateFor){
		List<CPUData> dataList = cpuData.get(whichCPUToCalculcateFor);
		CPUData dataPoint1 = dataList.get(dataList.size() - 1);
		CPUData dataPoint2 = dataList.get(dataList.size() - 2);
		double numerator = (dataPoint2.getUserModeTime() - dataPoint1.getUserModeTime());
		numerator += (dataPoint2.getUserIdleTime() - dataPoint1.getUserIdleTime());
		numerator += (dataPoint2.getSystemModeTime() - dataPoint1.getSystemModeTime());
		
		return (numerator / (numerator + (dataPoint2.getIdleTaskTime() - dataPoint1.getIdleTaskTime())));
	}
}
