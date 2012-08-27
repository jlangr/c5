#include "PlaceDescriptionService.h"
#include "AddressExtractor.h"
#include "Address.h"
#include <string>

using namespace std;
using namespace Json;

string PlaceDescriptionService::response_("");

PlaceDescriptionService::PlaceDescriptionService() 
   : curl(NULL) {
   curl_global_init(CURL_GLOBAL_ALL);
   curl = curl_easy_init();
   curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &PlaceDescriptionService::writeCallback);
}

size_t PlaceDescriptionService::writeCallback(const char* buf, size_t size, size_t nMemb, void*) {
   for (int i = 0; i < size * nMemb; i++) 
      response_.push_back(buf[i]);
   return size * nMemb;
}

// START:summaryDescriptionTopDown
string PlaceDescriptionService::summaryDescription(
      const string& latitude, const string& longitude) const {
   // retrieve JSON response via API
   response_ = "";
   string url = createGetRequestUrl(latitude, longitude);
   curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
   curl_easy_perform(curl);
   curl_easy_cleanup(curl);

   // parse json response
   Value location;
   Reader reader;
   reader.parse(response_, location);
   Value jsonAddress = location.get("address", Value::null);

   // populate address from json
   Address address;
   address.road = jsonAddress.get("road", "").asString();
   address.city = jsonAddress.get("city", "").asString();
   address.state = jsonAddress.get("state", "").asString();
   address.country = jsonAddress.get("country", "").asString();

   return address.road + ", " + address.city + ", " + 
          address.state + ", " + address.country;
}
// END:summaryDescriptionTopDown

string PlaceDescriptionService::getString(Value& result, const string& name) const {
   return result.get(name, "").asString();
}

string PlaceDescriptionService::summaryDescription(const Address& address) const {
   return address.road + ", " + address.city + ", " + 
          address.state + ", " + address.country;
}

string PlaceDescriptionService::createGetRequestUrl(
      const string& latitude, const string& longitude) const {
   string server = "http://open.mapquestapi.com/";
   string document = "nominatim/v1/reverse";
   return server + document + "?" + 
      keyValue("format", "json") + "&" + 
      keyValue("lat", latitude) + "&" + 
      keyValue("lon", longitude); 
}

string PlaceDescriptionService::keyValue(
      const string& key, const string& value) const {
   return key + "=" + value;
}

