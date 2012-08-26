#include "PlaceDescriptionService.h"
#include "Http.h"
#include "AddressExtractor.h"
#include "Address.h"
#include <string>

using namespace std;

PlaceDescriptionService::PlaceDescriptionService(Http* http) 
   : http_(http) {
}

// START:summaryDescription
string PlaceDescriptionService::summaryDescription(
      const string& latitude, const string& longitude) const {
   http_->get(createGetRequestUrl(latitude, longitude));
   return "";
}
// END:summaryDescription

string PlaceDescriptionService::summaryDescription(const Address& address) const {
   return address.road + ", " + address.city + ", " + 
          address.state + ", " + address.country;
}

string PlaceDescriptionService::createGetRequestUrl(
      const string& latitude, const string& longitude) const {
   string server = "http://open.mapquestapi.com/";
   string document = "nominatim/v1/reverse";
   return server + document + "?" + 
      keyValue("format", "json") + "&" + 
      keyValue("lat", latitude) + "&" + 
      keyValue("lon", longitude); 
}

string PlaceDescriptionService::keyValue(
      const string& key, const string& value) const {
   return key + "=" + value;
}

