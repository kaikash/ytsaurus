#include "foobar.h"

void Bar(NYT::NConcurrency::IThreadPoolPtr& threadPool, int x) {
    if (x > 0) {
        Foo(threadPool, x - 1);
    }
    AsyncStop(threadPool);
    exit(0);
}
