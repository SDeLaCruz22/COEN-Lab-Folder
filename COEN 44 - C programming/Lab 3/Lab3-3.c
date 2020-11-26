/*
 * This function computes the area of a circle with radius r.
 * r is defined and is > 0.
 * PI is a constant macro representing an approximation of pi.
 */
#include <stdio.h>
#include <math.h>

int main(void){

double r, area, circ, Pi=3.14159265359;

printf("Input the radius of the circule \n");
scanf("%lf", &r);

area= Pi*pow(r,2);
circ= 2*Pi*r;

printf("Area = %lf, Circumfrence = %lf \n", area, circ);
return(0);
}
