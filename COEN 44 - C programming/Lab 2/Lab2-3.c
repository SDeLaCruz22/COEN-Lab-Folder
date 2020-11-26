/*
* Fahrenheit to Celsius Conversion Program
* Converts degrees in fahrenheit to celsius through fahrenheit input and math conversion
*/

#include <stdio.h>
int main (void){
double fahrenheit;
float celsius;
printf ("Enter the degrees in Fahrenheit = \n");
scanf ("%lf", &fahrenheit);
printf ("That is %f degrees in Fahrenheit. \n", fahrenheit);
celsius = ((float)fahrenheit - 32)*5/9;
printf ("That is equal to %f degrees in Celsius. \n", celsius);
return (0);
}
