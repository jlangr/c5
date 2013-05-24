#ifndef PlaceDescriptionService_h
#define PlaceDescriptionService_h

#include <string>
#include <memory>
#include "Address.h"

class Http;

// START:PlaceDescriptionService
class PlaceDescriptionService {
public:
// START_HIGHLIGHT
   PlaceDescriptionService();
// END_HIGHLIGHT
   virtual ~PlaceDescriptionService() {}
   std::string summaryDescription(
      const std::string& latitude, const std::string& longitude) const;

private:
   // ...
// END:PlaceDescriptionService
   std::string createGetRequestUrl(
      const std::string& latitude, const std::string& longitude) const;
   std::string summaryDescription(const Address& address) const;
   std::string keyValue(
      const std::string& key, const std::string& value) const;
   std::string get(const std::string& requestUrl) const;
   std::string summaryDescription(const std::string& response) const;

// START:PlaceDescriptionService
// START_HIGHLIGHT
   std::shared_ptr<Http> http_;
// END_HIGHLIGHT

protected:
   virtual std::shared_ptr<Http> httpService() const;
};
// END:PlaceDescriptionService

#endif
