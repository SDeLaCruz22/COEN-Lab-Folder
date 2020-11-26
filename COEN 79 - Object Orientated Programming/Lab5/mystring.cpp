// FILE: mystring.h
// CLASS PROVIDED: string
//
//  COEN 79
//  --- Farokh Eskafi, COEN, SCI ----
//
//
// CONSTRUCTOR for the string class:
//   string(const char str[ ] = "") -- default argument is the empty string.
//     Precondition: str is an ordinary null-terminated string.
//     Postcondition: The string contains the sequence of chars from str.
//
//   string(char c)
//     Postcondition: The string contains c and then the null character.
//
//   string(const string& source) -- Copy Constructor.
//     Postcondition: The string becomes a copy of the source string.
//
// MODIFICATION MEMBER FUNCTIONS for the string class:
//   void operator +=(const string& addend)
//     Postcondition: addend has been catenated to the end of the string.
//
//   void operator +=(const char addend[ ])
//     Precondition: addend is an ordinary null-terminated string.
//     Postcondition: addend has been catenated to the end of the string.
//
//   void operator +=(char addend)
//     Postcondition: The single character addend has been catenated to the
//     end of the string.
//
//   void reserve(size_t n)
//     Postcondition: All functions will now work efficiently (without
//     allocating new memory) until n characters are in the string.
//
//   void insert(const string& source, unsigned int position)
//     Precondtion: position <= length()
//     Postcondition: The source string is inserted into this string before
//     the character at the given index.
//
//   void dlt(unsigned int position, unsigned int num)
//     Precondition: (position + num) <= length( ).
//     Postcondition: num characters are deleted from the sequence, starting
//     at index position.
//
//   void replace(char c, unsigned int position)
//     Precondition: position < length()
//     Postcondtion: the character at the given position in the string is
//     replaced with c.
//
//   void replace(const string& source, unsigned int position)
//     Precondition: (position + source.length()) <= length()
//     Postcondtion: the characters in this string starting at position are
//     replaced with those in the source srting.
//
// CONSTANT MEMBER FUNCTIONS for the string class:
//   size_t length( ) const
//     Postcondition: The return value is the number of characters in the
//     string.
//
//   char operator [ ](size_t position) const
//     Precondition: position < length( ).
//     Postcondition: The value returned is the character at the specified
//     position of the string. A string's positions start from 0 at the start
//     of the sequence and go up to length( )-1 at the right end.
//
//   int search(char c) const
//     Postcondition: The location of the first occurence of the character c
//     within this string is returned. If the string does not contain c, -1 is
//     is returned.
//
//   int search(const string& substring) const
//     Postcondition: Returns the index of the start of the first instance of
//     the given substring inside of this string. If the substring is not found,
//     this function returns -1.
//
//   unsigned int //cout(char c) const
//     Postcondition: The count of the occurence of the character c within this
//     string is returned.
//
// NON-MEMBER FUNCTIONS for the string class:
//   string operator +(const string& s1, const string& s2)
//     Postcondition: The string returned is the catenation of s1 and s2.
//
//   istream& operator >>(istream& ins, string& target)
//     Postcondition: A string has been read from the istream ins, and the
//     istream ins is then returned by the function. The reading operation
//     skips white space (i.e., blanks, newlines, tabs) at the start of ins.
//     Then the string is read up to the next white space or the end of the
//     file. The white space character that terminates the string has not
//     been read.
//
//   ostream& operator <<(ostream& outs, const string& source)
//     Postcondition: The sequence of characters in source has been written
//     to outs. The return value is the ostream outs.





