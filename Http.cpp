#include "Http.h"

#include <string>

using namespace std;

string Http::response_;

Http::Http() : curl(NULL) {
   curl_global_init(CURL_GLOBAL_ALL);
   curl = curl_easy_init();

   curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &Http::writeCallback);
}

Http::~Http() {
   curl_global_cleanup();
}

string Http::get(const string& url) const {
   response_ = "invalid request"; // TODO test
   curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
   curl_easy_perform(curl);
   curl_easy_cleanup(curl);
   
   return Http::Response();
}

string Http::Response() {
   return response_;
}

size_t Http::writeCallback(const char* buf, size_t size, size_t nMemb, void*) {
   for (int i = 0; i < size * nMemb; i++) 
      response_.push_back(buf[i]);
   return size * nMemb;
}

