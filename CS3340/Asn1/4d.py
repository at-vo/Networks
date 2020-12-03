def Merge(A,p,q,r):
    # general merge algorithm definitions
	n1= q-p+1
	n2= r-q
	L = []
	R = []
	for i in range(n1+1):      
		L.append( A[p+i-1])
	for i in range(n1+1):
		R[i] = A[q+i]
	L[n1+1] = float('inf')
	L[n2+1] = float('inf')
	i = 0
	j = 0
    check = false                           # add check for inversion count
	inversions = 0                          # add counter for inversions
	for (k=p) in range(r+1):    
		if( check==false and R[j]>L[i]):
			inversion+= n1-i+1              # add the number of inversions
            check = true                    # change to true once inversion is counted
		if (L[i]<=R[j]):
			A[k] = L[i]
			i+=1
		elif(A[k]==R[j])
			j+=1
            check = false                   # change to false on further iteration
	return inversions

def MergeSort(A,p,r):
	inversions = 0                          # add inversion counter
	if (p<r)
		int q = (p+r)/2             
        # change calls to add to inversion counter
		inversions+=MergeSort(A,p,q)
		inversions+=MergeSort(A,q+1,r)
		inversions+=Merge(A,p,q,r)
	return inversions




    