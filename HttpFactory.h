#ifndef HttpFactory_h
#define HttpFactory_h

#include <memory>
#include "Http.h"

class HttpFactory {
public:
   HttpFactory();
   std::shared_ptr<Http> get();
   void setInstance(std::shared_ptr<Http>);
   void reset();

private:
   std::shared_ptr<Http> instance;
};
#endif
