#include "stack.h"
#include <gtest/gtest.h>

namespace ds {
  namespace {

    class stackTest : public testing::Test {
    protected:
      void SetUp() override
      {
        // stk0_ remains empty
        stk1_.push(1);
        stk2_.push(2);
        stk2_.push(3);
      }

      // void TearDown() override {}

      stack<int32_t> stk0_;
      stack<int32_t> stk1_;
      stack<int32_t> stk2_;
    }; // stackTest

    TEST_F(stackTest, IsEmptyInitially)
    {
      EXPECT_EQ(stk0_.size(), 0);
    }

    TEST_F(stackTest, PopWorks)
    {
      EXPECT_EQ(stk1_.top(), 1);

      stk1_.pop();
      EXPECT_EQ(stk1_.size(), 0);

      EXPECT_EQ(stk2_.top(), 3);

      stk2_.pop();
      EXPECT_EQ(stk2_.top(), 2);
    }

    TEST_F(stackTest, PushWorks)
    {
      stk0_.push(0);
      stk0_.push(1);
      stk0_.push(2);
      EXPECT_EQ(stk0_.top(), 2);
      EXPECT_EQ(stk0_.size(), 3);

      stk1_.push(2);
      EXPECT_EQ(stk1_.size(), 2);
      EXPECT_EQ(stk1_.top(), 2);
    }

  } // namespace
} // namespace ds
