package gui;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Insets;
import java.awt.RenderingHints;
import java.util.ArrayList;

import javax.swing.JComponent;
import javax.swing.border.Border;

/**
 * SysGraph is a JComponent used to display a series of data points
 * in a manner that closely represents a system monitor graph.
 * 
 * @author Mark Godwin
 */
public class SysGraph extends JComponent {

	private static final long serialVersionUID = 1L;
	
	private ArrayList<ArrayList<Integer>> DataPoints;
	private int yMin, yMax, xMin, xMax, uIntVal;
	
	/**
	 * Initializes a new SysGraph object with the specified scale and
	 * number of data points.
	 * 
	 * @param tMin The minimum time value (seconds) for the graph - typically 0
	 * @param tMax The maximum time value (seconds) for the graph - typically 60
	 * @param yMin The minimum y value for the graph
	 * @param yMax The maximum y value for the graph
	 * @param numLines The number of lines that will be available on this graph.
	 * The last line will always be called RAM, so ensure you have enough lines for CPU and RAM
	 * together.
	 * @param updateIntervalMS How frequently the graph will be updated.  This determines
	 * how many data points will exist on the graph.
	 * 
	 */
	public SysGraph(int tMin, int tMax, int yMin, int yMax, int numLines, int updateIntervalMS)
	{
		this.yMin = yMin;
		this.yMax = yMax;
		this.xMin = tMin;
		this.xMax = tMax;
		this.uIntVal = (int)((double)this.xMax / (updateIntervalMS/1000.0));
		DataPoints = new ArrayList<ArrayList<Integer>>();
		for (int i = 0; i < numLines; i++)
		{
			DataPoints.add(new ArrayList<Integer>());
		}
		
		
	}
	
	/**
	 * Sets the update interval for the graph.  This ensures proper scaling.
	 * 
	 * @param updateIntervalMS
	 */
	public synchronized void setUInt(int updateIntervalMS)
	{
		this.uIntVal = (int)((double)this.xMax / (updateIntervalMS/1000.0));
	}
	
	
	/**
	 * Adds a data point to the graph for the specified line.
	 * 
	 * @param lineNum The number of the line to add the data point value to.
	 * This begins at index 0, not 1.
	 * @param value The data point value
	 */
	public synchronized void addDataPoint(int lineNum, int value)
	{
		while ((DataPoints.get(lineNum)).size() >= this.uIntVal + 1)
		{
			(DataPoints.get(lineNum)).remove(0);
		}
		
		DataPoints.get(lineNum).add(value);
		
	}
	
	/**
	 * A helper function to get a specific color associated with a line.
	 * 
	 * @param The line number
	 * @return A Color object associated with the number passed in
	 */
	private Color getEnumerableColor(int num)
	{
		switch (num)
		{
		case 0:
			return Color.RED;
		case 1:
			return Color.BLUE;
		case 2:
			return Color.GRAY;
		case 3:
			return Color.GREEN;
		case 4:
			return Color.MAGENTA;
		case 5:
			return Color.ORANGE;
		case 6:
			return Color.PINK;
		default:
			return Color.WHITE;
		}
	}
	
	/* (non-Javadoc)
	 * @see javax.swing.JComponent#paintComponent(java.awt.Graphics)
	 */
	protected synchronized void paintComponent(Graphics g)
	{
		// Here's where we draw the pretty graph!
		
		super.paintComponent(g);
		
		Graphics2D g2 = (Graphics2D)g;
		g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
		
		// Offsets in the case a border is specified.
		int oBot=0, oTop=0, oLeft=0, oRight=0;
		
		int height=this.getHeight();
		int width=this.getWidth();
		int x = 0, y = 0;
		
		// Find out if a border has been specified, if so, find the
		// offsets needed to make the drawable region not clip the border
		if (this.getBorder() != null)
		{
			Border a = this.getBorder();
			Insets b = a.getBorderInsets(this);
			oBot = b.bottom;
			oTop = b.top;
			oLeft = b.left;
			oRight = b.right;
			width  = width - oRight - oLeft;
			height = height - oBot - oTop;
			x += oLeft;
			y += oTop;
		}
		
		// Offset the graph size so we can draw labels.
		height = (int)(height*.7);
		width -= 40;
		x+=40;
		
		// Draw the Background
		g2.setColor(Color.WHITE);
		g2.fillRect(x, y, width, height);
		
		
		// If we don't have enough datapoints specified (need 2 to draw a line)
		// draw a message indicating that the graph doesn't have enough data.
		if ((DataPoints.get(0)).size() < 2)
		{
			g2.setColor(Color.WHITE);
			g2.drawString("Not Enough Data Polled Yet.", (int)(width/2.0) - 85, (int)(height/2.0)+oTop);
		}
		else
		{
			// Here we draw all the sweet lines.
			int index = 0;
			
			g2.setStroke(new BasicStroke(1,BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND));
			
			for (ArrayList<Integer> a : DataPoints)
			{
				g2.setColor(getEnumerableColor(index++));
				for (int i = a.size() - 2; i >= 0; i--)
				{
					int x1 = (width+x) - (int)((a.size()-1-(i+1))*((double)width/(this.uIntVal)));
					int x2 = (width+x) - (int)((a.size()-1-i) * ((double)width/(this.uIntVal)));
					int y1 = (height+oTop) - (int)((double)((double)(height) / (yMax - yMin)) * a.get(i+1));
					int y2 = (height+oTop) - (int)((double)((double)(height) / (yMax - yMin)) * a.get(i)); 
					g2.drawLine(x1, y1, x2, y2);
				}
			}
			
			// Here we want to draw the labels.
			
			int newy = (int)((this.getHeight()-(y+height))/2.0);
			if (newy > 14)
			{
				newy += y + height;
				g2.setStroke(new BasicStroke(1,BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND));
				
				for (int i = 0; i < DataPoints.size(); i++)
				{
					g2.setColor(getEnumerableColor(i));
					g2.fillRect(x+100*i, newy, 20, 10);
					g2.setColor(Color.BLACK);
					g2.drawRect(x+100*i, newy, 20, 10);
					String prefix = "CPU" + (i+1);
					
					// We assume the last series to be RAM for our application.
					if (DataPoints.size() > 1 && i == DataPoints.size()-1)
						prefix = "RAM";
					if (DataPoints.get(i).size() > 0)
						g2.drawString(prefix + " " + DataPoints.get(i).get(DataPoints.get(i).size()-1)+"%", x+22+100*i, newy+10);
			
				}
			}
		}
		
		
		// Draw the border and labels.
		float [] Dashes = { 2.0f, 4.0f };
		g2.setStroke(new BasicStroke(1.0f,BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND, 1.0f, Dashes, 0.0f ));
		g2.setColor(Color.BLACK);
		g2.drawLine((int)(x+(width/2.0)), y, (int)(x+(width/2.0)), y+height);
		g2.drawLine(x, (int)(y+(height/2.0)), x+width, (int)(y+height/2.0));
		g2.drawString(String.valueOf(yMax), x - 30, y+7);
		g2.drawString(String.valueOf((int)(yMax/2.0)), x - 25, (int)(y+height/2.0)+5);
		g2.drawString(String.valueOf(yMin), x - 20, y+height+5);
		g2.drawString(xMax + " seconds", x, y+height+12);
		g2.drawString(String.valueOf((int)(xMax/2.0)), (int)(x+width/2.0)-10, y+height+12);
		g2.drawString(String.valueOf(xMin), x+width-10, y+height+12);
		g2.drawRect(x, y, width, height);
		
	
	}


}
