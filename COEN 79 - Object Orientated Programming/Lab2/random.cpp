#include <cassert>   // Provides assert
#include <iostream>  // Provides istream class
#include <cmath>
#include "random.h"

using namespace std;
using namespace coen79_lab2;
namespace coen79_lab2 { 

  rand_gen::rand_gen(int ceed, int mult, int incr, int modu){ //these parameter were something I noticed when looking at the main file offered, so by doing this it will make it so an object created under this class can be constructed using these terms. It should be obvious what goes into what
    increment = incr;
    modulus = modu;
    multiplier = mult;
    seed = ceed;
  } 

  int rand_gen::next(){ //a number is generated which also becomes the seed afterwards
    seed = (multiplier*seed + increment)%modulus;
    return seed; //returns the random number which is also the new seed
  }
  void rand_gen::set_seed (int ceed) { //only sets the seed manually
    seed = ceed;
  }
}