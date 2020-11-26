#include <cstdlib>
#include <climits>
#include <cmath>
#include "poly.h"

using namespace std;
//using namespace coen79_lab4;

namespace coen79_lab4{

    polynomial::polynomial(double c, unsigned int exponent){//constructor
        if(exponent > MAXIMUM_DEGREE)
            return;
        clear();//set all values to 0
        data[exponent] = c;//set coeficceitn c to exponent
    } 


    // MODIFICATION MEMBER FUNCTIONS for the polynomial class
    void polynomial::assign_coef(double coefficient, unsigned int exponent){
        if(exponent > MAXIMUM_DEGREE)
            return;
        data[exponent] = coefficient;
    }

    void polynomial::add_to_coef(double amount, unsigned int exponent){
        if(exponent > MAXIMUM_DEGREE)
            return;
        data[exponent] += amount;
    }
    void polynomial::clear( ){
        for(int i=0; i<MAXIMUM_DEGREE; i++){
            data[i] = 0;
        }
    }
    //     POSTCONDITION: All coefficients of this polynomial are set to zero.


    //CONST functions
    double polynomial::operator( ) (double x) const{
        double sum = 0; //assume the sum is 0
        for(int i=0; i<MAXIMUM_DEGREE; i++){
            sum+= data[i] * pow(x, i); //coefficient * x^expoenent is added to the sum
        }
        return sum;
    }

    // CONSTANT MEMBER FUNCTIONS for the polynomial class
    polynomial polynomial::antiderivative( ) const{
        polynomial integral;
        if(degree() >= MAXIMUM_DEGREE)
            return integral;
        //ax^2 (index 2)--> a / 3 * x^3 (index 3)
        for(int i=MAXIMUM_DEGREE-1; i>0; i--){
            integral.data[i] = data[i-1] / i; //the x^3 index will have the index of x^2 and divide it by 3
        }
        integral.data[0] = 0;//the constant is set to 0
        return integral;
    }

    double polynomial::coefficient(unsigned int exponent) const{
        if(exponent > MAXIMUM_DEGREE)
            return 0;
        return data[exponent];
    }

    double polynomial::definite_integral(double x0, double x1) const{//assuming x0 is the lower bound and x1 is the upper bound
        //3 + 3(5) + 3(5^2) +.... coeffieicent * x^exponent.....3(5)^2 - 3(4)^2 == 3(5^2 - 4^2)
        polynomial integral = antiderivative();//create an object that is an antiderivative of the current data
        double sum = 0; //we will use this to sum the integral bounds and assume it is 0
        for(int i=1; i<MAXIMUM_DEGREE; i++){//starts at one since the constant will be 0 anyways
            integral.data[i] = integral.data[i] * (pow(x1, i) - pow(x0, i));
            sum+=integral.data[i];//add the newly produced bound subtraction
        }
        return sum;
    }

    unsigned int polynomial::degree( ) const{
        for(int i=MAXIMUM_DEGREE-1; i>=0; i--){
            if(data[i])//if current exponent has a coefficient value
                return i;//then it must be the largest
        }
        return 0;
    }

        unsigned int polynomial::degree( ){//same as the other except this isnt a const, the compiler willknow which one to choose
        for(int i=MAXIMUM_DEGREE-1; i>=0; i--){
            if(data[i])//if current exponent has a coefficient value
                return i;//then it must be the largest
        }
        return 0;
    }

    polynomial polynomial::derivative( ) const{
        //3x^2 ind 2--> 6x ind 1
        polynomial prime; 
        for(int i=0; i<MAXIMUM_DEGREE-1; i++){//we will stop at index 28 ([27])
            prime.data[i] = data[i+1] * (i+1); //coeefieicent in exponent 2 of prime will have coeffieicent of curr data* exponent 3
        }
        prime.data[MAXIMUM_DEGREE-1] = 0;//make sure the last elemeent is set to 0 
        return prime;
    }

    double polynomial::eval(double x) const{
        double sum = 0; //assume the sum is 0
        for(int i=0; i<MAXIMUM_DEGREE; i++){
            sum+= data[i] * pow(x, i); //coefficient * x^expoenent is added to the sum
        }
        return sum;
    }

