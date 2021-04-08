import numpy as np
import matplotlib.pyplot as plt

fin = np.loadtxt("sorted_input.txt")
fout = np.loadtxt("output.txt")
cinp = np.loadtxt("input.txt")

plt.scatter(fin[:,0],fin[:,1])

bounds = [[min(fin[:,0]),min(fin[:,1])],[max(fin[:,0]),max(fin[:,1])]]

for i in fout:
	if(i[0]==0):
		continue
	if(np.isnan(i[3])):
		ly = np.linspace(fin[int(i[1]-1)][1],fin[int(i[0]-1)][1],3)
		lx = [fin[int(i[1]-1)][0] for k in range(len(ly))]
	else:
		lx = np.linspace(fin[int(i[1]-1)][0],fin[int(i[0]-1)][0],3)
		ly = i[3]*lx+i[4]
	plt.plot(lx,ly, color="lime")

#for i in range(len(fout)-1):
#	if(i==0):
#		continue
#	plt.plot([fin[int(fout[i][1])-1][0],fin[int(fout[i+1][0])-1][0]],[fin[int(fout[i][1])-1][1],fin[int(fout[i+1][0])-1][1]],color="red",linestyle="--")

plt.title('C = '+str(cinp[0][1])+'   Total cost = '+str(fout[1][2]), loc="center")

plt.savefig("currplot")
plt.show()
