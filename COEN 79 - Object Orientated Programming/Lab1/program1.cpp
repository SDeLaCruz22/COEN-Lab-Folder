#include <iostream>
//#include "Lab1.h"

void program1();

int main() {
  int menu;
/*  MENU:
  std::cout << "What Program will you be using?\n";
  std::cin >> menu;
  switch(menu){
    case 1:   
      program1();
      break;
    case 2: 
      program2();
      break;
    case 3:
      program3();
      break;
    case 4:
      program4();
      break;
    default: 
      std::cout <<"Invalid Operation\n";
  } 
  goto MENU;*/
	program1();

}

void program1(){
  char type[25];
  int cCount=0, iCount=0, val;
  std::cout << "Please type something (make sure there are no spaces)\n";
  std::cin >> type;
  for(int i=0; i<25; i++){
    if(!int(type[i]))
      break;
    val= int(type[i]);

    if((val >= 65 && val <= 90) || (val >= 97 && val <= 122))//ascii code values for all albapheticals
      cCount++;

    else if(val)
      iCount++;
  }
  
  std::cout <<"\n" << type <<" has " << cCount <<" alphanumeric characters and " <<iCount << " non-alphanumeric characters\n\n" ;
}
