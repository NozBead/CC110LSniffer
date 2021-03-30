#include "../communication/radio.h"
#include <stdio.h>

unsigned twobytesint(const unsigned char *bigendian) {
	return (bigendian[0] << 8) | bigendian[1];
}

int isdataend(const unsigned *value) {
	return *value == 0xFF00;
}

int snifferloop(FILE *sniffer) {
	unsigned char isdata;
	unsigned value;
	unsigned char buffer[2];

	while (1) {
		if (fread(buffer, 1, 2, sniffer) == 0) {
			perror("Error reading sniffer");
			return -1;
		}
	
		value = twobytesint(buffer);
		if (isdataend(&value)) {
			printf("\n");
			isdata = 0;
		}
		else if (isdata){
			printf("%x ", value & 0xFF);
		}
		else {
			unsigned char header = value;
			isdata = !iscmd(&header);
			printheader(&header);
		}
	}
}

int main(int argc, char **argv) {
	if (argc != 2) {
		return 1;
	}

	FILE *spisniffer = fopen(argv[1], "r");
	if (spisniffer == NULL) {
		perror(argv[1]);
		return 2;
	}

	return snifferloop(spisniffer);
}
