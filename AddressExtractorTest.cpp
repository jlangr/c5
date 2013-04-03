#include "gmock/gmock.h"
#include "AddressExtractor.h"

#include <algorithm>
#include <string>

using namespace std;
using namespace testing;

class AnAddressExtractor: public Test {
public:
   AddressExtractor extractor;
};

MATCHER(IsEmpty, "") {
   return 
      arg.road.empty() &&
      arg.city.empty() &&
      arg.state.empty() &&
      arg.country.empty();
}

TEST_F(AnAddressExtractor, ReturnsAnEmptyAddressOnAFailedParse) {
   auto address = extractor.addressFrom("not valid json");

   ASSERT_THAT(address, IsEmpty());
}

TEST_F(AnAddressExtractor, ReturnsAnEmptyAddressWhenNoAddressFound) {
   auto json = R"({ "place_id":"15331615" })";

   auto address = extractor.addressFrom(json);

   ASSERT_THAT(address, IsEmpty());
}

TEST_F(AnAddressExtractor, ReturnsPopulatedAddressForValidJsonResult) {
   auto json = R"({
         "place_id":"15331615",
         "address":{
            "road":"War Eagle Court",
            "city":"Colorado Springs",
            "state":"Colorado",
            "country":"United States of America",
         }
      })";

   auto address = extractor.addressFrom(json);

   ASSERT_THAT(address.road, Eq("War Eagle Court"));
   ASSERT_THAT(address.city, Eq("Colorado Springs"));
   ASSERT_THAT(address.state, Eq("Colorado"));
   ASSERT_THAT(address.country, Eq("United States of America"));
}

TEST_F(AnAddressExtractor, DefaultsNonexistentFieldsToEmpty) {
   auto json = R"({
         "address":{
            "road":"War Eagle Court",
            "city":"Colorado Springs",
            "country":"United States of America" }})";

   auto address = extractor.addressFrom(json);

   ASSERT_THAT(address.state, Eq(""));
}

