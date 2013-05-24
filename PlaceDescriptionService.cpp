#include "PlaceDescriptionService.h"
#include "Http.h"
#include "AddressExtractor.h"
#include "Address.h"
#include "CurlHttp.h"
#include <string>

using namespace std;

// START:PlaceDescriptionService
PlaceDescriptionService::PlaceDescriptionService() 
   : http_{make_shared<CurlHttp>()} {}
// ...
// END:PlaceDescriptionService

string PlaceDescriptionService::summaryDescription(
      const string& latitude, const string& longitude) const {
   auto request = createGetRequestUrl(latitude, longitude);
   auto response = get(request);
   return summaryDescription(response);
}

string PlaceDescriptionService::summaryDescription(
      const string& response) const {
   AddressExtractor extractor;
   auto address = extractor.addressFrom(response);
   return address.summaryDescription();
}

string PlaceDescriptionService::get(const string& url) const {
   auto http = httpService();
   http->initialize();
   return http->get(url);
}

// START:PlaceDescriptionService
shared_ptr<Http> PlaceDescriptionService::httpService() const {
// START_HIGHLIGHT
   return http_;
// END_HIGHLIGHT
}
// END:PlaceDescriptionService

string PlaceDescriptionService::createGetRequestUrl(
      const string& latitude, const string& longitude) const {
   string server{"http://open.mapquestapi.com/"};
   string document{"nominatim/v1/reverse"};
   return server + document + "?" +
          keyValue("format", "json") + "&" +
          keyValue("lat", latitude) + "&" +
          keyValue("lon", longitude);
}

string PlaceDescriptionService::keyValue(
      const string& key, const string& value) const {
   return key + "=" + value;
}

