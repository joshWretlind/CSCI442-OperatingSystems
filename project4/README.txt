Josh Wretlind
Chris Sanford


1. Page cache maintains a history of what pages have been allocated.


2. The findbit function takes in a low address, a high address
(called startscan), and an allocation size (called pages). It
iterates through the bitmap between the high and low address,
working backwards and returns the starting location in the bitmap
of the first hole it finds that is large enough. Since the function
iterates from high to low, it will indicate the start of the hole
that is closest to startscan, or the end of the memory range.

3.
int max = 0, hole = 0, max_addr
for(i from mem_low to mem_high)
	if(page(i) is free) 
		hole = hole + 1
	else
		if(hole > max)
			max = hole
			max_addr = i
		endif
		hole = 0
	endif
endloop
if(max > pages)
	mem = max_addr
else
	mem = NO_MEM
endif

4. The hardest part of this project was proving our changes did what 
we wanted them to. This was challenging since minix would not allow us
to scroll within the terminal as well as alloc_pages being called so
frequently. We also had difficulties printing out the bitmap. At first we
had tried to loop over the free_page_bitmap array and print out all the 
values, however those were 32 bits, and it became very difficult to figure
out what exactly was happening.

5. It was interesting to be able to work within a OS and see how one might
go about proving their changes work or do what they say they will do.