#include "gmock/gmock.h"

#include <memory>

#include "PlaceDescriptionService.h"
#include "Http.h"
// START_HIGHLIGHT
#include "HttpFactory.h"
// END_HIGHLIGHT

using namespace std;
using namespace testing;

class HttpStub: public Http {
public:
   MOCK_METHOD0(initialize, void());
   MOCK_CONST_METHOD1(get, string(const string&));
};

class APlaceDescriptionService: public Test {
public:
   static const string ValidLatitude;
   static const string ValidLongitude;
};

// START:fixture
class APlaceDescriptionService_WithHttpMock: public APlaceDescriptionService {
public:
   PlaceDescriptionServiceTemplate<HttpStub> service;
};
// END:fixture

// START:test
TEST_F(APlaceDescriptionService_WithHttpMock, MakesHttpRequestToObtainAddress) {
   string urlStart{
      "http://open.mapquestapi.com/nominatim/v1/reverse?format=json&"};
   auto expectedURL = urlStart + 
      "lat=" + APlaceDescriptionService::ValidLatitude + "&" +
      "lon=" + APlaceDescriptionService::ValidLongitude;
// START_HIGHLIGHT
   EXPECT_CALL(service.http(), initialize());
   EXPECT_CALL(service.http(), get(expectedURL));
// END_HIGHLIGHT

   service.summaryDescription(ValidLatitude, ValidLongitude);
}
// END:test

class APlaceDescriptionService_WithNiceHttpMock: 
   public APlaceDescriptionService {
public:
   PlaceDescriptionServiceTemplate<NiceMock<HttpStub>> service;
};

TEST_F(APlaceDescriptionService_WithNiceHttpMock, 
      FormatsRetrievedAddressIntoSummaryDescription) {
   EXPECT_CALL(service.http(), get(_))
      .WillOnce(Return(
         R"({ "address": {
              "road":"Drury Ln",
              "city":"Fountain",
              "state":"CO",
              "country":"US" }})"));

   auto description = service.summaryDescription(ValidLatitude, ValidLongitude);

   ASSERT_THAT(description, Eq("Drury Ln, Fountain, CO, US"));
}

const string APlaceDescriptionService::ValidLatitude("38.005");
const string APlaceDescriptionService::ValidLongitude("-104.44");
