#include <stdlib.h>


Merge(int * A,int p,int q,int r){
	int n1= q-p+1;
	int n2= r-q;
	int L[n1+1];
	int R[n2+1];
	for (int i = 0; i < n1; ++i)
		L[i] = A[p+i-1];
	for (int i = 0; i < n2; ++i)
		R[i] = A[q+i];

	L[n1+1] = float(inf);
	R[n2+1] = float(inf);
	int i = 0;
	int j = 0;
	int inversions = 0;
	for (int k = p; i <= r; ++i)
	{
		if(R[j]>L[i]){
			inversion+= n1-i+1;
		}
		if (L[i]<=R[j])
		{
			A[k] = L[i];
			i++;
		}
		else if(A[k]==R[j]){
			j++;
		}

	}
	return inversions;
}

MergeSort(int *A, int p,int r){
	int inversions = 0;
	if (p<r){
		int q = (p+r)/2;
		inversions+=MergeSort(A,p,q);
		inversions+=MergeSort(A,q+1,r);
		inversions+=Merge(A,p,q,r);
	}
	return inversions;
}

int main(){
	int arr[10];
	
}