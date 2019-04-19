#ifndef CRYPTO
#define CRYPTO

std::string sign(std::string secret_key, std::string sms);
int verify_sign(std::string sig, std::string sms, std::string pk);


#endif
