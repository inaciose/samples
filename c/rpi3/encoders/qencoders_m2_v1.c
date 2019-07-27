//
//  qe.c
//  hidtest
//
//  Created by Albin Stigö on 09/09/2017.
//  Copyright © 2017 Albin Stigo. All rights reserved.
//
//  License BSD
//  https://opensource.org/licenses/BSD-2-Clause


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <wiringPi.h>

#define ERPIN1 28
#define ERPIN2 29

#define ELPIN1 25
#define ELPIN2 27

volatile long elpos;
volatile uint8_t elstate;

volatile long erpos;
volatile uint8_t erstate;

// Inspired by Paul Stoffregen's excellent Arduino library Encoder:
// https://github.com/PaulStoffregen/Encoder
void elpin_isr(void) {
    uint8_t p1val = digitalRead(ELPIN1);
    uint8_t p2val = digitalRead(ELPIN2);
    uint8_t s = elstate & 3;
    if (p1val) s |= 4;
    if (p2val) s |= 8;
    elstate = (s >> 2);

    switch (s) {
        case 1: case 7: case 8: case 14:
            elpos++;
            return;
        case 2: case 4: case 11: case 13:
            elpos--;
            return;
        case 3: case 12:
            elpos += 2;
            return;
        case 6: case 9:
            elpos -= 2;
            return;
    }
}

void erpin_isr(void) {
    uint8_t p1val = digitalRead(ERPIN1);
    uint8_t p2val = digitalRead(ERPIN2);
    uint8_t s = erstate & 3;
    if (p1val) s |= 4;
    if (p2val) s |= 8;
    erstate = (s >> 2);

    switch (s) {
        case 1: case 7: case 8: case 14:
            erpos--;
            return;
        case 2: case 4: case 11: case 13:
            erpos++;
            return;
        case 3: case 12:
            erpos -= 2;
            return;
        case 6: case 9:
            erpos += 2;
            return;
    }
}


int main(int argc, const char * argv[]) {

    // sets up the wiringPi library
    if (wiringPiSetup() < 0) {
        perror("wiringPiSetup");
        exit(EXIT_FAILURE);
    }

    pinMode (ELPIN1,  INPUT) ;
    printf("EL PIN1 DONE\n");
    pinMode (ELPIN2,  INPUT) ;
    printf("EL PIN2 DONE\n");

    pinMode (ERPIN1,  INPUT) ;
    printf("ER PIN1 DONE\n");
    pinMode (ERPIN2,  INPUT) ;
    printf("ER PIN2 DONE\n");

    pullUpDnControl(ELPIN1, PUD_UP);
    pullUpDnControl(ELPIN2, PUD_UP);

    pullUpDnControl(ERPIN1, PUD_UP);
    pullUpDnControl(ERPIN2, PUD_UP);

    if ( wiringPiISR (ELPIN1, INT_EDGE_BOTH, &elpin_isr) < 0 ) {
        perror("wiringPiISR");
        exit(EXIT_FAILURE);
    }

    if ( wiringPiISR (ELPIN2, INT_EDGE_BOTH, &elpin_isr) < 0 ) {
        perror("wiringPiISR");
        exit(EXIT_FAILURE);
    }

    if ( wiringPiISR (ERPIN1, INT_EDGE_BOTH, &erpin_isr) < 0 ) {
        perror("wiringPiISR");
        exit(EXIT_FAILURE);
    }

    if ( wiringPiISR (ERPIN2, INT_EDGE_BOTH, &erpin_isr) < 0 ) {
        perror("wiringPiISR");
        exit(EXIT_FAILURE);
    }


    // Show position every second
    while ( 1 ) {
        printf( "%ld\t%ld\n", elpos, erpos);
        delay( 1000 ); // wait 1 second
    }

    return 0;
}
