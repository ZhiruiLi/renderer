#include "gtest/gtest.h"

#define ASSERT_ARRAY_EQ(x, y, len)                                  \
  for (int i = 0; i < len; ++i) {                                   \
    ASSERT_EQ(x[i], y[i]) << "array x and y differ at index " << i; \
  }