//
//  VALUE SEMANTICS for the string class:
//    Assignments and the copy constructor may be used with string objects.
//
//  TOTAL ORDER SEMANTICS for the string class:
//    The six comparison operators (==, !=, >=, <=, >, and <) are implemented
//    for the string class, forming a total order semantics, using the usual
//    lexicographic order on strings.
//
// DYNAMIC MEMORY usage by the string class:
//   If there is insufficient dynamic memory then the following functions call
//   new_handler: The constructors, resize, operator +=, operator +, and the
//   assignment operator.
/*
For  example,  you should  use strncpyand strncat,  not  their  less  secure  alternatives  of strcpyand strcat. 
Finally, you may NOT use the "strdup" function

Some of the important functions to be implementedare:•A new constructor that has one parameter (a character). 
The constructor initializes the string to have just this one character.•An  insertion  function  that  allows  you  
to  insert  a  string  at  a  given  position  in  another string. •A deletion function that allows you to delete a portion 
of a string.
•A  replacement  function  that  allows you to  replace  a  single  character  in a  string with  a new character.
•A  replacement  function  that  allows  you  to  replace  a  portion  of  a  string  with  another string.
•A search function that searches a string for the first occurrence of a specified character.
•A  search  function  that  counts  the  number  of occurrences  of  a  specified  character  in  a string.
•A  more  complex  search  function  that  searches  through  a  string  for  an  occurrence  of some smaller string



char* characters;
char string [5] = "ay";
size_t k = strlen(string);
characters = new char [k];
strcpy(characters, string); THIS WORKS BABY
//cout <<characters <<endl;


    char* characters;
    char string [3] = "ay";
    size_t k = strlen(string);
    characters = new char [k];
    strcpy(characters, string);
    //cout <<characters <<endl;
    char* newchar = new char [k+1];
    strcpy(newchar, characters);
    strcat(newchar, "C");
    //cout <<newchar <<endl;

*/

#include <cstdlib>  // Provides size_t
#include <cstring>
#include <iostream>
#include "mystring.h"

using std::cout;
using std::cin;
using namespace coen79_lab5;

namespace coen79_lab5{
    // CONSTRUCTOR, COPY CONSTRUCTOR, and DESTRUCTOR
    string::string(const char str[ ]){
        characters = new char[strlen(str)+1]; //allocated memory equal to the length of string +1
        for(int i=0; characters[i]; i++) //idk why there are memory leaks, but this negates it
            characters[i] = '\0';
        strncpy(characters, str, strlen(str)); //copy the contetns into characters
        allocated = strlen(str) +1; //provide the null character as allocated space
        current_length = strlen(str); //the length of string is now qual to str
    }

    string::string(char c){                     // NEW FUNCTION 1
        allocated = 2; //c always takes up 1 unit of memroy since it is a single character
        reserve(2); //space for null character
        characters[0] = c; //simply add it
        characters[1] = '\0'; //we amke sure the string ends in null
        current_length = 1; //length of strig is equal to a characters
    }

    string::string(const string& source){
        if(characters!=NULL)
            delete[] characters;
        size_t slength =  source.length(); //minimize function calling
        allocated = slength + 1; //+1 for the null character
        characters = new char[allocated]; //give character memory
        for(int i=0; characters[i]; i++) //idk why there are memory leaks, but this negates it
            characters[i] = '\0';
        strncpy(characters, source.getString(), slength); //copy contents of the string in source into characters
        current_length = slength; //equal to the length of the strin gin source
    }

    string::~string( ){//destructor
        delete[] characters; //free memory
        current_length = 0; //no characters
        allocated = 0; //no memory
    }

    // CONSTANT MEMBER FUNCTIONS
    size_t string::length( ) const { return current_length;}

    char string::operator [ ](size_t position) const{
        if(position >= length())
            return '\0'; //return null characters
        return characters[position]; //otherwise return charcter at position
    }
    char* string::getString() const{ //this will help in retreiving the entirety of the string rather than using a loop
        return characters;
    }

    int string::search(char c) const{
        for(int i=0; i<strlen(characters); i++){ //searches throughout characters
            if(characters[i] == c) //when it finds the first instance of c it returns the location
                return i;
        }
        return -1; //otherwise it doesn't show up in the string
    }

    int string::search(const string& substring) const{ 
        char *temp;
        int i, j;
        size_t subsize = substring.length(); //minimize function calling
        for(i=0; i<=current_length-subsize; i++){ //begin searching
            if(!strncmp(&characters[i], substring.getString(), subsize)) //if the substring inside characters matches the substring it returns the index
                return i;
        }
        return -1;//it doesnt exist in the string
    }

