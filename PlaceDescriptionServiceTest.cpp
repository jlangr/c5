#include "gmock/gmock.h"

#include <vector>

#include "PlaceDescriptionService.h"
#include "Http.h"
#include "stringutil.h"

using namespace std;
using namespace testing;

class HttpStub: public Http {
public:
   MOCK_CONST_METHOD1(get, string(const string&));
};

class APlaceDescriptionService: public Test {
public:
   static const string ValidLatitude;
   static const string ValidLongitude;

   HttpStub httpStub;
   PlaceDescriptionService* service;

   void SetUp() {
      service = new PlaceDescriptionService(&httpStub);
   }

   void TearDown() {
      delete service;
   }
};

const string APlaceDescriptionService::ValidLatitude("38.005");
const string APlaceDescriptionService::ValidLongitude("-104.44");

TEST_F(APlaceDescriptionService, MakesHttpRequestToObtainAddress) {
   string expectedURL(
      string("http://open.mapquestapi.com/nominatim/v1/reverse?format=json&") +
      "lat=" + APlaceDescriptionService::ValidLatitude + 
      "&lon=" + APlaceDescriptionService::ValidLongitude);
   EXPECT_CALL(httpStub, get(expectedURL));

   service->summaryDescription(ValidLatitude, ValidLongitude);
}

TEST_F(APlaceDescriptionService, FormatsRetrievedAddressIntoSummaryDescription) {
   EXPECT_CALL(httpStub, get(_))
      .WillOnce(Return(
         stringutil::ticToQuote("{ 'address': {\
                                   'road':'Drury Ln',\
                                   'city':'Fountain',\
                                   'state':'CO',\
                                   'country':'US' }}")));

   string description = service->summaryDescription(ValidLatitude, ValidLongitude);

   ASSERT_THAT(description, Eq("Drury Ln, Fountain, CO, US"));
}

