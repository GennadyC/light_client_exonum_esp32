#include "../inc/transport.h"

int decoder(string sms){
	char device_key_id[32];
	char authentication_key[32];
	char biometrical_key[128];
	int wearout;
	char application_data[128];
	char shedule[128];
	int dlina = sms.length()/2;
	unsigned char* buffer = (unsigned char*)malloc(sms.length()/2);
	hexadecimalToUint8Array(sms, buffer);
	BlockchainCore_ShortDeviceKey message = BlockchainCore_ShortDeviceKey_init_zero;
	pb_istream_t stream = pb_istream_from_buffer(buffer, dlina);


	bool status = pb_decode(&stream, BlockchainCore_ShortDeviceKey_fields, &message);
	if (!status)
	{
	    Serial.println("Failed to decode");
	}
	strcpy(device_key_id, message.device_key_id.mm);
	strcpy(authentication_key, message.authentication_key);
	strcpy(biometrical_key, message.biometrical_key);
	wearout = message.wearout;
	strcpy(application_data, message.application_data);
	strcpy(shedule, message.shedule);
	free(buffer);
	return wearout;
}

string encoder(int count) {
	uint8_t buffer[128];
	Testing message = Testing_init_zero;
	pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
	message.wearout_count = count;

	bool status = pb_encode(&stream, Testing_fields, &message);
	if (!status)
	{
	    Serial.println("Failed to encode");
	}
	int n = stream.bytes_written;
	string mess = uint8_to_hex_string(buffer,n);
	return mess;
}

int read_from_node(std::string message1) {
	//Serial.println(ESP.getFreeHeap());
	string pk=message1.substr(0,SIZE_PK);
	string signature=message1.substr(message1.length()-128,SIZE_SIGN);
	string sms =message1.substr(MESSAGE_FROM, message1.length()-MESSAGE_LENGTH);
	int verify = verify_sign(signature, sms, pk);
	int s = decoder(sms);
	return s;

}

string trans(string message_id, int count) {
	string public_key = "6b34ec6fff56a5489465b6e881cc7a2bf99400cac391bc3cf51eb80f04aa8d7a";
	string secret_key = "b51ebb40a4b8692c483b67bdcf501574dab98e218b20de6782585b179f6e187a6b34ec6fff56a5489465b6e881cc7a2bf99400cac391bc3cf51eb80f04aa8d7a";
	string type = "00";
	string class1 = "00";
	string service_id = "0600";
	string message = encoder(count);
	string signature = sign(secret_key, public_key+type+class1+service_id+message_id+message);
	return "410Code" + public_key+type+class1+service_id+message_id+message+signature;
}

string registration(string ip) {
	string public_key = "6b34ec6fff56a5489465b6e881cc7a2bf99400cac391bc3cf51eb80f04aa8d7a";
	string secret_key = "b51ebb40a4b8692c483b67bdcf501574dab98e218b20de6782585b179f6e187a6b34ec6fff56a5489465b6e881cc7a2bf99400cac391bc3cf51eb80f04aa8d7a";
	string signature = sign(secret_key, public_key+string_to_hex(ip));
	return "404Code" + public_key + string_to_hex(ip) + signature;
}
