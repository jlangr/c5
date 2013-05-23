#include "HttpFactory.h"
#include "CurlHttp.h"
#include <memory>

using namespace std;

HttpFactory::HttpFactory() {
   reset();
}

shared_ptr<Http> HttpFactory::get() {
   return instance;
}

void HttpFactory::reset() {
   instance = make_shared<CurlHttp>();
}

void HttpFactory::setInstance(shared_ptr<Http> newInstance) {
   instance = newInstance;
}