    unsigned int string::count(char c) const{
        int counts = 0; //assume it doedsnt show up
        for(int i=0; i<current_length; i++){ 
             if(characters[i] == c) //for every instance of c in the string, the count increments
                counts++;
        }
        return counts; //return final count
    }
    
    // MODIFICATION MEMBER FUNCTIONS
    void string::reserve(size_t n){ 
        size_t tempsize = n + allocated; //total memory size will be the current memory + n
        char * temp = new char[tempsize]; //allocate temp with that memory
        if(characters){
            strncpy(temp, characters, strlen(characters)); //if characters isnt a null string, then we copy contents into temp
            delete[] characters;//delete characters
        }
        characters = new char [tempsize]; //allocate memory for characters equal to the new memory size
        strncpy(characters, temp, strlen(temp)); //copy contents back into characters
        allocated = tempsize; //allocated is now equal to the new memory size
    }


    size_t string::memory() const{ //simply returns the allocated memory
        return allocated;
    }

    void string::strncopy(char* s1, char* s2, size_t charz){ //these two strncpys are used. Without these, there would be errors in compilation due to strings not beign const
        for(int i=0; i<charz; i++){
            s1[i] = s2[i];
        }
    }

    void string::strncopy(char* s1, char* s2, size_t charz) const{
        for(int i=0; i<charz; i++){
            s1[i] = s2[i];
        }
    }
    
    void string::insert(const string& source, unsigned int position){
        if(position > strlen(characters))   //if the position is beyond the length of the string, then it is invalid
            return;
        
        size_t newsize = strlen(characters) + strlen(source.getString()) + 1; //newsize includes the null character
        char* newstring = new char[newsize]; //allocate it with the new memory
        size_t tempsize = strlen(characters) - position; //temp will be used to copy any characters that lie beyond the insertion
        char* temp = new char[tempsize];

        strncpy(temp, &characters[position], tempsize); //copy contents after the inserted portion into temp
        if(position!=0) //we want to preserve the characters up to the position
            strncpy(newstring, characters, position); //copy up to position if needed
        delete[] characters; //free memory of string
        allocated = 0;//now the memory is set back to 0

        strncat(newstring, source.getString(), strlen(source.getString())); //we now insert the string we want to insert in the middle after any characters that arent affected by the insertion
        strncat(newstring, temp, strlen(temp)); //then we copy the characters past the point of insertion
        characters = new char[newsize]; //reallocate memory to characters
        allocated = newsize; //with the new memory
        strncpy(characters, newstring, strlen(newstring)); //copy all of the contents from newstring to characters
        current_length = newsize-1; //minus the extra memory for null
    }

    void string::dlt(unsigned int position, unsigned int num){ 
        if(position + num > strlen(characters)) //if the position + the amount of elements we want to remove is beyond the length of the characters
            return; //we do nothing
        for(int i=position; i<current_length; i++){ //scan through the string
            characters[i] = characters[i+num];//replace all of the characters from [positoin] to [currentlength-1] as to "delete" them
        }
        current_length -= num; //deleted num characters //and finally we recognize that the size of the string has been decremented
    }

    void string::replace(char c, unsigned int position){
        if(position >=strlen(characters)) //if the position is beyond the length of the string then we do nothing
            return;
        characters[position] = c;//otherwise simply replace the current character with the new one
    }

    void string::replace(const string& source, unsigned int position){
        if(position + source.length() > strlen(characters)) //if the position and the length of the string is beyond the length of characters, we do nothing
            return;
        size_t sourceSize = source.length(); //minimize function calls
        char * temp;
        size_t k = strlen(characters) - sourceSize - position; //this iwll be used for the size of temp
        temp = new char [k];
        strncopy(temp, &characters[position + sourceSize], k); //copy characters past the position
        strncopy(&characters[position], source.getString(), sourceSize); //input the string
        strncopy(&characters[position + sourceSize], temp, k);//and add back the copied characters
        delete[] temp;
    }

