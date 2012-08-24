#include "gmock/gmock.h"

#include <vector>

#include "PlaceDescriptionService.h"
#include "Http.h"
#include "stringutil.h"

using namespace std;
using namespace testing;

class APlaceDescriptionService: public Test {
public:
   static const string ValidLatitude;
   static const string ValidLongitude;
};

const string APlaceDescriptionService::ValidLatitude("38.005");
const string APlaceDescriptionService::ValidLongitude("-104.44");

// START:returnURL
class HttpStub: public Http {
// START_HIGHLIGHT
public:
   string returnURL;
// END_HIGHLIGHT
   string get(const string& url) const {
      verify(url);
// START_HIGHLIGHT
      return returnURL;
// END_HIGHLIGHT
   }

   // ...
// END:returnURL
   void verify(const string& url) const {
      string urlStart(
         "http://open.mapquestapi.com/nominatim/v1/reverse?format=json&");
      string expected(urlStart + 
            "lat=" + APlaceDescriptionService::ValidLatitude + "&" +
            "lon=" + APlaceDescriptionService::ValidLongitude);
      ASSERT_THAT(url, Eq(expected));
   }
// START:returnURL
};

// START:ReturnsDescriptionForValidLocation
TEST_F(APlaceDescriptionService, ReturnsDescriptionForValidLocation) {
   HttpStub httpStub;
// START_HIGHLIGHT
   httpStub.returnURL =
      stringutil::ticToQuote("{ 'address': {\
              'road':'Drury Ln',\
              'city':'Fountain',\
              'state':'CO',\
              'country':'US' }}");
// END_HIGHLIGHT

   PlaceDescriptionService service(&httpStub);

   string description = service.summaryDescription(ValidLatitude, ValidLongitude);

   ASSERT_THAT(description, Eq("Drury Ln, Fountain, CO, US"));
}
// END:ReturnsCityDescriptionForValidLocation
// END:returnURL

