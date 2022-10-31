/**
 * @file GruffSpartyTest.cpp
 * @author Will Morant
 */

#include <pch.h>
#include <GruffSparty.h>
#include <Level.h>
#include "gtest/gtest.h"



TEST(GruffSpartyTest, Construct)
{
    GruffSparty gruff(nullptr);

}

TEST(GruffSpartyTest, BasePosition)
{
    GruffSparty Gruff(nullptr);

    ASSERT_EQ(0, Gruff.GetX());
    ASSERT_EQ(0, Gruff.GetY());
}
