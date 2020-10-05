#include <cstring>
#include <fstream>
#include <iostream>
#include "dol_header_parser.hpp"

void CDolHeader::SwapEndian(uint32_t& val) {
    val = (val << 24) | ((val << 8) & 0x00ff0000) |
          ((val >> 8) & 0x0000ff00) | (val >> 24);
}

void CDolHeader::SwapEndian() {
    for (int i = 0; i < TEXT_SECTION_SIZE; i++) {
        SwapEndian(this->m_section_offsets.m_text_offset[i]);
        SwapEndian(this->m_section_addresses.m_text_address[i]);
        SwapEndian(this->m_section_lengths.m_text_length[i]);
    }
    for (int i = 0; i < DATA_SECTION_SIZE; i++) {
        SwapEndian(this->m_section_offsets.m_data_offset[i]);
        SwapEndian(this->m_section_addresses.m_data_address[i]);
        SwapEndian(this->m_section_lengths.m_data_length[i]);
    }

    SwapEndian(this->m_bss_address);
    SwapEndian(this->m_bss_length);
    SwapEndian(this->m_entry_point);
}

void CDolHeader::Parse(char* filePath) {
    fstream fh;

    fh.open(filePath, ifstream::in | ifstream::binary);
    fh.read((char *)this, DOL_HEADER_SIZE);
    fh.close();
    this->SwapEndian();
}

void CDolHeader::Parse(void* buffer) {
    memcpy(this, buffer, sizeof(buffer));
    this->SwapEndian();
}