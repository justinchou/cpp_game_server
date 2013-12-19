#include <string.h>
#include "../include/pushNotification.h"

#define DEVICE_BINARY_SIZE 32

using namespace std;

int main(int argc,char *argv[])
{
	char nType[] = "";

	char DeviceToken[] = "47d555b9569370be8e5fbfed980fc084b86fcd75b40ce6d8c27b749653217726";

	char sDeviceToken[DEVICE_BINARY_SIZE+1];

	char PayLoadBuff[] = "{\"aps\":{\"alert\":\"This is justinchou's fancy message.\",\"badge\":1}}";
	int PayLoadLen = strlen(PayLoadBuff);

	char MessageBuff[MESSAGE_BUFF_LEN];

	SSL_init();

	memset(sDeviceToken,0,DEVICE_BINARY_SIZE+1);
	Hex2Chr(sDeviceToken,DeviceToken,strlen(DeviceToken));

	int MessageLen = CreateMessage(MessageBuff,sDeviceToken,PayLoadBuff,PayLoadLen);
	ConnectSSL(nType,"520086631",MessageBuff,MessageLen);

	return 0;
}
