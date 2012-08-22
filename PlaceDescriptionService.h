#ifndef PlaceDescriptionService_h
#define PlaceDescriptionService_h

#include <string>
#include "Address.h"

class Http;

class PlaceDescriptionService {
public:
   PlaceDescriptionService(Http* http);
   std::string summaryDescription(
      const std::string& latitude, const std::string& longitude) const;

private:
   std::string createGetRequestUrl(
      const std::string& latitude, const std::string& longitude) const;
   std::string summaryDescription(const Address& address) const;

   Http* http_;
};

#endif
