#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <array>

// напишите эту функцию
inline bool DecodeRLE(const std::string& src_name, const std::string& dst_name) {
    std::ifstream in(src_name, std::ios::binary);
    if (!in) {
        return false;
    }
    std::ofstream out(dst_name, std::ios::binary);
    
    while (1) {
        int c  = in.get();
        if (c == std::istream::traits_type::eof() || !in) {
            return true;
        }
		unsigned char header = c;
        int block_type = (header & 1);
		int data_size = (header >> 1) + 1;
        if (!block_type) {
            char buffer[10240];
            in.read(buffer, data_size);
            out.write(buffer, data_size);
        } else {
            char buffer[10240];
            int element = in.get();
            for (int i = 0; i < data_size; i++) {
                buffer[i] = element;
            }
            out.write(buffer, data_size);
        }
    }
    
    in.close();
    out.close();
    return true;
}
