#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include "convert.h"
#include "convert.cpp"
#include <fstream>
#include <stdexcept>
#include "crypto.h"
#include "sha256.cpp"
#include "sha256.h"
#include "tweetnacl.h"
#include "tweetnacl.c"


using namespace std;


//////Подписать сообщение//////////
string sign(string secret_key, string sms) {
	unsigned char* smschar = (unsigned char*)malloc(sms.length()/2);
	unsigned char* sk = (unsigned char*)malloc(secret_key.length()/2);
	unsigned char sm[128];
	hexadecimalToUint8Array(sms, smschar);
	hexadecimalToUint8Array(secret_key, sk);
	crypto_sign(sm, smschar, sms.length()/2, sk);
	unsigned char signature[64];
	for(int i = 0; i<64; i++){
		signature[i]=sm[i];
	}
	string signa = uint8ArrayToHexadecimal(signature, 64);
	free(smschar);
	free(sk);
	return signa;
}

////////////Проверить подпись//////////

int verify_sign(string signature, string message, string public_key) {
	unsigned char s[64+message.length()/2];
	unsigned char sm[64+message.length()/2];

	unsigned char* sms = (unsigned char*)malloc(message.length()/2);
	unsigned char* pk = (unsigned char*)malloc(public_key.length()/2);
	unsigned char* sign = (unsigned char*)malloc(signature.length()/2);

	hexadecimalToUint8Array(message,sms);
	hexadecimalToUint8Array(public_key,pk);
	hexadecimalToUint8Array(signature, sign);
	for(int i =0; i<64; i++) {
		sm[i] = sign[i];
	}
	for(int i = 0; i < message.length()/2; i++) {
			sm[64 + i] = sms[i];
	}
	int ver = crypto_sign_open(s,sm,64+message.length()/2,pk);
	free(sms); free(pk); free(sign);
	return ver;
}

////////Получить публичный и секретный ключи////////
////////В качестве параметром передать два буфера куда записать публичный и приватный клюси////////////////
/*
int keyPair(unsigned char *pk, unsigned char *sk) {
	crypto_sign_keypair(pk, sk);
	return 0;
}*/


////////Получить SHA256 HASH. Сообщения в формате hex/////////
/*
string hash(string data) {
	//SHA256 sha256;
	string myHash  = sha256(data);
	return myHash;
}*/

/*

//////Подписать сообщение//////////
string sign(string secret_key, string sms) {
	unsigned char* buffer = (unsigned char*)malloc(sms.length()/2);
	unsigned char sm[128];
	unsigned char* smschar = hexadecimalToUint8Array(sms);
	unsigned char* sk = hexadecimalToUint8Array(secret_key);
	crypto_sign(sm, smschar, sms.length()/2, sk);
	unsigned char signature[64];
	for(int i = 0; i<64; i++){
		signature[i]=sm[i];
	}
	string signa = uint8ArrayToHexadecimal(signature, 64);
	return signa;
}

////////////Проверить подпись//////////

int verify_sign(string signature, string message, string public_key) {
	unsigned char s[64+message.length()/2];
	unsigned char sm[64+message.length()/2];
	unsigned char* sms = hexadecimalToUint8Array(message);
	unsigned char* pk = hexadecimalToUint8Array(public_key);
	unsigned char* sign = hexadecimalToUint8Array(signature);
	for(int i =0; i<64; i++) {
		sm[i] = sign[i];
	}
	for(int i = 0; i < message.length()/2; i++) {
			sm[64 + i] = sms[i];
	}
	return crypto_sign_open(s,sm,64+message.length()/2,pk);
}*/

