/*Sebastian De La Cruz
9/30/2019
Lab2 - Part 3: Carbon dioxide fee calculation 
* This is the CO2 fee calculation. This will calculate the amount of money due based on your miles per gallon and d$
* This will take your vehicle's odometer readings, converting it to distance and then finally converting it to gall$
*/

#include <stdio.h>
int main (void) {

double distance, gallon;
int mpg;
float carbon, fine, carbonA, fineA;

printf("Welcome to the CO2 fee calculation. Please input values when prompted \n");
printf ("Miles per gallon of vehicle = \n");
scanf ("%d", &mpg);
printf ("Average number of miles driven annually in the vehicle = \n");
scanf ("%lf", &distance);

gallon = distance/mpg;
carbon = 6453*gallon/1000;
carbonA = carbon * 24487807;
fine = carbon * .25;
fineA = carbonA * .25;

printf ("You have used %lf gallons. \n", gallon);
printf ("You have produced %f kilograms of carbon. \n", carbon);
printf ("You will be fined %f dollars. \n", fine);
printf ("If all Californian drivers had the same values: \n");
printf ("California drivers produced %f kilograms of Carbon Dioxide \n", carbonA);
printf ("California drivers pay %f in Carbon Dioxide emission fees \n", fineA);
return (0);
}

