#include "AddressExtractor.h"

#include <string>

using namespace std;
using namespace Json;

Address AddressExtractor::addressFrom(const string& json) const {
   Address address;
   populate(address, jsonAddressFrom(json));
   return address; 
}

Value AddressExtractor::jsonAddressFrom(const string& json) const {
   Value location = parse(json);
   return location.get("address", Value::null);
}

// && rvalue reference thing--sidebar!
void AddressExtractor::populate(Address& address, Value&& jsonAddress) const {
   address.road = getString(jsonAddress, "road");
   address.city = getString(jsonAddress, "city");
   address.state = getString(jsonAddress, "state");
   address.country = getString(jsonAddress, "country");
}

Value AddressExtractor::parse(const string& json) const {
   Value root;
   Reader reader;
   reader.parse(json, root);
   return root; 
}

string AddressExtractor::getString(Value& result, const string& name) const {
   return result.get(name, "").asString();
}

