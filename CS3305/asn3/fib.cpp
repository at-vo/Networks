#include <iostream>
#include <iomanip>

double * fibonacci(int n, double * fib){
	if (n==1)                  			// base case = 1 
        {
			double *arr = new double[2];
			arr[1] = 1;					// set index 1 to 1
			return arr;
		}
    else if(n==0)                		// base case = 0
        {
			double *arr = new double[2];// create new array [0,0]
			return arr;
		}
    fib = fibonacci(n-1,fib);    		// decrease n and call again
    double nextFib = fib[0]+fib[1];     // add fibonacci 
    fib[0]=fib[1];               		// assign last fibonacci
    fib[1] = nextFib;            		// assign next fibonacci
    return fib;
}

int main(){
	for (int i = 0; i <= 30; i++)
	{
		double *arr = new double[2];
		arr = fibonacci(i*10,arr);
		std::cout << "Part A"<<std::endl;
		std::cout << "fibonachi at "<< i*10<<" is "<< std::setprecision(100) << arr[1] << std::endl;
		free(arr);
	}
}