    bool polynomial::is_zero( ) const{
        for(int i=0; i<MAXIMUM_DEGREE; i++){
            if(data[i])//if the current exponenet has a coeffiecient...
                return false;//it is not the 0 polynomial
        }
        return true;//is true otherwise
    }

    unsigned int polynomial::next_term(unsigned int e) const{
        if(e>=MAXIMUM_DEGREE)
            return 0; //[28] is the largest index
        for(int i=MAXIMUM_DEGREE-1; i>e; i--){//we going from high to low expoenent. stop at e+1
            if(data[i])//if the expoenent has a coefficient...
                return i; //return the current expoenent
        }
        return 0; //no exponenet greater than e has a coefficient
    }

    unsigned int polynomial::previous_term(unsigned int e) const{
        if(e>=MAXIMUM_DEGREE)
            return UINT_MAX; //[28] is the largest index
        for(int i=0; i<e; i++){//we go up to exponenet e-1
            if(data[i])//if the expoenent has a coefficient...
                return i; //return the current expoenent
        }
        return UINT_MAX; //no exponenet greater than e has a coefficient
    }


    // NON-MEMBER BINARY OPERATORS
        
        // NON-MEMBER OUTPUT FUNCTIONS
    std::ostream& operator << (std::ostream& out, const polynomial& p){
        int mindeg;
        for(int i=0; i<p.degree(); i++){
            if(p.data[i])
                mindeg = i;//we will set this up as the lowest exponent with a coefficeint
        }
        if(p.degree()==1)
            cout <<p.data[1] <<"x";
        else
            cout <<p.data[p.degree()] <<"x^" <<p.degree();
        for(int i=p.degree()-1; i>=mindeg; i--){//we will only go down to the smallest deg +1
            if(!p.data[i])//if current exponenet has no coefficent
                continue;//go to next loop
            if(i<=1){//special condition for exp 1 and constant
                if(p.data[i]<0)//if the coefficeint is negative (and also implies that data[i] exists)
                    cout <<" - " <<p.data[i]*-1;//negative cout
                else if(p.data[i])//we have to verify that dat[i] exists
                    cout <<" + " <<p.data[i];//else positive cout

                if(i==1 && p.data[i])//if the first polynomial has a coeffieceint
                    cout <<"x";//print out this special condition
                continue;//continue to next loop
            }
            if(p.data[i] < 0)
                cout <<" - " <<p.data[i]*-1 <<"x^" <<i;//we will make the value positive but add the "-" as a subtraction not a negative
            else
                cout <<" + " <<p.data[i] <<"x^" <<i;//the output is just " + val"
        }
        return out;
    }

    polynomial operator +(const polynomial& p1, const polynomial& p2){
        polynomial nu;
        for(int i=0; i<29; i++){//goes up to 28, max is [28]
            nu.data[i] = p1.data[i] + p2.data[i];//the coeffiecient at exp i is equal to the sum of the coeffeicents
        }
        return nu;
    }

    polynomial operator -(const polynomial& p1, const polynomial& p2){
        polynomial nu;
        for(int i=0; i<29; i++){//goes up to 28, max is [28]
            nu.data[i] = p1.data[i] - p2.data[i];//the coeffiecient at exp i is equal to the difference of the coeffeicents
        }
        return nu;     
    }

    polynomial operator *(const polynomial& p1, const polynomial& p2){
        polynomial nu;
        if(p1.degree() + p2.degree() > 29)
            return nu;//return the empty polynomail since the addition of the p1 and p2 is too big
        nu.clear(); //set all the coefficeints to 0
        for(int i=0; i<=p1.degree(); i++){//we go up to the max degree since degree returns the index of the largest exponenet
            for(int j=0; j<=p2.degree(); j++){//NESTED LOOP POG
                nu.data[i+j]+= p1.data[i] * p2.data[j];//the exponenet at new is the sum of the expoenents being multiplied
            }
        }
        return nu;
    }

}