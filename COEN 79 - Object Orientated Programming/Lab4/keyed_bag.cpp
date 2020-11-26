// FILE: keyed_bag.h
// CLASS PROVIDED: keyed_bag (part of the namespace coen79_lab4)
//
//
//  COEN 79
// 
//
//
// TYPEDEF and MEMBER CONSTANTS for the keyed_bag class:
//   typedef ____ value_type
//     keyed_bag::value_type is the data type of the items in the keyed_bag. It may be any of
//     the C++ built-in types (int, char, etc.), or a class with a default
//     constructor, an assignment operator, and operators to
//     test for equality (x == y) and non-equality (x != y).
//
//   typedef ____ key_type
//     keyed_bag::key_type is the data type of the items used as keys for the items
//     in the keyed_bag. It may be any of the C++ built-in types (int, char, etc.),
//     or a class with a default constructor, an assignment operator, and
//     operators to test for equality (x == y) and non-equality (x != y).
//
//   typedef ____ size_type
//     keyed_bag::size_type is the data type of any variable that keeps track of how many items
//     are in a keyed_bag.
//
//   static const size_type CAPACITY = _____
//     keyed_bag::CAPACITY is the maximum number of items that a keyed_bag can hold.
//
// CONSTRUCTOR for the keyed_bag class:
//   keyed_bag( )
//     Postcondition: The keyed_bag has been initialized as an empty keyed_bag.
//
//
// MODIFICATION MEMBER FUNCTIONS for the keyed_bag class:
//   void erase();
//     Postcondition: This keyed_bag is emptied of all items and keys.
//
//   bool erase(const key_type& key);
//     Postcondition: If key was in the keyed_bag, then the key and its value have been removed;
//     otherwise the keyed_bag is unchanged. A true return value indicates that an
//     item was removed; false indicates that nothing was removed.
//
//   void insert(const value_type& entry, const key_type& key)
//     Precondition:  size( ) < CAPACITY, and the keyed_bag does not yet contain
//     the given key.
//     Postcondition: A new copy of entry has been added to the keyed_bag with
//     the corresponding key.
//
//   void operator +=(const keyed_bag& addend)
//     Precondition:  size( ) + addend.size( ) <= CAPACITY.
//     The intersection of the keyed_bags' key tables is empty (i.e. the keyed_bags)
//     share no keys.
//     Postcondition: Each item and its key in addend has been added to this keyed_bag.
//
//
// CONSTANT MEMBER FUNCTIONS for the keyed_bag class:
//   bool has_key(const key_type& key) const
//     Postcondition: The return value is whether or not the given key is in
//     the keyed_bag's list of keys.
//
//   value_type get(const key_type& key) const;
//     Precondition: has_key returns true for the given key.
//     Postcondtion: the data value corresponding to the given key is returned.
//
//   size_type size( ) const
//     Postcondition: The return value is the total number of items in the keyed_bag.
//
//   size_type count(const value_type& target) const
//     Postcondition: The return value is number of times target is in the keyed_bag.
//
//   bool hasDuplicateKey(const keyed_bag& otherBag) const
//     Postcondition: The return value is true if there is at least one key used by both this bag and the "otherBag". In other words, this function checks if there is any shared key by the two bags.
//
// NONMEMBER FUNCTIONS for the keyed_bag class:
//   keyed_bag operator +(const keyed_bag& b1, const keyed_bag& b2)
//     Precondition:  b1.size( ) + b2.size( ) <= keyed_bag::CAPACITY.
//                    The intersection of the keyed_bags' key tables is empty.
//                    (i.e. The two keyed_bag's have no keys in common.)
//     Postcondition: The keyed_bag returned is the union of b1 and b2.
//
//
// VALUE SEMANTICS for the keyed_bag class:
//    Assignments and the copy constructor may be used with keyed_bag objects.
/*

To this end, two arrays are used:
    key_type keys[CAPACITY];    // The array to store the keys
    value_type data[CAPACITY];  // The array to store items

Each item added to the keyed bag must have a unique key; two items cannot have the same key. 
So, the insertion function has the specification shown here:

void keyed_bag::insert(const value_type& entry, int key);
Precondition: size( ) < CAPACITY, and thebag does not yet contain any item with the given key.
Postcondition: A new copy of entry hasbeen added to the bag, with the given key.

When the programmer wants to remove an item from a keyed bag, the key of the item must be specified, 
rather than the item itself. The keyed bag should also have a boolean member function that can be used to 
determine whether the bag has an item with a specified key.

*/

#include <iostream>
#include <cmath>
#include <cstring>
#include "keyed_bag.h"

using namespace std;
using namespace coen79_lab4;

