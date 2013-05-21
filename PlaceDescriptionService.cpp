#include "PlaceDescriptionService.h"
#include "Http.h"
#include "AddressExtractor.h"
#include "Address.h"
#include <string>

using namespace std;

// START:ctor
PlaceDescriptionService::PlaceDescriptionService(Http* http) : http_(http) {}
// END:ctor

// START:summaryDescription
string PlaceDescriptionService::summaryDescription(
      const string& latitude, const string& longitude) const {
   auto getRequestUrl = "lat=" + latitude + "&lon=" + longitude; 
   auto jsonResponse = http_->get(getRequestUrl);

   AddressExtractor extractor;
   auto address = extractor.addressFrom(jsonResponse);
   return address.road + ", " + address.city + ", " + 
          address.state + ", " + address.country;
}
// END:summaryDescription

