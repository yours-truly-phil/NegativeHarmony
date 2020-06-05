//
// Created by phili on 05/06/2020.
//

#include "gtest/gtest.h"
#include "../Source/MidiProcessor.h"

class MidiProcessorFixture : public ::testing::Test {
 protected:
  virtual void SetUp() {
    midi_processor_ = new MidiProcessor();
  }
  virtual void TearDown() {
    delete midi_processor_;
  }

  MidiProcessor *midi_processor_;
};

TEST_F(MidiProcessorFixture, SomeTest) {
  int negHarmNn = midi_processor_->getNegHarmNn(0, 0);

  EXPECT_EQ(negHarmNn, 7);
}