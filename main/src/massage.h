#ifndef MESSAGE
#define MESSAGE
class protocol_encode
{
public:
	uint8_t buffer[128];
	int n;
	std::string mess;
	//protocol_encode(char* device_key_id, char* authentication_key, char* biometrical_key, int wearout, char* application_data, char* shedule);
	protocol_encode(/*std::string msg*/ int count);
	~protocol_encode();
};
class protocol_decode
{
public:
	uint8_t buf[1024];
	int k;
	std::string m;
	protocol_decode(std::string sms);
	~protocol_decode();
	char device_key_id[32];
	char authentication_key[32];
	char biometrical_key[128];
	int wearout;
	char application_data[128];
	char shedule[128];


};

#endif
