#include "ExtendedHeader.h"

// Constructor
ExtendedHeader::ExtendedHeader() : packet(nullptr), size(0) {}

void ExtendedHeader::setBuffer(void * buf, int sz) {
  packet = static_cast<uint8_t*> (buf);
  size = sz;
}

// Setter and Getter for Type (2 bits)
void ExtendedHeader::setType(uint8_t type) {
    if (packet != nullptr && size >= NEW_HEADER_SZ) {
        packet[TYPE_OFFSET] = (packet[TYPE_OFFSET] & ~0x03) | (type & 0x03);  // Set first 2 bits
    }
}

uint8_t ExtendedHeader::getType() const {
    if (packet != nullptr && size >= NEW_HEADER_SZ) {
        return packet[TYPE_OFFSET] & 0x03;  // Extract first 2 bits
    }
    return 0;
}

// Setter and Getter for Window (5 bits)
void ExtendedHeader::setWindow(uint8_t window) {
    if (packet != nullptr && size >= NEW_HEADER_SZ) {
        packet[WINDOW_OFFSET] = (packet[WINDOW_OFFSET] & ~0xF8) | ((window & 0x1F) << 3);  // Set bits 3–7
    }
}

uint8_t ExtendedHeader::getWindow() const {
    if (packet != nullptr && size >= NEW_HEADER_SZ) {
        return (packet[WINDOW_OFFSET] >> 3) & 0x1F;  // Extract bits 3–7
    }
    return 0;
}

// Setter and Getter for Sequence Number (8 bits)
void ExtendedHeader::setSeqNum(uint8_t seqNum) {
    if (packet != nullptr && size >= NEW_HEADER_SZ) {
        packet[SEQ_NUM_OFFSET] = seqNum;  // Set byte 1
    }
}

uint8_t ExtendedHeader::getSeqNum() const {
    if (packet != nullptr && size >= NEW_HEADER_SZ) {
        return packet[SEQ_NUM_OFFSET];  // Get byte 1
    }
    return 0;
}

// Setter and Getter for Length (8 bits)
void ExtendedHeader::setLength(uint8_t length) {
    if (packet != nullptr && size >= NEW_HEADER_SZ) {
        packet[LENGTH_OFFSET] = length;  // Set byte 2
    }
}

uint8_t ExtendedHeader::getLength() const {
    if (packet != nullptr && size >= NEW_HEADER_SZ) {
        return packet[LENGTH_OFFSET];  // Get byte 2
    }
    return 0;
}

// Setter and Getter for CRC1 (32 bits)
void ExtendedHeader::setCRC1(uint32_t crc1) {
    if (packet != nullptr && size >= NEW_HEADER_SZ) {
        packet[CRC1_OFFSET] = (crc1 >> 24) & 0xFF;
        packet[CRC1_OFFSET + 1] = (crc1 >> 16) & 0xFF;
        packet[CRC1_OFFSET + 2] = (crc1 >> 8) & 0xFF;
        packet[CRC1_OFFSET + 3] = crc1 & 0xFF;
    }
}

uint32_t ExtendedHeader::getCRC1() const {
    if (packet != nullptr && size >= NEW_HEADER_SZ) {
        return (packet[CRC1_OFFSET] << 24) |
               (packet[CRC1_OFFSET + 1] << 16) |
               (packet[CRC1_OFFSET + 2] << 8) |
               packet[CRC1_OFFSET + 3];
    }
    return 0;
}