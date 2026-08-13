#include "can_frame.h"

uint16_t can_compute_crc(const uint8_t *payload, uint8_t dlc) {
    if (!payload && dlc > 0) return 0;
    uint16_t crc = 0xFFFF;
    for (uint8_t i = 0; i < dlc; i++) {
        crc ^= ((uint16_t)payload[i] << 8);
        for (uint8_t bit = 0; bit < 8; bit++) {
            if (crc & 0x8000) {
                crc = (crc << 1) ^ 0x1021;
            } else {
                crc = (crc << 1);
            }
        }
    }
    return crc;
}

can_status_t can_validate_frame(const can_frame_t *frame) {
    if (!frame) {
        return CAN_ERR_NULL_PTR;
    }

    // DLC Boundary Check (0 to 8 bytes)
    if (frame->dlc > CAN_MAX_DLC) {
        return CAN_ERR_INVALID_DLC;
    }

    // CAN ID Bounds Check
    if (frame->is_extended) {
        if (frame->id > CAN_EXT_ID_MAX) return CAN_ERR_INVALID_ID;
    } else {
        if (frame->id > CAN_STD_ID_MAX) return CAN_ERR_INVALID_ID;
    }

    // CRC Verification
    uint16_t computed_crc = can_compute_crc(frame->payload, frame->dlc);
    if (frame->crc != computed_crc) {
        return CAN_ERR_CRC_MISMATCH;
    }

    return CAN_OK;
}