#include "gmock/gmock.h"

#include <vector>

#include "PlaceDescriptionService.h"
#include "stringutil.h"

using namespace std;
using namespace testing;

class APlaceDescriptionService: public Test {
public:
   static const string ValidLatitude;
   static const string ValidLongitude;

   PlaceDescriptionService* service;

   void SetUp() {
      service = new PlaceDescriptionService();
   }

   void TearDown() {
      delete service;
   }
};

const string APlaceDescriptionService::ValidLatitude("38.734311");
const string APlaceDescriptionService::ValidLongitude("-104.711332");

TEST_F(APlaceDescriptionService, FormatsRetrievedAddressIntoSummaryDescription) {
   string description = service->summaryDescription(ValidLatitude, ValidLongitude);

   ASSERT_THAT(description, Eq(
      "Drury Lane, Fountain, Colorado, United States of America"));
}

