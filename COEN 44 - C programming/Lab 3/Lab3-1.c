#include <stdio.h>
#include <math.h>

int main (void) {

int i=1, j=2, k=2, m=2, x=12, y=25;

printf("k!=3 is %d \n", k!=3);
printf("i==1 is %d \n", i==1);
printf("j==3 is %d \n", j==3);
printf("i>= && j<4 is %d \n", i>=1&&j<4);
printf("5: %d \n", m<=99&&k<m);
printf("6: %d \n", j>=i||k==m);
printf("7: %d \n", k+m<j||3-j>=k);
printf("8: %d \n", !m );
printf("9: %d \n",!(j-m));
printf("10: %d \n", !(k>m));
printf("11: %d \n", !(j>k));
printf("12: %d \n", x&y);
printf("13: %d \n", x|y);
printf("14: %d \n", x>>j);
printf("15: %d \n", y<<k);
printf("16: %d \n", x^y);
printf("17: %d \n", x|y);
printf("18: %d \n", ~x);
printf("19: %d \n", i-x*-y-k/m+(float)y*j);
printf("20: %d \n", 5*(1 + ++y)+y/2);
printf("21: %d \n", (x==y)&&!(m>y));
printf("22: %d \n", (x==y)||!(m>y));

return(0);
}
