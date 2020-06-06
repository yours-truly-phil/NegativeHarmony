//
// Created by phili on 05/06/2020.
//

#include "gtest/gtest.h"
#include "../Source/NegativeHarmony.h"

class NegativeHarmonyTest : public ::testing::Test
{
protected:
    NegativeHarmonyTest() {}
    ~NegativeHarmonyTest() override {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(NegativeHarmonyTest, Key_of_C)
{
    int negHarmNn = NegativeHarmony::calculate(0, 0.0f, 0.0f, 127.0f, 12.0f);

    EXPECT_EQ(negHarmNn, 7);
}
