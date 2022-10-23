#include "../third-party/ctest/ctest.h"

CTEST(suite, simple)
{
    ASSERT_STR("foo", "foo");
}
