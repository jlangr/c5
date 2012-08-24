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

// START:expectationURL
class HttpStub: public Http {
public:
   string returnResponse;
// START_HIGHLIGHT
   string expectedURL;
// END_HIGHLIGHT

   string get(const string& url) const {
      verify(url);
      return returnResponse;
   }

   void verify(const string& url) const {
// START_HIGHLIGHT
      ASSERT_THAT(url, Eq(expectedURL));
// END_HIGHLIGHT
   }
};

TEST_F(APlaceDescriptionService, ReturnsDescriptionForValidLocation) {
   HttpStub httpStub;
   httpStub.returnResponse = // ...
// END:expectationURL
      stringutil::ticToQuote("{ 'address': {\
              'road':'Drury Ln',\
              'city':'Fountain',\
              'state':'CO',\
              'country':'US' }}");
// START:expectationURL
// START_HIGHLIGHT
   string urlStart(
      "http://open.mapquestapi.com/nominatim/v1/reverse?format=json&");
   httpStub.expectedURL = urlStart + 
         "lat=" + APlaceDescriptionService::ValidLatitude + "&" +
         "lon=" + APlaceDescriptionService::ValidLongitude;
// END_HIGHLIGHT

   PlaceDescriptionService service(&httpStub);

   string description = service.summaryDescription(ValidLatitude, ValidLongitude);

   ASSERT_THAT(description, Eq("Drury Ln, Fountain, CO, US"));
}
// END:expectationURL

