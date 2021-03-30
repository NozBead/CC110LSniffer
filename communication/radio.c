#include "radio.h"

void setread(unsigned char *header) {
	*header |= RWMSK;
}

void setwrite(unsigned char *header) {
	*header &= ~RWMSK;
}

int isread(const unsigned char *header) {
	return *header & RWMSK;
}

void setburst(unsigned char *header) {
	*header |= BRSTMSK;
}

void setnoburst(unsigned char *header) {
	*header &= ~BRSTMSK;
}

int isburst(const unsigned char *header) {
	return *header & BRSTMSK;
}

unsigned char getaddr(const unsigned char *header) {
	return *header & ADDRMSK;
}

void setaddr(unsigned char *header, unsigned char addr) {
	*header &= ~ADDRMSK;
	*header |= addr & ADDRMSK;
}

int iscmd(const unsigned char *header) {
	unsigned char addr = getaddr(header);
	return !isburst(header) && (addr >= RESADDR && addr <= NOPADDR);
}

int isstatusreg(const unsigned char *header) {
	unsigned char addr = getaddr(header);
	return isburst(header) && (addr >= RESADDR && addr <= NOPADDR);
}

char *cmdstr(char *dest, unsigned char addr) {
	char *tmp;
	switch (addr) {
		case RESADDR : tmp = "Reset chip"; break;
		case FRXADDR : tmp = "Flush RX"; break;
		case FTXADDR : tmp = "Flush TX"; break;
		case NOPADDR : tmp = "Noop"; break;
		case IDLEADDR : tmp = "Go idle"; break;
		case RXADDR : tmp = "Enable RX"; break;
		case TXADDR : tmp = "Enable TX"; break;
		default : tmp = "Unknown op";
	}
	sprintf(dest, "%s", tmp);
	return dest;
}

char *addrstr(char *dest, unsigned char addr) {
	char *tmp;
	switch (addr) {
		case FIFOADDR : tmp = "FIFO"; break;
		case PATADDR : tmp = "PATABLE"; break;
		default : tmp = "CONFIG REG";	
	}
	sprintf(dest, "%s", tmp);
	return dest;
}

void printheader(const unsigned char *header) {
	int read = isread(header);
	unsigned char addr = getaddr(header);

	if (iscmd(header)) {
		char cmd[16];
		cmdstr(cmd, addr);
		printf("%s (%x)\n", cmd, addr);
	}
	else if(isstatusreg(header)) {
		printf("Reading status register (%x)\n", addr);
	}
	else {
		char dest[16];
		addrstr(dest, addr);
		printf("%s with%s burst %s %s (%x)\n",
			read ? "Reading" : "Writting",
			isburst(header) ? "" : "out",
			read ? "from" : "to",
			dest,
			addr);
	}
}
