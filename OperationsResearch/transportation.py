import numpy as np

def reduce(Z,supply,demand,soln):
	soln = soln[:]
	supplySum = np.sum(supply)
	demandSum = np.sum(demand)
	i,j = np.unravel_index(Z.argmin(), Z.shape)
	Z[i][j] = 1000
	soln[i][j] = min(supply[i],demand[j])
	if(supply[i]>demand[j]):
		demandSum -= demand[j]
		supply[i] -= demand[j]
		demand[j] = 0
		Z[:,j] = 1000
	if(supply[i]<demand[j]):
		supplySum -= supply[i]
		demand[j] -= supply[i]
		supply[i] = 0
		Z[i] = 1000
	if(supply[i]==demand[j]):
		supplySum -= supply[i]
		demandSum -= demand[j]
		supply[i] -= demand[j]
		demand[j] -= supply[i]
		supply[i] = 0
		demand[j] = 0
		Z[i] = 1000
		Z[:,j] = 1000
	return Z,supply,demand,soln

def findIncoming(soln,Z,nNew,mNew):
	r = np.zeros(nNew)
	k = np.zeros(mNew)
	rassign = np.zeros(nNew)
	kassign = np.zeros(mNew)
	tillzero = np.zeros((nNew,mNew))
	tillzero[:,:] = soln[:,:]
	i,j = np.unravel_index(tillzero.argmax(), tillzero.shape)
	flag = 0
	while np.sum(tillzero) != 0:
		# print "i:%d , j:%d" %(i,j)
		print "Loop soln"
		print soln
		tillzero[i,j] = 0
		rassign[i] = 1
		kassign[j] = 1
		if flag == 0:
			k[j] = Z[i][j]-r[i]
		else:
			r[i] = Z[i][j]-k[j]
		# print tillzero
		for m in range(nNew):
			for n in range(mNew):
				if (rassign[m]==1 and kassign[n]==0) and soln[m,n]>0:
					i = m
					j = n
					flag = 0
				if (rassign[m]==0 and kassign[n]==1) and soln[m,n]>0:
					i = m
					j = n
					flag = 1
	incoming = np.zeros((nNew,mNew))
	for m in range(nNew):
		for n in range(mNew):
			incoming[m,n] = r[m] + k[n] - Z[m,n]
	i,j = np.unravel_index(incoming.argmin(), incoming.shape)
	return i,j,incoming[i,j]

def printSolution(sol,nNew,mNew):
    for i in range(nNew):
        for j in range(mNew):
            print " %d " %(sol[i][j]);

def isSafe(maze, x, y,nNew,mNew):
    if(x >= 0 and x < nNew and y >= 0 and y < mNew and maze[x][y] == 1):
        return 1
    return 0

def solveMaze(maze,nNew,mNew):
    sol = np.zeros((nNew,mNew))
    if(solveMazeUtil(maze, 0, 0, sol,nNew,mNew) == 0):
        print "Solution doesn't exist";
        return 0
    printSolution(sol,nNew,mNew);
    return 1
 
def solveMazeUtil(maze, x, y, sol,nNew,mNew):
    if(x == nNew-1 and y == mNew-1):
        sol[x][y] = 1
        return 1;
 
    if(isSafe(maze, x, y,nNew,mNew) == 1):
        sol[x][y] = 1;
        if (solveMazeUtil(maze, x+1, y, sol) == 1):
            return 1;
        if (solveMazeUtil(maze, x, y+1, sol) == 1):
            return 1;
        sol[x][y] = 0;
        return 0;
    return 0;

def evaluateIncoming(soln,r,k,nNew,mNew):
	t = np.zeros((nNew,mNew))
	for i in range(nNew):
		for j in range(mNew):
			if(soln[i,j] > 0):
				t[i,j] = 1
	solveMaze(t,nNew,mNew)


def transportation(Y):
	Y = np.array(Y,dtype=float)
	n = len(Y)-1
	m = len(Y[0])-1
	nNew = n
	mNew = m
	supply = Y[:,n]
	demand = Y[m,:]
	supplySum = np.sum(supply)
	demandSum = np.sum(demand)
	print "Total Supply:%d Total Demand:%d" %(supplySum,demandSum)
	if supplySum>demandSum:
		mNew += 1;
		demand[n]=supplySum-demandSum
	if demandSum>supplySum:
		nNew += 1
		supply[m]=demandSum-supplySum
	Z = np.zeros((nNew,mNew))
	costcalc = np.zeros((nNew,mNew))
	soln = np.zeros((nNew,mNew))
	Z[0:n,0:m] = Y[0:n,0:m]
	soln = np.zeros((nNew,mNew))
	solnfinal = np.zeros((nNew,mNew))
	costcalc[0:n,0:m] = Y[0:n,0:m]
	while supplySum>0 and demandSum>0:
		Z,supply,demand,soln = reduce(Z,supply,demand,soln)
		supplySum = np.sum(supply)
		demandSum = np.sum(demand)
	print "Initial solution:"
	print soln
	solnfinal = soln[:]
	print solnfinal
	Z = costcalc[:]
	r,k,val = findIncoming(soln,Z,nNew,mNew) 
	print r,k,val
	print solnfinal
	evaluateIncoming(soln,r,k,nNew,mNew)

Y = [[10,3,2,50],[6,8,5,60],[7,10,4,80],[40,80,70,0]]
transportation(Y)