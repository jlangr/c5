#include "gmock/gmock.h"

#include <vector>

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

class HttpStub: public Http {
public:
   MOCK_METHOD0(initialize, void());
   MOCK_CONST_METHOD1(get, string(const string&));
};

TEST_F(APlaceDescriptionService, MakesHttpRequestToObtainAddress) {
   HttpStub httpStub;
   string urlStart{
      "http://open.mapquestapi.com/nominatim/v1/reverse?format=json&"};
   auto expectedURL = urlStart + 
      "lat=" + APlaceDescriptionService::ValidLatitude + "&" +
      "lon=" + APlaceDescriptionService::ValidLongitude;
   EXPECT_CALL(httpStub, get(expectedURL));
   PlaceDescriptionService service{&httpStub};

   service.summaryDescription(ValidLatitude, ValidLongitude);
}

// START:FormatsRetrievedAddress
TEST_F(APlaceDescriptionService, FormatsRetrievedAddressIntoSummaryDescription) {
   HttpStub httpStub;
// START_HIGHLIGHT
   EXPECT_CALL(httpStub, get(_))
      .WillOnce(Return(
         R"({ "address": {
              "road":"Drury Ln",
              "city":"Fountain",
              "state":"CO",
              "country":"US" }})"));
// END_HIGHLIGHT
   PlaceDescriptionService service(&httpStub);

   auto description = service.summaryDescription(ValidLatitude, ValidLongitude);

   ASSERT_THAT(description, Eq("Drury Ln, Fountain, CO, US"));
}
// END:FormatsRetrievedAddress
