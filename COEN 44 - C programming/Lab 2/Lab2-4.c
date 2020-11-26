/*
* Mileage reimbursement program
* produces amount due based on amount of gas consumed which then charges 1 dollar per kg of CO2 produced
*/

#include <stdio.h>
int main (void){
double odometerBeg;
double odometerEnd;
double distance;
float reimburse;
printf ("Initial odometer reading =  \n");
scanf ("%lf", &odometerBeg);
printf ("The initial reading is %lf miles. \n", odometerBeg);
printf ("Final odometer reading = \n");
scanf ("%lf", &odometerEnd);
printf ("The final reading is %lf miles. \n", odometerEnd);
distance = odometerEnd - odometerBeg;
reimburse = (float)distance * .35;
printf ("You owe %f dollars. \n", reimburse);
return (0);
}  
