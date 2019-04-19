#ifndef _TRANSPORT_H
#define _TRANSPORT_H

#include <string>
#include "convert.h"
#include "crypto.h"
#include "pb_common.h"
#include "pb_decode.h"
#include "pb_encode.h"
#include "pb.h"
#include "sha256.h"
#include "short_device_key.pb.h"
#include "tweetnacl.h"

using namespace std;

int decoder(string sms);
string encoder(int count);
int read_from_node(std::string message1);
string trans(string message_id, int count);
string registration(string ip);

#endif //_TRANSPORT_H
