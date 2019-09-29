#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

// gpio
#include <bcm2835.h>

// lcd
#include "nokia5110.h"

// ip address
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>

// uptime
#include <sys/sysinfo.h>

// LCD pins
#define LCD_PIN_BL    21
#define LCD_PIN_SCE   8
#define LCD_PIN_RESET 24
#define LCD_PIN_DC    23
#define LCD_PIN_SDIN  10
#define LCD_PIN_SCLK  11

void getIfAddress(char* ifname, char* result) {
	int fd;
	struct ifreq ifr;

	// open soket
	fd = socket(AF_INET, SOCK_DGRAM, 0);
	// get an IPv4 IP address
	ifr.ifr_addr.sa_family = AF_INET;
	// get IP address attached to ifname: ex. "eth0" or "wlx0013efcb0cbc"
        strncpy(ifr.ifr_name, ifname, IFNAMSIZ-1);
	ioctl(fd, SIOCGIFADDR, &ifr);
	close(fd);
	// convert to human readable
	sprintf(result, "%s", inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
	// debug
	//printf("%s %s\n", ifname, result);
}

int main() {

	char lcdOutString1[24];
        char lcdOutString2[24];
        char lcdOutString3[24];
        //char lcdOutString4[24];
        //char lcdOutString5[24];
        char lcdOutString6[24];

	// uptime
	struct sysinfo info;
        int uptimeDays = 0;
        int uptimeHours = 0;
        int uptimeMins = 0;
        int uptimeSecs = 0;

	// GPIO init
	if(!bcm2835_init()) {
		printf("BCM2835 Init Error\n");
		return 1;
	}

	//
	// LCD
	//

	// set the nokia 5110 lcd pins on bcm2835
	lcdCreate(LCD_PIN_RESET, LCD_PIN_SCE, LCD_PIN_DC, LCD_PIN_SDIN, LCD_PIN_SCLK, LCD_PIN_BL);

	// start the lcd
        lcdInit();

  	// blink display
        //lcdBackLight (0);
        //bcm2835_delay(1000);
        //lcdBackLight (1);

        while(1) {
		// get the ip addresses
                getIfAddress("eth0", lcdOutString2);
		getIfAddress("wlx0013efcb0cbc", lcdOutString3);

		// get uptime (from system info)
		// we can also get the load
		sysinfo(&info);

		// convert to human standart
		uptimeMins = info.uptime / 60;
		uptimeSecs = info.uptime - uptimeMins * 60;

		uptimeHours = uptimeMins / 60;
		uptimeMins = uptimeMins - uptimeHours * 60;

                uptimeDays = uptimeHours / 24;
                uptimeHours = uptimeHours - uptimeDays * 24;

		// debug
		//printf("Uptime = %ld %d %02d:%02d:%02d\n", info.uptime, uptimeDays, uptimeHours, uptimeMins, uptimeSecs);

		// display on lcd
                lcdClear();

		sprintf(lcdOutString1, "IP & uptime ");
                lcdGotoXY(0,0);
                lcdString(lcdOutString1);

                lcdGotoXY(0,1);
                lcdString(lcdOutString2);

                lcdGotoXY(0,3);
                lcdString(lcdOutString3);

                //sprintf(string4,"line 4");
                //lcdGotoXY(0,4);
                //lcdString(lcdOutString);

                lcdGotoXY(0,5);
                sprintf(lcdOutString6,"%d %02d:%02d:%02d", uptimeDays, uptimeHours, uptimeMins, uptimeSecs);
                lcdString(lcdOutString6);

                bcm2835_delay(800);
          }
}
