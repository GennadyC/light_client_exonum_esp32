#ifndef CRYPTO
#define CRYPTO

std::string sign(std::string secret_key, std::string sms);
int verify_sign(std::string sig, std::string sms, std::string pk);

//std::string hash(std::string data);
//int keyPair(unsigned char *pk, unsigned char *sk);


#endif
