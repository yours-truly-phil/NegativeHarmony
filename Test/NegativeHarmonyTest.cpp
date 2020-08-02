//
// Created by phili on 05/06/2020.
//

#include "gtest/gtest.h"
#include "../Source/NegativeHarmony.h"

class NegativeHarmonyTest : public ::testing::Test
{
protected:
    NegativeHarmonyTest() = default;
    ~NegativeHarmonyTest() override = default;
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(NegativeHarmonyTest, negHarmCalcChecks_allows_in_midi_range_valid_keys)
{
    ASSERT_TRUE(NegativeHarmony::negHarmCalcChecks(0, 0, 127, 12));
    ASSERT_TRUE(NegativeHarmony::negHarmCalcChecks(1, 24, 127, 12));
    ASSERT_TRUE(NegativeHarmony::negHarmCalcChecks(11, 0, 127, 12));
}
TEST_F(NegativeHarmonyTest, negHarmCalcChecks_forbids_implausible_keys)
{
    ASSERT_FALSE(NegativeHarmony::negHarmCalcChecks(-1, 0, 127, 12));
    ASSERT_FALSE(NegativeHarmony::negHarmCalcChecks(12, 0, 127, 12));
    ASSERT_TRUE(NegativeHarmony::negHarmCalcChecks(23, 0, 127, 24));
    ASSERT_FALSE(NegativeHarmony::negHarmCalcChecks(24, 0, 127, 24));
}
TEST_F(NegativeHarmonyTest, negHarmCalcChecks_available_notes_le_one_octave)
{
    ASSERT_TRUE(NegativeHarmony::negHarmCalcChecks(0, 0, 11, 12));
    ASSERT_FALSE(NegativeHarmony::negHarmCalcChecks(0, 0, 10, 12));
}

TEST_F(NegativeHarmonyTest, calculate_in_88_piano_range_C4_all_keys)
{
    ASSERT_EQ(49, NegativeHarmony::calculate(60, 3, 21, 108, 12));
    ASSERT_EQ(51, NegativeHarmony::calculate(60, 4, 21, 108, 12));
    ASSERT_EQ(53, NegativeHarmony::calculate(60, 5, 21, 108, 12));
    ASSERT_EQ(55, NegativeHarmony::calculate(60, 6, 21, 108, 12));
    ASSERT_EQ(57, NegativeHarmony::calculate(60, 7, 21, 108, 12));
    ASSERT_EQ(59, NegativeHarmony::calculate(60, 8, 21, 108, 12));
    ASSERT_EQ(61, NegativeHarmony::calculate(60, 9, 21, 108, 12));
    ASSERT_EQ(63, NegativeHarmony::calculate(60, 10, 21, 108, 12));
    ASSERT_EQ(65, NegativeHarmony::calculate(60, 11, 21, 108, 12));
    ASSERT_EQ(67, NegativeHarmony::calculate(60, 0, 21, 108, 12));
    ASSERT_EQ(69, NegativeHarmony::calculate(60, 1, 21, 108, 12));
    ASSERT_EQ(71, NegativeHarmony::calculate(60, 2, 21, 108, 12));
}
TEST_F(NegativeHarmonyTest, calculate_result_move_into_range)
{
    ASSERT_EQ(7 + 2 * 12, NegativeHarmony::calculate(0, 0.0f, 21.0f, 108.0f, 12.0f));
    ASSERT_EQ(31 - 1 * 12, NegativeHarmony::calculate(24, 0.0f, 0.0f, 23.0f, 12.0f));
}
