#ifndef PlaceDescriptionService_h
#define PlaceDescriptionService_h

#include <string>
// START:overrideFactoryMethod
#include <memory>
// ...
// END:overrideFactoryMethod
#include "Address.h"

class Http;

class PlaceDescriptionService {
public:
// START:overrideFactoryMethod
   virtual ~PlaceDescriptionService() {}
// ...
// END:overrideFactoryMethod
   std::string summaryDescription(
      const std::string& latitude, const std::string& longitude) const;

private:
   std::string createGetRequestUrl(
      const std::string& latitude, const std::string& longitude) const;
   std::string summaryDescription(const Address& address) const;
   std::string keyValue(
      const std::string& key, const std::string& value) const;
   std::string get(const std::string& requestUrl) const;
   std::string summaryDescription(const std::string& response) const;

// START:overrideFactoryMethod
protected:
   virtual std::shared_ptr<Http> httpService() const;
// END:overrideFactoryMethod
};

#endif
