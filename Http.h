#ifndef Http_h
#define Http_h

#include <string>
#include <curl/curl.h>

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

   static std::string response_;
};

#endif
