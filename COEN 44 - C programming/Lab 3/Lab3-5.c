/* 
* Sebastian De La Cruz
* 10/07/2019
* Title: Lab3- step 5
* Description: Program finds the amount of taxes to pay based on the salary inputted.
*/ 


#include <stdio.h>

int main(void){

double salary, tax;

printf("Input salary \n");
scanf("%lf", &salary);

if ((salary>=0) && (salary<15000.00)){                       
 tax = 0.15 * salary;}
	else if ((salary>=15000.00) && (salary<30000.00)){                        
	 tax = (salary - 15000.00) * 0.18 + 2250.00;}
		else if ((salary>=30000.00) && (salary<80000.00)){                        
		 tax = (salary - 30000.00) * 0.22 + 5400.00;}
			else if ((salary>=80000.00) && (salary<150000.00)){                        
			 tax = (salary - 50000.00) * 0.27 + 11000.00;}
				else if (salary>=150000.00){                     
				 tax = (salary - 80000.00) * 0.33 + 21600.00;}
				     else{
					printf("invalid \n");
					return(0);}

printf("You have $%lf to pay in taxes \n", tax);
return(0);
}
