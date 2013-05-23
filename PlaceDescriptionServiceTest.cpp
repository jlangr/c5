#include "gmock/gmock.h"

#include <memory>

#include "PlaceDescriptionService.h"
#include "Http.h"

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
const string APlaceDescriptionService::ValidLatitude("38.005");
const string APlaceDescriptionService::ValidLongitude("-104.44");

// START:overrideFactoryMethodTestSetup
class PlaceDescriptionService_StubHttpService: public PlaceDescriptionService {
public:
   PlaceDescriptionService_StubHttpService(shared_ptr<HttpStub> httpStub) 
      : httpStub_{httpStub} {}
   shared_ptr<Http> httpService() const override { return httpStub_; }
   shared_ptr<Http> httpStub_;
};
// END:overrideFactoryMethodTestSetup

// START:MakesHttpRequest
TEST_F(APlaceDescriptionService, MakesHttpRequestToObtainAddress) {
   InSequence forceExpectationOrder;
// START_HIGHLIGHT
   shared_ptr<HttpStub> httpStub{new HttpStub};
// END_HIGHLIGHT
   string urlStart{
      "http://open.mapquestapi.com/nominatim/v1/reverse?format=json&"};
   auto expectedURL = urlStart + 
      "lat=" + APlaceDescriptionService::ValidLatitude + "&" +
      "lon=" + APlaceDescriptionService::ValidLongitude;
// START_HIGHLIGHT
   EXPECT_CALL(*httpStub, initialize());
   EXPECT_CALL(*httpStub, get(expectedURL));
   PlaceDescriptionService_StubHttpService service{httpStub};
// END_HIGHLIGHT

   service.summaryDescription(ValidLatitude, ValidLongitude);
}
// END:MakesHttpRequest

// START:FormatsRetrievedAddress
TEST_F(APlaceDescriptionService, FormatsRetrievedAddressIntoSummaryDescription) {
   shared_ptr<HttpStub> httpStub{new NiceMock<HttpStub>};
   EXPECT_CALL(*httpStub, get(_))
      .WillOnce(Return(
         R"({ "address": {
              "road":"Drury Ln",
              "city":"Fountain",
              "state":"CO",
              "country":"US" }})"));
   PlaceDescriptionService_StubHttpService service{httpStub};

   auto description = service.summaryDescription(ValidLatitude, ValidLongitude);

   ASSERT_THAT(description, Eq("Drury Ln, Fountain, CO, US"));
}
// END:FormatsRetrievedAddress
