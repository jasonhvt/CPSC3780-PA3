#include "ExtendedHeader.h"
#include "gtest/gtest.h"

#define TEST_BUFFER_SIZE 12

class ExtendedHeaderTest : public testing::Test {
protected:
    ExtendedHeader * h_;
    uint8_t * buffer_;

    void SetUp() override {
    h_ = new ExtendedHeader;  // create a new class before each test to start fresh
    buffer_ = new uint8_t[TEST_BUFFER_SIZE]; // allocate a buffer to test
    memset(buffer_, 0, TEST_BUFFER_SIZE);  // initialize the buffer with zeros
    h_->setBuffer(buffer_, TEST_BUFFER_SIZE);  // set the buffer for the class
  }

  void TearDown() override {
    delete h_;
    delete [] buffer_;
  }

};

// Test setType and getType
TEST_F(ExtendedHeaderTest, setType) {
    h_->setType(2);  // Set Type to 2 (should occupy bits 0–1)
    ASSERT_EQ(buffer_[0] & 0x03, 2);  // Check that the first 2 bits are set to 2
}

TEST_F(ExtendedHeaderTest, getType) {
    buffer_[0] = 0x03;  // Set the first 2 bits to 3
    ASSERT_EQ(h_->getType(), 3);  // Get Type should return 3
}

// Test setWindow and getWindow
TEST_F(ExtendedHeaderTest, setWindow) {
    h_->setWindow(15);  // Set Window to 15 (should occupy bits 3–7)
    ASSERT_EQ((buffer_[0] & 0xF8) >> 3, 15);  // Check that bits 3–7 are set to 15
}

TEST_F(ExtendedHeaderTest, getWindow) {
    buffer_[0] = 0x78;  // Set bits 3–7 to 15 (0b01111)
    ASSERT_EQ(h_->getWindow(), 15);  // Get Window should return 15
}

// Test setSeqNum and getSeqNum
TEST_F(ExtendedHeaderTest, setSeqNum) {
    h_->setSeqNum(255);  // Set Sequence Number to 255 (full byte)
    ASSERT_EQ(buffer_[1], 255);  // Check that byte 1 is set to 255
}

TEST_F(ExtendedHeaderTest, getSeqNum) {
    buffer_[1] = 0xAB;  // Set Sequence Number to 171 (0xAB)
    ASSERT_EQ(h_->getSeqNum(), 171);  // Get Sequence Number should return 171
}

// Test setLength and getLength
TEST_F(ExtendedHeaderTest, setLength) {
    h_->setLength(128);  // Set Length to 128 (full byte)
    ASSERT_EQ(buffer_[2], 128);  // Check that byte 2 is set to 128
}

TEST_F(ExtendedHeaderTest, getLength) {
    buffer_[2] = 0x7F;  // Set Length to 127 (0x7F)
    ASSERT_EQ(h_->getLength(), 127);  // Get Length should return 127
}

// Test setCRC1 and getCRC1
TEST_F(ExtendedHeaderTest, setCRC1) {
    h_->setCRC1(0xDEADBEEF);  // Set CRC1 to 0xDEADBEEF
    ASSERT_EQ(buffer_[7], 0xDE);  // Check most significant byte
    ASSERT_EQ(buffer_[8], 0xAD);
    ASSERT_EQ(buffer_[9], 0xBE);
    ASSERT_EQ(buffer_[10], 0xEF);  // Check least significant byte
}

TEST_F(ExtendedHeaderTest, getCRC1) {
    buffer_[7] = 0x12;
    buffer_[8] = 0x34;
    buffer_[9] = 0x56;
    buffer_[10] = 0x78;
    ASSERT_EQ(h_->getCRC1(), 0x12345678);  // Get CRC1 should return 0x12345678
}