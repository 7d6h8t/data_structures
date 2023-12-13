#include "list.h"
#include <gtest/gtest.h>
#include <string>

namespace ds {
  namespace {

    class listTest : public testing::Test {
    protected:
      void SetUp() override
      {
        lst1_.push_back(0);
        lst1_.push_back(1);
        lst1_.push_back(2);
        lst1_.push_back(3);
      }

      // void TearDown() override {}

      list<int32_t> lst0_;
      list<int32_t> lst1_;
      list<int32_t> lst2_{0, 1, 2, 3, 4};
      list<std::string> lst3_;
    }; // listTest

    TEST_F(listTest, IsEmptyInitially)
    {
      EXPECT_EQ(lst0_.size(), 0);
      EXPECT_TRUE(lst0_.empty());

      lst0_.push_back(1);

      EXPECT_NE(lst0_.size(), 0);
      EXPECT_FALSE(lst0_.empty());

      lst0_.clear();

      EXPECT_EQ(lst0_.size(), 0);
      EXPECT_TRUE(lst0_.empty());

      EXPECT_NE(lst1_.size(), 0);
      EXPECT_FALSE(lst1_.empty());
    }

    TEST_F(listTest, PushWorks)
    {
      lst0_.push_back(0);
      lst0_.push_back(1);
      lst0_.push_back(2);
      lst0_.push_back(3);
      lst0_.push_back(4);

      EXPECT_EQ(lst0_.size(), 5);
    }

  } // namespace
} // namespace ds