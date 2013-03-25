#ifndef AddressExtractor_h
#define AddressExtractor_h

#include <json/reader.h>
#include <json/value.h>
#include <string>
#include "Address.h"

class AddressExtractor {
public:
   Address addressFrom(const std::string& json) const;

private:
   Json::Value jsonAddressFrom(const std::string& json) const;
   void populate(Address& address, Json::Value& jsonAddress) const;
   Json::Value parse(const std::string& json) const;
   std::string getString(Json::Value& result, const std::string& name) const;
};

#endif
