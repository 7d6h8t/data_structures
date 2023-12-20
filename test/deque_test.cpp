#include "deque.h"

#include <gtest/gtest.h>

namespace ds {
namespace {

class dequeTest : public testing::Test {
 protected:
  void SetUp() override {
    deq1_.push_back(0);
    deq1_.push_back(1);
    deq1_.push_back(2);
    deq1_.push_back(3);
  }

  // void TearDown() override {}

  deque<int32_t> deq0_;
  deque<int32_t> deq1_;
  deque<int32_t> deq2_{0, 1, 2, 3, 4};
  deque<std::string> deq3_;
};  // arrayTest

TEST_F(dequeTest, IsEmptyInitially) {
  EXPECT_EQ(deq0_.size(), 0);
  EXPECT_TRUE(deq0_.empty());

  EXPECT_EQ(deq3_.size(), 0);
  EXPECT_TRUE(deq3_.empty());
}

TEST_F(dequeTest, ClearWorks) {
  deq0_.clear();
  EXPECT_EQ(deq0_.size(), 0);
  EXPECT_TRUE(deq0_.empty());

  deq2_.clear();
  EXPECT_EQ(deq2_.size(), 0);
  EXPECT_TRUE(deq2_.empty());
}

TEST_F(dequeTest, PushWorks) {
  deq0_.push_front(3);
  deq0_.push_front(2);
  deq0_.push_front(1);
  deq0_.push_back(4);
  deq0_.push_back(5);
  deq0_.push_back(6);
  deq0_.push_front(0);
  EXPECT_EQ(deq0_.size(), 7);

  deq2_.push_back(5);
  deq2_.push_back(6);
  deq2_.push_front(11);
  deq2_.push_front(10);

  EXPECT_EQ(deq2_.size(), 9);
  EXPECT_EQ(deq2_[1], 11);
  EXPECT_EQ(deq2_.front(), 10);
  EXPECT_EQ(deq2_.back(), 6);

  deq3_.push_back("hello");
  deq3_.push_back("world");
  deq3_.push_back("!");
  EXPECT_EQ(deq3_.size(), 3);
  EXPECT_EQ(deq3_[1], "world");
}

TEST_F(dequeTest, PopWorks) {
  deq1_.pop_back();
  deq1_.pop_back();
  EXPECT_EQ(deq1_.size(), 2);
  EXPECT_EQ(deq1_.back(), 1);

  deq2_.pop_back();
  deq2_.pop_front();
  deq2_.pop_front();
  EXPECT_EQ(deq2_.size(), 2);
  EXPECT_EQ(deq2_.front(), 2);
}

}  // namespace
}  // namespace ds