#include "LocationLookup.h"
#include "Http.h"
#include "AddressExtractor.h"
#include <string>

using namespace std;

LocationLookup::LocationLookup(Http* http) : http_(http) {}

string LocationLookup::summaryDescription(
      const string& latitude, const string& longitude) const {
   //throw InvalidLocationException();

   if (!http_) return "";

   string jsonResponse = http_->get(getUrl(latitude, longitude));

   AddressExtractor extractor;
   Address address = extractor.addressFrom(jsonResponse);

   return format(address);
}

string LocationLookup::getUrl(
      const string& latitude, const string& longitude) const {
   string server = "http://open.mapquestapi.com/";
   string document = "nominatim/v1/reverse";
   return server + document + "?" + 
      keyValue("format", "json") + "&" + 
      keyValue("lat", latitude) + "&" + 
      keyValue("lon", longitude); 
}

string LocationLookup::keyValue(const string& key, const string& value) const {
   return key + "=" + value;
}

string LocationLookup::format(const Address& address) const {
   return address.road + ", " + address.city + ", " + 
          address.state + ", " + address.country;
}

