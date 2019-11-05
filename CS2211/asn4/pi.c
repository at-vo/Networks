#include <stdio.h>

int get_n(double epsilon){

    double compare;
    int n = 1;
    do {
        n++;
        int denm = (2 * n) - 1;
        compare = 4.0/(double)denm;
    } while(!(compare < epsilon));
    return n;
}

double get_pi(int n){
    double pi = 0;
    int i;
    for (i=1; i<=n; i++){
        double result;
        int denm = (2 * i) - 1;
        result = 4.0/(double)denm;
        if ((i+1) % 2 != 0){result = -result;}
        pi+=result;
    }
    return pi;
}

int main(){

    double userInput;
    int n;
    printf("enter a number for epsilon (0< epsilon <1): ");
    scanf("%lf",&userInput);
    n = get_n(userInput);
    printf("n: %d\n",n);
    double pi = get_pi(n);
    printf("pi: %.10lf\n",pi);
    return 0;
}