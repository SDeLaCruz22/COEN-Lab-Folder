#ifndef STATS_H     // Prevent duplicate definition
#define STATS_H
#include <iostream>

namespace coen79_lab2{
  class statistician{
    private:
      double val; //the next value
    public:
        statistician();
        double data[5]; // length, sum, mean, min, max. This was made public so that the operator overloading functions could use them
        void next(double r);
        void reset( );
        int length( ) const;
        double sum( ) const;
        double mean( ) const;
        double minimum( ) const;
        double maximum( ) const;
  };

  statistician operator +(const statistician& s1, const statistician& s2);
  statistician operator *(double scale, const statistician& s);
  bool operator ==(const statistician& s1, const statistician& s2);
}

#endif
