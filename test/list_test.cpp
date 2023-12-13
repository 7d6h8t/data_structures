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

      EXPECT_NE(lst1_.size(), 0);
      EXPECT_FALSE(lst1_.empty());
    }

    TEST_F(listTest, ClearWorks)
    {
      lst0_.clear();
      EXPECT_EQ(lst0_.size(), 0);
      EXPECT_TRUE(lst0_.empty());

      lst2_.clear();
      EXPECT_EQ(lst2_.size(), 0);
      EXPECT_TRUE(lst2_.empty());
    }

    TEST_F(listTest, PushWorks)
    {
      lst0_.push_back(0);
      lst0_.push_back(1);
      lst0_.push_back(2);
      lst0_.push_back(3);
      lst0_.push_back(4);
      EXPECT_EQ(lst0_.size(), 5);

      lst1_.push_front(10);
      lst1_.push_front(11);
      lst1_.push_front(12);
      EXPECT_EQ(lst1_.size(), 7);

      lst2_.push_front(11);
      lst2_.push_front(10);
      lst2_.push_back(5);
      lst2_.push_back(6);
      EXPECT_EQ(lst2_.size(), 9);
      EXPECT_EQ(*(++lst2_.begin()), 11);
      EXPECT_EQ(lst2_.front(), 10);
      EXPECT_EQ(lst2_.back(), 6);

      lst3_.push_back("hello");
      lst3_.push_back("world");
      lst3_.push_back("!");
      EXPECT_EQ(lst3_.size(), 3);
      EXPECT_EQ(*(--lst3_.end()), "!");
    }

    TEST_F(listTest, PopWorks)
    {
      lst1_.pop_front();
      lst1_.pop_back();
      EXPECT_EQ(lst1_.size(), 2);
      EXPECT_EQ(lst1_.back(), 2);

      lst2_.pop_back();
      lst2_.pop_back();
      lst2_.pop_back();
      EXPECT_EQ(lst2_.size(), 2);
      EXPECT_EQ(lst2_.back(), 1);
    }

    TEST_F(listTest, InsertWorks)
    {
      lst2_.insert(lst2_.end(), 5);
      for (auto itr = lst2_.begin(); itr != lst2_.end(); ++itr) {
        if (*itr == 1) {
          lst2_.insert(itr, 10);
          break;
        }
      }
      EXPECT_EQ(lst2_.size(), 7);
      EXPECT_EQ(lst2_.front(), 0);
      EXPECT_EQ(*(++lst2_.begin()), 10);
    }

    TEST_F(listTest, EraseWorks)
    {
      lst1_.erase(lst1_.begin());
      for (auto itr = lst1_.begin(); itr != lst1_.end();) {
        if (*itr % 2 == 0)
          itr = lst1_.erase(itr);
        else
          ++itr;
      }

      EXPECT_EQ(lst1_.size(), 2);
      EXPECT_EQ(lst1_.back(), 3);
      EXPECT_EQ(*(++lst1_.begin()), 3);
    }

  } // namespace
} // namespace ds