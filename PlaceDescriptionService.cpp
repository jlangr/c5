#include "PlaceDescriptionService.h"
#include "Http.h"
#include "AddressExtractor.h"
#include "Address.h"
#include <string>

using namespace std;

// START:ctor
PlaceDescriptionService::PlaceDescriptionService(Http* http) 
   : http_(http) {
}
// END:ctor

// START:summaryDescription
string PlaceDescriptionService::summaryDescription(
      const string& latitude, const string& longitude) const {
   string jsonResponse = http_->get(createGetRequestUrl(latitude, longitude));

   AddressExtractor extractor;
   Address address = extractor.addressFrom(jsonResponse);

   return summaryDescription(address);
}
// END:summaryDescription

string PlaceDescriptionService::createGetRequestUrl(
      const string& latitude, const string& longitude) const {
   return "http://example.com/request/TODO";
}

string PlaceDescriptionService::summaryDescription(const Address& address) const {
   return address.road + ", " + address.city + ", " + 
          address.state + ", " + address.country;
}

