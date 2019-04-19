#ifndef CONVERT
#define CONVERT
#include <string>


void hexadecimalToUint8Array(const std::string& hex, unsigned char * bytes);
std::string uint8_to_hex_string(const uint8_t *v, const size_t s);
std::string string_to_hex(const std::string& input);

#endif
