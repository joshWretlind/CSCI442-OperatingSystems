/**
 * 
 */
package main;

import gui.SystemMonitorWindow;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * @author Josh Wretlind
 *
 */
public class CPUGatherer extends Gatherer {
	
	private List<List<CPUData>> cpuData = new ArrayList<List<CPUData>>();
	private List<Double> cpuUsagePercentageList = new ArrayList<Double>();
	private int numOfCPUs;
	private BufferedReader reader;
	
	/**
	 * The constructor for a CPUGatherer
	 * @param gui the gui to place our data into
	 */
	public CPUGatherer(SystemMonitorWindow gui){
		super.setDelay(250);
		super.gui = gui;
	}
	
	/**
	 * Extracts CPUData from a input line
	 * @param line the line to parse data from
	 * @return a CPUData object with its fields filled in
	 */
	public CPUData parseData(String line){
		Pattern cpuPattern = Pattern.compile("cpu[0-9]");
		Matcher cpuMatcher = cpuPattern.matcher(line);
		while(cpuMatcher.find()){
			CPUData usageData = new CPUData();
			Pattern usagePattern = Pattern.compile(" [0-9]*");
			Matcher usageMatcher = usagePattern.matcher(line);
			int i = 0;
			//System.out.println(cpuMatches.)
			while(usageMatcher.find()){
				if(i < 4){
					switch (i){
						case 0:
							usageData.setUserModeTime(
									new Integer(line.substring(usageMatcher.start() + 1, usageMatcher.end())) );
							break;
						case 1:
							usageData.setUserIdleTime(
									new Integer(line.substring(usageMatcher.start() + 1, usageMatcher.end())) );
							break;
						case 2:
							usageData.setSystemModeTime(
									new Integer(line.substring(usageMatcher.start() + 1, usageMatcher.end())) );
							break;
						case 3:
							usageData.setIdleTaskTime(
									new Integer(line.substring(usageMatcher.start() + 1, usageMatcher.end())) );
							break;
					}
				}
				i++;
			}
			
			return usageData;
		}
		return null;
	}
	
	/**
	 * This reads through a process's stats, puts it into a list, and then adds the lists to the appropriate spot in the gui
	 */
	@Override
	void getInformation(){
		try {
			reader = new BufferedReader(new FileReader("/proc/stat"));
			String line = reader.readLine();
			int i = 0;
			while(line != null){
				CPUData data = parseData(line);
				line = reader.readLine();
				if(data != null){
				
				if(cpuData.size() <= i){
					List<CPUData> listOfData = new ArrayList<CPUData>();
					listOfData.add(data);
					addNewCPUsData(listOfData);
				} else {
					addNewDataToACPU(i,data);
					double cpuUsage = calculateCPUUsage(i);
					if(cpuUsagePercentageList.size() <= i){
						cpuUsagePercentageList.add(cpuUsage);
					} else {
						cpuUsagePercentageList.set(i, cpuUsage);
					}
					gui.getCPUGraph().addDataPoint(i, (int) (cpuUsagePercentageList.get(i)*100));
				}
				
				i++;
				}
			}
			this.setNumOfCPUs(i);
			
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			try {
				reader.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
	
	@Override
	public synchronized void run(){
		while(true){
			synchronized(gui){
				getInformation();
				gui.repaint();
			}
			try {
				this.wait();
			} catch (InterruptedException ie) {
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
	
	/**
	 * Adds a new CPU's data to the cpu list
	 * @param newCPUData
	 */
	public void addNewCPUsData(List<CPUData>  newCPUData){
		cpuData.add(newCPUData);
	}
	
	/**
	 * Adds a new data point to a specific cpu's data
	 * @param whichCPUToAddDataTo whichever cpu we need to add the data to
	 * @param data the data to add
	 */
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
	
	/**
	 * Calculates the cpu's usage for a specific cpu
	 * @param whichCPUToCalculcateFor which cpu to calculate for
	 * @return the calculated cpu data
	 */
	public double calculateCPUUsage(int whichCPUToCalculcateFor){
		List<CPUData> dataList = cpuData.get(whichCPUToCalculcateFor);
		CPUData dataPoint1 = dataList.get(dataList.size() - 1);
		CPUData dataPoint2 = dataList.get(dataList.size() - 2);
		double numerator = (dataPoint2.getUserModeTime() - dataPoint1.getUserModeTime());
		numerator += (dataPoint2.getUserIdleTime() - dataPoint1.getUserIdleTime());
		numerator += (dataPoint2.getSystemModeTime() - dataPoint1.getSystemModeTime());
		return (numerator / (numerator + (dataPoint2.getIdleTaskTime() - dataPoint1.getIdleTaskTime())));
	}

	/**
	 * @return the numOfCPUs
	 */
	public int getNumOfCPUs() {
		return numOfCPUs;
	}

	/**
	 * @param numOfCPUs the numOfCPUs to set
	 */
	public void setNumOfCPUs(int numOfCPUs) {
		this.numOfCPUs = numOfCPUs;
	}

	@Override
	public void updateGUI() {
		
	}
}
