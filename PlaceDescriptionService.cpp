#include "PlaceDescriptionService.h"
#include "Http.h"
#include "AddressExtractor.h"
#include "Address.h"
// START:overrideFactoryMethod
#include "CurlHttp.h"
// END:overrideFactoryMethod
#include <string>

using namespace std;

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

// START:overrideFactoryMethod
string PlaceDescriptionService::get(const string& url) const {
// START_HIGHLIGHT
   auto http = httpService();
   http->initialize();
   return http->get(url);
// END_HIGHLIGHT
}

// START_HIGHLIGHT
shared_ptr<Http> PlaceDescriptionService::httpService() const {
   return make_shared<CurlHttp>();
}
// END_HIGHLIGHT
// END:overrideFactoryMethod

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