    void string::operator +=(const string& addend){
        size_t addendsize = addend.length(); 
        reserve(addendsize+1); //reserve memory + 1 for null
        strncat(characters, addend.getString(), addendsize); //simply just place it in the bakc of th string
        current_length+=addendsize; //the current length has been increased to fit the new string
    }

    void string::operator +=(const char addend[ ]){
        size_t addendsize = strlen(addend); //length of addend is recorded
        reserve(addendsize+1); //add memory + for the null character
        strncat(characters, addend, addendsize); //copy the string at end of characters
        current_length+=addendsize; //lenght of the string is changed
    }

    void string::operator +=(char addend){
        size_t addendsize = 1; //simple character has a size of 1
        reserve(addendsize+1); //reserve it more space
        characters[current_length] = addend; //attach at end note that the last character in characters was at [length-1]
        current_length++; //length is increasd
    }

    string& string::operator =(const string& source){//honestly I had a bit of help on this one. This one gave me a lot of problems.
        this->dlt(0, current_length); //We empty the contents of the current string, "this" is not a stack memory variable so we can return it later
        if(length() < source.length())
            reserve(source.memory());//we want current string to be as spacious as source
        strncopy(characters, source.getString(), source.length()); //copy the new string into characters
        current_length = source.length(); //length is eual to the new string
        characters[current_length] = '\0';
        return *this; //return the curretn object
    }
    // FRIEND FUNCTIONS
    std::ostream& operator <<(std::ostream& outs, const string& source){
        cout <<source.getString() <<""; //simply print out the current string
        return outs;
    }

    bool operator ==(const string& s1, const string& s2){
        if(s1.length() != s2.length())
            return false;//different string lengths, not same
        for(int i=0; i<s1.length(); i++){
            if(s1[i] != s2[i])
                return false; //a single character is not the same, so they are not the same
        }
        return true;
    }
    bool operator !=(const string& s1, const string& s2){
        size_t max = (s1.length()>s2.length())? s1.length():s2.length(); //max is s1 if s1>larger, other wise s2 is max
        for(int i=0; i<max; i++){
            if(s1[i] != s2[i])
                return true; //one character, not equal, so they are not the same
        }
        return false; //they are equal
    }
    bool operator > (const string& s1, const string& s2){
        size_t max = (s1.length()>s2.length())? s1.length():s2.length();
        if(strncmp(s1.characters, s2.characters, max) > 0) //compares which value is higher,
            return true; //s1 is higher
        return false; //s1 is not higher
    }
    bool operator < (const string& s1, const string& s2){
        size_t max = (s1.length()>s2.length())? s1.length():s2.length();
        if(strncmp(s1.characters, s2.characters, max) < 0)
            return true; //s1 has a lowe value
        return false;//s2 does not have a lower value
    }
    bool operator >=(const string& s1, const string& s2){
        size_t max = (s1.length()>s2.length())? s1.length():s2.length();
        if(strncmp(s1.characters, s2.characters, max) < 0)
            return false; //s1 has a greater or equal value
        return true; //has a lesser value
    }
    bool operator <=(const string& s1, const string& s2){
        size_t max = (s1.length()>s2.length())? s1.length():s2.length();
        if(strncmp(s1.characters, s2.characters, max) > 0)    
            return false; //s1 is of lesser or equal value
        return true;//s1 has a greater value
    }

    // NON-MEMBER FUNCTIONS for the string class
    string operator +(const string& s1, const string& s2){
        string news(s1); //news is now s1
        news.insert(s2, strlen(news.getString())); //insert s2 string into news after s1
        return news; //return the combined string
    }

    string operator +(const string& s1, const char addend[ ]){
        string news(s1);
        news.insert(addend, news.length()); //insert the string after s1
        return news; //return combined string
    }
    std::istream& operator >> (std::istream& ins, string& target){//this one also gave me trouble, so I had to ask for help
        char* scan; //we call the temporary cin scan
        scan = new char[50];//should be enough for most situations
        ins >> scan; //this line I have never used, but the input is copied into scan
        target = string(scan); //we use the = operator overload to copy the string into target
        return ins; //will return targer....for some reason
    }
}
