import numpy as np
import matplotlib.pyplot as plt

fin = np.loadtxt("sorted_input.txt")
fout = np.loadtxt("output.txt")

plt.scatter(fin[:,0],fin[:,1])

bounds = [[min(fin[:,0]),min(fin[:,1])],[max(fin[:,0]),max(fin[:,1])]]

for i in fout:
	if(i[0]==0):
		continue
	if(np.isnan(i[3])):
		ly = np.linspace(bounds[0][1]-1,bounds[1][1]+1,3)
		lx = [fin[int(i[1]-1)][0] for k in range(len(ly))]
	else:
		lx = np.linspace(bounds[0][0]-1,bounds[1][0]+1,3)
		ly = i[3]*lx+i[4]
	plt.plot(lx,ly, color="red")

plt.savefig("currplot")
plt.show()
