#include <gtest/gtest.h>
#include "../include/can_frame.h"

// 1. Nominal Test: Valid Standard CAN Frame
TEST(CANFrameTest, ValidStandardFramePasses) {
    can_frame_t frame = {};
    frame.id = 0x123;
    frame.dlc = 4;
    frame.is_extended = false;
    frame.payload[0] = 0xDE;
    frame.payload[1] = 0xAD;
    frame.payload[2] = 0xBE;
    frame.payload[3] = 0xEF;
    frame.crc = can_compute_crc(frame.payload, frame.dlc);

    EXPECT_EQ(can_validate_frame(&frame), CAN_OK);
}

// 2. Boundary Test: Max DLC (8 bytes) & Extended ID
TEST(CANFrameTest, MaxDLCAndExtendedIDPasses) {
    can_frame_t frame = {};
    frame.id = 0x18FEF600; // Example J1939 PGN ID
    frame.dlc = 8;
    frame.is_extended = true;
    for (int i = 0; i < 8; i++) frame.payload[i] = (uint8_t)i;
    frame.crc = can_compute_crc(frame.payload, frame.dlc);

    EXPECT_EQ(can_validate_frame(&frame), CAN_OK);
}

// 3. Fault Injection Test: DLC Overflow (> 8)
TEST(CANFrameTest, InvalidDLCReturnsError) {
    can_frame_t frame = {};
    frame.id = 0x100;
    frame.dlc = 9; // Fault: DLC exceeds maximum of 8
    frame.is_extended = false;
    frame.crc = 0x1234;

    EXPECT_EQ(can_validate_frame(&frame), CAN_ERR_INVALID_DLC);
}

// 4. Fault Injection Test: Corrupted CRC
TEST(CANFrameTest, CorruptedCRCReturnsError) {
    can_frame_t frame = {};
    frame.id = 0x123;
    frame.dlc = 2;
    frame.is_extended = false;
    frame.payload[0] = 0xAA;
    frame.payload[1] = 0xBB;
    
    // Intentionally assign bad CRC (Fault Injection)
    frame.crc = 0xDEAD; 

    EXPECT_EQ(can_validate_frame(&frame), CAN_ERR_CRC_MISMATCH);
}

// 5. Fault Injection Test: Null Pointer Safety Check
TEST(CANFrameTest, NullPointerReturnsError) {
    EXPECT_EQ(can_validate_frame(NULL), CAN_ERR_NULL_PTR);
}