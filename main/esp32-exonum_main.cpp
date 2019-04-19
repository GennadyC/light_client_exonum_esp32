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
#include <EEPROM.h>
#include <string>
#include "esp_system.h"
#include "inc/crypto.h"
#include "inc/convert.h"
#include "inc/short_device_key.pb.h"
#include "inc/test.pb.h"
#include "inc/pb_common.h"
#include "inc/pb.h"
#include "inc/pb_encode.h"
#include "inc/pb_decode.h"
#include "inc/transport.h"

#define SIZE_PK 64
#define SIZE_SIGN 128
#define MESSAGE_FROM 128
#define MESSAGE_LENGTH 256
const char* ssid = "MikroTik-6D25EC";
const char* password = "Mult1Pa$5";
const uint16_t port = 5001;
const char* host0 = "192.168.88.79";
const char* host1 = "192.168.88.112";
const char* host2 = "192.168.88.110";
const char* host3 = "192.168.88.111";

using namespace std;







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
				cout<<status<<endl;

				if (status == 1111111) {
					string sms1 = trans("0000", 1000000);
					client.print(sms1.c_str());
					cout<<"REGISTATION"<<endl;
					cout<<sms1<<endl;
				}
				else {
					string sms1 = trans("0100", status-1);
					client.print(sms1.c_str());
					cout<<"STATUS-1"<<endl;
					cout<<sms1<<endl;
				}

				while (client.connected() || client.available())
					{

						if (client.available()) {
							String line = client.readStringUntil('\n');
							unsigned long time = millis(); ///Время прочтения сообщения
							int len = line.length() + 1;
							char char_array[len];
							line.toCharArray(char_array, len);
							string str = string(char_array);
							cout<<"Mass from node task1: ";
							cout<<str<<endl;
							int p = read_from_node(str);
							cout<<"Wearout from node task1: ";
							cout<<p<<endl;
							string sms = trans("0100", p-1);
							cout<<"Message to node task1: ";
							cout<<sms<<endl;
							client.print(sms.c_str());
							Serial.print("\n: ");  ////Время отправки сообщения
							Serial.println(millis()-time);
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

				cout<<status<<endl;

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
							cout<<"Mass from node task2: ";
							cout<<str<<endl;
							int p = read_from_node(str);
							cout<<"Wearout from node task2: ";
							cout<<p<<endl;
							string sms = trans("0100", p-1);
							cout<<"Message to node task2: ";
							cout<<sms<<endl;
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

				cout<<status<<endl;

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
							cout<<"Mass from node task3: ";
							cout<<str<<endl;
							int p = read_from_node(str);
							cout<<"Wearout from node task3: ";
							cout<<p<<endl;
							string sms = trans("0100", p-1);
							cout<<"Message to node task3: ";
							cout<<sms<<endl;
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




