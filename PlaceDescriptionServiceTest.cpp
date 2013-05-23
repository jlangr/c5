#include "gmock/gmock.h"

#include <memory>

#include "PlaceDescriptionService.h"
//#include "Http.h"

using namespace std;
using namespace testing;

class APlaceDescriptionService: public Test {
public:
   static const string ValidLatitude;
   static const string ValidLongitude;

   PlaceDescriptionService* service;

   void SetUp() override {
      service = new PlaceDescriptionService();
   }

   void TearDown() override {
      delete service;
   }
};

const string APlaceDescriptionService::ValidLatitude("38.734311");
const string APlaceDescriptionService::ValidLongitude("-104.711332");

TEST_F(APlaceDescriptionService, FormatsRetrievedAddressIntoSummaryDescription) {
   auto description = service->summaryDescription(ValidLatitude, ValidLongitude);

   ASSERT_THAT(description, Eq(
      "Drury Lane, Widefield, Colorado, United States of America"));
}

