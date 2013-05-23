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

class HttpStub: public Http {
public:
   MOCK_METHOD0(initialize, void());
   MOCK_CONST_METHOD1(get, string(const string&));
};

// START:MakesHttpRequest
TEST_F(APlaceDescriptionService, MakesHttpRequestToObtainAddress) {
// START_HIGHLIGHT
   InSequence forceExpectationOrder;
// END_HIGHLIGHT
   HttpStub httpStub;
   string urlStart{
      "http://open.mapquestapi.com/nominatim/v1/reverse?format=json&"};
   auto expectedURL = urlStart + 
      "lat=" + APlaceDescriptionService::ValidLatitude + "&" +
      "lon=" + APlaceDescriptionService::ValidLongitude;
   EXPECT_CALL(httpStub, initialize());
   EXPECT_CALL(httpStub, get(expectedURL));
   PlaceDescriptionService service{&httpStub};

   service.summaryDescription(ValidLatitude, ValidLongitude);
}
// END:MakesHttpRequest

// START:FormatsRetrievedAddress
TEST_F(APlaceDescriptionService, FormatsRetrievedAddressIntoSummaryDescription) {
   NiceMock<HttpStub> httpStub;
   EXPECT_CALL(httpStub, get(_))
      .WillOnce(Return(
         R"({ "address": {
              "road":"Drury Ln",
              "city":"Fountain",
              "state":"CO",
              "country":"US" }})"));
   PlaceDescriptionService service(&httpStub);

   auto description = service.summaryDescription(ValidLatitude, ValidLongitude);

   ASSERT_THAT(description, Eq("Drury Ln, Fountain, CO, US"));
}
// END:FormatsRetrievedAddress
