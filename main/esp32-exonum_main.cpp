#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "Arduino.h"
#include "WiFi.h"
#include "mbedtls/md.h"
#include <iostream>
#include "HTTPClient.h"
#include <vector>
#include <sstream>
#include <iomanip>
#include "src/massage.cpp"
#include "src/massage.h"
#include "src/convert.h"
#include <EEPROM.h>
#include <string>


#define SIZE_PK 64
#define SIZE_SIGN 128
#define MESSAGE_FROM 128
#define MESSAGE_LENGTH 256


using namespace std;

const char* ssid = "MikroTik-6D25EC";
const char* password = "Mult1Pa$5";
//const char* ssid = "uuu";
//const char* password = "12345678";
//const char* ssid = "TP-LINK_BB26";
//const char* password = "88145372";

const uint16_t port = 5001;
//const uint16_t port0 = 5079;
//const uint16_t port1 = 5088;
//const uint16_t port2 = 5111;
//const uint16_t port3 = 5112;

//const char* host0 = "46.241.87.38";
const char* host0 = "192.168.88.79";
const char* host1 = "192.168.88.112";
const char* host2 = "192.168.88.110";
const char* host3 = "192.168.88.111";


#include "src/crypto.cpp"
#include "src/crypto.h"


#include "src/short_device_key.pb.h"
#include "src/test.pb.h"
#include "src/pb_common.h"
#include "src/pb.h"
#include "src/pb_encode.h"
#include "src/pb_decode.h"
#include "src/convert.h"

struct data {
	char device_key_id[32];
	char authentication_key[32];
	char biometrical_key[128];
	int wearout;
	char application_data[128];
	char shedule[128];
};

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
	//unsigned char* buffer = hexadecimalToUint8Array(sms);

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
	Serial.println(ESP.getFreeHeap());
	string pk=message1.substr(0,SIZE_PK);
	string signature=message1.substr(message1.length()-128,SIZE_SIGN);
	string sms =message1.substr(MESSAGE_FROM, message1.length()-MESSAGE_LENGTH);
	int verify = verify_sign(signature, sms, pk);

		int s = decoder(sms);
		cout<<endl;
		//Serial.println(ESP.getFreeHeap());
		cout<<endl;
		return s;

}

string trans(string message_id, int count) {
	string public_key = "91fc61fc1ed1856da51725f530951917ab5301d1c1f72a88a86c2950cb8f44ff";
	string secret_key = "bad81c68022715969f73bd858f6e9e5b11bb7fb1d41b0a9158d9cfe5e00c0bc791fc61fc1ed1856da51725f530951917ab5301d1c1f72a88a86c2950cb8f44ff";
	string type = "00";
	string class1 = "00";
	string service_id = "0600";
	string message = encoder(count);
	string signature = sign(secret_key, public_key+type+class1+service_id+message_id+message);
	return "410Code" + public_key+type+class1+service_id+message_id+message+signature;
}

string registration(string ip) {
	string public_key = "91fc61fc1ed1856da51725f530951917ab5301d1c1f72a88a86c2950cb8f44ff";
	string secret_key = "bad81c68022715969f73bd858f6e9e5b11bb7fb1d41b0a9158d9cfe5e00c0bc791fc61fc1ed1856da51725f530951917ab5301d1c1f72a88a86c2950cb8f44ff";
	string signature = sign(secret_key, public_key+string_to_hex(ip));
	return "404Code" + public_key + string_to_hex(ip) + signature;
}

