#include "PlaceDescriptionService.h"
#include "Http.h"
#include "AddressExtractor.h"
#include "Address.h"
#include <string>

using namespace std;

PlaceDescriptionService::PlaceDescriptionService(Http* http) : http_(http) {}

// START:summaryDescription
string PlaceDescriptionService::summaryDescription(
      const string& latitude, const string& longitude) const {
   string server{"http://open.mapquestapi.com/"};
   string document{"nominatim/v1/reverse"};
   string url = server + document + "?" +
                keyValue("format", "json") + "&" +
                keyValue("lat", latitude) + "&" +
                keyValue("lon", longitude);
// START_HIGHLIGHT
   auto response = http_->get(url);
// END_HIGHLIGHT

// START_HIGHLIGHT
   AddressExtractor extractor;
   auto address = extractor.addressFrom(response);
   return address.summaryDescription();
// END_HIGHLIGHT
}
// END:summaryDescription

string PlaceDescriptionService::keyValue(
      const string& key, const string& value) const {
   return key + "=" + value;
}

