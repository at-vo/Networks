#include <iostream>


Fib(int num){
	int sum = 0;
	if (num == 0 ){
		return 0;
	}
	else if (num==1){
		return 1;
	}
	sum+=Fib(num-1)+Fib(n-2);
	return sum;
}

int main(){
	int fi = Fib(3);
	std::cout << fi << endl;
}