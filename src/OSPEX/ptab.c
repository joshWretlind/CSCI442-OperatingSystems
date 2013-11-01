#include "com.h"
#include "glo.h"
#include <X11/Xlib.h>
#include "student.h"
#include "procs.h"

int nr_queues,nr_buttons;
int verPos[NR_SCHED_QUEUES];
GC gc_red,gc_green,gc_yellow;

/*Function Declerations */
void drawPtab(int pTabPos,
	      Display *dispPtr,
	      Window window,
	      XRectangle rectPts[nr_queues+nr_buttons],
	      GC gc,
	      int rWidth,
	      int rHeight);

void drawScreen (Display *dispPtr,
		 Window window,
		 XRectangle rectPts[nr_queues+nr_buttons],
		 GC gc,
		 int rMid,
		 char *queueArray[nr_queues],
		 int sizeArray[nr_queues],
		 int startButState);

void printQGui (struct pi *procPtr,
	     int endpoint,
	     XRectangle rectPts,
	     Display *dispPtr,
	     Window window,
	     GC gc_red,
	     int *verPos);
	     
void drawExtras(struct pi *procPtr,
		struct pi *prevProcPtr,
		XRectangle startButton,
		int rHeight,
		int rYStart,
		Display *dispPtr,
		Window window,
		GC gc);

/*Set text constants for button*/
char* stButText;
char* rgButText;
char* scButText;
char* etButText;
char* ntButText;
char* psButText;

int stSize;
int rgSize;
int scSize;
int etSize;
int ntSize;
int psSize;

