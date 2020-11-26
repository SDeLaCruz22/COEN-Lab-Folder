#include <cassert>   // Provides assert
#include <iostream>  // Provides istream class
#include <cmath>
#include "statistician.h"

using namespace std;
using namespace coen79_lab2;
namespace coen79_lab2{

  statistician::statistician(){
    data[0]=0; //set the length to 0 since almost every function will be impacted by this
  }

  void statistician::next(double r){
    val = r;
    cout << "Last " <<r <<endl;     //not integral, its there to make this look similar to expectedstat.txt 
    data[0] = length() + 1;         //this is so the length can be called in another function while giving an accurate length
    if(!data[0])        //a 0 length...
      data[1] = 0;      //corresponds to no summation
    else if(data[0] == 1)   //there is only one number in the sequence
      data[1] = val;        //that number is it's own sum
    else
      data[1] += val;       //otherwise the next value is added to the sum of the previous next value. The reason why sum in the "next" function is because the main program calls on sum, meaning sum should only return the final summation
    data[2] = mean();   
    data[3] = minimum();
    data[4] = maximum();
  }

  void statistician::reset( ){
    data[0] = 0; //length is 0 now. ALl other functions are impacted by this
    data[1] = 0; //sum was made in the next function, so this should also be resetted just in case
  }

  int statistician::length( ) const{
    if(!data[0])  //if the length is 0 or empty index
      return 0;   //we must pass 0 based on the previous condition (it would have returned a default value otherwise)
    else{
      return data[0]; //return current value of length
    }
  }

  double statistician::sum( ) const{
    return data[1]; //returns the sum that was created by the last inputed next value
  }

  double statistician::mean( ) const{
    if(!data[0])    //the length is 0
      return NAN;   //essentially the value doesn't exist 
    else{
      double avg = data[1]/data[0]; //the total sum / length. This is safe to do since sum is calculated when the next value is added
      return avg;
    }
  }

  double statistician::minimum( ) const{
    if(!data[0])    //length is 0
      return NAN;   //so there isn't a minimum value
    else if(data[0] == 1)    //if it is the only number in the sequence, it is the smallest number
      return val;    //returns as the new min value
    else if(val < data[3])      //if its smaller than the alredy placed minimum value
      return val;       //it wil return the new value is the min value
    else
      return data[3]; //the next value is greater than or equal to the min, so the current min stays
  }

  double statistician::maximum( ) const{
    if(!data[0])  //length is 0
      return NAN; //no max value can be achieved
    else if(data[0] == 1)//if it is the only number in the sequence, it is the largest number
      return val;
    else if(val > data[4]) //if it is larger than current max, it becomes the new max
      return val;
    else
      return data[4]; //the current max value holds
  }

  statistician operator +(const statistician& s1, const statistician& s2){
      statistician newS; //new object under statistician class
      newS.data[0] = s1.data[0] + s2.data[0]; //summation of lengths, holds the amount of numbers
      newS.data[1] = s1.data[1] + s2.data[1]; //the sum of both sums
      newS.data[2] = newS.data[1]/newS.data[0]; //the total sum / the total length
      newS.data[3] = (s1.data[3] < s2.data[3]) ? s1.data[3] : s2.data[3]; //assigns the overall minimum
      newS.data[4] = (s1.data[4] > s2.data[4]) ? s1.data[4] : s2.data[4]; //assigns the overall maximum

      return newS;
  }
    statistician operator *(double scale, const statistician& s){

    statistician newS; //new object under statistician class
    newS.data[0] = s.data[0]; //the length is not affected by the scalar
    for(int i=1;i<3; i++){
      newS.data[i] = scale * s.data[i]; //the sum and average are multiplied by the scalar
    }
    if(scale< 0){ //the max and min values are switched if the scalar is negative
      newS.data[3] = scale * s.data[4];
      newS.data[4] = scale * s.data[3];
    }
    else{//normal scaling is applied since the scalar is positive (or 0)
      newS.data[3] = scale * s.data[3];
      newS.data[4] = scale * s.data[4];
    }
    return newS; 
  }
  
  bool operator ==(const statistician& s1, const statistician& s2){
    int same=0;   //same counter
    if(s1.data[0] == 0 && s2.data[0] == 0) //the precondition that if two objects have 0 length, then they have no other statistic, thus they are the same
      return true;
    else{       //for any object larger than 0 length
      for(int i=0; i<5; i++){
        if(s1.data[i] == s2.data[i]) //if two values of a statistic are the same the counter "same" increases
          same++;
      }
      if(same==5) //if all five statistics are the same, then they are the same 
        return true;
    }
    return false; //otherwise they are not the same
  }
}