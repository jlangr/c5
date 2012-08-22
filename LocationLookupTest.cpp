#include "gmock/gmock.h"

#include <vector>

#include "LocationLookup.h"
#include "Http.h"
#include "stringutil.h"

using namespace std;
using namespace testing;

class ALocationLookup: public Test {
public:
   static const string ValidLatitude;
   static const string ValidLongitude;
};

const string ALocationLookup::ValidLatitude("38.005");
const string ALocationLookup::ValidLongitude("-104.44");

TEST_F(ALocationLookup, DISABLED_ThrowsForInvalidCoordinates) {
   LocationLookup lookup(NULL);

   string latitudeOutOfRange("91");
   ASSERT_THROW(lookup.summaryDescription(latitudeOutOfRange, "0"), InvalidLocationException);
}

// START:HttpStub
class HttpStub: public Http {
   std::string get(const std::string& url) const {
      return stringutil::ticToQuote("{ 'address': {\
              'road':'Drury Ln',\
              'city':'Fountain',\
              'state':'CO',\
              'country':'US' }}");
   }
};
// END:HttpStub

// START:ReturnsSummaryDescriptionForValidLocation
TEST_F(ALocationLookup, ReturnsCityDescriptionForValidLocation) {
   HttpStub httpStub;
   LocationLookup lookup(&httpStub);

   string description = lookup.summaryDescription(ValidLatitude, ValidLongitude);

   ASSERT_THAT(description, Eq("Drury Ln, Fountain, CO, US"));
}
// END:ReturnsCityDescriptionForValidLocation

