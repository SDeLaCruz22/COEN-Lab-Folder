#ifndef RAND_NUM_GEN_H
#define RAND_NUM_GEN_H

#include <iostream>
#include <cassert>

using namespace std;

namespace coen79_lab2 {
  class rand_gen    {
    private:
      int increment;
      int modulus;
      int multiplier;
      int seed;

    public:
      //constructor only happens once
      rand_gen(int ceed, int mult, int incr, int modu);

      int next();
      void set_seed (int ceed); //where ceed is the manually inputted seed 
  };
}


#endif
