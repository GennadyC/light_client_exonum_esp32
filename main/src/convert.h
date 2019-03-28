#ifndef CONVERT
#define CONVERT

//std::string uint8_to_hex_string(const uint8_t *v, const size_t s);

unsigned char* hexadecimalToUint8Array(const std::string& hex);

std::string uint8ArrayToHexadecimal(const unsigned char* vec/*std::vector<uint8_t> v*/, int dlina);
void freebuffer(unsigned char* buffer);
std::string string_to_hex(const std::string& input);
#endif