int displayTab;
char *displayTab_text;
int displayTab_size;
int displayTab_x;
int displayTab_y;
int window_height;

	
int main (void){
int startButState = 0;
message m;
int i = 0,a;
int nr_procs;
nr_queues = 16; /* This needs to be changed to to a variable amount based on priorities */
nr_buttons = 4;
int ptabReady = 0;
int ptabReceived = 0;

char *runningProcName;

/* X11 Declerations */
Display *dispPtr;
Screen *screenPtr;
Window window;
char *display_str = (char*) getenv("DISPLAY");
GC gc;
XGCValues gcv,gcv_red,gcv_green,gcv_yellow;
XColor red_col, green_col, yellow_col;
int x,y,screenNum;
unsigned int display_width, display_height,window_width;
Colormap colormap;

/* Setup the X11 GUI display */
dispPtr = XOpenDisplay(display_str);
screenPtr = DefaultScreenOfDisplay(dispPtr);
screenNum = DefaultScreen(dispPtr);
display_width = DisplayWidth(dispPtr, screenNum);
display_height = DisplayHeight(dispPtr, screenNum);
window_width = 0.75*display_width;
window_height = 0.75*display_height;
colormap = DefaultColormap(dispPtr,0);

displayTab = 0;
displayTab_text = malloc(sizeof(char) * 50);
displayTab_size = sprintf(displayTab_text,"You are looking at snapshot: %d",displayTab);
displayTab_x = 30;
displayTab_y = floor((1.0/16.0)*window_width);

/*Set text constants for button*/
char* stButText = "Start Simulation";
char* rgButText = "Running...";
char* scButText = "Sim Complete";
char* etButText = "Exit";
char* ntButText = "Next >>>";
char* psButText = "<<< Previous";

int stSize = sprintf(NULL,"%s",stButText);
int rgSize = sprintf(NULL,"%s",rgButText);
int scSize = sprintf(NULL,"%s",scButText);
int etSize = sprintf(NULL,"%s",etButText);
int ntSize = sprintf(NULL,"%s",ntButText);
int psSize = sprintf(NULL,"%s",psButText);

/* Create the points for the priority queue rectanges */
XRectangle rectPts[nr_queues+nr_buttons]; /* One set of rectangle points for each priority queue */
double sbr = ((1.0/3.0)*window_width)/(nr_queues+1); /* Space between rectangles */
int y_start = floor((1.0/8.0)*window_height);
unsigned int rHeight = floor((5.0/8.0)*window_height);
unsigned int rWidth = floor(((2.0/3.0)*window_width)/nr_queues);
	for(i=0;i<nr_queues;i++){
		rectPts[i].x = ((i+1)*sbr) + (i*rWidth);
		rectPts[i].y = y_start;
		rectPts[i].height = rHeight;
		rectPts[i].width = rWidth;
	}
/* Set the position and text constants for the buttons. */
	for(i=0;i<nr_buttons;i++){
		int pos = nr_queues+i;
		rectPts[pos].y = floor((7.0/8.0)*window_height);
		rectPts[pos].width = floor((1.0/8.0)*window_width);
		rectPts[pos].height = floor((1.0/16.0)*window_height);
	}
/* Exit button */
rectPts[nr_queues+0].x = 20.0;
/*Start Simulation Button*/
rectPts[nr_queues + 1].x = floor(((1.0/8.0)*window_width)+30);
/*Next Button*/
rectPts[nr_queues + 2].x = floor((5.0/8.0)*window_width);
/*Previous Button */
rectPts[nr_queues+3].x = floor(((6.0/8.0)*window_width)+20);



/* Create labels for each priority queue */
double rMid = rWidth/2.0;
char *queueArray[nr_queues];
/* I think there is something wrong with snprintf, so I'm going to allocate space for the strings*/ 
	for(i=0;i<nr_queues;i++){
		queueArray[i] = malloc(sizeof(char) * 4); /*Should not have over 999 queues (I know it's a hack)*/
	}

int sizeArray[nr_queues], widthArray[nr_queues];
XFontStruct *font_info;
window = XCreateSimpleWindow(dispPtr, RootWindowOfScreen(screenPtr),
		0,0,window_width,window_height,1,BlackPixel(dispPtr, DefaultScreen(dispPtr)),
		WhitePixel(dispPtr,DefaultScreen(dispPtr)));

gcv.foreground = BlackPixel(dispPtr,screenNum);
gcv.background = WhitePixel(dispPtr,screenNum);
gc = XCreateGC(dispPtr, window, GCForeground, &gcv);
/* Create Graphics contexts for red,yellow,green text colors */
char green[] = "#008A2E";
char red[] = "#B20000";
char yellow[] = "#FF9900";
gc_green = XCreateGC(dispPtr,window,0,0);
gc_red = XCreateGC(dispPtr,window,0,0);
gc_yellow = XCreateGC(dispPtr,window,0,0);
XParseColor(dispPtr,colormap,green,&green_col);
XParseColor(dispPtr,colormap,red,&red_col);
XParseColor(dispPtr,colormap,yellow,&yellow_col);
XAllocColor(dispPtr,colormap,&green_col);
XAllocColor(dispPtr,colormap,&red_col);
XAllocColor(dispPtr,colormap,&yellow_col);
XSetForeground(dispPtr,gc_green,green_col.pixel);
XSetForeground(dispPtr,gc_red,red_col.pixel);
XSetForeground(dispPtr,gc_yellow,yellow_col.pixel);

XClearWindow(dispPtr, window);
XMapRaised(dispPtr,window);
XEvent report;

/* Draw the priority queues from the Graphics Context */
XSelectInput(dispPtr,window,ExposureMask|ButtonPressMask);
int exitCondition = 0;


while(!exitCondition){
	XNextEvent(dispPtr, &report);
	switch(report.type){
		case Expose:
			 drawScreen (dispPtr, window, rectPts, gc, rMid, queueArray, sizeArray,startButState);
			 if(startButState==2){
				printf("Start button state: %d\n",startButState);
				drawPtab(displayTab, dispPtr,window,rectPts, gc,rWidth,rHeight);
			}
		  	 break;
		case ButtonPress:
			/* Exit Button*/
			if(report.xbutton.x > rectPts[nr_queues].x &&
			   report.xbutton.x < rectPts[nr_queues].x + rectPts[nr_queues].width &&
			   report.xbutton.y > rectPts[nr_queues].y &&
			   report.xbutton.y < rectPts[nr_queues].y + rectPts[nr_queues].height){
			   	exitCondition = 1;
				break;
			}
			/* Start Button */
			if(report.xbutton.x > rectPts[nr_queues+1].x &&
			   report.xbutton.x < rectPts[nr_queues+1].x + rectPts[nr_queues+1].width &&
			   report.xbutton.y > rectPts[nr_queues+1].y &&
			   report.xbutton.y < rectPts[nr_queues+1].y + rectPts[nr_queues+1].height){
				if(startButState == 0){
					startButState = 1;
					drawScreen (dispPtr, window, rectPts, gc, rMid, queueArray, sizeArray,startButState);
					studentInput();
						if(!(strcmp(pInfoPtrs[0]->p_name,"NOPTABCOPY"))){ /* Student has not implemented simulation */
							startButState = 3;
						}
						else{
							startButState = 2;
						}
					displayTab = 0;
					drawScreen (dispPtr, window, rectPts, gc, rMid, queueArray, sizeArray,startButState);
					if(startButState != 3){
						drawPtab(displayTab, dispPtr,window,rectPts, gc,rWidth,rHeight);
					}
				}
			   }
			   /* Next Button */
			if(report.xbutton.x > rectPts[nr_queues+3].x &&
			   report.xbutton.x < rectPts[nr_queues+3].x + rectPts[nr_queues+3].width &&
			   report.xbutton.y > rectPts[nr_queues+3].y &&
			   report.xbutton.y < rectPts[nr_queues+3].y + rectPts[nr_queues+3].height){
			   	if(displayTab<(HISTORY-1)){
					displayTab++;
					/* Update the snapshot count on screen */
					displayTab_size = sprintf(displayTab_text,"You are looking at snapshot: %d",displayTab);
					drawScreen (dispPtr, window, rectPts, gc, rMid, queueArray, sizeArray,startButState);
					drawPtab(displayTab, dispPtr,window,rectPts, gc,rWidth,rHeight);
					XFlush(dispPtr);
				}

			   }
			   /* Prev Button */
			if(report.xbutton.x > rectPts[nr_queues+2].x &&
			   report.xbutton.x < rectPts[nr_queues+2].x + rectPts[nr_queues+2].width &&
			   report.xbutton.y > rectPts[nr_queues+2].y &&
			   report.xbutton.y < rectPts[nr_queues+2].y + rectPts[nr_queues+2].height){
				   if(displayTab>0){
						displayTab--;
						/* Update the snapshot count on screen */
						displayTab_size = sprintf(displayTab_text,"You are looking at snapshot: %d",displayTab);
						drawScreen (dispPtr, window, rectPts, gc, rMid, queueArray, sizeArray,startButState);
						drawPtab(displayTab, dispPtr,window,rectPts, gc,rWidth,rHeight);

					}

			   }


	}
XFlush(dispPtr);
}

	/*Reset the vertical position of the test after each iteration*/
return(0);
}

