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
public:
// START_HIGHLIGHT
   MOCK_CONST_METHOD1(get, string(const string&));
// END_HIGHLIGHT
};
// END:HttpStub

// START:MakesHttpRequest
TEST_F(APlaceDescriptionService, MakesHttpRequestToObtainAddress) {
   HttpStub httpStub;
   string urlStart(
      "http://open.mapquestapi.com/nominatim/v1/reverse?format=json&");
   string expectedURL = urlStart + 
         "lat=" + APlaceDescriptionService::ValidLatitude + "&" +
         "lon=" + APlaceDescriptionService::ValidLongitude;
// START_HIGHLIGHT
   EXPECT_CALL(httpStub, get(expectedURL));
// END_HIGHLIGHT
   PlaceDescriptionService service(&httpStub);

   service.summaryDescription(ValidLatitude, ValidLongitude);
}
// END:MakesHttpRequest

class Updater {
public:
// START:SecondExampleIF
   virtual void add(const string& key, const string& value) { throw 1; }
// END:SecondExampleIF
};

class UpdaterMock: public Updater {
public:
// START:SecondExampleMock
   MOCK_METHOD2(add, void(const string&, const string&));
// END:SecondExampleMock
};

TEST(Mock, Works) {
   UpdaterMock updater;
   EXPECT_CALL(updater, add(_,_));
   updater.add("", "");
}

