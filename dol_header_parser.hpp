#pragma once
#include <stdint.h>
#define DOL_HEADER_SIZE 0x100
#define TEXT_SECTION_SIZE 0x7
#define DATA_SECTION_SIZE 0xB

using namespace std;

struct SectionOffset {
    uint32_t m_text_offset[TEXT_SECTION_SIZE];
    uint32_t m_data_offset[DATA_SECTION_SIZE];
};

struct SectionAddress {
    uint32_t m_text_address[TEXT_SECTION_SIZE];
    uint32_t m_data_address[DATA_SECTION_SIZE];
};

struct SectionLength {
    uint32_t m_text_length[TEXT_SECTION_SIZE];
    uint32_t m_data_length[DATA_SECTION_SIZE];
};

class CDolHeader {
   public:
    SectionOffset m_section_offsets;
    SectionAddress m_section_addresses;
    SectionLength m_section_lengths;
    uint32_t m_bss_address;
    uint32_t m_bss_length;
    uint32_t m_entry_point;
    uint8_t m_padding[0x1C];

    void SwapEndian(uint32_t& val);
    void SwapEndian();
    void Parse(char* filePath);
    void Parse(void* buffer);
};