void drawPtab(int pTabPos,
	      Display *dispPtr,
	      Window window,
	      XRectangle rectPts[nr_queues+nr_buttons],
	      GC gc,
	      int rWidth,
	      int rHeight){
int a, b, nr_fake_procs = 2, j,i,k;
int q,size;
char *procNames[nr_fake_procs];
/* Modify a copy of the pointer instead of the original */
struct pi *pInfoPtrCpyPrev;
struct pi *pInfoPtrCpy = pInfoPtrs[pTabPos]; 
struct qh *pQhPtrCopy;

if(pTabPos > 0){
	pInfoPtrCpyPrev = pInfoPtrs[pTabPos -1];
}

for(a=0;a<NR_SCHED_QUEUES;a++){ 
		verPos[a] = 40;
		}

	for(a=0;a<nr_fake_procs;a++){
		procNames[a] = malloc(sizeof(char)*PROC_NAME_LEN);
		sprintf(procNames[a],"proc%d",a+1);
		}
		
	/* This code draws the CPU process that ran previously */
	if(pTabPos > 0){
		drawExtras(pInfoPtrs[pTabPos],pInfoPtrs[pTabPos-1],rectPts[nr_queues+1],rHeight,rectPts[0].y,dispPtr,window,gc);
	}

	/* This for loop only draws the runnable processes and draws them in the correct order. */
	pQhPtrCopy = pQhPtrs[pTabPos];
	for(i=0; i<NR_SCHED_QUEUES; i++){
		if(pQhPtrCopy->p_endpoint != -1){
			printQGui (pInfoPtrCpy, pQhPtrCopy->p_endpoint, rectPts[i], dispPtr,window,gc_green,(int *) &verPos[i]);
		}
		XDrawLine(dispPtr,window,gc_red,rectPts[i].x,rectPts[i].y+verPos[i]-18,rectPts[i].x+rWidth,rectPts[i].y+verPos[i]-18);
		pQhPtrCopy++;
	}


for(a=0; a<ALL_PROCS; a++){	
	q = pInfoPtrCpy->p_priority;
	if(pInfoPtrCpy->p_rts_flags != 0 && verPos[q]<rHeight){ 
		if(pInfoPtrCpy->p_rts_flags != RTS_SLOT_FREE){
			size = sprintf(NULL,"%s",pInfoPtrCpy->p_name);
			/*Color code the processes by their status: runnable,io blocked,preempted */
			if(pInfoPtrCpy->p_rts_flags == 0){  /*Process is runnable */
				XDrawString(dispPtr,window,gc_green,(rectPts[q].x)+2,
					(rectPts[q].y)+verPos[q],pInfoPtrCpy->p_name,
					size);
			}
			else if (pInfoPtrCpy->p_rts_flags == RTS_SENDING ||
				 pInfoPtrCpy->p_rts_flags == RTS_RECEIVING){ /*Process is io blocked */
				 XDrawString(dispPtr,window,gc_red,(rectPts[q].x)+2,
					(rectPts[q].y)+verPos[q],pInfoPtrCpy->p_name,
					size);
			}
			if(pTabPos > 0){
				for(k=0;k<ALL_PROCS;k++){
					if (pInfoPtrCpyPrev->p_endpoint==pInfoPtrCpy->p_endpoint){ /*Process was preempted*/ 
						 if(pInfoPtrCpyPrev->p_priority != q){
							 XDrawString(dispPtr,window,gc_yellow,(rectPts[q].x)+2,
								(rectPts[q].y)+verPos[q],pInfoPtrCpy->p_name,
								size);
						}
					}
				pInfoPtrCpyPrev++;
				}
			pInfoPtrCpyPrev = pInfoPtrs[pTabPos -1];
			}
			verPos[q] = verPos[q] + 20;
		}
	}
		pInfoPtrCpy++;
}

}

