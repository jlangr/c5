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

// START:HttpStub
class HttpStub: public Http {
   std::string get(const std::string& url) const {
      return "???";
   }
};
// END:HttpStub

// START:ReturnsSummaryDescriptionForValidLocation
TEST_F(APlaceDescriptionService, ReturnsCityDescriptionForValidLocation) {
   HttpStub httpStub;
   PlaceDescriptionService service(&httpStub);

   string description = service.summaryDescription(ValidLatitude, ValidLongitude);

   ASSERT_THAT(description, Eq("Drury Ln, Fountain, CO, US"));
}
// END:ReturnsCityDescriptionForValidLocation

