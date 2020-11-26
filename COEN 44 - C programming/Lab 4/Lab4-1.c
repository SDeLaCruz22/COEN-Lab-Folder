#include <stdio.h>

double maxval (v1, v2, v3) {
	if ((v1>v2) && (v1>v3))
		return (v1);
	else if ((v2>v1) && (v2>v3)) 
		return v2;
	else if ((v3>v1) && (v3>v2))
		return v3;
	else if ((v1==v2) && (v2>v3))
		return v1;
	else if ((v1==v3) && (v1>v3))
		return v1;
	else if ((v2==v3) && (v2>v1))
		return v2;
	else if ((v1==v2) && (v2==v3))
		return v1;
}

int main(void){

double v1, v2, v3, c;

printf("input 3 values \n");
scanf("%lf %lf %lf", &v1, &v2, &v3);

scanf("%lf", &c);

printf("%f \n", c);
printf("%f \n", maxval (v1, v2, v3));

return(0);
}


