#ifndef EXTENDEDHEADER_H
#define EXTENDEDHEADER_H

#include <cstdint>

// Maximum payload size for the packet 
#define NEW_DATA_SZ 512
// Header size (12 bytes = 96 bits)
#define NEW_HEADER_SZ 12

class ExtendedHeader {
private:
    uint8_t *packet;
    int size;

    // Field offsets based on the header layout
    const int TYPE_OFFSET = 0;   // First byte, bits 0-1
    const int WINDOW_OFFSET = 0; // First byte, bits 3-7
    const int SEQ_NUM_OFFSET = 1; // Second byte
    const int LENGTH_OFFSET = 2;  // Third byte
    const int CRC1_OFFSET = 7;    // CRC1 starts at byte 7

public:
    // Constructor
    ExtendedHeader();

    // Set External Buffer
    void setBuffer(void *buf, int sz);

    // Type (2 bits)
    void setType(uint8_t type);
    uint8_t getType() const;

    // Window (5 bits)
    void setWindow(uint8_t window);
    uint8_t getWindow() const;

    // Sequence Number (8 bits)
    void setSeqNum(uint8_t seqNum);
    uint8_t getSeqNum() const;

    // Length (8 bits)
    void setLength(uint8_t length);
    uint8_t getLength() const;

    // CRC1 (32 bits)
    void setCRC1(uint32_t crc1);
    uint32_t getCRC1() const;

    // Return the buffer size (header + payload)
    unsigned int getBufferSize() const;

    // Return a pointer to the payload
    void *getPayloadAddress();
};

#endif