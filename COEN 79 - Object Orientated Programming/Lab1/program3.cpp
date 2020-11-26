#include <iostream>
#include <cstdio>
//#include "Lab1.h"

int main (void){
  FILE *fp;
  char string[30];
  int cCount=0, val, i;
  fp= fopen("program3.txt", "r");
  while(!feof(fp)){
    fscanf(fp, "%s", string);
    for(i=0; i<30; i++){
      val = int(string[i]);
      if((val >= 65 && val <= 90) || (val >= 97 && val <= 122))
        cCount++;
      else if (val==0)//spcae null
        break;
      else 
        continue;
    }
    if(cCount >= 10){
      for(i=0; i<30; i++){
        val = int(string[i]);
        if((val >= 65 && val <= 90) || (val >= 97 && val <= 122))
          putchar(toupper(string[i])); 
      }
//      std::cout <<" " <<string;
      puts("\n");
    }
    cCount=0;
  }
return 0;
}
