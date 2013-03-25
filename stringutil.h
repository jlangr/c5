#ifndef stringutil_h
#define stringutil_h

#include <string>
#include <algorithm>

namespace stringutil {
   inline std::string ticToQuote(const std::string& text) {
      std::string copy(text);
      std::replace(copy.begin(), copy.end(), '\'', '"');
      return copy;
   }
}

#endif
