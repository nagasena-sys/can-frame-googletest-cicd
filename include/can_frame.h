#ifndef CAN_FRAME_H
#define CAN_FRAME_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define CAN_MAX_DLC 8
#define CAN_STD_ID_MAX 0x7FF
#define CAN_EXT_ID_MAX 0x1FFFFFFF

typedef enum {
    CAN_OK = 0,
    CAN_ERR_NULL_PTR = -1,
    CAN_ERR_INVALID_DLC = -2,
    CAN_ERR_INVALID_ID = -3,
    CAN_ERR_CRC_MISMATCH = -4
} can_status_t;

typedef struct {
    uint32_t id;
    uint8_t dlc;
    uint8_t payload[CAN_MAX_DLC];
    bool is_extended;
    uint16_t crc;
} can_frame_t;

#ifdef __cplusplus
extern "C" {
#endif

// Function Declarations
uint16_t can_compute_crc(const uint8_t *payload, uint8_t dlc);
can_status_t can_validate_frame(const can_frame_t *frame);

#ifdef __cplusplus
}
#endif

#endif // CAN_FRAME_H