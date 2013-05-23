#include "PlaceDescriptionService.h"
#include "Http.h"
#include "AddressExtractor.h"
#include "Address.h"
#include "HttpFactory.h"
#include <string>

using namespace std;

PlaceDescriptionService::PlaceDescriptionService(shared_ptr<HttpFactory> httpFactory) 
   : httpFactory_{httpFactory} {}

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

// START:get
string PlaceDescriptionService::get(const string& url) const {
// START_HIGHLIGHT
   auto http = httpFactory_->get();
// END_HIGHLIGHT
   http->initialize();
   return http->get(url);
}
// END:get

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

