#include "PlaceDescriptionService.h"
#include "Http.h"
#include "AddressExtractor.h"
#include "Address.h"
#include <string>

using namespace std;

PlaceDescriptionService::PlaceDescriptionService(Http* http) : http_(http) {}

// START:emptySummaryDescription
string PlaceDescriptionService::summaryDescription(
      const string& latitude, const string& longitude) const {
   return "";
}
// END:emptySummaryDescription

