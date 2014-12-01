#include <node.h>
#include <v8.h>
#include "modbus-core.h"

using namespace v8;

unsigned short crcCalc(unsigned char *buf, unsigned short length) /* The function returns the CRC as a unsigned short type */
{
	unsigned char CRCHi = 0xFF; /* high byte of CRC initialized */
	unsigned char CRCLo = 0xFF; /* low byte of CRC initialized */
	unsigned uIndex; /* will index into CRC lookup table */
	while (length--) /* pass through message buffer */
	{
		uIndex = CRCLo ^ *buf++; /* calculate the CRC */
		CRCLo = CRCHi ^ tableCRCHi[uIndex];
		CRCHi = tableCRCLo[uIndex];
	}
	return (CRCHi << 8 | CRCLo);
}

bool crcCheck(char message[]){
	char* buf = new char[sizeof message - 2];
	memcpy(buf, message, sizeof message - 2);
	unsigned short crc = crcCalc((unsigned char*)buf, sizeof message - 2);
	unsigned short mcrc = (unsigned char)message[sizeof message - 1] << 8 | (unsigned char)message[sizeof message - 2];
	return  crc == mcrc;
};

void init(Handle<Object> exports) {

}

NODE_MODULE(nodbus, init)