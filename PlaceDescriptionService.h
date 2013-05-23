#ifndef PlaceDescriptionService_h
#define PlaceDescriptionService_h

#include <string>
#include <memory>
#include "Address.h"
#include "AddressExtractor.h"
#include "Http.h"

// START:PlaceDescriptionServiceTemplate
template<typename HTTP>
class PlaceDescriptionServiceTemplate {
public:
   // ...
// END:PlaceDescriptionServiceTemplate
   std::string summaryDescription(
         const std::string& latitude, const std::string& longitude) {
      auto request = createGetRequestUrl(latitude, longitude);
      auto response = get(request);
      return summaryDescription(response);
   }

// START:PlaceDescriptionServiceTemplate
   // mocks in tests need the reference
   HTTP& http() {
      return http_;
   }

private:
   // ...
// END:PlaceDescriptionServiceTemplate
   std::string summaryDescription(const std::string& response) const {
      AddressExtractor extractor;
      auto address = extractor.addressFrom(response);
      return address.summaryDescription();
   }

// START:PlaceDescriptionServiceTemplate
   std::string get(const std::string& url) {
      http_.initialize();
      return http_.get(url);
   }
   // ...
// END:PlaceDescriptionServiceTemplate

   std::string createGetRequestUrl(
         const std::string& latitude, const std::string& longitude) const {
      std::string server{"http://open.mapquestapi.com/"};
      std::string document{"nominatim/v1/reverse"};
      return server + document + "?" +
             keyValue("format", "json") + "&" +
             keyValue("lat", latitude) + "&" +
             keyValue("lon", longitude);
   }

   std::string keyValue(
         const std::string& key, const std::string& value) const {
      return key + "=" + value;
   }

// START:PlaceDescriptionServiceTemplate
   HTTP http_;
};

class Http;
typedef PlaceDescriptionServiceTemplate<Http> PlaceDescriptionService;
// END:PlaceDescriptionServiceTemplate

#endif
