#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

int main(void){
  int i, j;
  char num[11], temp; //char array with 11 slots doesn't cause problems (int array causes problems and a 10 slot array also causes problems, though am not sure)
  char* copy =  (char*) malloc(100);
  REINPUT: //goto label (a rarity, I know)
  j=0;
  puts("Please input exactly 10 numbers with no spaces inbetween");
  std::cin >> num; //ask for reinput if not 10
  
  

 for(i=0; i<12; i++){ //goes to 11 just to make sure there isn't an extra character
    if(num[i]!= '\0'){ //if its not a null, proceed
      j++;
    }
    else{ //null character encountered
      break;
    }
  }

  if(j!=10){ //needs to be 10 numbers exactly
    puts("Needs to be exactly 10 numbers!");
    goto REINPUT; //go to the label REINPUT
  }
  
  strcpy(copy, num);

  for(int i=0; i<=4; i++){ //this is a pretty basic reverse algorithm
    temp = num[9-i];
    num[9-i] = num[i];
    num[i] = temp;
  }
  
  strcat(copy, "        ");
  strcat(copy, num);//combined both strings with a space of 8 in between

    for(int j=1; j<6; j++){
      std::cout <<copy <<"\n";
      for(int k=0; k<j; k++)
        std::cout <<" ";
    }
  return 0;
}

