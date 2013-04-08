#ifndef Http_h
#define Http_h

#include <string>

class Http {
public:
// START:publicInterface
   virtual ~Http() {}
   virtual void initialize() = 0;
   virtual std::string get(const std::string& url) const = 0;
// END:publicInterface
};

#endif
