#include <iostream>


double Fib(int num){
	double sum = 0;
	if (num == 0 ){
		return 0;
	}
	else if (num==1){
		return 1;
	}
	sum+=Fib(num-1)+Fib(num-2);
	return sum;
}

int main(){
	for (int i = 0; i <= 10; i++)
	{
		std::cout << "fibonachi of "<< i*5<<" is "<< Fib(i*5) << std::endl;
	}
	
	
}