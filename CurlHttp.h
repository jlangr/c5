#ifndef CurlHttp_h
#define CurlHttp_h

#include <curl/curl.h>
#include <string>

#include "Http.h"

class CurlHttp: public Http {
public:
   CurlHttp();
   virtual ~CurlHttp();

   void initialize();
   virtual std::string get(const std::string& url) const;
   static std::string Response();
   static size_t writeCallback(const char* buf, size_t size, size_t nMemb, void*);

private:
   CURL* curl;

   static std::string response_;
};

#endif
