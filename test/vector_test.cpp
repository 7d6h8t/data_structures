#include "vector.h"

#include <gtest/gtest.h>

#include <string>

namespace ds {
namespace {

class vectorTest : public testing::Test {
 protected:
  void SetUp() override {
    vec1_.reserve(4);
    vec1_.push_back(0);
    vec1_.push_back(1);
    vec1_.push_back(2);
    vec1_.push_back(3);
  }

  // void TearDown() override {}

  vector<int32_t> vec0_;
  vector<int32_t> vec1_;
  vector<int32_t> vec2_{0, 1, 2, 3, 4};
  vector<std::string> vec3_;
};  // vectorTest

TEST_F(vectorTest, IsEmptyInitially) {
  EXPECT_EQ(vec0_.size(), 0);
  EXPECT_TRUE(vec0_.empty());

  EXPECT_EQ(vec3_.size(), 0);
  EXPECT_TRUE(vec3_.empty());
}

TEST_F(vectorTest, ClearWorks) {
  vec0_.clear();
  EXPECT_EQ(vec0_.size(), 0);
  EXPECT_TRUE(vec0_.empty());

  vec2_.clear();
  EXPECT_EQ(vec2_.size(), 0);
  EXPECT_TRUE(vec2_.empty());
}

TEST_F(vectorTest, PushWorks) {
  vec0_.push_back(0);
  vec0_.push_back(1);
  vec0_.push_back(2);
  vec0_.push_back(3);
  vec0_.push_back(4);
  EXPECT_EQ(vec0_.size(), 5);

  vec2_.push_back(5);
  vec2_.push_back(6);
  EXPECT_EQ(vec2_.size(), 7);
  EXPECT_EQ(vec2_[1], 1);
  EXPECT_EQ(vec2_.front(), 0);
  EXPECT_EQ(vec2_.back(), 6);

  vec3_.push_back("hello");
  vec3_.push_back("world");
  vec3_.push_back("!");
  EXPECT_EQ(vec3_.size(), 3);
  EXPECT_EQ(vec3_[1], "world");
}

TEST_F(vectorTest, PopWorks) {
  vec1_.pop_back();
  vec1_.pop_back();
  EXPECT_EQ(vec1_.size(), 2);
  EXPECT_EQ(vec1_.back(), 1);

  vec2_.pop_back();
  vec2_.pop_back();
  vec2_.pop_back();
  EXPECT_EQ(vec2_.size(), 2);
  EXPECT_EQ(vec2_.back(), 1);
}

TEST_F(vectorTest, InsertWorks) {
  vec2_.insert(vec2_.end(), 5);
  for (auto itr = vec2_.begin(); itr != vec2_.end(); ++itr) {
    if (*itr == 1) {
      vec2_.insert(itr, 10);
      break;
    }
  }
  EXPECT_EQ(vec2_.size(), 7);
  EXPECT_EQ(vec2_.front(), 0);
  EXPECT_EQ(vec2_[1], 10);
}

TEST_F(vectorTest, EraseWorks) {
  vec1_.erase(vec1_.begin());
  for (auto itr = vec1_.begin(); itr != vec1_.end();) {
    if (*itr % 2 == 0)
      itr = vec1_.erase(itr);
    else
      ++itr;
  }

  EXPECT_EQ(vec1_.size(), 2);
  EXPECT_EQ(vec1_.back(), 3);
  EXPECT_EQ(vec1_[1], 3);
}

}  // namespace
}  // namespace ds