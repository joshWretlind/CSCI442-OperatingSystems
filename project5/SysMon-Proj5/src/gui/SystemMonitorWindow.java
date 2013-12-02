package gui;

import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.BorderFactory;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.table.DefaultTableModel;

import main.SystemMonitor;

/**
 * A class that sets up and shows the GUI for the Project 5 system monitor.
 * 
 * @author Mark Godwin
 *
 */
public class SystemMonitorWindow extends JFrame implements ActionListener{

	private SysGraph CPUGraph;
	private JPanel WindowPanel;
	private JMenuBar MenuBar;
	private static final long serialVersionUID = 1L;
	private JLabel[] MemoryLabels;
	private DefaultTableModel TableData;
	
	
	public DefaultTableModel getProcTable(){
		return this.TableData;
	}
	/**
	 * A getter function for the CPU graph.  Your threads can use this
	 * to add data points to the CPU graph.
	 * 
	 * @return The CPUGraph associated with this SystemMonitorWindow
	 */
	public synchronized SysGraph getCPUGraph()
	{
		return CPUGraph;
	}
	
	/**
	 * Adds rows to the process list.  Call removeAllRowsFromProcList prior to adding new rows
	 * when updating the process list.  This is definitely not the most efficient way to update
	 * this table, but it works.  It also explains why the list may appear to 'jump' if you're
	 * scrolling while updating
	 * 
	 * @param data
	 */
	public synchronized void addRowToProcList(String[] data)
	{
		TableData.addRow(data);
		TableData.fireTableDataChanged();
	}
	
	/**
	 * Removes all rows from the process list JTable.
	 */
	public synchronized void removeAllRowsFromProcList()
	{

		   int rowCount= TableData.getRowCount();

		  // System.out.println(rowCount);

		   for(int i=0;i<rowCount;i++ ){
		        TableData.removeRow(0);
		        //System.out.println(i);
		   }
		   TableData.fireTableDataChanged();
		   
	}
	
	
	/**
	 * This helper function takes the memory information as parameters and updates the GUI appropriately.
	 * 
	 * @param totalMem The total memory
	 * @param memFree The memory free
	 * @param memActive The memory active
	 * @param memInactive The memory inactive
	 * @param swapTotal The total swap
	 * @param swapFree The total swap free
	 * @param dirtyPages The dirty pages
	 * @param writeback The writeback
	 */
	public synchronized void updateMemoryInfo(int totalMem, int memFree, int memActive, int memInactive, int swapTotal, int swapFree, int dirtyPages, int writeback)
	{
		MemoryLabels[0].setText("Memory Total: " + totalMem + " KB");
		MemoryLabels[1].setText("Memory Free: "+ memFree + " KB");
		MemoryLabels[2].setText("Memory Active: " + memActive + " KB");
		MemoryLabels[3].setText("Memory Inactive: " + memInactive + " KB");
		MemoryLabels[4].setText("Swap Total: " + swapTotal + " KB");
		MemoryLabels[5].setText("Swap Free: " + swapFree + " KB");
		MemoryLabels[6].setText("Dirty Pages: " + dirtyPages + " KB");
		MemoryLabels[7].setText("Writeback: " + writeback + " KB");
	}
	
	
	// Default constructor
	/**
	 * Default Constructor for the system monitor
	 * @param numOfCPUs
	 */
	public SystemMonitorWindow(int numOfCPUs)
	{
		this.setTitle("Linux System Monitor");
		this.setSize(600, 500);
		this.setMinimumSize(new Dimension(600,500));
		
		WindowPanel = new JPanel();
		WindowPanel.setLayout(new GridLayout(3,0));
		
		// Creating the Menu Bar
		MenuBar = new JMenuBar();
		JMenu Prefs = new JMenu("Update Interval");
		JMenuItem halfSec = new JMenuItem("1/2 Second");
		halfSec.addActionListener(this);
		Prefs.add(halfSec);
		JMenuItem oneSec = new JMenuItem("1 Second");
		oneSec.addActionListener(this);
		Prefs.add(oneSec);
		JMenuItem fiveSec = new JMenuItem("5 Seconds");
		fiveSec.addActionListener(this);
		Prefs.add(fiveSec);
		MenuBar.add(Prefs);
		
		// Creating the System Graph.  Don't forget that you need to make the number
		// of lines dynamic, I'd recommend passing in a variable.
		CPUGraph = new SysGraph(0, 60, 0, 100, numOfCPUs, 500);
		CPUGraph.setBorder(BorderFactory.createTitledBorder("CPU/Memory Usage"));
		WindowPanel.add(CPUGraph);
		
		// Setting up the panel for memory info
		JPanel MemoryInfo = new JPanel();
		MemoryInfo.setLayout(new GridLayout(4,1,5,5));
		MemoryLabels = new JLabel[8];
		
		MemoryLabels[0] = new JLabel("Memory Total: N/A");
		MemoryLabels[1] = new JLabel("Memory Free: N/A");
		MemoryLabels[2] = new JLabel("Memory Active: N/A");
		MemoryLabels[3] = new JLabel("Memory Inactive: N/A");
		MemoryLabels[4] = new JLabel("Swap Total: N/A");
		MemoryLabels[5] = new JLabel("Swap Free: N/A");
		MemoryLabels[6] = new JLabel("Dirty Pages: N/A");
		MemoryLabels[7] = new JLabel("Writeback: N/A");
		
		for (int i = 0; i < 8; i++)
		{
			MemoryInfo.add(MemoryLabels[i]);
		}
		MemoryInfo.setBorder(BorderFactory.createTitledBorder("Memory Information"));
		WindowPanel.add(MemoryInfo);
		
		// Setting up the panel for individual process info
		JPanel ProcInfo = new JPanel();
		ProcInfo.setLayout(new GridLayout(1,0));
		ProcInfo.setBorder(BorderFactory.createTitledBorder("Process Information"));

		// Initializing the Table to hold our data for proc info.
		String[] columnNames = {"Name", "pid", "State", "# Threads", "Vol ctxt sw", "nonVol ctxt sw"};
		String[][] data = {{"N/A", "N/A", "N/A", "N/A", "N/A", "N/A"}};
		TableData = new DefaultTableModel(data, columnNames);
		JTable table = new JTable(TableData);
        table.setFillsViewportHeight(true);
        
        //Create the scroll pane and add the table to it.
        JScrollPane scrollPane = new JScrollPane(table);
        ProcInfo.add(scrollPane);
        
        // Finishing Touches
		WindowPanel.add(ProcInfo);
		this.add(WindowPanel);
		this.setJMenuBar(MenuBar);
		this.setVisible(true);
		this.setDefaultCloseOperation(EXIT_ON_CLOSE);
	}

	/* (non-Javadoc)
	 * @see java.awt.event.ActionListener#actionPerformed(java.awt.event.ActionEvent)
	 */
	@Override
	public synchronized void actionPerformed(ActionEvent arg0) {
		// This function handles our menu click event.  My code here is based off of how I implemented
		// the interval code, if you do it differently, make appropriate changes.
		JMenuItem j = (JMenuItem)arg0.getSource();
		
		int newInterval = 0;
		if (j.getText().equals("1/2 Second"))
			newInterval = 500;
		if (j.getText().equals("1 Second"))
			newInterval = 1000;
		if (j.getText().equals("5 Seconds"))
			newInterval = 5000;
			
		SystemMonitor.setUpdateInterval(newInterval);
		this.CPUGraph.setUInt(newInterval);
		
	}

	
}
