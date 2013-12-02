/**
 * This is a class for all of the memory gathering procedure
 */
package main;

import gui.SystemMonitorWindow;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * @author Josh Wretlind
 *
 */
public class MemoryGatherer extends Gatherer {
	
	BufferedReader reader;
	MemoryData memoryData;
	
	/**
	 * The constructor for a memoryGatherer object
	 * @param gui
	 */
	public MemoryGatherer(SystemMonitorWindow gui){
		super.setDelay(250);
		super.gui = gui;
	}
	
	/**
	 * Extracts a information about memory from a line of a file
	 * @param line the line to parse information from
	 */
	public void parseData(String line){
		Pattern totalMemoryPattern = Pattern.compile("MemTotal:.*");
		
		Matcher totalMemoryMatcher = totalMemoryPattern.matcher(line);
		if(totalMemoryMatcher.matches()){
			Matcher numberMatcher = numberPattern.matcher(line);
			while(numberMatcher.find()){
				if(numberMatcher.start() != numberMatcher.end()){
					memoryData.setTotalRam(new Integer(line.substring(numberMatcher.start(), numberMatcher.end())));
					break;
				}
			}
			return;
		}
		
		Pattern freeMemoryPattern = Pattern.compile("MemFree: *[0-9]*");
		Matcher freeMemoryMatcher = freeMemoryPattern.matcher(line);
		if(freeMemoryMatcher.find()){
			Matcher numberMatcher = numberPattern.matcher(line);
			while(numberMatcher.find()){
				if(numberMatcher.start() != numberMatcher.end()){
					memoryData.setFreeRam(new Integer(line.substring(numberMatcher.start(), numberMatcher.end())));
					break;
				}
			}
			return;
		}
		
		Pattern activeMemoryPattern = Pattern.compile("Active: *[0-9]*");
		Matcher activeMemoryMatcher = activeMemoryPattern.matcher(line);
		if(activeMemoryMatcher.find()){
			Matcher numberMatcher = numberPattern.matcher(line);
			while(numberMatcher.find()){
				if(numberMatcher.start() != numberMatcher.end()){
					memoryData.setActiveRam(new Integer(line.substring(numberMatcher.start(), numberMatcher.end())));
					break;
				}
			}
			return;
		}
		
		Pattern inactiveMemoryPattern = Pattern.compile("Inactive: *[0-9]*");
		Matcher inactiveMemoryMatcher = inactiveMemoryPattern.matcher(line);
		if(inactiveMemoryMatcher.find()){
			Matcher numberMatcher = numberPattern.matcher(line);
			while(numberMatcher.find()){
				if(numberMatcher.start() != numberMatcher.end()){
					memoryData.setInactiveRam(new Integer(line.substring(numberMatcher.start(), numberMatcher.end())));
					break;
				}
			}
			return;
		}
		
		Pattern totalSwapPattern = Pattern.compile("SwapTotal: *[0-9]*");
		Matcher totalSwapMatcher = totalSwapPattern.matcher(line);
		if(totalSwapMatcher.find()){
			Matcher numberMatcher = numberPattern.matcher(line);
			while(numberMatcher.find()){
				if(numberMatcher.start() != numberMatcher.end()){
					memoryData.setTotalSwap(new Integer(line.substring(numberMatcher.start(), numberMatcher.end())));
					break;
				}
			}
			return;
		}
		
		Pattern freeSwapPattern = Pattern.compile("SwapFree: *[0-9]*");
		Matcher freeSwapMatcher = freeSwapPattern.matcher(line);
		if(freeSwapMatcher.find()){
			Matcher numberMatcher = numberPattern.matcher(line);
			while(numberMatcher.find()){
				if(numberMatcher.start() != numberMatcher.end()){
					memoryData.setFreeSwap(new Integer(line.substring(numberMatcher.start(), numberMatcher.end())));
					break;
				}
			}
			return;
		}
		
		Pattern dirtyPagesPattern = Pattern.compile("Dirty: *[0-9]*");
		Matcher dirtyPagesMatches = dirtyPagesPattern.matcher(line);
		if(dirtyPagesMatches.find()){
			Matcher numberMatcher = numberPattern.matcher(line);
			while(numberMatcher.find()){
				if(numberMatcher.start() != numberMatcher.end()){
					memoryData.setNumOfDirtyPages(new Integer(line.substring(numberMatcher.start(), numberMatcher.end())));
					break;
				}
			}
			return;
		}
		
		Pattern writeBackPattern = Pattern.compile("Writeback: *[0-9]*");
		Matcher writeBackMatcher = writeBackPattern.matcher(line);
		if(writeBackMatcher.find()){
			Matcher numberMatcher = numberPattern.matcher(line);
			while(numberMatcher.find()){
				if(numberMatcher.start() != numberMatcher.end()){
					memoryData.setWriteBack(new Integer(line.substring(numberMatcher.start(), numberMatcher.end())));
					break;
				}
			}
			return;
		}
	}
	
	/**
	 * Fills in all of the information for a memoryData object, updates the gui with the information
	 */
	@Override
	void getInformation(){
		try {
			reader = new BufferedReader(new FileReader("/proc/meminfo"));
			String line = reader.readLine();
			memoryData = new MemoryData();
			
			while(line != null){
				parseData(line);
				line = reader.readLine();
			}
			gui.updateMemoryInfo(memoryData.getTotalRam(),
					             memoryData.getFreeRam(),
			                     memoryData.getActiveRam(),
					             memoryData.getInactiveRam(),
				                 memoryData.getTotalSwap(),
				                 memoryData.getFreeSwap(),
				                 memoryData.getNumOfDirtyPages(),
				                 memoryData.getWriteBack());
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
		
	}
	
	@Override
	public synchronized void run(){
		while(true){
			synchronized(gui){
				getInformation();
				gui.repaint();
			}
			try{
				wait();
			} catch(InterruptedException ie){
			}
		}
	}

	@Override
	public void updateGUI() {
		
	}
	
	
}
