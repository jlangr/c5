#include "gmock/gmock.h"

#include "PlaceDescriptionService.h"
#include "Http.h"

using namespace std;
using namespace testing;

class APlaceDescriptionService: public Test {
public:
   static const string ValidLatitude;
   static const string ValidLongitude;
};

const string APlaceDescriptionService::ValidLatitude("38.005");
const string APlaceDescriptionService::ValidLongitude("-104.44");

// START:HttpStub
class HttpStub: public Http {
   void initialize() override {}
   std::string get(const std::string& url) const override {
// START_HIGHLIGHT
      verify(url);
// END_HIGHLIGHT
      return R"({ "address": {
         "road":"Drury Ln",
         "city":"Fountain",
         "state":"CO",
         "country":"US" }})";
   }

// START:verify
   void verify(const string& url) const {
// START_HIGHLIGHT
      string urlStart(
         "http://open.mapquestapi.com/nominatim/v1/reverse?format=json&");
// END_HIGHLIGHT
// START_HIGHLIGHT
      string expected(urlStart + 
// END_HIGHLIGHT
         "lat=" + APlaceDescriptionService::ValidLatitude + "&" +
         "lon=" + APlaceDescriptionService::ValidLongitude);
// START_HIGHLIGHT
      ASSERT_THAT(url, Eq(expected));
// END_HIGHLIGHT
   }
// END:verify
};
// END:HttpStub

// START:ReturnsDescriptionForValidLocation
TEST_F(APlaceDescriptionService, ReturnsDescriptionForValidLocation) {
   HttpStub httpStub;
   PlaceDescriptionService service{&httpStub};

   auto description = service.summaryDescription(ValidLatitude, ValidLongitude);

   ASSERT_THAT(description, Eq("Drury Ln, Fountain, CO, US"));
}
// END:ReturnsCityDescriptionForValidLocation

