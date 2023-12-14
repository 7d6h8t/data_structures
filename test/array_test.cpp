#include "array.h"

#include <gtest/gtest.h>

namespace ds {
namespace {

class arrayTest : public testing::Test {
 protected:
  void SetUp() override {
    for (std::size_t i = 0; i < arr1_.size(); ++i) arr1_[i] = i;
  }

  // void TearDown() override {}

  array<int32_t, 5> arr0_;
  array<int32_t, 5> arr1_;
  array<int32_t, 5> arr2_{0, 1, 2, 3, 5};
};  // arrayTest

TEST_F(arrayTest, IsEmptyInitially) { EXPECT_NE(arr0_.size(), 0); }

TEST_F(arrayTest, CompareWorks) {
  EXPECT_FALSE(arr1_ == arr2_);
  EXPECT_TRUE((arr1_ <=> arr2_) == std::weak_ordering::less);
  EXPECT_FALSE((arr1_ <=> arr2_) == std::weak_ordering::greater);
  EXPECT_FALSE((arr1_ <=> arr2_) == std::weak_ordering::equivalent);

  arr2_[4] = 4;
  EXPECT_TRUE((arr1_ <=> arr2_) == std::weak_ordering::equivalent);
  EXPECT_TRUE(arr1_ == arr2_);
}

}  // namespace
}  // namespace ds