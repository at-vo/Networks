#include <iostream>
#include <iomanip>

double Fib(int num){
	double sum = 0;
	if (num == 0 ){						// base case = 0
		return 0;
	}
	else if (num==1){					// base case = 1
		return 1;
	}
	sum+=Fib(num-1)+Fib(num-2);			// add fibonacci
	return sum;							// return frame
}


int main(){
	for (int i = 0; i < 11; i++)
	{
		std::cout << "fibonacci at " << i*5 << " is " << std::setprecision(100) << Fib(i*5) << std::endl; 
	}
}