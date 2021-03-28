# Line-Fitting-Algo

#Make run.sh an executable.
#./run.sh will 
#1) Take input points from input.txt (least_sq_new.cpp)
#2) Sort the points w.r.t. increasing x, if x coordinates of two points are the same, then sort with increasing y (least_sq_new.cpp)
#2) Compute the segments of best fit (least_sq_new.cpp)
#3) Store the information of segments in output.txt (least_sq_new.cpp)
#4) Plot the points and segments (plotter.py)

#Input Format
#N C
#x1 y1
#x2 y2
#..
#xn yn

#Where N is the number of points, C is the cost of one segment and the coordinates of the ith point are [xi,yi]

#Output Format
#0 0 0 0 0
#j i cost a b 
#..(one line for each segment)

#For each segment, i is the left-most point included in fitting, j is the right-most point included in fitting. Total cost incurred by a segment is given by cost. Slope of line is a, intercept is b.