void vTaskSocketZero(void * pvParameters) {
	delay(10000);
	while (1) {
		WiFiClient client;
		if(client.connect(host0, port)) {
			int status;

			String ip = WiFi.localIP().toString();
			int len = ip.length() + 1;
			char char_array[len];
			ip.toCharArray(char_array, len);
			string str = string(char_array);
			string reg = registration(str);
			client.print(reg.c_str());
			delay(2000);
			{

				String line = client.readStringUntil('\n');
				Serial.println(line);
				len = line.length() + 1;
				char char_array[len];
				line.toCharArray(char_array, len);
				string str = string(char_array);
				status = atoi(str.c_str());

			}


			if (status == 1111111) {
				string sms1 = trans("0000", 1000000);
				client.print(sms1.c_str());
				cout<<"REGISTATION"<<endl;
			}
			else {
				string sms1 = trans("0100", status-1);
				client.print(sms1.c_str());
				cout<<"STATUS-1"<<endl;
			}

			while (client.connected() || client.available())
				{

					if (client.available()) {
						String line = client.readStringUntil('\n');
						int len = line.length() + 1;
						char char_array[len];
						line.toCharArray(char_array, len);
						string str = string(char_array);
						cout<<str<<endl;
						int p = read_from_node(str);
						string sms = trans("0100", p-1);
						client.print(sms.c_str());
					}
				}
			delay(500);
		}
		else {
			Serial.println("FAILED TO CONNECT");
			delay(10000);
		}
	}
}
void vTaskSocketOne(void * pvParameters) {
	delay(10000);
		while (1) {
			WiFiClient client;
			if(client.connect(host1, port)) {
				int status;

				String ip = WiFi.localIP().toString();
				int len = ip.length() + 1;
				char char_array[len];
				ip.toCharArray(char_array, len);
				string str = string(char_array);
				string reg = registration(str);
				client.print(reg.c_str());
				delay(2000);
				{

					String line = client.readStringUntil('\n');
					Serial.println(line);
					len = line.length() + 1;
					char char_array[len];
					line.toCharArray(char_array, len);
					string str = string(char_array);
					status = atoi(str.c_str());

				}


				if (status == 1111111) {
					string sms1 = trans("0000", 1000000);
					client.print(sms1.c_str());
					cout<<"REGISTATION"<<endl;
				}
				else {
					string sms1 = trans("0100", status-1);
					client.print(sms1.c_str());
					cout<<"STATUS-1"<<endl;
				}

				while (client.connected() || client.available())
					{

						if (client.available()) {
							String line = client.readStringUntil('\n');
							int len = line.length() + 1;
							char char_array[len];
							line.toCharArray(char_array, len);
							string str = string(char_array);
							cout<<str<<endl;
							int p = read_from_node(str);
							string sms = trans("0100", p-1);
							client.print(sms.c_str());
						}
					}
				delay(500);
			}
			else {
				Serial.println("FAILED TO CONNECT");
				delay(10000);
			}
		}
}
void vTaskSocketTwo(void * pvParameters) {
	delay(10000);
		while (1) {
			WiFiClient client;
			if(client.connect(host2, port)) {
				int status;

				String ip = WiFi.localIP().toString();
				int len = ip.length() + 1;
				char char_array[len];
				ip.toCharArray(char_array, len);
				string str = string(char_array);
				string reg = registration(str);
				client.print(reg.c_str());
				delay(2000);
				{

					String line = client.readStringUntil('\n');
					Serial.println(line);
					len = line.length() + 1;
					char char_array[len];
					line.toCharArray(char_array, len);
					string str = string(char_array);
					status = atoi(str.c_str());

				}


				if (status == 1111111) {
					string sms1 = trans("0000", 1000000);
					client.print(sms1.c_str());
					cout<<"REGISTATION"<<endl;
				}
				else {
					string sms1 = trans("0100", status-1);
					client.print(sms1.c_str());
					cout<<"STATUS-1"<<endl;
				}

				while (client.connected() || client.available())
					{

						if (client.available()) {
							String line = client.readStringUntil('\n');
							int len = line.length() + 1;
							char char_array[len];
							line.toCharArray(char_array, len);
							string str = string(char_array);
							cout<<str<<endl;
							int p = read_from_node(str);
							string sms = trans("0100", p-1);
							client.print(sms.c_str());
						}
					}
				delay(500);
			}
			else {
				Serial.println("FAILED TO CONNECT");
				delay(10000);
			}
		}
}
void vTaskSocketThree(void * pvParameters) {
	delay(10000);
		while (1) {
			WiFiClient client;
			if(client.connect(host3, port)) {
				int status;

				String ip = WiFi.localIP().toString();
				int len = ip.length() + 1;
				char char_array[len];
				ip.toCharArray(char_array, len);
				string str = string(char_array);
				string reg = registration(str);
				client.print(reg.c_str());
				delay(2000);
				{

					String line = client.readStringUntil('\n');
					Serial.println(line);
					len = line.length() + 1;
					char char_array[len];
					line.toCharArray(char_array, len);
					string str = string(char_array);
					status = atoi(str.c_str());

				}


				if (status == 1111111) {
					string sms1 = trans("0000", 1000000);
					client.print(sms1.c_str());
					cout<<"REGISTATION"<<endl;
				}
				else {
					string sms1 = trans("0100", status-1);
					client.print(sms1.c_str());
					cout<<"STATUS-1"<<endl;
				}

				while (client.connected() || client.available())
					{

						if (client.available()) {
							cout<<"Socket_send"<<endl;
							String line = client.readStringUntil('\n');
							int len = line.length() + 1;
							char char_array[len];
							line.toCharArray(char_array, len);
							string str = string(char_array);
							cout<<str<<endl;
							int p = read_from_node(str);
							string sms = trans("0100", p-1);
							client.print(sms.c_str());
						}
					}
				delay(500);
			}
			else {
				Serial.println("FAILED TO CONNECT");
				delay(10000);
			}
		}
}

extern "C" void app_main()
{
	initArduino();
	Serial.begin(115200);
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.println("Can't connect");
		delay(1000);
	}
	Serial.print("WiFi connected with IP: ");
	  Serial.println(WiFi.localIP());

	//xTaskCreate(vTaskSocketZero, "vTaskSocketZero", 8024, NULL , 1, NULL );
	xTaskCreate(vTaskSocketOne, "vTaskSocketOne", 8024, NULL , 1, NULL );
	xTaskCreate(vTaskSocketTwo, "vTaskSocketTwo", 8024, NULL , 1, NULL );
	xTaskCreate(vTaskSocketThree, "vTaskSocketThree", 8024, NULL , 1, NULL );

}




