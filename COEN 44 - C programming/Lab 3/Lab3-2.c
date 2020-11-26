/*
* Problem: Convert change to personalized credit slips. User manually enters the number of each kind of coin in collection

Analysis:
•	Customer initials: first, middle, last
•	Coins: dollars, quarters, dimes, nickels, pennies
•	Total values in cents
*/

#include <stdio.h>
#include <math.h>

int main(void){

char first, middle, last;  
int dollars; 		 
int quarters;      	
int dimes; 		       
int nickels; 		  
int pennies; 		  
int Tdollars;  
int change;        

int Tchange; 

printf("Plese input the following information \n");

printf("Dollars \n");
scanf("%d%", &dollars);
printf("Quarters \n");
scanf("%d", &quarters );
printf("Dimes \n");
scanf("%d", &dimes);
printf("Nickels \n");
scanf("%d", &nickels);
printf("Pennies \n");
scanf("%d", &pennies);

change= quarters*25 + dimes*10 + nickels*5 + pennies; 
Tdollars= dollars + change/100;
Tchange= Tdollars-dollars-(float)change/100;


printf("%d dollars and %d cents \n", Tdollars, Tchange*-100+.000001);
return(0);
}

