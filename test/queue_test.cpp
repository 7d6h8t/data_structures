#include "queue.h"
#include <gtest/gtest.h>

namespace ds {
  namespace {

    class queueTest : public testing::Test {
    protected:
      void SetUp() override
      {
        // q0_ remains empty
        q1_.push(1);
        q2_.push(2);
        q2_.push(3);
      }

      // void TearDown() override {}

      queue<int32_t> q0_;
      queue<int32_t> q1_;
      queue<int32_t> q2_;
    }; // queueTest

    TEST_F(queueTest, IsEmptyInitially)
    {
      EXPECT_EQ(q0_.size(), 0);
    }

    TEST_F(queueTest, PopWorks)
    {
      EXPECT_EQ(q1_.front(), 1);

      q1_.pop();
      EXPECT_EQ(q1_.size(), 0);

      EXPECT_EQ(q2_.front(), 2);

      q2_.pop();
      EXPECT_EQ(q2_.front(), 3);
    }

    TEST_F(queueTest, PushWorks)
    {
      q0_.push(0);
      q0_.push(1);
      q0_.push(2);
      EXPECT_EQ(q0_.front(), 0);
      EXPECT_EQ(q0_.back(), 2);
      EXPECT_EQ(q0_.size(), 3);

      q1_.push(2);
      EXPECT_EQ(q1_.size(), 2);
      EXPECT_EQ(q1_.front(), 1);
      EXPECT_EQ(q1_.back(), 2);
    }

  } // namespace
} // namespace ds
