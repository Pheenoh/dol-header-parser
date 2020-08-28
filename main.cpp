#include <fstream>
#include <iostream>

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

    void SwapEndian(uint32_t& val) {
        val = (val << 24) | ((val << 8) & 0x00ff0000) |
              ((val >> 8) & 0x0000ff00) | (val >> 24);
    }
    void SwapEndian() {
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
};

int main(int argc, char* argv[]) {

    fstream fh;
    CDolHeader header;
#define DEBUG 0

    if (DEBUG) {
        argv[1] = (char *)"boot.dol";
        argc = 2;
    }

    if ( argc == 2) {
    fh.open(argv[1], ifstream::in | ifstream::binary);
    } else {
        cout << "Usage: dhp.exe <your.dol>\n";
        return 1;
    }
    if (!fh) {
        cout << "Cannot open file.\n";
        return 1;
    }

    fh.read((char*)&header, DOL_HEADER_SIZE);
    fh.close();
    
    header.SwapEndian();

    for (int i = 0; i < TEXT_SECTION_SIZE; i++) {
        if (header.m_section_offsets.m_text_offset[i] != 0x0) {
            printf(".text%d\n",i);
            printf(" offset: 0x%02X",header.m_section_offsets.m_text_offset[i]);
            printf(" address: 0x%02X",header.m_section_addresses.m_text_address[i]);
            printf(" length: 0x%02X\n",header.m_section_lengths.m_text_length[i]);
        }
    }

    for (int i = 0; i < DATA_SECTION_SIZE; i++) {
        if (header.m_section_offsets.m_data_offset[i] != 0x0) {
            printf(".data%d\n",i);
            printf(" offset: 0x%02X",header.m_section_offsets.m_data_offset[i]);
            printf(" address: 0x%02X",header.m_section_addresses.m_data_address[i]);
            printf(" length: 0x%02X\n",header.m_section_lengths.m_data_length[i]);
        }
    }

    printf(".bss\n");
    printf(" address: %02X", header.m_bss_address);
    printf(" length: %02X\n", header.m_bss_length);
    printf("entry point: %02X\n", header.m_entry_point);

    return 0;
}