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
// START_HIGHLIGHT
   auto getRequestUrl = "lat=" + latitude + "&lon=" + longitude;
// END_HIGHLIGHT
   auto jsonResponse = http_->get(getRequestUrl);
   // ...
// END:summaryDescription

   AddressExtractor extractor;
   auto address = extractor.addressFrom(jsonResponse);
   return address.road + ", " + address.city + ", " + 
          address.state + ", " + address.country;
// START:summaryDescription
}
// END:summaryDescription

