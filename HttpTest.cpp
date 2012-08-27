#include "gmock/gmock.h"
#include <string>
#include "Http.h"

using namespace std;
using namespace ::testing;

TEST(Http, WriteCallback) {
   string buffer("123456789012");
   size_t size(12);
   size_t numberOfMembers(1);
   Http::writeCallback("123456789012", size, numberOfMembers, NULL);
   ASSERT_THAT(Http::Response(), Eq("123456789012"));
}

TEST(HttpIntegration, Get) {
   Http http;
   string response = http.get("http://langrsoft.com");
   ASSERT_THAT(response, HasSubstr("Jeff Langr"));
}

