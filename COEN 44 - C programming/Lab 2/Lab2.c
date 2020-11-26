#include <stdio.h>
int main (void){
int num = 10;
int value1 = 5*(1 + ++num) + num/2;
int value2 = (4 + ++num) + (6 + ++num);
printf ("Value1 = %d\nValue2 = %d\n", value1, value2);
return (0);
}

