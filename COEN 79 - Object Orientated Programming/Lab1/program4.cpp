#include <iostream>
#include <cstdio>
#include <cstdlib>
//#include "Lab1.h"

int main (void){
  int n=20;
  puts("Please think of a number between 1 and 20. Press enter to continue");
  std::cin.ignore();

  int num[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ,11, 12, 13, 14, 15, 16, 17, 18, 19 ,20};int tries=0, guess;
  char answer;

  guess =  rand() % 20 +1; 

  while(1){
    tries++;
    //std::cout << tries;
    std::cout <<"Is the number " << guess <<"?(Type Y or N)\n";
    std::cin >> answer;
    if(answer == 'Y'||answer == 'y'){
      std::cout <<"Number found in " <<tries <<" tries\n";
      return 0;
    }
    else{
      if(tries==20){
        puts("You aren't playing the game fairly!\n");
        return 0;
      }
      num[guess] = 0;
      while(1){
        guess = rand() % 20 +1;
        if(num[guess-1])
          break;
      }
    }
  }
return 0;
}

