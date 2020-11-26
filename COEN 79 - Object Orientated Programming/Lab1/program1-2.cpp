#include <iostream>
#include <cctype>

int main (void){
  char type[25]; //ease of use
  char *temp;
  int cCount=0, iCount=0;
  std::cout << "Please type something (make sure there are no spaces)\n";
  std::cin >> type; 

  for(int i=0; i<25; i++){
    if(!int(type[i]))//a space or NULL will stop the loop
      break;

    if(isalnum(type[i]))//checks to see if num or letter
      cCount++;

    else //doesn't specify number, just that it is not a letter
      iCount++;
  }

  std::cout <<"\n" << type <<" has " << cCount <<" alphanumeric characters and " <<iCount << " non-alphanumeric characters\n\n" ; 


}


