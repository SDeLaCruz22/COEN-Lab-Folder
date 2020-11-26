#include <iostream>
#include <cstdio>
//#include "Lab1.h"


int main(void){
  int i, j;
  char num[11], temp; //does not work with int...? Also 10 slots does a funny but 11 is perfectly fine....
  
  REINPUT:
  j=0;
  puts("Please input exactly 10 numbers with no spaces inbetween");
  std::cin >> num; //ask for reinput if not 10

 for(i=0; i<12; i++){
   //std::cout <<"\nLOOP " <<i <<"\n";
    if(num[i]!= '\0'){
      //std::cout <<num[i] <<"\n";
      j++;
    }
    else{
      //puts("IT BROKE MAN");
      break;
    }  
  }

  //std::cout <<"Num Count : " <<j <<"\n"; 
  if(j!=10){
    puts("Needs to be exactly 10 numbers!");
    goto REINPUT;
  }

  for(int i=0; i<=4; i++){
    temp = num[9-i];
    num[9-i] = num[i];
    num[i] = temp;
  }

  std::cout <<"\n" <<num <<"\n";
  return 0;
}
