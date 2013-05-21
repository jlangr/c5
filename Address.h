#ifndef Address_h
#define Address_h

#include <string>

struct Address {
   std::string road;
   std::string city;
   std::string state;
   std::string country;

   std::string summaryDescription() const {
      return road + ", " + city + ", " + state + ", " + country;
   }
};

#endif