void drawScreen (Display *dispPtr,
		 Window window,
		 XRectangle rectPts[nr_queues+nr_buttons],
		 GC gc,
		 int rMid,
		 char *queueArray[nr_queues],
		 int sizeArray[nr_queues],
		 int startButState){

	int i;
	/*Set text constants for button*/
	char* stButText = "Start Simulation";
	char* rgButText = "Running...";
	char* scButText = "Sim Complete";
	char* etButText = "Exit";
	char* ntButText = "Next >>>";
	char* psButText = "<<< Previous";
	char* erButText = "Not Implemented";

	int stSize = sprintf(NULL,"%s",stButText);
	int rgSize = sprintf(NULL,"%s",rgButText);
	int scSize = sprintf(NULL,"%s",scButText);
	int etSize = sprintf(NULL,"%s",etButText);
	int ntSize = sprintf(NULL,"%s",ntButText);
	int psSize = sprintf(NULL,"%s",psButText);
	int erSize = sprintf(NULL,"%s",erButText);

	XClearWindow(dispPtr,window);

	XDrawRectangles (dispPtr, window, gc, rectPts, nr_queues+nr_buttons);
		for(i=0; i<nr_queues; i++){
			sizeArray[i] = sprintf(queueArray[i],"%d",i);
		XDrawString(dispPtr,window,gc,rectPts[i]. x+ rMid, rectPts[i].y + 20.0,
				queueArray[i],sizeArray[i]); 
		}
	/*Draw labels for the buttons */
	XDrawString(dispPtr,window,gc,rectPts[nr_queues+0].x+10,rectPts[nr_queues+0].y+20,etButText,etSize);
	XDrawString(dispPtr,window,gc,rectPts[nr_queues+2].x+10,rectPts[nr_queues+2].y+20,psButText,psSize);
	XDrawString(dispPtr,window,gc,rectPts[nr_queues+3].x+10,rectPts[nr_queues+3].y+20,ntButText,ntSize);
	XDrawString(dispPtr,window,gc,displayTab_x,displayTab_y,displayTab_text,displayTab_size);

	switch(startButState){
		case 0: /*Start Simulation */
			XDrawString(dispPtr,window,gc,rectPts[nr_queues+1].x+10,rectPts[nr_queues+1].y+20,stButText,stSize);
			break;
		case 1: /*Running*/
			XDrawString(dispPtr,window,gc,rectPts[nr_queues+1].x+10,rectPts[nr_queues+1].y+20,rgButText,rgSize);
			break;
		case 2: /*Simulation Complete*/
			XDrawString(dispPtr,window,gc,rectPts[nr_queues+1].x+10,rectPts[nr_queues+1].y+20,scButText,scSize);
			break;
		case 3:
			XDrawString(dispPtr,window,gc,rectPts[nr_queues+1].x+10,rectPts[nr_queues+1].y+20,erButText,erSize);
			break;


	}
	XFlush(dispPtr);
}

