#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

int main (void){
  int n=20;
  puts("Please think of a number between 1 and 20. Press enter to continue");
  std::cin.ignore(); //stops, press enter to continue

  int num[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ,11, 12, 13, 14, 15, 16, 17, 18, 19 ,20}; //this will be used to make the program run faster
  int tries=0, guess;
  char* answer = (char*)malloc(100);

  guess =  rand() % 20 +1; //generating a value from 1 to 20

  while(1){
    tries++; 
    RETYPE:
    std::cout <<"Is the number " << guess <<"?(Type Y or N)\n";
    std::cin >> answer;
    if(!strcmp(answer, "y")|| !strcmp(answer, "Y")||!strcmp(answer, "yes")){ //yes 
      std::cout <<"Number found in " <<tries <<" tries\n"; //outputs number of guesses
      return 0;
    }
    else if(!strcmp(answer, "n") || !strcmp(answer, "N")|| !strcmp(answer, "no")){//if it is neither Y or N this happens
      if(tries==20){ //just a precautionary, also makes it have a little personality
        puts("You aren't playing the game fairly!\n");
        return 0;
      }
      num[guess] = 0; //0 isn't in the set so this is fine
      while(1){
        guess = rand() % 20 +1; //new guess
        if(num[guess-1]) //if the guess is in the array, then it goes through, otherwise new number needs to be generated
          break;
      }
    }
    else{ 
        puts("Please type Y or N");
        goto RETYPE;
    }
  }
return 0;
}