namespace coen79_lab4 {


    keyed_bag::keyed_bag(){//constructor
        used = 0;
    }

    //CONSTANT MEMBER FUNCTIONS for the keyed_bag class:
    bool keyed_bag::has_key(const key_type& key) const{
        for(int i=0; i<used; i++){
            if(!std::strcmp(keyData[i], key))//compare teh strings, if they are the same, then the key already exists in the bag
                return true;
        }
        return false;
    }

    keyed_bag::value_type keyed_bag::get(const key_type& key) const{
        if(!has_key(key))//if the key isnt in the data, then we cant return anything
            return 0;
        for(int i=0; i<used; i++){
            if(!std::strcmp(keyData[i], key))//if the key matches then return the data held at the key
                return data[i];
        }
        return 0;
    }

    keyed_bag::size_type keyed_bag::size() const{
        return used;
    }
        // Postcondition: The return value is the total number of items in the keyed_bag.

    keyed_bag::key_type keyed_bag::getKey(const int index){
        if(index>used || !keyData[index])//if the index is higher than used or if the data at index doesnt exist, then return null
            return NULL;
        return keyData[index]; //no need for preconditions, if it failed to meet the preconditions it will simply return a null
    }

    keyed_bag::keyed_bag::key_type keyed_bag::getKey(const int index) const{ //the const version of getKey just in case. Compiler willknow which to use
        if(index>used || !keyData[index])//if the index is higher than used or if the data at index doesnt exist, then return null
            return NULL;
        return keyData[index]; //no need for preconditions, if it failed to meet the preconditions it will simply return a null
    }

    keyed_bag::size_type keyed_bag::count(const value_type& target) const{
        int Tshows=0;//assume that the target doesnt appear
        for(int i=0; i<used; i++){
            if(data[i]==target)
                Tshows++;//increments every time target is in the data
        }
        return Tshows;
    }

    bool keyed_bag::hasDuplicateKey(const keyed_bag& otherBag) const{
        for(int i=0; i<used; i++){
            if(otherBag.has_key(keyData[i])){//if the other bag has the key, then we know a key exists in both bags
                cout<<"A key exists in both bags!" <<endl;
                return true;
            }
        }
        return false;
    }

    //MODIFICATION MEMBER FUNCTIONS for the keyed_bag class:
    void keyed_bag::erase(){
        for(int i=0; i<used; i++){//set all data to 0/NULL string
            data[i] = 0;
            std::strcpy(keyData[i], NULL);
        }
        used =0;//finally set used to 0
    }
        //Postcondition: This keyed_bag is emptied of all items and keys.

    bool keyed_bag::erase(const key_type& key){
        for(int i=0; i<used; i++){
            if(!std::strcmp(keyData[i], key)){ //if there is a key in the data...
                std::strcpy(keyData[i], NULL);//erase teh key
                data[i] = 0;//erase the data
                used--;//used goes down
                return true; //removal success
            }
        }
        return false;
    }

    void keyed_bag::insert(const value_type& entry, const key_type& key){
        if(size() >= CAPACITY)//self explanatory
            return;
        if(has_key(key)) //if the key is already in the bag return
            return;
        keyData[used] = malloc(sizeof(char*)*key);
        data[used] = entry; //insert the entry
        std::strcpy(keyData[used], key); //copy the key into the data
        used++;
    }

    void keyed_bag::operator +=(const keyed_bag& addend){
        if((size() + addend.size()) > CAPACITY){
            cout <<"Addition of the new bag will be too big for current bag!" <<endl;
            return;
        }
        if(hasDuplicateKey(addend))//if a key is already in the bag, then no += will be perofrmed
            return;
        for(int i=0; i<addend.size(); i++){
            insert(addend.get(addend.getKey(i)), addend.getKey(i)); //insert (value, key)
        }
    }
                

    // NONMEMBER FUNCTIONS for the keyed_bag class
    keyed_bag operator +(const keyed_bag& b1, const keyed_bag& b2){
        keyed_bag newB;
        if(b1.size() + b2.size() > keyed_bag::CAPACITY){
            cout<<"Resulting bag is too big for capacity!" <<endl;
            return newB;//return the empty bag
        }
        if(b1.hasDuplicateKey(b2)) //if a key is already in both bags then we return empty bag
            return newB;
        for(int i=0; i<b1.size(); i++){
            newB.insert(b1.get(b1.getKey(i)), b1.getKey(i)); //insert (value, key) of b1 first
        }
        for(int i=b1.size(); i<b2.size(); i++){
           newB.insert(b2.get(b2.getKey(i)), b2.getKey(i));//insert (value, key) of b2 then
        }
        return newB;
    }


}