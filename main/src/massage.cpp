#include "short_device_key.pb.h"
#include "short_device_key.pb.c"
#include "test.pb.h"
#include "test.pb.c"
#include "pb_common.h"
#include "pb_common.c"
#include "pb.h"
#include "pb_encode.h"
#include "pb_encode.c"
#include "pb_decode.h"
#include "pb_decode.c"
#include <iostream>
//#include "convert.h"
//#include "crypto.h"
//#include "crypto.cpp"
#include <stdio.h>
#include "mbedtls/md.h"
#include "massage.h"
#include "convert.h"
//#include "convert.cpp"



/*
protocol_encode::protocol_encode(char* device_key_id, char* authentication_key, char* biometrical_key, int wearout, char* application_data, char* shedule){
	cout<<wearout<<endl;

	BlockchainCore_ShortDeviceKey message = BlockchainCore_ShortDeviceKey_init_zero;
	pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));

	strcpy(message.device_key_id.mm, device_key_id);
	strcpy(message.authentication_key, authentication_key);
	strcpy(message.biometrical_key, biometrical_key);
	message.wearout = wearout;
	strcpy(message.application_data, application_data);
	strcpy(message.shedule, shedule);


	bool status = pb_encode(&stream, BlockchainCore_ShortDeviceKey_fields, &message);
	if (!status)
	{
	    Serial.println("Failed to encode");
	}
	n = stream.bytes_written;
}*/

protocol_encode::protocol_encode(int count){

	Testing message = Testing_init_zero;
	pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
	message.wearout_count = count;
	//strcpy(message.a, msg.c_str());


	bool status = pb_encode(&stream, Testing_fields, &message);
	if (!status)
	{
	    Serial.println("Failed to encode");
	}
	n = stream.bytes_written;
}
protocol_encode::~protocol_encode(){}


protocol_decode::protocol_decode(std::string sms){
	 int dlina = sms.length()/2;
	 unsigned char* buffer = hexadecimalToUint8Array(sms);

	 BlockchainCore_ShortDeviceKey message = BlockchainCore_ShortDeviceKey_init_zero;
	 pb_istream_t stream = pb_istream_from_buffer(buffer, dlina);


	 bool status = pb_decode(&stream, BlockchainCore_ShortDeviceKey_fields, &message);
	 if (!status)
	 {
	     Serial.println("Failed to decode");
	 }
	 //cout<<message.wearout<<endl;

	 strcpy(device_key_id, message.device_key_id.mm);
	 strcpy(authentication_key, message.authentication_key);
	 strcpy(biometrical_key, message.biometrical_key);
	 wearout = message.wearout;
	 strcpy(application_data, message.application_data);
	 strcpy(shedule, message.shedule);
	 //cout<<wearout<<endl;

	 //char device_key_id = message.device_key_id;
	 //char authentication_key = message.authentication_key;
	 //char biometrical_key = message.biometrical_key;
	 //char application_data = message.application_data;
	 //char shedule = message.shedule;

}
protocol_decode::~protocol_decode(){}



















