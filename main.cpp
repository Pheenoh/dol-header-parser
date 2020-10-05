#include <iostream>
#include "dol_header_parser.hpp"

int main(int argc, char* argv[]) {
    CDolHeader header;

#define DEBUG 0

    if (DEBUG) {
        argv[1] = (char*)"boot.dol";
        argc = 2;
    }

    if (argc == 2) {
        header.Parse(argv[1]);
    } else {
        cout << "Usage: dhp.exe <your.dol>\n";
        return 1;
    }

    for (int i = 0; i < TEXT_SECTION_SIZE; i++) {
        if (header.m_section_offsets.m_text_offset[i] != 0x0) {
            printf(".text%d\n", i);
            printf(" offset: 0x%02X", header.m_section_offsets.m_text_offset[i]);
            printf(" address: 0x%02X", header.m_section_addresses.m_text_address[i]);
            printf(" length: 0x%02X\n", header.m_section_lengths.m_text_length[i]);
        }
    }

    for (int i = 0; i < DATA_SECTION_SIZE; i++) {
        if (header.m_section_offsets.m_data_offset[i] != 0x0) {
            printf(".data%d\n", i);
            printf(" offset: 0x%02X", header.m_section_offsets.m_data_offset[i]);
            printf(" address: 0x%02X", header.m_section_addresses.m_data_address[i]);
            printf(" length: 0x%02X\n", header.m_section_lengths.m_data_length[i]);
        }
    }

    printf(".bss\n");
    printf(" address: %02X", header.m_bss_address);
    printf(" length: %02X\n", header.m_bss_length);
    printf("entry point: %02X\n", header.m_entry_point);

    return 0;
}