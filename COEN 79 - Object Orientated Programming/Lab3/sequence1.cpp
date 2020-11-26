#include <iostream>
#include <cmath>
#include "sequence1.h"

using namespace std;
using namespace coen79_lab3;

namespace coen79_lab3 {

    sequence::sequence(){ //constructor
        used = 0; //the sequence has a size 0
    }

    //MODIFICATION MEMBER FUNCTIONS for the sequence class:
    void sequence::start(){
        index = 0; //index goes to the front
    }

    void sequence::end(){
        index = used -1; //if we have 5 indexes in use, then the last one in order is data[4] so index = used-1
    }

    void sequence::last(){
        index = CAPACITY -1; //go to the last index of array
    }

    void sequence::advance(){
        if(!isitem()) //if there is no current value at the index, do nothing
            return;
        if(index == CAPACITY-1) //can not move the index up if it is at the end
            return;
        index++; //otherwise increase the index
    }

    void sequence::retreat(){
        if(index == 0) //can not decrement, is already at front
            return;
        index--; //simply moves the index one value lower
    }

    void sequence::insert(const value_type& entry){
        if(!(size() < CAPACITY)) //can not insert if size is equal to capacity
            return;
        if(!isitem()){//curent doesnt have a value so it goes to the front
            for(int i=used; i>0; i--)
                data[i] = data[i-1]; //right shift any value that exist after it
            data[0] = entry; //insert at front
            used++; //size increases
            index=0;
        }
        else{ //entry goes before current
            for(int i=used; i>index; i--)
                data[i] = data[i-1]; //right shift to make space for new value
            used++; //size incremeted, new value added to sequence
            data[index] = entry; //the index value doesn't change here so the previous entry @ index is now at index+1. The new entry is at index
        }
        return;
    }

    void sequence::attach(const value_type& entry){
        if(!(size() < CAPACITY)) //can not insert if size is equal to capacity
            return;
        if(!isitem()){ //if the current item does not have a value, then we can simply just insert the value where the index is at
            index = used; 
            data[index] = entry;
            used++; //size increments because we added new value to sequence
        }
        else{
            for(int i=used; i>index+1; i--)
                data[i] = data[i-1]; //we want to right shift values to make space for the new value
            data[++index] = entry; //we can increment index since we inserted a value AFTER the index. This new value is the new current item
            used++; //inserted new value, size is incremented
        }
    }

    void sequence::remove_current(){
        if(!isitem()) //as long as there is something to remove, we can proceed
            return;
        for(int i=index; i<used-1; i++){
            data[i] = data[i+1]; //we want to left shift values
        }
        data[--used]= 0; //removed an item so we decrement size and that final element is turned to 0 since the loop doesn't account for that
    }

    void sequence::remove_front(){
        if(!isitem()) //as long as there is something to remove, we can proceed
            return;
        for(int i=0; i<used-1; i++)
            data[i] = data[i+1]; //we want to left shift the values
        used--; //removed an element, so size is decremented
        data[used] = 0; //make sure the last element is 0
        index = 0; //the index remains (does not specify to change index)
    }

    void sequence::insert_front(const value_type& entry){
        if(!(size() < CAPACITY)) //can not insert if size is equal to capcity
            return;
        for(int i=used; i>0; i--)
            data[i] = data[i-1]; //we want to right shift the values
        index=0; //we go back to the front, so the 0 index
        used++; //new value added so the size has increased
    }

    void sequence::attach_back(const value_type& entry){
        if(!(size() < CAPACITY)) //if the size is equal to capacity, then we can not insert anything
            return;
        data[used++] = entry; //the previous used iterator becomes filled with the new entry
        index = used-1; //if an array has size 10, then the max index is 9
    }


    
    size_t sequence::size() const{
        return used;} //used is the size of the sequence

    bool sequence::isitem( ) const{
        if(!data[index]) //if the value at index is 0 (nothing), return false
            return false;
        return true; //otherwise there is a value at the index, so return true
    }

    sequence::value_type sequence::current() const{
        if(!isitem()) //if the value at index is 0 (nothing), return 0
            return 0;
        return data[index]; //return the value held at the current index
    }

    
    
    
    
    
    
    double sequence::mean() const{
        double sum=0; //assume sum is 0
        for(int i=0; i<used; i++){
            sum+=data[i]; //previous sum + value
        }
        return sum/used;            }
    
    double sequence::standardDeviation() const{
        double avg = mean();
        double summ=0;
        for(int i=0; i<used; i++)
            summ+= pow((data[i] - avg), 2); //the difference between the value and the average squared
        summ = summ /(used-1); //divide previous step by population - 1
        summ = pow(summ, 1/2); //sqrt of the previous step
        return summ;
    }
    
    
    
    //operator overloads
    
    
    void sequence::operator +=(const sequence& rhs){
        if((size() + rhs.size() )> CAPACITY){ //if the sum of the sequences size is greater than capcity, end the function
            cout <<"The resulting sequence would be too large!" <<endl;
            return;
        } 
        int max = rhs.size(); //say we wanted A+=A and we made the loop dependent on rhs.size(), well inserting a new element would constantly increase the size, making the loop infinite
        for(int i=0; i<max; i++){
            attach_back(rhs[i]);//we will use this relationship of functions a lot. This will make it so that
        }
    }

    sequence::value_type sequence::operator[](int indx) const{
        if(!(indx<used))
            return 0; //this will make isitem a lot better
        return data[indx];
    }

    sequence operator +(const sequence& lhs, const sequence& rhs){
        sequence newS; 
        int totalSize = lhs.size() + rhs.size();//total size of both sequences together
        if(totalSize>30){ //the total size of the combined sequence best not be greater than CAPACITY (which is 30)
            cout <<"The addition of these two sequence is too big for the new sequence!" <<endl;
            return newS; //this will just be an empty sequence
        }
        int lsize = lhs.size(); //this is for insurance purposes, in case we want to add A + A. This will prevent infinite loops
        int rsize = rhs.size();
        for(int i=0; i<lsize; i++){ //first place the lhs sequence in the new sequence
            newS.attach_back(lhs[i]); //using the attach back and the [] overload make it so that we don't actually modify the contents of lhs or rhs
        }
        for(int j=0; j<rsize; j++){ //do a similar thing to the rhs
            newS.attach_back(rhs[j]); //a note that attach back increases used so we don't have to worry about used here
        }
        return newS; //finally return the new sequence
    }


    sequence::value_type summation(const sequence &s){
        return s.mean()*s.size();} //since mean is sum/used and size = used, then to find the sum would be to call mean and multiply by used to get just the sum
}