void printQGui (struct pi *procPtr,
	     int endpoint,
	     XRectangle rectPts,
	     Display *dispPtr,
	     Window window,
	     GC gc_red,
	     int *verPos){

/*This is probably unnecessary, but I'm creating a copy of the pointer to the head of the list */
struct pi *start = procPtr;
struct pi *cpy = procPtr;
int size;

/*Find the process that was the nextready process in the proc table*/
	while(cpy->p_endpoint != endpoint){
		cpy++;
	}

/* Print the process to the file, then see if there is another process in the nextready spot. If yes, recursively call this routine. If no, write a line feed for the next queue */
size = sprintf(NULL,"%s",cpy->p_name);
XDrawString(dispPtr,window,gc_red,(rectPts.x)+2,
		(rectPts.y)+*verPos,cpy->p_name,
		size);
		*verPos = *verPos + 20;
	if(cpy->p_nextready_endpoint != -1){
		printQGui(start,cpy->p_nextready_endpoint,rectPts,dispPtr,window,gc_red,verPos);
	}
	
}

void drawExtras(struct pi *procPtr,
		struct pi *prevProcPtr,
		XRectangle startButton,
		int rHeight,
		int rYStart,
		Display *dispPtr,
		Window window,
		GC gc){

struct pi *cpy = procPtr;
struct pi *prevCpy = prevProcPtr;
struct pi *prevStart = prevProcPtr;
u64_t cpuTimeDiff;
int i,j,k, size;
int verPos = rYStart + rHeight + 20;
char *drawString = malloc(sizeof(char) * 100);
double cpuTime;
char procNames[PROCNUM][PROC_NAME_LEN];

	for(i=0;i<PROCNUM;i++){ /*Create proc names array*/
		sprintf(&procNames[i][0],"proc%d",i+1);
		}

	for(j = 0; j<ALL_PROCS; j++){
		for(i = 0; i<ALL_PROCS; i++){
			if(cpy -> p_endpoint == prevCpy -> p_endpoint){ /*Make sure the process existed in the last proc table snapshot */
				if(verPos < window_height){
					for(k=0;k<PROCNUM;k++){
						if(strcmp(cpy->p_name,procNames[k])==0){
							cpuTimeDiff = diff64(prevCpy->p_cycles,cpy->p_cycles); 	
							cpuTimeDiff = mul64(cpuTimeDiff,1000);
							if(!(cmp64(cpuTimeDiff,0) == 0)){
								size = sprintf(drawString,"Process %s ran for %lu milliseconds",
										cpy->p_name,div64(cpuTimeDiff,cpuFreq));
										XDrawString(dispPtr,window,gc,startButton.x + startButton.width + 10,verPos,drawString,size);
										verPos = verPos + 20;
							}
						}
					}
				}
			}
			prevCpy++;
		}
		prevCpy = prevStart;
		cpy++;
	}
		
}

void testFunction (void){
	printf("Testing if I can build an API to my GUI\n");
	}
