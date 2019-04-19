#include <string>
#include <vector>
#include <iostream>
#include <math.h>
#include <sstream>
#include <cstring> 
#include "../inc/convert.h"
#include <stdint.h>
#include <sstream>
#include <iomanip>
#include <errno.h>
#include <cstdlib>
using namespace std;

void hexadecimalToUint8Array(const string& hex, unsigned char * bytes) {
  int k = 0;
  for (unsigned int i = 0; i < hex.length(); i += 2) {
    string byteString = hex.substr(i, 2);
    uint8_t byte = (uint8_t) strtol(byteString.c_str(), NULL, 16);
    bytes[k] = byte;
    k+=1;
  }
}

string uint8_to_hex_string(const uint8_t *v, const size_t s) {
  stringstream ss;

  ss << hex << setfill('0');

  for (int i = 0; i < s; i++) {
    ss << hex << setw(2) << static_cast<int>(v[i]);
  }

  return ss.str();
}

/*
string hexadecimalToBinaryString(string hex) {
	string byte;
	int len = hex.length();
	for(int i = 0; i < len; i ++)
	{
		switch(hex[i])
		{
			case '0': byte+="0000"; break;
			case '1': byte+="0001"; break;
			case '2': byte+="0010"; break;
			case '3': byte+="0011"; break;
			case '4': byte+="0100"; break;
			case '5': byte+="0101"; break;
			case '6': byte+="0110"; break;
			case '7': byte+="0111"; break;
			case '8': byte+="1000"; break;
			case '9': byte+="1001"; break;
			case 'a': byte+="1010"; break;
			case 'b': byte+="1011"; break;
			case 'c': byte+="1100"; break;
			case 'd': byte+="1101"; break;
			case 'e': byte+="1110"; break;
			case 'f': byte+="1111"; break;
		}
	}
	return byte;
}*/


/*
string uint8ArrayToBinaryString(vector<uint8_t> vec) {
	return hexadecimalToBinaryString(uint8ArrayToHexadecimal(vec));
}

string BinaryStringTohexadecimal(string byte) {
	string hex;
	int len = byte.length();
	for(int i = 0; i < len/4; i ++)
	{
		string p = byte.substr(4*i, 4);
			if(p == "0000") hex+='0';
			else if(p == "0001") hex+='1'; 
			else if(p == "0010") hex+='2';
			else if(p == "0011") hex+='3';
			else if(p == "0100") hex+='4';
			else if(p == "0101") hex+='5';
			else if(p == "0110") hex+='6';
			else if(p == "0111") hex+='7';
			else if(p == "1000") hex+='8';
			else if(p == "1001") hex+='9';
			else if(p == "1010") hex+='a';
			else if(p == "1011") hex+='b';
			else if(p == "1100") hex+='c';
			else if(p == "1101") hex+='d';
			else if(p == "1110") hex+='e';
			else if(p == "1111") hex+='f';
	}
	return hex;
}

vector<uint8_t> binaryStringToUint8Array(string binary) {
	string hex = BinaryStringTohexadecimal(binary);
	vector<uint8_t> uint8array = hexadecimalToUint8Array(hex);
	return uint8array;
}
*/
/*
vector<uint8_t> stringToUint8Array(string msg) {
	vector<uint8_t> v;
	for (int i = 0; i < msg.length(); i ++ ) {
		v.push_back(int(msg[i]));
	}
	return v;
}*/

string string_to_hex(const string& input)
{
    static const char* const lut = "0123456789abcdef";
    size_t len = input.length();

    string output;
    output.reserve(2 * len);
    for (size_t i = 0; i < len; ++i)
    {
        const unsigned char c = input[i];
        output.push_back(lut[c >> 4]);
        output.push_back(lut[c & 15]);
    }

    return output;
}

