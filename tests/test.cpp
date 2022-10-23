#include "../third-party/ctest/ctest.h"

CTEST(suite, test1) {
    ASSERT_STR("foo", "foo");
}
