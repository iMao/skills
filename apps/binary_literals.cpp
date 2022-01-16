/**
 * C++14 feature: binary literals 0b00110000 or 0B00110000
 */

#include <iostream>

int main() {
  int value = 0x00F18112;  // 0b0000'0000'1111'0001'1000'0001'0001'0010
  uint8_t binary_mask_0 = 0b0001'0010;
  uint8_t binary_mask_1 = 0b1000'0001;
  uint8_t binary_mask_2 = 0b1111'0001;

  if (value & binary_mask_0) {
    std::cout << "0 byte: " << std::hex
              << static_cast<unsigned int>(binary_mask_0) << std::endl;
  }

  if (value & (binary_mask_1 << 8)) {
    std::cout << "1 byte: " << std::hex << (binary_mask_1 << 8) << std::endl;
  }

  if (value & (binary_mask_2 << 16)) {
    std::cout << "2 byte: " << std::hex << (binary_mask_2 << 16) << std::endl;
  }

  return 0;
}
