#include <stdio.h>

int main(void){

int prev, curr, demand=35, Late=2;
double unpaid, bill, use, PER=1.10;

printf("Input previous water meter reading in thousands gallons \n");
scanf("%d", &prev);

printf("Input curr water meter reading in thousands of gallons \n");
scanf("%d", &curr);

printf("Input any unpaid balance from previous quarter \n");
scanf("%lf", &unpaid);
	if (unpaid>0){ 
		bill= demand + PER*(curr + prev) + unpaid + Late;
		printf("Your bill is %lf \n", bill);
	}
	else{
		 bill= demand + PER*(curr + prev);
                printf("Your bill is %lf \n", bill);
}
return(0);
}
