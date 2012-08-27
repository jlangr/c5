#ifndef PlaceDescriptionService_h
#define PlaceDescriptionService_h

#include <string>
#include "Address.h"
#include <curl/curl.h>
#include <json/reader.h>
#include <json/value.h>

class PlaceDescriptionService {
public:
   PlaceDescriptionService();
   ~PlaceDescriptionService() {
      curl_global_cleanup();
   }
   std::string summaryDescription(
      const std::string& latitude, const std::string& longitude) const;
   static size_t writeCallback(const char* buf, size_t size, size_t nMemb, void*);

private:
   std::string createGetRequestUrl(
      const std::string& latitude, const std::string& longitude) const;
   std::string summaryDescription(const Address& address) const;
   std::string keyValue(
      const std::string& key, const std::string& value) const;
   std::string getString(Json::Value& result, const std::string& name) const;

   CURL* curl;
   static std::string response_;
};

#endif
