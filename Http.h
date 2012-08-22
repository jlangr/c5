#ifndef Http_h
#define Http_h

#include <string>

#include <json/reader.h>
#include <json/value.h>

#include <curl/curl.h>

using namespace std;

class Http {
public:
   Http();
   virtual ~Http();

// START:publicInterface
   virtual std::string get(const std::string& url) const;
// END:publicInterface

   static std::string Response();
   static size_t writeCallback(const char* buf, size_t size, size_t nMemb, void*);

private:
   CURL* curl;

   static string response_;
};

#endif
