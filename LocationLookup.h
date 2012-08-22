#ifndef LocationLookup_h
#define LocationLookup_h

#include <string>
#include <vector>
#include <exception>

#include "Address.h"

class Http;

class InvalidLocationException : public std::exception {
};

class LocationLookup {
public:
   LocationLookup(Http* http);
   std::string summaryDescription(
      const std::string& latitude, const std::string& longitude) const;

private:
   std::string getUrl(
      const std::string& latitude, const std::string& longitude) const;
   std::string keyValue(
      const std::string& key, const std::string& value) const;
   std::string format(const Address& address) const;

   Http* http_;
};
#endif
